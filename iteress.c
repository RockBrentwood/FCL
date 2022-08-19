// FCALGS: Formal Concept Analysis (FCA) Algorithms
// Copyright (C) 2007
// Jan Outrata, <jan.outrata@upol.cz>
// Vilem Vychodil, <vilem.vychodil@gmail.com>
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

// Iterative Greedy Concepts on Demand from Essential Elements
// (IterEss) algorithm
// Copyright (C) 2013
// Jan Outrata, <jan.outrata@upol.cz>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include <time.h>

#define STATS

// Basic data types
typedef long count_t;
typedef char small_count_t;

// Error handling
char *program_name = NULL;

void error(char *Format, ...) {
   fprintf(stderr, "%s: ", program_name);
   va_list args; va_start(args, Format), vfprintf(stderr, Format, args), va_end(args);
}

// Counters and times
#ifdef STATS
typedef struct {
   count_t *counters;
   char **counter_texts;
   int ncounters;
   struct timeval *times;
   char **time_texts;
   int ntimes;
   int time_pos;
} stats_t;
#   define STATS_INITIALIZER {NULL, NULL, 0, NULL, NULL, 0, 0}
#   define Counter	(stats[0].counters)
#   define CounterText	(stats[0].counter_texts)
#   define Counters	(stats[0].ncounters)
#   define Time		(stats[0].times)
#   define TimeText	(stats[0].time_texts)
#   define Times	(stats[0].ntimes)
#   define TimePos	(stats[0].time_pos)
#   define STATS_DATA_PARAM , stats_t *stats
#   define STATS_DATA_ARG , stats
#   define INC_COUNTER(c) Counter[c]++
#   define ADD_COUNTER(c, v) Counter[c] += v
#   define SET_COUNTER(c, v) Counter[c] = v
#   define SET_COUNTER_TEXT(c, t) CounterText[c] = t
#   define SAVE_TIME(t) if (TimePos < Times) (gettimeofday(&Time[TimePos], NULL), TimeText[TimePos++] = t)
#else
#   define STATS_DATA_PARAM
#   define STATS_DATA_ARG
#   define INC_COUNTER(c)
#   define ADD_COUNTER(c, v)
#   define SET_COUNTER(c, v)
#   define SET_COUNTER_TEXT(c, t)
#   define SAVE_TIME(t)
#endif

#ifdef STATS
void init_stats(stats_t **stats_p, int count, int counters, int times) {
   stats_t *stats = *stats_p = malloc(count * sizeof *stats);
   Counter = calloc(count * counters, sizeof *Counter);
   CounterText = calloc(count * counters, sizeof *CounterText);
   Time = malloc(count * times * sizeof *Time);
   TimeText = malloc(count * times * sizeof *TimeText);
   while (--count > 0) {
      stats[count].counters = Counter + count * counters;
      stats[count].counter_texts = CounterText;
      stats[count].times = Time + count * times;
      stats[count].time_texts = TimeText;
      stats[count].time_pos = 0;
      stats[count].ncounters = counters;
      stats[count].ntimes = times;
   }
   TimePos = 0;
   Counters = counters;
   Times = times;
}

void free_stats(stats_t **stats_p) {
   stats_t *stats = *stats_p;
   free(Counter);
   free(CounterText);
   free(Time);
   free(TimeText);
   free(stats);
   *stats_p = NULL;
}
#endif

// Input/Output interface
#define IO_BUFFER_BLOCK	0x100000
typedef enum {
   IO_MARK_CONCEPT_HELP = -7,
   IO_MARK_CONCEPT_UPPER,
   IO_MARK_CONCEPT_LOWER,
   IO_MARK_CONCEPT_MODIFIED,
   IO_SEP_OA,
   IO_SEP_CLASS,
   IO_END_SET
} io_char_t;

typedef enum { INPUT_LABELS = 1, INPUT_LABELS_ONLY = 1 << 1, OUTPUT_ALL = 1 << 8 } io_flags_t;

typedef struct {
   count_t *write_ptr;
   count_t *read_ptr;
   int write_left;
   int read_left;
   int size;
   count_t *base;
} io_buffer_t;

struct io_struc;
typedef void (io_func_t)(struct io_struc *io, void *data, io_flags_t flags);
typedef struct io_struc {
   io_buffer_t buffer;
   io_func_t *func;
   void *func_data;
} io_t;

#define IO_INITIALIZER {{NULL, NULL, 0, 0, 0, NULL}, NULL, NULL}

#define IO_WRITE(_io, _value) { \
   if ((_io)->buffer.write_left == 0) alloc_io_buffer(_io, (_io)->buffer.size + IO_BUFFER_BLOCK); \
   *(_io)->buffer.write_ptr = _value, (_io)->buffer.write_ptr++, (_io)->buffer.write_left--, (_io)->buffer.read_left++; \
}

#define IO_READ(_io, _var) (_var = *(_io)->buffer.read_ptr, (_io)->buffer.read_ptr++, (_io)->buffer.read_left--)

#define IO_FUNC(_io, _flags) { \
   if ((_io)->func != NULL) (_io)->func(_io, (_io)->func_data, _flags); \
}

void reset_io(io_t *io) {
   io->buffer.write_ptr = io->buffer.read_ptr = io->buffer.base;
   io->buffer.write_left = io->buffer.size;
   io->buffer.read_left = 0;
}

void init_io(io_t *io, io_func_t *func, void *func_data) {
   io->buffer.base = NULL;
   io->buffer.size = 0;
   reset_io(io);
   io->func = func;
   io->func_data = func_data;
}

void free_io(io_t *io) {
   if (io->buffer.base) free(io->buffer.base);
   init_io(io, NULL, NULL);
}

io_buffer_t *alloc_io_buffer(io_t *io, int size) {
   if (io->buffer.base != NULL) {
      count_t *old_base = io->buffer.base;
      io->buffer.base = realloc(io->buffer.base, size * sizeof *io->buffer.base);
      if (io->buffer.base != NULL && io->buffer.base != old_base) {
         io->buffer.write_ptr += io->buffer.base - old_base;
         io->buffer.read_ptr += io->buffer.base - old_base;
      }
   } else io->buffer.base = io->buffer.write_ptr = io->buffer.read_ptr = malloc(size * sizeof *io->buffer.base);
   if (io->buffer.base == NULL) {
      error("cannot allocate I/O buffer");
      return NULL;
   }
   io->buffer.write_left += size - io->buffer.size;
   io->buffer.size = size;
   return &io->buffer;
}

// File input
bool get_next_number_from_file(FILE *file, count_t *value) {
   *value = IO_END_SET;
   int ch = ' ';
   while (ch != EOF && !isdigit(ch)) {
      ch = fgetc(file);
      if (ch == '\n') return true;
      else if (ch == '|') {
         *value = IO_SEP_CLASS;
         return true;
      }
   }
   if (ch == EOF) return false;
   *value = 0;
   while (isdigit(ch)) {
      *value *= 10;
      *value += ch - '0';
      ch = fgetc(file);
   }
   ungetc(ch, file);
   return true;
}

void read_file_to_io(io_t *io, FILE *file, io_flags_t flags) {
   count_t last_object = -1;
   IO_WRITE(io, last_object + 1);
   count_t last_attribute = -1;
   if (!(flags & INPUT_LABELS_ONLY)) IO_WRITE(io, last_attribute + 1);
   small_count_t classes = 0;
   if (flags & (INPUT_LABELS | INPUT_LABELS_ONLY)) IO_WRITE(io, classes);
   count_t value = 0;
   small_count_t last_class = -1;
   int labels = flags & INPUT_LABELS_ONLY;
   while (get_next_number_from_file(file, &value) != 0) {
      if (value == IO_END_SET) {
         last_object++;
         IO_WRITE(io, IO_END_SET);
         if (last_class >= classes) classes = last_class + 1;
         last_class = -1;
         labels = flags & INPUT_LABELS_ONLY;
      } else if (value == IO_SEP_CLASS) {
         labels = 1;
         if ((flags & INPUT_LABELS) && !(flags & INPUT_LABELS_ONLY)) IO_WRITE(io, IO_SEP_CLASS);
      } else if (labels != 0) {
         last_class++;
         if (flags & (INPUT_LABELS | INPUT_LABELS_ONLY)) IO_WRITE(io, value);
      } else {
         if (value > last_attribute) last_attribute = value;
         IO_WRITE(io, value);
      }
   }
   if (value >= 0) {
      last_object++;
      IO_WRITE(io, IO_END_SET);
      if (last_class >= classes) classes = last_class + 1;
   }
   *io->buffer.read_ptr = last_object + 1;
   if (!(flags & INPUT_LABELS_ONLY)) {
      *(io->buffer.read_ptr + 1) = last_attribute + 1;
      if (flags & INPUT_LABELS) *(io->buffer.read_ptr + 2) = classes;
   } else *(io->buffer.read_ptr + 1) = classes;
}

// File output
#define OUTPUT_BLOCK 0x400

void write_file_from_io(io_t *io, FILE *file, io_flags_t flags) {
   if (io->buffer.read_left < OUTPUT_BLOCK && !(flags & OUTPUT_ALL)) return;
   bool first = true;
   while (io->buffer.read_left != 0) {
      count_t value; IO_READ(io, value);
      if (value == IO_END_SET) fprintf(file, "\n"), first = true;
      else {
         if (!first) fprintf(file, " ");
         switch (value) {
            case IO_SEP_CLASS: case IO_SEP_OA: fprintf(file, "|"); break;
            case IO_MARK_CONCEPT_MODIFIED: fprintf(file, "*"); break;
            case IO_MARK_CONCEPT_LOWER: fprintf(file, "<"); break;
            case IO_MARK_CONCEPT_UPPER: fprintf(file, ">"); break;
            case IO_MARK_CONCEPT_HELP: fprintf(file, "-"); break;
            default: fprintf(file, "%li", value);
         }
         first = false;
      }
   }
   reset_io(io);
}

// Formal context
typedef unsigned long data_t;
const data_t BitU = (data_t)1, NilU = (data_t)0, AllU = (data_t)-1;
#define DATA_BITS	(8 * sizeof(data_t))
#define DT_SIZE_A	(sizeof(data_t) * context->dt_count_a)
#define DT_SIZE_O	(sizeof(data_t *) * (context->objects + 1))
#define DT_SIZE_Ox(x)	(sizeof(data_t *) * (x + 1))

typedef enum { CONTEXT_SORT_COLS = 1, CONTEXT_SORT_ROWS = 1 << 1 } context_sort_t;

typedef struct context_struc {
   count_t attributes;
   count_t objects;
   count_t dt_count_a;
   count_t table_entries;
   data_t *bitarray;
   data_t **rows;
   count_t *supps;
   count_t *attrib_numbers;
   count_t *object_numbers;
} context_t;

#define CONTEXT_INITIALIZER {0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL}

context_t *qsort_context = NULL;

void create_context(context_t *context, count_t objects, count_t attributes) {
   context->attributes = attributes;
   context->objects = objects;
   context->dt_count_a = attributes / DATA_BITS + 1;
   context->bitarray = calloc(context->dt_count_a * objects, sizeof *context->bitarray);
   if (context->bitarray == NULL) error("cannot allocate context");
   context->rows = malloc(objects * sizeof *context->rows);
   for (count_t i = 0; i < objects; i++) context->rows[i] = context->bitarray + i * context->dt_count_a;
   context->supps = calloc(attributes, sizeof *context->supps);
   context->table_entries = 0;
   context->attrib_numbers = malloc(attributes * sizeof *context->attrib_numbers);
   for (count_t i = 0; i < attributes; i++) context->attrib_numbers[i] = i;
   context->object_numbers = malloc(objects * sizeof *context->object_numbers);
   for (count_t i = 0; i < objects; i++) context->object_numbers[i] = i;
}

void destroy_context(context_t *context) {
   if (context->bitarray) free(context->bitarray);
   if (context->rows) free(context->rows);
   if (context->supps) free(context->supps);
   if (context->attrib_numbers) free(context->attrib_numbers);
   if (context->object_numbers) free(context->object_numbers);
}

void copy_context(context_t *to_context, context_t *from_context) {
   create_context(to_context, from_context->objects, from_context->attributes);
   memcpy(to_context->bitarray, from_context->bitarray, to_context->dt_count_a * to_context->objects * sizeof *to_context->bitarray);
   memcpy(to_context->supps, from_context->supps, to_context->attributes * sizeof *to_context->supps);
   to_context->table_entries = from_context->table_entries;
   memcpy(to_context->attrib_numbers, from_context->attrib_numbers, to_context->attributes * sizeof *to_context->attrib_numbers);
   memcpy(to_context->object_numbers, from_context->object_numbers, to_context->objects * sizeof *to_context->object_numbers);
}

void input_context_from_io(context_t *context, io_t *io, count_t attr_offset) {
   IO_FUNC(io, 0);
   count_t object; IO_READ(io, object);
   count_t value; IO_READ(io, value);
   create_context(context, object, value);
   object = 0;
   while (io->buffer.read_left != 0) {
      IO_READ(io, value);
      if (value == IO_END_SET) object++;
      else if ((value -= attr_offset) < 0) error("invalid input value %li (minimum value is %li)", value + attr_offset, attr_offset);
      else {
         context->rows[object][value / DATA_BITS] |= BitU << (DATA_BITS - 1 - value % DATA_BITS);
         context->supps[value]++;
         context->table_entries++;
      }
   }
}

void output_context_to_io(context_t *context, io_t *io) {
   for (count_t i = 0; i < context->objects; i++) {
      for (count_t j = 0, total = 0; j < context->dt_count_a; j++) for (int k = DATA_BITS - 1; k >= 0; k--, total++) {
         if (total >= context->attributes) goto skipout;
         if (context->rows[i][j] & (BitU << k)) IO_WRITE(io, context->attrib_numbers[total]);
      }
   skipout:
      IO_WRITE(io, IO_END_SET);
   }
   IO_FUNC(io, OUTPUT_ALL);
}

int context_attrib_numbers_compar(const void *a, const void *b) {
   count_t x = qsort_context->supps[*(count_t const *)a], y = qsort_context->supps[*(count_t const *)b];
   return x < y ? -1 : x > y ? +1 : 0;
}

int context_object_numbers_compar(const void *a, const void *b) {
   for (count_t i = 0; i < qsort_context->dt_count_a; i++)
      if (qsort_context->rows[*(count_t const *)a][i] < qsort_context->rows[*(count_t const *)b][i]) return -1;
      else if (qsort_context->rows[*(count_t const *)a][i] > qsort_context->rows[*(count_t const *)b][i]) return +1;
   return 0;
}

int context_objects_compar(const void *a, const void *b) {
   for (count_t i = 0; i < qsort_context->dt_count_a; i++)
      if (((data_t const *)a)[i] < ((data_t const *)b)[i]) return -1;
      else if (((data_t const *)a)[i] > ((data_t const *)b)[i]) return +1;
   return 0;
}

void reorder_attribs_in_context(context_t *context, count_t *attrib_numbers) {
   data_t *bitarray = malloc(context->dt_count_a * context->objects * sizeof *bitarray);
   memcpy(bitarray, context->bitarray, context->dt_count_a * context->objects * sizeof *bitarray);
   memset(context->bitarray, 0, context->dt_count_a * context->objects * sizeof *context->bitarray);
   count_t *supps = malloc(context->attributes * sizeof *supps);
   memcpy(supps, context->supps, context->attributes * sizeof *supps);
   for (count_t i = 0, total = 0; i < context->dt_count_a; i++) for (int j = DATA_BITS - 1; j >= 0; j--, total++) {
      if (total >= context->attributes) goto skipout;
      for (count_t o = 0; o < context->objects; o++)
         if (bitarray[o * context->dt_count_a + attrib_numbers[total] / DATA_BITS] & (BitU << (DATA_BITS - 1 - attrib_numbers[total] % DATA_BITS))) context->rows[o][i] |= BitU << j;
      context->supps[total] = supps[attrib_numbers[total]];
   }
skipout:
   if (context->attrib_numbers != attrib_numbers) memcpy(context->attrib_numbers, attrib_numbers, context->attributes * sizeof *context->attrib_numbers);
   free(bitarray);
   free(supps);
}

void sort_context(context_t *context, int sort_by) {
   if (sort_by & CONTEXT_SORT_COLS) {
      qsort_context = context;
      qsort(context->attrib_numbers, context->attributes, sizeof *context->attrib_numbers, context_attrib_numbers_compar);
      reorder_attribs_in_context(context, context->attrib_numbers);
   }
   if (sort_by & CONTEXT_SORT_ROWS) {
      qsort_context = context;
      qsort(context->object_numbers, context->objects, sizeof *context->object_numbers, context_object_numbers_compar);
      qsort(context->bitarray, context->objects, context->dt_count_a * sizeof *context->bitarray, context_objects_compar);
   }
}

void remove_low_support_attribs_from_context(context_t *context, count_t min_support) {
   count_t attribs = 0;
   for (count_t i = 0; i < context->attributes; i++)
      if (context->supps[i] >= min_support) attribs++;
   context_t new_context; create_context(&new_context, context->objects, attribs);
   int jj = DATA_BITS - 1;
   for (count_t i = 0, ii = 0, ttotal = 0, total = 0; i < context->dt_count_a; i++) for (int j = DATA_BITS - 1; j >= 0; j--, total++) {
      if (total >= context->attributes) goto skipout;
      else if (context->supps[total] < min_support) continue;
      for (count_t o = 0; o < context->objects; o++)
         if (context->rows[o][i] & (BitU << j)) new_context.rows[o][ii] |= BitU << jj;
      new_context.supps[ttotal] = context->supps[total];
      new_context.table_entries += context->supps[total];
      new_context.attrib_numbers[ttotal] = context->attrib_numbers[total];
      ttotal++;
      if (--jj < 0) ii++, jj = DATA_BITS - 1;
   }
skipout:
   memcpy(new_context.object_numbers, context->object_numbers, context->objects * sizeof *new_context.object_numbers);
   destroy_context(context);
   *context = new_context;
}

void transpose_context(context_t *context) {
   context_t new_context; create_context(&new_context, context->attributes, context->objects);
   for (count_t i = 0, total = 0; i < context->dt_count_a; i++) for (int j = DATA_BITS - 1; j >= 0; j--, total++) {
      if (total >= context->attributes) goto skipout;
      for (count_t o = 0; o < context->objects; o++)
         if (context->rows[o][i] & (BitU << j)) {
            new_context.rows[total][o / DATA_BITS] |= BitU << (DATA_BITS - 1 - o % DATA_BITS);
            new_context.supps[o]++;
         }
   }
skipout:
   memcpy(new_context.object_numbers, context->attrib_numbers, context->attributes * sizeof *new_context.object_numbers);
   memcpy(new_context.attrib_numbers, context->object_numbers, context->objects * sizeof *new_context.attrib_numbers);
   destroy_context(context);
   *context = new_context;
}

void compute_ess_context(context_t *ess_context, context_t *context) {
   copy_context(ess_context, context);
   context_t transp_context; copy_context(&transp_context, context);
   transpose_context(&transp_context);
   context_t transp_ess_context; copy_context(&transp_ess_context, &transp_context);
   context_t *tmp_context = context, *tmp_ess_context = ess_context;
   for (int n = 0; n < 2; n++) {
      for (count_t o = 0; o < tmp_context->objects; o++) for (count_t p = o + 1; p < tmp_context->objects; p++) {
         bool geq = true, leq = true;
         for (count_t i = 0; (geq || leq) && i < tmp_context->dt_count_a; i++) {
            if (geq && (~tmp_context->rows[o][i] & tmp_context->rows[p][i])) geq = false;
            if (leq && (tmp_context->rows[o][i] & ~tmp_context->rows[p][i])) leq = false;
         }
         if (geq > leq)
            for (count_t i = 0; i < tmp_context->dt_count_a; i++) tmp_ess_context->rows[o][i] &= ~tmp_context->rows[p][i];
	 else if (leq > geq)
            for (count_t i = 0; i < tmp_context->dt_count_a; i++) tmp_ess_context->rows[p][i] &= ~tmp_context->rows[o][i];
      }
      tmp_context = &transp_context, tmp_ess_context = &transp_ess_context;
   }
   destroy_context(&transp_context);
   transpose_context(&transp_ess_context);
   memset(ess_context->supps, 0, context->attributes * sizeof *ess_context->supps);
   ess_context->table_entries = 0;
   for (count_t o = 0; o < context->objects; o++) {
      for (count_t i = 0, total = 0; i < context->dt_count_a; i++) {
         ess_context->rows[o][i] &= transp_ess_context.rows[o][i];
         for (int j = DATA_BITS - 1; j >= 0; j--, total++) {
            if (total >= context->attributes) goto skipout;
            if (ess_context->rows[o][i] & (BitU << j)) ess_context->supps[total]++, ess_context->table_entries++;
         }
      }
   skipout:
      ;
   }
   destroy_context(&transp_ess_context);
}

void _transform_objects_to_context(data_t **objects, data_t **from_objects, context_t *context, context_t *from_context) {
   *objects = NULL;
   for (count_t o = (count_t)*from_objects++; o > 0; from_objects++, o--)
      if ((*from_objects - *from_context->rows) / from_context->dt_count_a < context->objects) {
         *objects = (data_t *)((count_t)*objects + 1);
         objects[(count_t)*objects] = context->rows[(*from_objects - *from_context->rows) / from_context->dt_count_a];
      }
}

count_t compute_table_entries_percent(count_t table_entries, int percent) {
   return ((percent / 10) * table_entries / 10 + (percent % 10) * table_entries / 100);
}

// Formal concept and concepts.
#ifdef STATS
enum { CONCEPTS = 0, CLOSURES, FAIL_SUPPORT, NEXT_CONCEPTS_COUNTER };
#endif

typedef enum {
   CONCEPT_NEW = 1, CONCEPT_MODIFIED = 1 << 1, CONCEPT_LOWER = 1 << 2,
   CONCEPT_UPPER = 1 << 3, CONCEPT_HELP = 1 << 4,
   CONCEPT_SAVE_ATTRIBS_ONLY = 1 << 8, CONCEPT_SAVE_OBJECTS_ONLY = 1 << 9
} concept_flags_t;

typedef struct {
   data_t *start;
   data_t *iter;
   data_t *end;
} concept_list_t;

typedef void (concept_save_func_t)(data_t *intent, data_t **extent, context_t *context, void *data, concept_flags_t flags);
typedef void (concept_info_func_t)(data_t *intent, data_t **extent, context_t *context, concept_flags_t flags STATS_DATA_PARAM);

typedef struct {
   count_t min_support;
   concept_save_func_t *save_func;
   void *save_data;
   concept_info_func_t *info_func;
   concept_flags_t flags;
} concepts_t;

#define CONCEPTS_INITIALIZER {0, NULL, NULL, NULL, 0}

#define SAVE_CONCEPT(_intent, _extent, _context, _concepts, _flags) { \
   if ((_concepts)->save_func != NULL || (_concepts)->info_func != NULL) { \
      if ((_concepts)->save_func != NULL) (_concepts)->save_func(_intent, _extent, _context, (_concepts)->save_data, (_concepts)->flags | _flags); \
      if ((_concepts)->info_func != NULL) (_concepts)->info_func(_intent, _extent, _context, (_concepts)->flags | _flags STATS_DATA_ARG); \
   } \
}

void compute_closure_from_attrs(data_t *intent, data_t **extent, data_t *attrs, context_t *context);
void compute_closure_from_objects(data_t *intent, data_t **extent, data_t **objects, context_t *context);

data_t upto_bit[DATA_BITS];

void init_concepts(concepts_t *concepts, count_t min_support, concept_save_func_t *save_func, void *save_data, concept_info_func_t *info_func, concept_flags_t flags) {
   concepts->min_support = min_support;
   concepts->save_func = save_func;
   concepts->save_data = save_data;
   concepts->info_func = info_func;
   concepts->flags = flags;
}

void free_concepts(concepts_t *concepts) { }

void compute_closure_plus_attr(data_t *intent, data_t **extent, data_t **prev_extent, data_t *prev_intent, context_t *context, count_t attr_dt, data_t attr_mask, count_t min_support) {
   data_t data = 0;
   memset(intent, 0xff, DT_SIZE_A);
   if (prev_extent != NULL) {
      for (count_t i = (count_t)*prev_extent++, o = i; o > 0; prev_extent++, o--) {
         if ((*prev_extent)[attr_dt] & attr_mask) extent[(count_t)++data] = *prev_extent;
         else if (--i < min_support) {
            *extent = (data_t *)data;
            return;
         }
      }
      *extent = (data_t *)data;
      for (count_t i = 0; i < context->dt_count_a; i++, intent++) {
         data = *intent;
         if (data != 0 && (prev_intent[i] ^ AllU)) for (count_t o = (count_t)*extent; data && o; o--) data &= extent[o][i];
         *intent = data;
      }
   } else {
      *extent = (data_t *)context->objects;
      for (count_t o = 0; o < context->objects; o++) {
         extent[o + 1] = context->rows[o];
         for (count_t i = 0; i < context->dt_count_a; i++) intent[i] &= context->rows[o][i];
      }
   }
}

void compute_extent_from_attrs(data_t **extent, data_t *attrs, context_t *context) {
   data_t data = 0;
   for (count_t o = 0; o < context->objects; o++) {
      for (count_t i = 0; i < context->dt_count_a; i++)
         if (attrs[i] & ~(context->rows[o][i])) goto skip;
      extent[(count_t)++data] = context->rows[o];
   skip:
      ;
   }
   *extent = (data_t *)data;
}

void compute_intent_from_objects(data_t *intent, data_t **objects, context_t *context) {
   memset(intent, 0xff, DT_SIZE_A);
   for (count_t i = 0; i < context->dt_count_a; i++, intent++) {
      data_t data = *intent;
      if (data != 0)
         for (count_t o = (count_t)*objects; data && o; o--) data &= objects[o][i];
      *intent = data;
   }
}

__inline void compute_closure_from_attrs(data_t *intent, data_t **extent, data_t *attrs, context_t *context) {
   compute_extent_from_attrs(extent, attrs, context);
   compute_intent_from_objects(intent, extent, context);
}

__inline void compute_closure_from_objects(data_t *intent, data_t **extent, data_t **objects, context_t *context) {
   compute_intent_from_objects(intent, objects, context);
   compute_extent_from_attrs(extent, intent, context);
}

void compute_attribute_concepts(data_t *intents, context_t *context, count_t min_support STATS_DATA_PARAM) {
   data_t *intent_largest = malloc(DT_SIZE_A + DT_SIZE_O);
   data_t **extent_largest = (data_t **)(intent_largest + context->dt_count_a);
   compute_closure_plus_attr(intent_largest, extent_largest, NULL, NULL, context, 0, 0, min_support);
   INC_COUNTER(CLOSURES);
   data_t *intent = intents;
   data_t **extent = (data_t **)(intent + context->dt_count_a);
   for (count_t j = 0, total = 0; j < context->dt_count_a; j++) for (int i = DATA_BITS - 1; i >= 0; i--) {
      if (total >= context->attributes) return;
      compute_closure_plus_attr(intent, extent, extent_largest, intent_largest, context, j, BitU << i, min_support);
      INC_COUNTER(CLOSURES);
      intent = (data_t *)(extent + context->objects + 1);
      extent = (data_t **)(intent + context->dt_count_a);
      total++;
   }
   free(intent_largest);
}

void output_attributes_to_io(data_t *set, context_t *context, io_t *io) {
   for (count_t j = 0, c = 0; j < context->dt_count_a; j++) for (data_t i = BitU << (DATA_BITS - 1); i; i >>= 1) {
      if (set[j] & i) IO_WRITE(io, context->attrib_numbers[c]);
      if (++c >= context->attributes) goto out;
   }
out:;
}

void output_objects_to_io(data_t **set, context_t *context, io_t *io) {
   for (count_t o = (count_t)*set++; o > 0; set++, o--) IO_WRITE(io, context->object_numbers[(count_t)(*set - *context->rows) / context->dt_count_a]);
}

void save_concept_to_list(data_t *intent, data_t **extent, context_t *context, concept_list_t *list, concept_flags_t flags) {
   if (list->iter + context->dt_count_a + (count_t)*extent + 1 > list->end) {
      count_t length = list->iter - list->start;
      list->start = realloc(list->start, (length << 1) * sizeof *list->start);
      list->iter = list->start + length;
      list->end = list->start + (length << 1);
   }
   if (!(flags & CONCEPT_SAVE_OBJECTS_ONLY))
      memcpy(list->iter, intent, DT_SIZE_A), list->iter += context->dt_count_a;
   if (!(flags & CONCEPT_SAVE_ATTRIBS_ONLY))
      memcpy(list->iter, extent, DT_SIZE_Ox((count_t)*extent)), list->iter += (count_t)*extent + 1;
}

// Boolean factors as formal concepts.
#ifdef STATS
enum { FACTORS = 0, UNCOVERED = 2, OVERCOVERED, NEXT_FACTORS_COUNTER };
#endif

typedef struct {
   int threshold;
   concepts_t concepts;
} factors_t;

void init_factors(factors_t *factors, int threshold) { factors->threshold = threshold; }

void compute_closure_masked_size(data_t *intent, data_t **extent, context_t *context, context_t *mask_context, count_t *size, count_t *over_size) {
   *size = 0;
   if (over_size != NULL) *over_size = 0;
   for (count_t o = (count_t)*extent++; o > 0; extent++, o--) {
      count_t over_count = 0, count = 0;
      for (count_t i = 0; i < context->dt_count_a; i++) {
         data_t cell = intent[i] & mask_context->rows[(*extent - *context->rows) / context->dt_count_a][i];
         for (int j = 0; j < DATA_BITS && cell; cell >>= BitU, j++)
            if (cell & BitU) {
               if (context->rows[(*extent - *context->rows) / context->dt_count_a][i] & (BitU << j))
                  count++;
               else
                  over_count++;
            }
      }
      *size += count;
      if (over_size != NULL) *over_size += over_count;
   }
}

void output_factor_to_io(data_t *intent, data_t **extent, context_t *context, io_t *io, concept_flags_t flags) {
   if (!(flags & CONCEPT_SAVE_OBJECTS_ONLY)) output_attributes_to_io(intent, context, io);
   if (!(flags & CONCEPT_SAVE_ATTRIBS_ONLY)) {
      if (!(flags & CONCEPT_SAVE_OBJECTS_ONLY)) IO_WRITE(io, IO_SEP_OA);
      output_objects_to_io(extent, context, io);
   }
   IO_WRITE(io, IO_END_SET);
   IO_FUNC(io, 0);
}

// IterEss algorithm.
#ifdef STATS
enum { ESS_CONTEXTS = NEXT_FACTORS_COUNTER };
#endif

int ess_iters = 1;

__inline void SwapIntent(data_t **AP, data_t **BP) {
   data_t *A = *AP, *B = *BP;
   *AP = B, *BP = A;
}

__inline void SwapExtent(data_t ***AP, data_t ***BP) {
   data_t **A = *AP, **B = *BP;
   *AP = B, *BP = A;
}

__inline void SwapConcepts(concept_list_t **AP, concept_list_t **BP) {
   concept_list_t *A = *AP, *B = *BP;
   *AP = B, *BP = A;
}

void find_factors(context_t *context, factors_t *factors STATS_DATA_PARAM) {
   SET_COUNTER_TEXT(ESS_CONTEXTS, "Ess contexts");
   count_t table_entries_percent = compute_table_entries_percent(context->table_entries, 100 - factors->threshold);
   int contexts_length = 8;
   context_t **contexts = malloc(contexts_length * sizeof *contexts);
   *contexts = context;
   count_t c = 0;
   do {
      if (++c == contexts_length) contexts_length <<= 1, contexts = realloc(contexts, contexts_length * sizeof *contexts);
      contexts[c] = malloc(sizeof *contexts[c]);
      compute_ess_context(contexts[c], contexts[c - 1]);
   } while ((ess_iters == 0 || c < ess_iters) && contexts[c]->table_entries != contexts[c - 1]->table_entries);
   if (contexts[c]->table_entries == contexts[c - 1]->table_entries && c > 1) c--;
   count_t last_c = c;
   SAVE_TIME("Ess contexts time");
   SET_COUNTER(ESS_CONTEXTS, last_c);
   struct { data_t *start, *iter; } attribute_intents;
   attribute_intents.start = attribute_intents.iter = malloc((DT_SIZE_A + DT_SIZE_O) * (context->attributes + 12) + DT_SIZE_O);
   data_t *intent = (data_t *)(attribute_intents.start + (context->dt_count_a + context->objects + 1) * context->attributes);
   data_t **extent = (data_t **)(intent + context->dt_count_a);
   data_t *new_intent = (data_t *)(extent + context->objects + 1);
   data_t **new_extent = (data_t **)(new_intent + context->dt_count_a);
   data_t *best_intent = (data_t *)(new_extent + context->objects + 1);
   data_t **best_extent = (data_t **)(best_intent + context->dt_count_a);
   data_t *intent_parent_intent = (data_t *)(best_extent + context->objects + 1);
   data_t **intent_parent_extent = (data_t **)(intent_parent_intent + context->dt_count_a);
   data_t *intent_new_parent_intent = (data_t *)(intent_parent_extent + context->objects + 1);
   data_t **intent_new_parent_extent = (data_t **)(intent_new_parent_intent + context->dt_count_a);
   data_t *intent_best_parent_intent = (data_t *)(intent_new_parent_extent + context->objects + 1);
   data_t **intent_best_parent_extent = (data_t **)(intent_best_parent_intent + context->dt_count_a);
   data_t *extent_parent_intent = (data_t *)(intent_best_parent_extent + context->objects + 1);
   data_t **extent_parent_extent = (data_t **)(extent_parent_intent + context->dt_count_a);
   data_t *extent_new_parent_intent = (data_t *)(extent_parent_extent + context->objects + 1);
   data_t **extent_new_parent_extent = (data_t **)(extent_new_parent_intent + context->dt_count_a);
   data_t *extent_best_parent_intent = (data_t *)(extent_new_parent_extent + context->objects + 1);
   data_t **extent_best_parent_extent = (data_t **)(extent_best_parent_intent + context->dt_count_a);
   data_t *factor_intent = (data_t *)(extent_best_parent_extent + context->objects + 1);
   data_t **factor_extent = (data_t **)(factor_intent + context->dt_count_a);
   data_t *intent_factor_parent_intent = (data_t *)(factor_extent + context->objects + 1);
   data_t **intent_factor_parent_extent = (data_t **)(intent_factor_parent_intent + context->dt_count_a);
   data_t *extent_factor_parent_intent = (data_t *)(intent_factor_parent_extent + context->objects + 1);
   data_t **extent_factor_parent_extent = (data_t **)(extent_factor_parent_intent + context->dt_count_a);
   data_t **objects = (data_t **)(extent_factor_parent_extent + context->objects + 1);
   concept_list_t _factor_concepts[2];
   concept_list_t *factor_concepts = _factor_concepts;
   factor_concepts->iter = factor_concepts->start = malloc(DT_SIZE_A + DT_SIZE_O);
   factor_concepts->end = factor_concepts->start + context->dt_count_a + context->objects + 1;
   compute_closure_plus_attr(factor_concepts->start, (data_t **)(factor_concepts->start + context->dt_count_a), NULL, NULL, context, 0, 0, factors->concepts.min_support);
   memset(factor_concepts->start, 0xff, DT_SIZE_A);
   factor_concepts->start[context->dt_count_a - 1] &= ~BitU;
   concept_list_t *new_factor_concepts = _factor_concepts + 1;
   new_factor_concepts->iter = new_factor_concepts->start = malloc((DT_SIZE_A + DT_SIZE_O) * context->attributes);
   new_factor_concepts->end = new_factor_concepts->start + (context->dt_count_a + context->objects + 1) * context->attributes;
   SET_COUNTER(FACTORS, 0);
   SET_COUNTER(UNCOVERED, context->table_entries);
   count_t new_size;
   data_t *factor_concept = NULL;
   while (c >= 0) {
      if (c == 0) SAVE_TIME("Ess factors time");
      context_t new_context; copy_context(&new_context, contexts[c]);
      if (c == last_c) compute_attribute_concepts(attribute_intents.start, contexts[c], factors->concepts.min_support STATS_DATA_ARG);
      else {
         compute_closure_plus_attr(attribute_intents.start, (data_t **)(attribute_intents.start + context->dt_count_a), NULL, NULL, contexts[c], 0, 0, factors->concepts.min_support);
         INC_COUNTER(CLOSURES);
      }
      while (true) {
         count_t factor_size = 0;
         data_t **factor_concepts_extent;
         for (factor_concepts->iter = factor_concepts->start; factor_concepts->iter < factor_concepts->end; factor_concepts->iter = (data_t *)(factor_concepts_extent + (count_t)*factor_concepts_extent + 1)) {
            factor_concepts_extent = (data_t **)(factor_concepts->iter + context->dt_count_a);
            if (c == last_c) memset(intent, 0, DT_SIZE_A + DT_SIZE_O);
            else {
               if (factor_concepts->iter[context->dt_count_a - 1] & BitU) continue;
               memcpy(intent, attribute_intents.start, DT_SIZE_A);
               memcpy(extent, (data_t *)factor_concepts_extent, DT_SIZE_Ox((count_t)*factor_concepts_extent));
            }
            count_t size = 0, best_size = size;
            attribute_intents.iter = attribute_intents.start;
            while (true) {
               for (count_t j = 0, total = 0; j < context->dt_count_a; j++) for (int i = DATA_BITS - 1; i >= 0; i--) {
                  if (total >= context->attributes) goto skipout;
                  if (intent[j] & (BitU << i)) goto skip;
                  if (!(factor_concepts->iter[j] & (BitU << i))) goto skip;
                  if (size == 0 && c == last_c) {
                     memcpy(new_intent, attribute_intents.iter, DT_SIZE_A + DT_SIZE_O);
                     attribute_intents.iter += context->dt_count_a + context->objects + 1;
                  } else {
                     compute_closure_plus_attr(new_intent, new_extent, extent, intent, contexts[c], j, BitU << i, factors->concepts.min_support);
                     INC_COUNTER(CLOSURES);
                  }
                  if (c != 0) {
                     compute_closure_from_attrs(intent_new_parent_intent, intent_new_parent_extent, new_intent, contexts[c - 1]);
                     INC_COUNTER(CLOSURES);
                     _transform_objects_to_context(objects, new_extent, contexts[c - 1], contexts[c]);
                     compute_closure_from_objects(extent_new_parent_intent, extent_new_parent_extent, objects, contexts[c - 1]);
                     INC_COUNTER(CLOSURES);
                     compute_closure_masked_size(intent_new_parent_intent, extent_new_parent_extent, contexts[c - 1], &new_context, &new_size, NULL);
                  } else compute_closure_masked_size(new_intent, new_extent, context, &new_context, &new_size, NULL);
                  if (new_size > best_size) {
                     best_size = new_size;
                     SwapIntent(&new_intent, &best_intent);
                     SwapExtent(&new_extent, &best_extent);
                     if (c != 0) {
                        SwapIntent(&intent_new_parent_intent, &intent_best_parent_intent);
                        SwapExtent(&intent_new_parent_extent, &intent_best_parent_extent);
                        SwapIntent(&extent_new_parent_intent, &extent_best_parent_intent);
                        SwapExtent(&extent_new_parent_extent, &extent_best_parent_extent);
                     }
                  }
               skip:
                  total++;
               }
            skipout:
               if (best_size > size) {
                  size = best_size;
                  SwapIntent(&intent, &best_intent);
                  SwapExtent(&extent, &best_extent);
                  if (c != 0) {
                     SwapIntent(&intent_parent_intent, &intent_best_parent_intent);
                     SwapExtent(&intent_parent_extent, &intent_best_parent_extent);
                     SwapIntent(&extent_parent_intent, &extent_best_parent_intent);
                     SwapExtent(&extent_parent_extent, &extent_best_parent_extent);
                  }
               } else break;
            }
            if (size > factor_size) {
               factor_size = size;
               SwapIntent(&factor_intent, &intent);
               SwapExtent(&factor_extent, &extent);
               if (c != 0) {
                  SwapIntent(&intent_factor_parent_intent, &intent_parent_intent);
                  SwapExtent(&intent_factor_parent_extent, &intent_parent_extent);
                  SwapIntent(&extent_factor_parent_intent, &extent_parent_intent);
                  SwapExtent(&extent_factor_parent_extent, &extent_parent_extent);
               }
               factor_concept = factor_concepts->iter;
            }
         }
         if (factor_size == 0) break;
         new_context.table_entries -= factor_size;
         if (c != 0) save_concept_to_list(extent_factor_parent_intent, intent_factor_parent_extent, contexts[c - 1], new_factor_concepts, 0);
         else {
            ADD_COUNTER(UNCOVERED, -factor_size);
            SAVE_CONCEPT(factor_intent, factor_extent, context, &factors->concepts, CONCEPT_NEW);
            INC_COUNTER(FACTORS);
         }
         if (c != 0 ? new_context.table_entries == 0 : new_context.table_entries <= table_entries_percent) break;
         if (c != last_c) factor_concept[context->dt_count_a - 1] |= BitU;
         data_t *tmp_intent, **tmp_extent;
         if (c != 0) {
            tmp_intent = factor_intent, factor_intent = intent_factor_parent_intent;
            tmp_extent = factor_extent, factor_extent = extent_factor_parent_extent;
            context = contexts[c - 1];
         }
         for (count_t o = (count_t)*factor_extent; o > 0; o--) for (int i = 0; i < context->dt_count_a; i++)
            new_context.rows[(factor_extent[o] - *context->rows) / context->dt_count_a][i] &= ~factor_intent[i];
         if (c != 0) factor_intent = tmp_intent, factor_extent = tmp_extent, context = *contexts;
      }
      new_factor_concepts->end = new_factor_concepts->iter;
      SwapConcepts(&factor_concepts, &new_factor_concepts);
      factor_concepts->iter = factor_concepts->start;
      new_factor_concepts->iter = new_factor_concepts->start;
      c--;
   }
}

void find_factors_help(bool descr) {
   if (!descr)
      fprintf(stderr, " [-ness_iters]");
   else
      fprintf(stderr, "-ness_iters    maximal number of Ess context iterations, ess_iters = 0+, 0 = while changes, default 1\n\n");
}

int find_factors_process_args(int argc, char **argv) {
   int index = 0;
   if (argv[index][0] == '-') switch (argv[index][1]) {
      case 'n': ess_iters = atoi(argv[index++] + 2);
   }
   return index;
}

// CLI prints.
typedef enum {
   VERBOSITY_NONE = 0, VERBOSITY_OUTPUT, VERBOSITY_STATS,
   VERBOSITY_OUTPUT_STATS, VERBOSITY_INFO,
   VERBOSITY_OUTPUT_INFO
} verbosity_t;

int threshold = 100;
count_t min_support = 0;
concept_flags_t factor_output = CONCEPT_SAVE_ATTRIBS_ONLY;
context_sort_t context_sort = 0;
verbosity_t verbosity = VERBOSITY_OUTPUT;
FILE *input_file = NULL, *output_file = NULL;
count_t attr_offset = 0;

void print_context_info(context_t *context, char *name) {
   fprintf(stderr, "%s objects: %li\n%s attributes: %li\n%s table entries: %li\n%s fill ratio: %.3f%%\n", name, context->objects, name, context->attributes, name, context->table_entries, name, 100.0 * context->table_entries / (context->objects * context->attributes));
}

#ifdef STATS
void print_stats(stats_t *stats) {
   for (int i = 0; i < Counters; i++)
      if (CounterText[i] != NULL) fprintf(stderr, "%s: %li\n", CounterText[i], Counter[i]);
   int i = 1;
   for (; i < TimePos; i++) {
      int usec_less = Time[i].tv_usec < Time[i - 1].tv_usec ? 1 : 0;
      fprintf(stderr, "%s: %li.%06li s\n", TimeText[i], Time[i].tv_sec - Time[i - 1].tv_sec - usec_less, usec_less * 1000000 + Time[i].tv_usec - Time[i - 1].tv_usec);
   }
   i--;
   int usec_less = Time[i].tv_usec < Time[0].tv_usec ? 1 : 0;
   fprintf(stderr, "total time: %li.%06li s\n", Time[i].tv_sec - Time[0].tv_sec - usec_less, usec_less * 1000000 + Time[i].tv_usec - Time[0].tv_usec);
}
#endif

// CLI Boolean factors as formal concepts finding main, prints and help
#ifdef STATS
void print_factor_info(data_t *intent, data_t **extent, context_t *context, concept_flags_t flags, stats_t *stats) {
   fprintf(stderr, "factor %li: covered %li = %.3f%%", Counter[FACTORS], context->table_entries - Counter[UNCOVERED], 100.0 - 100.0 * Counter[UNCOVERED] / context->table_entries);
   if (Counter[OVERCOVERED] != 0) fprintf(stderr, ", overcovered %li = %.3f%%", Counter[OVERCOVERED], 100.0 * Counter[OVERCOVERED] / (context->objects * context->attributes - context->table_entries));
   fprintf(stderr, "\n");
}
#else
void print_factor_info(data_t *intent, data_t **extent, context_t *context, concept_flags_t flags) {
   static count_t i = 1;
   fprintf(stderr, "factor %li\n", i++);
}
#endif

void main_help(bool DoExit) {
   fprintf(stderr, "%s [-Vverbosity] [-attr_offset] [-Tthreshold] [-Smin_support] [-Oa|-Oo|-Of] [-sc|-sr|-sb]", program_name);
   find_factors_help(false);
   fprintf(stderr, " [input_filename [output_filename]]\n");
   fprintf(stderr,
      "\n"
      "-h             help (display this message)\n"
      "-Vverbosity    verbosity level, verbosity = 0-5, 0 = no output, 1 = factors output, 2 = counters & time stderr output, 3 = 1 + 2, 4 = 2 + info stderr output, 5 = 1 + 4, default 1\n"
      "-attr_offset   number of the first attribute in input, attr_offset = 0+, default 0\n"
   );
   fprintf(stderr,
      "-Tthreshold    sufficient factorization threshold in %%, threshold = 0-100, default 100\n"
      "-Smin_support  minimal support of factors, min_support = 0+, default 0\n"
      "-Oa|-Oo|-Of    output attributes | objects | factors (attributes | objects), default -Oa\n"
      "-sc|-sr|-sb    sort columns by support | rows lexicaly | both prior to computation\n"
   );
   find_factors_help(true);
   fprintf(stderr, "input_filename input context data file name\n");
   if (DoExit) exit(EXIT_SUCCESS);
}

int main_process_args(int argc, char **argv) {
   int index = 0;
   if (argv[index][0] == '-') switch (argv[index][1]) {
      case 'T': threshold = atoi(argv[index++] + 2); break;
      case 'S': min_support = atoi(argv[index++] + 2); break;
      case 'O': switch (argv[index++][2]) {
         case 'a': factor_output = CONCEPT_SAVE_ATTRIBS_ONLY; break;
         case 'o': factor_output = CONCEPT_SAVE_OBJECTS_ONLY; break;
         case 'f': factor_output = 0; break;
         default: return 0;
      }
      break;
      case 's': switch (argv[index++][2]) {
         case 'c': context_sort = CONTEXT_SORT_COLS; break;
         case 'r': context_sort = CONTEXT_SORT_ROWS; break;
         case 'b': context_sort = CONTEXT_SORT_COLS | CONTEXT_SORT_ROWS; break;
         default: return 0;
      }
      break;
      default: index += find_factors_process_args(argc - index, &argv[index]);
   }
   return index;
}

void main_program(void) {
#ifdef STATS
   stats_t *stats; init_stats(&stats, 1, 6, 10);
#endif
   SAVE_TIME("");
   io_t io; init_io(&io, (io_func_t *)read_file_to_io, input_file);
   context_t context; input_context_from_io(&context, &io, attr_offset);
   if (verbosity >= VERBOSITY_INFO) print_context_info(&context, "input");
   SAVE_TIME("input read time");
   if (context_sort != 0) sort_context(&context, context_sort);
   if (min_support != 0) {
      remove_low_support_attribs_from_context(&context, min_support);
      if (verbosity >= VERBOSITY_INFO) print_context_info(&context, "preprocessed");
   }
   SAVE_TIME("preprocessing time");
   SET_COUNTER_TEXT(FACTORS, "factors");
   SET_COUNTER_TEXT(CLOSURES, "closures");
   SET_COUNTER_TEXT(UNCOVERED, "uncovered entries");
   SET_COUNTER_TEXT(OVERCOVERED, "overcovered entries");
   free_io(&io);
   init_io(&io, (io_func_t *)write_file_from_io, output_file);
   factors_t factors; init_factors(&factors, threshold);
   if (verbosity % 2)
      init_concepts(&factors.concepts, min_support, (concept_save_func_t *)output_factor_to_io, &io, verbosity >= VERBOSITY_INFO ? (concept_info_func_t *)print_factor_info : NULL, factor_output);
   else
      init_concepts(&factors.concepts, min_support, NULL, NULL, verbosity >= VERBOSITY_INFO ? (concept_info_func_t *)print_factor_info : NULL, 0);
   find_factors(&context, &factors STATS_DATA_ARG);
   IO_FUNC(&io, OUTPUT_ALL);
   SAVE_TIME("find time");
   free_concepts(&factors.concepts);
   free_io(&io);
#ifdef STATS
   if (verbosity >= VERBOSITY_STATS) print_stats(stats);
   free_stats(&stats);
#endif
   destroy_context(&context);
}

// CLI main
int main(int argc, char **argv) {
   program_name = argv[0]; if (program_name == NULL || *program_name == '\0') program_name = "iteress";
   bool input_file_stdin = false;
   input_file = stdin, output_file = stdout;
   for (int index = 1; index < argc; )
      if (argv[index][0] == '-') switch (argv[index][1]) {
         case '\0': input_file_stdin = true, index++; break;
         case 'h': main_help(true); break;
         case 'V': verbosity = atoi(argv[index++] + 2); break;
         case '0': case '1': case '2': case '3': case '4':
         case '5': case '6': case '7': case '8': case '9':
            attr_offset = atoi(argv[index++] + 1);
         break;
         default: {
            int shift = main_process_args(argc - index, &argv[index]);
            if (shift == 0) main_help(false), index++; else index += shift;
         }
      } else {
         if (input_file == stdin && !input_file_stdin) input_file = fopen(argv[index++], "rb");
         else if (output_file == stdout) {
            if (input_file != NULL) output_file = fopen(argv[index++], "wb");
         } else {
            int shift = main_process_args(argc - index, &argv[index]);
            if (shift == 0) main_help(false), index++; else index += shift;
         }
      }
   if (input_file == NULL) { error("cannot open input data stream"); return EXIT_FAILURE; }
   if (output_file == NULL) { error("cannot open output data stream"); return EXIT_FAILURE; }
   main_program();
   fclose(input_file);
   fclose(output_file);
   return EXIT_SUCCESS;
}
