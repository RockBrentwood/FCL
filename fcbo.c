// FCbO: Fast Close-by-One (INS Version; http://fcalgs.sourceforge.net/)
//
// Copyright (C) 2007-2010
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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>

const unsigned long BitU = 1UL, NilU = 0UL;
#define DATA_BITS	(8 * sizeof(unsigned long))
const size_t BufferBlock = 0x400;

int attributes = 0;
int objects = 0;
int int_count_a = 0;
int int_count_o = 0;
int table_entries = 0;
int min_support = 0;
unsigned long *context;
unsigned long **cols;
int *supps;
int *attrib_numbers;
unsigned long upto_bit[DATA_BITS];
int attr_offset = 0;
FILE *in_file, *out_file;

int verbosity_level = 1;
struct stats_t {
   int total;
   int closures;
   int fail_canon;
   int fail_fcbo;
   int fail_support;
} stats = { 0, 0, 0, 0, 0 };

struct timeval time_start, time_inner, time_end;
int *buff = NULL;
int buff_index = 0;
size_t buff_size = BufferBlock;

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
   return true;
}

void allocate_buffer(int **buffer, int size) {
   *buffer = *buffer == NULL ? malloc(size * sizeof *buffer) : realloc(*buffer, size * sizeof *buffer);
   if (*buffer == NULL) fprintf(stderr, "Cannot reallocate buffer, quitting."), exit(EXIT_FAILURE);
}

#define PUSH_NEW_INTEGER(__value) { \
   if (buff_index >= buff_size) allocate_buffer(&buff, buff_size += BufferBlock); \
   buff[buff_index++] = (__value); \
}

void read_file(FILE *file) {
   allocate_buffer(&buff, buff_size);
   int last_value = -1, last_attribute = -1, last_object = -1;
   for (int value = 0; get_next_integer(file, &value); )
      if (value >= 0 || last_value >= 0) {
         if (value < 0) {
            last_object++;
            PUSH_NEW_INTEGER(-1);
         } else {
            if (value > last_attribute) last_attribute = value;
            PUSH_NEW_INTEGER(value);
         }
         last_value = value;
      }
   if (last_value >= 0) {
      last_object++;
      PUSH_NEW_INTEGER(-1);
   }
   objects = last_object + 1;
   attributes = last_attribute + 1;
}

void create_context(void) {
   int_count_a = attributes / DATA_BITS + 1, int_count_o = objects / DATA_BITS + 1;
   context = calloc(int_count_a * objects, sizeof *context);
   if (context == NULL) fprintf(stderr, "Cannot allocate bitcontext, quitting."), exit(EXIT_FAILURE);
   supps = calloc(attributes, sizeof *supps);
   for (int i = 0, row = 0; i < buff_index; i++)
      if (buff[i] < 0) row++;
      else {
         context[row * int_count_a + buff[i] / DATA_BITS] |= BitU << (DATA_BITS - 1 - buff[i] % DATA_BITS);
         supps[buff[i]]++;
         table_entries++;
      }
   if (verbosity_level >= 2) fprintf(stderr, "objects: %6i\nattributes: %4i\nentries: %8i\n", objects, attributes, table_entries);
}

void initialize_output(void) {
   attrib_numbers = malloc(attributes * sizeof *attrib_numbers);
   for (int i = 0; i < attributes; i++) attrib_numbers[i] = i;
}

void print_attributes(unsigned long *set, size_t supp) {
   if (verbosity_level <= 0) return;
   bool first = true;
   for (int j = 0, c = 0; j < int_count_a; j++) for (int i = DATA_BITS - 1; i >= 0; i--) {
      if (set[j] & (BitU << i)) {
         if (!first) fprintf(out_file, " ");
         fprintf(out_file, "%i", attrib_numbers[c]);
         first = false;
      }
      if (++c >= attributes) goto out;
   }
out:
   fprintf(out_file, "\n");
}

int cols_compar(const void *a, const void *b) {
   int x = supps[*(int const *)a], y = supps[*(int const *)b];
   return x >= min_support ?
      (y < min_support || x < y ? -1 : x > y ? +1 : 0) :
      (y >= min_support || x > y ? +1 : x < y ? -1 : 0);
}

int rows_compar(const void *a, const void *b) {
   for (int i = 0; i < int_count_a; i++)
      if (((unsigned long *)a)[i] < ((unsigned long *)b)[i]) return -1;
      else if (((unsigned long *)a)[i] > ((unsigned long *)b)[i]) return +1;
   return 0;
}

void sort_context(void) {
   int aa = attributes;
   attributes = 0;
   for (int i = 0; i < aa; i++)
      if (supps[i] >= min_support) attributes++;
   qsort(attrib_numbers, aa, sizeof *attrib_numbers, cols_compar);
   int a = int_count_a;
   int_count_a = attributes / DATA_BITS + 1;
   unsigned long *new_context = calloc(int_count_a * objects, sizeof *new_context);
   for (int jj = 0, k = 0, ii = DATA_BITS - 1; k < aa; k++)
      if (supps[attrib_numbers[k]] >= min_support) {
         int j = attrib_numbers[k] / DATA_BITS, i = DATA_BITS - 1 - attrib_numbers[k] % DATA_BITS;
         for (int x = 0, y = j, z = jj; x < objects; x++, y += a, z += int_count_a)
            if (context[y] & (BitU << i)) new_context[z] |= BitU << ii;
         if (ii > 0) ii--; else ii = DATA_BITS - 1, jj++;
      }
   free(context), context = new_context;
   qsort(context, objects, int_count_a * sizeof *context, rows_compar);
}

void initialize_algorithm(void) {
   for (int i = 0; i < DATA_BITS; i++) {
      upto_bit[i] = NilU;
      for (int j = DATA_BITS - 1; j > i; j--) upto_bit[i] |= BitU << j;
   }
   unsigned long *cols_buff = calloc(int_count_o * attributes, sizeof *cols_buff);
   cols = malloc(attributes * sizeof *cols);
   unsigned long *ptr = cols_buff;
   for (int j = 0, k = 0; j < int_count_a; j++) for (int i = DATA_BITS - 1; i >= 0; i--, k++) {
      if (k >= attributes) return;
      unsigned long mask = BitU << i;
      cols[k] = ptr;
      for (int x = 0, y = j; x < objects; x++, y += int_count_a)
         if (context[y] & mask) ptr[x / DATA_BITS] |= BitU << (x % DATA_BITS);
      ptr += int_count_o;
   }
}

void compute_closure(unsigned long *intent, unsigned long *extent, unsigned long *prev_extent, unsigned long *attr_extent, int *supp) {
   stats.closures++;
   memset(intent, 0xff, int_count_a * sizeof *intent);
   if (attr_extent != NULL) {
      *supp = 0;
      for (int k = 0; k < int_count_o; k++) {
         extent[k] = prev_extent[k] & attr_extent[k];
         if (extent[k] != 0UL)
            for (int l = 0; l < DATA_BITS && (extent[k] >> l); l++)
               if ((extent[k] >> l) & BitU) {
                  ++*supp;
                  for (int i = 0, j = int_count_a * (k * DATA_BITS + l); i < int_count_a; i++, j++) intent[i] &= context[j];
               }
      }
   } else {
      memset(extent, 0xff, int_count_o * sizeof *extent);
      for (int j = 0; j < objects; j++) for (int i = 0; i < int_count_a; i++) intent[i] &= context[int_count_a * j + i];
   }
}

void generate_from_node(unsigned long *intent, unsigned long *extent, int start_int, int start_bit, int *starts, unsigned long **implied, unsigned long ***implied_stack) {
   int supp = 0;
   unsigned long ***implied_stack_i = implied_stack;
   int *start_i = starts;
   int total = (start_int + 1) * DATA_BITS - 1 - start_bit;
   unsigned long *new_intent = malloc((int_count_a + int_count_o) * (attributes - total) * sizeof *new_intent);
   unsigned long *new_intents_head = new_intent;
   unsigned long *new_extent = new_intent + int_count_a;
   for (; start_int < int_count_a; start_int++) {
      for (; start_bit >= 0; start_bit--) {
         if (total >= attributes) goto skipout;
         if (intent[start_int] & (BitU << start_bit)) goto skip;
         if (implied[total] != NULL) {
            if (implied[total][start_int] & ~(intent[start_int]) & upto_bit[start_bit]) {
               stats.fail_fcbo++;
               goto skip;
            }
            for (int i = 0; i < start_int; i++)
               if (implied[total][i] & ~(intent[i])) {
                  stats.fail_fcbo++;
                  goto skip;
               }
         }
         compute_closure(new_intent, new_extent, extent, cols[total], &supp);
         if (supp < min_support) {
            stats.fail_support++;
            goto skip;
         }
         if ((new_intent[start_int] ^ intent[start_int]) & upto_bit[start_bit]) {
            stats.fail_canon++;
            goto skiptoelse;
         }
         for (int i = 0; i < start_int; i++)
            if (new_intent[i] ^ intent[i]) {
               stats.fail_canon++;
               goto skiptoelse;
            }
         print_attributes(new_intent, supp);
         stats.total++;
         *start_i++ = start_int;
         *start_i++ = start_bit;
         goto skipoverelse;
      skiptoelse:
         *implied_stack_i++ = &implied[total];
         *implied_stack_i++ = (unsigned long **)implied[total];
         implied[total] = new_intent;
         new_intent[int_count_a - 1] |= BitU;
      skipoverelse:
         new_intent = new_extent + int_count_o;
         new_extent = new_intent + int_count_a;
      skip:
         total++;
      }
      start_bit = DATA_BITS - 1;
   }
skipout:
   for (unsigned long *new_intent_i = new_intents_head; new_intent_i != new_intent; new_intent_i = new_extent + int_count_o) {
      new_extent = new_intent_i + int_count_a;
      if (new_intent_i[int_count_a - 1] & BitU) continue;
      if (*(starts + 1) == 0)
         generate_from_node(new_intent_i, new_extent, *starts + 1, DATA_BITS - 1, start_i, implied, implied_stack_i);
      else
         generate_from_node(new_intent_i, new_extent, *starts, *(starts + 1) - 1, start_i, implied, implied_stack_i);
      starts += 2;
   }
   for (; implied_stack != implied_stack_i; implied_stack += 2) **implied_stack = (unsigned long *)*(implied_stack + 1);
   free(new_intents_head);
}

void find_all_intents(void) {
   unsigned long *intent = malloc((int_count_a + int_count_o) * sizeof *intent);
   unsigned long *extent = intent + int_count_a;
   compute_closure(intent, extent, NULL, NULL, NULL);
   print_attributes(intent, objects);
   stats.total++;
   if (intent[int_count_a - 1] & BitU) return;
   int *starts = malloc((attributes + 1) * attributes * sizeof *starts);
   unsigned long **implied = calloc(attributes, sizeof *implied);
   unsigned long ***implied_stack = malloc((attributes + 1) * attributes * sizeof *implied_stack);
   generate_from_node(intent, extent, 0, DATA_BITS - 1, starts, implied, implied_stack);
}

int main(int argc, char **argv) {
   in_file = stdin, out_file = stdout;
   if (argc > 1) {
      int index = 1;
      for (; index < argc && argv[index][0] == '-' && argv[index][1] != 0; index++) switch (argv[index][1]) {
         case 'h': fprintf(stderr, "synopsis: %s [-h] [-index] [-Smin-support] [-Vlevel] [INPUT-FILE] [OUTPUT-FILE]\n", argv[0]); return EXIT_SUCCESS;
         case 'S': min_support = atoi(argv[index] + 2); break;
         case 'V': verbosity_level = atoi(argv[index] + 2); break;
         default:
            attr_offset = atoi(argv[index] + 1);
            if (attr_offset < 0) attr_offset = 0;
      }
      if (argc > index && argv[index][0] != '-') in_file = fopen(argv[index], "rb");
      if (argc > index + 1 && argv[index + 1][0] != '-') out_file = fopen(argv[index + 1], "wb");
   }
   if (in_file == NULL) { fprintf(stderr, "%s: cannot open input data stream\n", argv[0]); return EXIT_FAILURE; }
   if (out_file == NULL) { fprintf(stderr, "%s: open output data stream\n", argv[0]); return EXIT_FAILURE; }
   if (verbosity_level >= 3) gettimeofday(&time_start, NULL);
   read_file(in_file);
   create_context();
   free(buff);
   fclose(in_file);
   if (verbosity_level >= 3) gettimeofday(&time_inner, NULL);
   initialize_output();
   sort_context();
   initialize_algorithm();
   find_all_intents();
   if (verbosity_level >= 3) {
      gettimeofday(&time_end, NULL);
      long usec_less = time_end.tv_usec < time_inner.tv_usec ? 1L : 0L;
      fprintf(stderr, "inner time: %li.%06li s\n", time_end.tv_sec - time_inner.tv_sec - usec_less, usec_less * 1000000 + time_end.tv_usec - time_inner.tv_usec);
      usec_less = time_end.tv_usec < time_start.tv_usec ? 1L : 0L;
      fprintf(stderr, "total time: %li.%06li s\n", time_end.tv_sec - time_start.tv_sec - usec_less, usec_less * 1000000 + time_end.tv_usec - time_start.tv_usec);
   }
   if (verbosity_level >= 2) fprintf(stderr, "total: %i\nclosures: %i\nfail_canon: %i\nfail_fcbo: %i\nfail_support: %i\n", stats.total, stats.closures, stats.fail_canon, stats.fail_fcbo, stats.fail_support);
   fclose(out_file);
   return EXIT_SUCCESS;
}
