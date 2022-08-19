// PCbO: Parallel Close-by-One (AMAI Version; http://fcalgs.sourceforge.net/)
//
// Copyright (C) 2007-2009
// Petr Krajca, <petr.krajca@upol.cz>
// Jan Outrata, <jan.outrata@upol.cz>
// Vilem Vychodil, <vilem.vychodil@upol.cz>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// ===========================================================================
//
// Users in academia are kindly asked to cite the following resources if the
// program is used to pursue any research activities which may result in
// publications:
//
// Krajca P., Outrata J., Vychodil V.: Parallel Recursive Algorithm for FCA.
// In: Proc. CLA 2008, CEUR WS, 433(2008), 71-82. ISBN 978-80-244-2111-7.
// http://sunsite.informatik.rwth-aachen.de/Publications/CEUR-WS/Vol-433/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Configuration-dependent functions for mutexes and threads.
#ifdef WINNT
#   include <windows.h>
#   include <process.h>
typedef HANDLE thread_id_t;
typedef unsigned __stdcall thread_op_t;
const thread_op_t thread_nil = 0U;
typedef HANDLE mutex_t;
// #   define INIT_MUTEX
#   define init_mutex(M) ((M) = CreateMutex(NULL, FALSE, NULL));
#   define acquire_mutex(M) WaitForSingleObject((M), INFINITE)
#   define release_mutex(M) ReleaseMutex((M))
#   define init_thread(Th, Op, Arg) ((Th) = (HANDLE)_beginthreadex(NULL, 0, (Op), (Arg), 0, NULL))
#   define join_thread(Th) (WaitForSingleObject(Th, INFINITE), CloseHandle(Th))
#else
#   include <pthread.h>
typedef pthread_t thread_id_t;
typedef void *thread_op_t;
const thread_op_t thread_nil = NULL;
typedef pthread_mutex_t mutex_t;
// The distribution version initialized mutexes statically for non-Windows, instead of dynamically with pthread_mutex_init().
// #   define INIT_MUTEX = PTHREAD_MUTEX_INITIALIZER
#   define init_mutex(M) pthread_mutex_init(&(M), NULL)
#   define acquire_mutex(M) pthread_mutex_lock(&(M))
#   define release_mutex(M) pthread_mutex_unlock(&(M))
#   define init_thread(Th, Op, Arg) pthread_create(&(Th), NULL, (Op), (Arg))
#   define join_thread(Th) pthread_join(Th, NULL)
#endif

const unsigned long BitU = 1UL, NilU = 0UL;
const size_t IntSize = sizeof(int), LongSize = sizeof(unsigned long);
#define DATA_BITS	(8 * sizeof(unsigned long))
const size_t BufferBlock = 0x400;
#define MAX_DECIMAL_INT_SIZE (11)
#define OUTPUT_BUF_CAPACITY (32 * MAX_DECIMAL_INT_SIZE)
struct str_int {
   char str[MAX_DECIMAL_INT_SIZE];
   int length;
} *table_of_ints;
int attributes = 0;
int objects = 0;
int int_count_a = 0;
int int_count_o = 0;
int table_entries = 0;
int min_support = 0;
unsigned long *context;
unsigned long *(*cols)[DATA_BITS];
int (*supps)[DATA_BITS];
unsigned long upto_bit[DATA_BITS];
int attr_offset = 0;
FILE *in_file, *out_file;

int cpus = 1;
int threads;
int para_level = 2;
int verbosity_level = 1;
thread_id_t *thread_id;
int *thread_i;
unsigned char **thread_queue;
unsigned char **thread_queue_head;
unsigned char **thread_queue_limit;
unsigned long **thread_intents;
mutex_t output_lock/* INIT_MUTEX*/;
struct thread_stat {
   int closures;
   int computed;
   int queue_length;
};
struct thread_stat *counts;
struct thread_stat initial_thr_stat;

bool get_next_integer(FILE *file, int *value) {
   *value = -1;
   int ch = ' ';
   while (ch != EOF && !isdigit(ch)) {
      ch = fgetc(file);
      if (ch == '\n') return true;
   }
   if (ch == EOF) return false;
   *value = 0;
   while (isdigit(ch)) {
      *value *= 10;
      *value += ch - '0';
      ch = fgetc(file);
   }
   ungetc(ch, file);
   *value -= attr_offset;
   if (*value < 0) fprintf(stderr, "Invalid input value: %i (minimum value is %i), quitting.\n", *value + attr_offset, attr_offset), exit(EXIT_FAILURE);
   return true;
}

#define PUSH_NEW_INTEGER(__value) { \
   if (index >= buff_size) { \
      buff = realloc(buff, (buff_size += BufferBlock) * sizeof *buff); \
      if (buff == NULL) fprintf(stderr, "Cannot reallocate buffer, quitting.\n"), exit(EXIT_FAILURE); \
   } \
   buff[index++] = (__value); \
}

void table_of_ints_init(int max) {
   table_of_ints = malloc(max * sizeof *table_of_ints);
   for (int i = 0; i < max; i++) {
      sprintf(table_of_ints[i].str, "%i", i);
      table_of_ints[i].length = strlen(table_of_ints[i].str);
   }
}

void read_context(FILE *file) {
   size_t buff_size = BufferBlock;
   if (attr_offset < 0) attr_offset = 0;
   int *buff = malloc(buff_size * sizeof *buff);
   if (buff == NULL) fprintf(stderr, "Cannot allocate buffer, quitting.\n"), exit(EXIT_FAILURE);
   int last_value = -1, last_attribute = -1, last_object = -1;
   int index = 0;
   for (int value = 0; get_next_integer(file, &value); )
      if (value >= 0 || last_value >= 0) {
         if (value < 0) {
            last_object++;
            PUSH_NEW_INTEGER(-1);
         } else {
            if (value > last_attribute) last_attribute = value;
            PUSH_NEW_INTEGER(value);
            table_entries++;
         }
         last_value = value;
      }
   if (last_value >= 0) {
      last_object++;
      PUSH_NEW_INTEGER(-1);
   }
   objects = last_object + 1, int_count_o = objects / DATA_BITS + 1;
   attributes = last_attribute + 1, int_count_a = attributes / DATA_BITS + 1;
   context = calloc(int_count_a * objects, sizeof *context);
   if (context == NULL) fprintf(stderr, "Cannot allocate bitcontext, quitting.\n"), exit(EXIT_FAILURE);
   int row = 0;
   for (int i = 0; i < index; i++)
      if (buff[i] < 0)
         row++;
      else
         context[row * int_count_a + buff[i] / DATA_BITS] |= BitU << (DATA_BITS - 1 - buff[i] % DATA_BITS);
   free(buff);
}

void print_attributes(const unsigned long *set) {
   if (verbosity_level <= 0) return;
   bool first = true;
   char buf[OUTPUT_BUF_CAPACITY + MAX_DECIMAL_INT_SIZE + 2];
   int buf_ptr = 0;
   bool locked = false;
   for (int j = 0, c = 0; j < int_count_a; j++) for (int i = DATA_BITS - 1; i >= 0; i--) {
      if (set[j] & (BitU << i)) {
         if (!first) buf[buf_ptr++] = ' ';
         strcpy(buf + buf_ptr, table_of_ints[c].str);
         buf_ptr += table_of_ints[c].length;
         if (buf_ptr >= OUTPUT_BUF_CAPACITY) {
            buf[buf_ptr] = '\0';
            buf_ptr = 0;
            if (!locked) {
               acquire_mutex(output_lock);
               locked = true;
            }
            fputs(buf, out_file);
         }
         first = false;
      }
      if (++c >= attributes) goto out;
   }
out:
   buf[buf_ptr++] = '\n';
   buf[buf_ptr] = '\0';
   if (!locked) acquire_mutex(output_lock);
   fputs(buf, out_file);
   release_mutex(output_lock);
}

void print_context_info(void) {
   if (verbosity_level >= 2) fprintf(stderr, "(:objects %6i :attributes %4i :entries %8i)\n", objects, attributes, table_entries);
}

void print_thread_info(int id, struct thread_stat stat) {
   if (verbosity_level >= 2) fprintf(stderr, "(:proc %3i :closures %7i :computed %7i :queue-length %3i)\n", id, stat.closures, stat.computed, stat.queue_length);
}

void print_initial_thread_info(int levels, struct thread_stat stat, int last_level_concepts) {
   if (verbosity_level >= 2) fprintf(stderr, "(:proc %3i :closures %7i :computed %7i :levels %i :last-level-concepts %i)\n", 0, stat.closures, stat.computed, levels + 1, last_level_concepts);
}

void initialize_algorithm(void) {
   for (int i = 0; i < DATA_BITS; i++) {
      upto_bit[i] = NilU;
      for (int j = DATA_BITS - 1; j > i; j--) upto_bit[i] |= BitU << j;
   }
   unsigned long *cols_buff = calloc(int_count_o * DATA_BITS * int_count_a, sizeof *cols_buff);
   cols = malloc(DATA_BITS * int_count_a * sizeof *cols), supps = malloc(DATA_BITS * int_count_a * sizeof *supps);
   unsigned long *ptr = cols_buff;
   for (int j = 0; j < int_count_a; j++) for (int i = DATA_BITS - 1; i >= 0; ptr += int_count_o, i--) {
      unsigned long mask = BitU << i;
      cols[j][i] = ptr, supps[j][i] = 0;
      for (int x = 0, y = j; x < objects; x++, y += int_count_a)
         if (context[y] & mask) ptr[x / DATA_BITS] |= BitU << (x % DATA_BITS), supps[j][i]++;
   }
   table_of_ints_init(attributes);
}

void compute_closure(unsigned long *intent, unsigned long *extent, unsigned long *prev_extent, unsigned long *atr_extent, size_t *supp) {
   memset(intent, 0xff, int_count_a * sizeof *intent);
   if (atr_extent != NULL) {
      *supp = 0;
      for (int k = 0; k < int_count_o; k++) {
         extent[k] = prev_extent[k] & atr_extent[k];
         if (extent[k] != 0UL)
            for (int l = 0; l < DATA_BITS; l++)
               if (extent[k] & (BitU << l)) {
                  for (int i = 0, j = int_count_a * (k * DATA_BITS + l); i < int_count_a; i++, j++) intent[i] &= context[j];
                  ++*supp;
               }
      }
   } else {
      memset(extent, 0xff, int_count_o * sizeof *extent);
      for (int j = 0; j < objects; j++) for (int i = 0; i < int_count_a; i++) intent[i] &= context[int_count_a * j + i];
   }
}

void generate_from_node(unsigned long *intent, unsigned long *extent, int start_int, int start_bit, int id) {
   size_t supp = 0;
   unsigned long *new_intent = extent + int_count_o, *new_extent = new_intent + int_count_a;
   int total = (start_int + 1) * DATA_BITS - 1 - start_bit;
   for (; start_int < int_count_a; start_int++) {
      for (; start_bit >= 0; start_bit--) {
         if (total >= attributes) goto out;
         total++;
         if ((intent[start_int] & (BitU << start_bit)) || supps[start_int][start_bit] < min_support) continue;
         compute_closure(new_intent, new_extent, extent, cols[start_int][start_bit], &supp);
         counts[id].closures++;
         if ((new_intent[start_int] ^ intent[start_int]) & upto_bit[start_bit]) goto skip;
         for (int i = 0; i < start_int; i++)
            if (new_intent[i] ^ intent[i]) goto skip;
         if (supp < min_support) goto skip;
         counts[id].computed++;
         print_attributes(new_intent);
         if (new_intent[int_count_a - 1] & BitU) goto skip;
         if (start_bit == 0)
            generate_from_node(new_intent, new_extent, start_int + 1, DATA_BITS - 1, id);
         else
            generate_from_node(new_intent, new_extent, start_int, start_bit - 1, id);
      skip:
         ;
      }
      start_bit = DATA_BITS - 1;
   }
out: ;
}

thread_op_t thread_func(void *params) {
   for (int id = *(int *)params; thread_queue_head[id] < thread_queue[id]; ) {
      memcpy(thread_intents[id], thread_queue_head[id], (int_count_a + int_count_o) * sizeof *thread_intents[id]);
      thread_queue_head[id] += (int_count_a + int_count_o) * sizeof *thread_intents[id];
      generate_from_node(thread_intents[id], thread_intents[id] + int_count_a, *(int *)thread_queue_head[id], *(int *)(thread_queue_head[id] + IntSize), id);
      thread_queue_head[id] += IntSize << 1;
   }
   return thread_nil;
}

void parallel_generate_from_node(unsigned long *intent, unsigned long *extent, int start_int, int start_bit, int rec_level, int id) {
   static int num = 0;
   if (rec_level == para_level) {
      int i = num % threads;
      memcpy(thread_queue[i], intent, (int_count_a + int_count_o) * LongSize);
      thread_queue[i] += (int_count_a + int_count_o) * LongSize;
      *(int *)thread_queue[i] = start_int, thread_queue[i] += IntSize;
      *(int *)thread_queue[i] = start_bit, thread_queue[i] += IntSize;
      counts[i].queue_length++;
      if (thread_queue[i] == thread_queue_limit[i]) {
         int total = thread_queue_limit[i] - thread_queue_head[i];
         thread_queue_head[i] = realloc(thread_queue_head[i], total << 1);
         thread_queue[i] = thread_queue_head[i] + total;
         thread_queue_limit[i] = thread_queue_head[i] + (total << 1);
      }
      num++;
      return;
   }
   size_t supp = 0;
   unsigned long *new_intent = extent + int_count_o, *new_extent = new_intent + int_count_a;
   for (int total = (start_int + 1) * DATA_BITS - 1 - start_bit; start_int < int_count_a; start_int++) {
      for (; start_bit >= 0; start_bit--) {
         if (total++ >= attributes) goto out;
         if ((intent[start_int] & (BitU << start_bit)) || supps[start_int][start_bit] < min_support) continue;
         compute_closure(new_intent, new_extent, extent, cols[start_int][start_bit], &supp);
         counts[id].closures++;
         if ((new_intent[start_int] ^ intent[start_int]) & upto_bit[start_bit]) goto skip;
         for (int i = 0; i < start_int; i++)
            if (new_intent[i] ^ intent[i]) goto skip;
         if (supp < min_support) goto skip;
         counts[id].computed++;
         print_attributes(new_intent);
         if (new_intent[int_count_a - 1] & BitU) goto skip;
         if (start_bit == 0)
            parallel_generate_from_node(new_intent, new_extent, start_int + 1, DATA_BITS - 1, rec_level + 1, id);
         else
            parallel_generate_from_node(new_intent, new_extent, start_int, start_bit - 1, rec_level + 1, id);
      skip:
         ;
      }
      start_bit = DATA_BITS - 1;
   }
out:
   if (rec_level == 0) {
      print_initial_thread_info(para_level, counts[0], num);
      initial_thr_stat = counts[0];
      counts[0].closures = 0;
      counts[0].computed = 0;
      for (int i = 1; i < threads; i++)
         if (thread_queue_head[i] != thread_queue[i]) init_thread(thread_id[i], thread_func, &thread_i[i]);
      for (; thread_queue_head[id] < thread_queue[id]; ) {
         memcpy(thread_intents[id], thread_queue_head[id], (int_count_a + int_count_o) * sizeof *thread_intents[id]);
         thread_queue_head[id] += (int_count_a + int_count_o) * sizeof *thread_intents[id];
         generate_from_node(thread_intents[id], thread_intents[id] + int_count_a, *(int *)thread_queue_head[id], *(int *)(thread_queue_head[id] + IntSize), id);
         thread_queue_head[id] += IntSize << 1;
      }
   }
}

void find_all_intents(void) {
   if (para_level <= 0) para_level = 1;
   if (para_level > attributes) para_level = attributes;
   threads = cpus;
   if (threads <= 0) threads = 1;
   if (verbosity_level >= 3) fprintf(stderr, "INFO: running in %i threads\n", threads);
   counts = calloc(threads, sizeof *counts);
   thread_id = calloc(threads, sizeof *thread_id);
   thread_i = malloc(threads * sizeof *thread_i);
   thread_queue = malloc(threads * sizeof *thread_queue);
   thread_queue_head = malloc(threads * sizeof *thread_queue_head);
   thread_queue_limit = malloc(threads * sizeof *thread_queue_limit);
   thread_intents = malloc(threads * sizeof *thread_intents);
   int queue_size = attributes / threads + 1, attrs = attributes - para_level + 1;
   for (int i = 0; i < threads; i++) {
      thread_i[i] = i;
      thread_queue_head[i] = thread_queue[i] = malloc(((int_count_a + int_count_o) * sizeof *thread_intents[i] + (IntSize << 1)) * queue_size);
      thread_queue_limit[i] = thread_queue_head[i] + ((int_count_a + int_count_o) * sizeof *thread_intents[i] + (IntSize << 1)) * queue_size;
      thread_intents[i] = malloc((int_count_a + int_count_o) * attrs * sizeof *thread_intents[i]);
   }
   compute_closure(thread_intents[0], thread_intents[0] + int_count_a, NULL, NULL, NULL);
   counts[0].closures++, counts[0].computed++;
   print_attributes(thread_intents[0]);
   if (thread_intents[0][int_count_a - 1] & BitU) return;
   parallel_generate_from_node(thread_intents[0], thread_intents[0] + int_count_a, 0, DATA_BITS - 1, 0, 0);
   print_thread_info(1, counts[0]);
   for (int i = 1; i < threads; i++) {
      if (thread_id[i] != 0) join_thread(thread_id[i]);
      print_thread_info(i + 1, counts[i]);
      counts[0].closures += counts[i].closures, counts[0].computed += counts[i].computed;
   }
   counts[0].closures += initial_thr_stat.closures, counts[0].computed += initial_thr_stat.computed;
   if (verbosity_level >= 3)
      fprintf(stderr, "INFO: total %7i closures\n", counts[0].closures),
      fprintf(stderr, "INFO: total %7i concepts\n", counts[0].computed);
}

int main(int argc, char **argv) {
   in_file = stdin, out_file = stdout;
   if (argc > 1) {
      int index = 1;
      for (; index < argc && argv[index][0] == '-' && argv[index][1] != 0; index++) switch (argv[index][1]) {
         case 'h': fprintf(stderr, "synopsis: %s [-h] [-index] [-Smin-support] [-Vlevel] [-Pcpus] [-Lpara_level] [INPUT-FILE] [OUTPUT-FILE]\n", argv[0]); return EXIT_SUCCESS;
         case 'S': min_support = atoi(argv[index] + 2); break;
         case 'P': cpus = atoi(argv[index] + 2); break;
         case 'L': para_level = atoi(argv[index] + 2) - 1; break;
         case 'V': verbosity_level = atoi(argv[index] + 2); break;
         default: attr_offset = atoi(argv[index] + 1);
      }
      if (argc > index && argv[index][0] != '-') in_file = fopen(argv[index], "rb");
      if (argc > index + 1 && argv[index + 1][0] != '-') out_file = fopen(argv[index + 1], "wb");
   }
   if (in_file == NULL) { fprintf(stderr, "%s: cannot open input data stream\n", argv[0]); return EXIT_FAILURE; }
   if (out_file == NULL) { fprintf(stderr, "%s: open output data stream\n", argv[0]); return EXIT_FAILURE; }
   init_mutex(output_lock);
   read_context(in_file);
   fclose(in_file);
   print_context_info();
   initialize_algorithm();
   find_all_intents();
   fclose(out_file);
   return EXIT_SUCCESS;
}
