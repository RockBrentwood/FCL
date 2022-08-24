// PCbO: Parallel Close-by-One (AMAI Version; http://fcalgs.sourceforge.net/)
//
// Copyright (C) 2007-2009
// Petr Krajca, <petr.krajca@upol.cz>
// Jan Outrata, <jan.outrata@upol.cz>
// Vilem Vychodil, <vilem.vychodil@upol.cz>
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License version 2 as published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program;
// if not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// Users in academia are kindly asked to cite the following resources
// if the program is used to pursue any research activities which may result in publications:
//	Krajca P., Outrata J., Vychodil V.: Parallel Recursive Algorithm for FCA.
//	In: Proc. CLA 2008, CEUR WS, 433(2008), 71-82. ISBN 978-80-244-2111-7.
//	http://sunsite.informatik.rwth-aachen.de/Publications/CEUR-WS/Vol-433/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Configuration-dependent functions for mutexes and threads.
#ifdef WINNT
#   include <windows.h>
#   include <process.h>
typedef HANDLE ThreadIdT;
typedef unsigned __stdcall ThreadOpT;
const ThreadOpT ThreadNil = 0U;
typedef HANDLE MutExT;
// #   define INIT_MUTEX
#   define InitMutEx(M) ((M) = CreateMutex(NULL, FALSE, NULL));
#   define AcquireMutEx(M) WaitForSingleObject((M), INFINITE)
#   define ReleaseMutEx(M) ReleaseMutex((M))
#   define InitThread(Th, Op, Arg) ((Th) = (HANDLE)_beginthreadex(NULL, 0, (Op), (Arg), 0, NULL))
#   define JoinThread(Th) (WaitForSingleObject(Th, INFINITE), CloseHandle(Th))
#else
#   include <pthread.h>
typedef pthread_t ThreadIdT;
typedef void *ThreadOpT;
const ThreadOpT ThreadNil = NULL;
typedef pthread_mutex_t MutExT;
// The distribution version initialized mutexes statically for non-Windows, instead of dynamically with pthread_mutex_init().
// #   define INIT_MUTEX = PTHREAD_MUTEX_INITIALIZER
#   define InitMutEx(M) pthread_mutex_init(&(M), NULL)
#   define AcquireMutEx(M) pthread_mutex_lock(&(M))
#   define ReleaseMutEx(M) pthread_mutex_unlock(&(M))
#   define InitThread(Th, Op, Arg) pthread_create(&(Th), NULL, (Op), (Arg))
#   define JoinThread(Th) pthread_join(Th, NULL)
#endif

#define BitU(D)	(1UL << (D))
const unsigned long NilU = 0UL;
const size_t IntSize = sizeof(int);
#define DataN	(8*sizeof(unsigned long))

#define MaxNumSize	11
#define ExBufMax	(32*MaxNumSize)

struct { char Id[MaxNumSize]; int N; } *InTab;
int Atrs = 0, AtrN = 0;
int Objs = 0, ObjN = 0;
int Entries = 0;
int LoSup = 0;
unsigned long *Context, *(*AtrTab)[DataN];
int (*SupTab)[DataN];
unsigned long UpToBit[DataN];
int Atr0 = 0;
FILE *InF, *ExF;
int Noise = 1;

int ParLevel = 2;
int CPUs = 1;
int Threads;
ThreadIdT *ThreadId;
int *ThreadIx;
unsigned char **ThreadQ, **ThreadBegQ, **ThreadEndQ;
unsigned long **ThreadIn;
MutExT ExLock/* INIT_MUTEX*/;
struct StatT { int Closures, Concepts, QueueN; } *Counts, Count;

bool GetNumber(FILE *InF, int *ValueP) {
   *ValueP = -1;
   int Ch = fgetc(InF);
   for (; !isdigit(Ch); Ch = fgetc(InF))
      if (Ch == EOF) return false;
      else if (Ch == '\n') return true;
   for (*ValueP = 0; isdigit(Ch); Ch = fgetc(InF)) *ValueP = 10*(*ValueP) + Ch - '0';
   ungetc(Ch, InF);
   *ValueP -= Atr0;
   if (*ValueP < 0) fprintf(stderr, "Invalid input value: %i (minimum value is %i), quitting.\n", *ValueP + Atr0, Atr0), exit(EXIT_FAILURE);
   return true;
}

int *GrowBuffer(int *Buf, size_t N) {
   bool WasEmpty = Buf == NULL;
   Buf = WasEmpty? malloc(N*sizeof *Buf): realloc(Buf, N*sizeof *Buf);
   if (Buf == NULL) fprintf(stderr, "Cannot %s the input buffer, quitting.\n", WasEmpty? "allocate": "reallocate"), exit(EXIT_FAILURE);
   return Buf;
}

void GetContext(FILE *InF) {
   const size_t BufMax = 0x400;
// Read in the file.
   size_t CurMax = BufMax, CurN = 0;
   int *CurBuf = GrowBuffer(NULL, CurMax);
   Atrs = 0, Objs = 0;
   int ExValue = -1;
   for (int Value; GetNumber(InF, &Value); ) {
      if (Value >= Atrs) Atrs = Value + 1;
      else if (Value < 0) {
         if (ExValue < 0) continue;
         Objs++, Value = -1;
      }
      if (CurN >= CurMax) CurBuf = GrowBuffer(CurBuf, CurMax += BufMax);
      ExValue = CurBuf[CurN++] = Value;
   }
   if (ExValue >= 0) {
      Objs++;
      if (CurN >= CurMax) CurBuf = GrowBuffer(CurBuf, CurMax += BufMax);
      CurBuf[CurN++] = -1;
   }
// Create the context.
   AtrN = Atrs/DataN + 1, ObjN = Objs/DataN + 1;
   Context = calloc(AtrN*Objs, sizeof *Context);
   if (Context == NULL) fprintf(stderr, "Cannot allocate bitcontext, quitting.\n"), exit(EXIT_FAILURE);
   for (int n = 0, Row = 0; n < CurN; n++)
      if (CurBuf[n] < 0) Row++;
      else
         Context[Row*AtrN + CurBuf[n]/DataN] |= BitU(DataN - 1 - CurBuf[n]%DataN),
         Entries++;
   free(CurBuf);
}

void PutAtrs(const unsigned long *Set) {
   if (Noise < 1) return;
   bool First = true, Locked = false;
   char Buf[ExBufMax + MaxNumSize + 2], *BufP = Buf;
   for (int A = 0, C = 0; A < AtrN; A++) for (int D = DataN - 1; D >= 0; D--) {
      if (Set[A]&BitU(D)) {
         if (!First) *BufP++ = ' '; else First = false;
         strcpy(BufP, InTab[C].Id), BufP += InTab[C].N;
         if (BufP >= Buf + ExBufMax) {
            *BufP = '\0', BufP = Buf;
            if (!Locked) AcquireMutEx(ExLock), Locked = true;
            fputs(Buf, ExF);
         }
      }
      if (++C >= Atrs) goto Break;
   }
Break:
   *BufP++ = '\n', *BufP = '\0';
   if (!Locked) AcquireMutEx(ExLock);
   fputs(Buf, ExF);
   ReleaseMutEx(ExLock);
}

void PutContextInfo(void) {
   if (Noise >= 2) fprintf(stderr, "(:objects %6i :attributes %4i :entries %8i)\n", Objs, Atrs, Entries);
}

void PutThreadInfo(int T, struct StatT Stat) {
   if (Noise >= 2) fprintf(stderr, "(:proc %3i :closures %7i :concepts %7i :queue-length %3i)\n", T, Stat.Closures, Stat.Concepts, Stat.QueueN);
}

void PutInitialThreadInfo(int ParLevel, struct StatT Stat, int Level) {
   if (Noise >= 2) fprintf(stderr, "(:proc %3i :closures %7i :concepts %7i :levels %i :last-level-concepts %i)\n", 0, Stat.Closures, Stat.Concepts, ParLevel + 1, Level);
}

void MakeInTab(int N) {
   InTab = malloc(N*sizeof *InTab);
   for (int n = 0; n < N; n++) sprintf(InTab[n].Id, "%i", n), InTab[n].N = strlen(InTab[n].Id);
}

void InitializeAlgorithm(void) {
   for (int D0 = 0; D0 < DataN; D0++) {
      UpToBit[D0] = NilU;
      for (int D1 = DataN - 1; D1 > D0; D1--) UpToBit[D0] |= BitU(D1);
   }
   unsigned long *ColBuf = calloc(ObjN*DataN*AtrN, sizeof *ColBuf), *ColP = ColBuf;
   AtrTab = malloc(DataN*AtrN*sizeof *AtrTab), SupTab = malloc(DataN*AtrN*sizeof *SupTab);
   for (int N = 0; N < AtrN; N++) for (int D = DataN - 1; D >= 0; ColP += ObjN, D--) {
      unsigned long Mask = BitU(D);
      AtrTab[N][D] = ColP, SupTab[N][D] = 0;
      for (int O = 0, ON = N; O < Objs; O++, ON += AtrN)
         if (Context[ON]&Mask) ColP[O/DataN] |= BitU(O%DataN), SupTab[N][D]++;
   }
   MakeInTab(Atrs);
}

void Closure(unsigned long *In, unsigned long *Ex, unsigned long *ExEx, unsigned long *AtrEx, size_t *SupP) {
   memset(In, 0xff, AtrN*sizeof *In);
   if (AtrEx != NULL) {
      *SupP = 0;
      for (int O = 0; O < ObjN; O++) {
         Ex[O] = ExEx[O]&AtrEx[O];
         if (Ex[O] != NilU)
            for (int D = 0; D < DataN && (Ex[O] >> D) != NilU; D++)
               if (Ex[O]&BitU(D)) {
                  for (int A = 0, C = AtrN*(O*DataN + D); A < AtrN; A++, C++) In[A] &= Context[C];
                  ++*SupP;
               }
      }
   } else {
      memset(Ex, 0xff, ObjN*sizeof *Ex);
      for (int O = 0; O < Objs; O++) for (int A = 0; A < AtrN; A++) In[A] &= Context[AtrN*O + A];
   }
}

void ExpandNode(unsigned long *In, unsigned long *Ex, int I0, int D0, int Id) {
   size_t Sup = 0;
   int Total = (I0 + 1)*DataN - 1 - D0;
   unsigned long *NewIn = Ex + ObjN, *NewEx = NewIn + AtrN;
   for (; I0 < AtrN; D0 = DataN - 1, I0++) for (; D0 >= 0; Total++, D0--) {
      if (Total >= Atrs) goto Break;
      if ((In[I0]&BitU(D0)) || SupTab[I0][D0] < LoSup) continue;
      Closure(NewIn, NewEx, Ex, AtrTab[I0][D0], &Sup);
      Counts[Id].Closures++;
      if (Sup < LoSup) continue;
      if ((NewIn[I0] ^ In[I0])&UpToBit[D0]) continue;
      for (int I = 0; I < I0; I++)
         if (NewIn[I] ^ In[I]) goto Continue;
      Counts[Id].Concepts++;
      PutAtrs(NewIn);
      if (NewIn[AtrN - 1]&BitU(0)) continue;
      bool DoHi = D0 == 0;
      int I1 = DoHi? I0 + 1: I0, D1 = DoHi? DataN: D0;
      ExpandNode(NewIn, NewEx, I1, D1 - 1, Id);
   Continue: ;
   }
Break: ;
}

ThreadOpT ThreadOp(void *Arg) {
   for (int Id = *(int *)Arg; ThreadBegQ[Id] < ThreadQ[Id]; ) {
      memcpy(ThreadIn[Id], ThreadBegQ[Id], (AtrN + ObjN)*sizeof *ThreadIn[Id]);
      ThreadBegQ[Id] += (AtrN + ObjN)*sizeof *ThreadIn[Id];
      ExpandNode(ThreadIn[Id], ThreadIn[Id] + AtrN, *(int *)ThreadBegQ[Id], *(int *)(ThreadBegQ[Id] + IntSize), Id);
      ThreadBegQ[Id] += IntSize << 1;
   }
   return ThreadNil;
}

void ParExpandNode(unsigned long *In, unsigned long *Ex, int I0, int D0, int RecLevel, int Id) {
   static int Level = 0;
   if (RecLevel == ParLevel) {
      int T = Level%Threads;
      memcpy(ThreadQ[T], In, (AtrN + ObjN)*sizeof *ThreadIn[T]), ThreadQ[T] += (AtrN + ObjN)*sizeof *ThreadIn[T];
      *(int *)ThreadQ[T] = I0, ThreadQ[T] += sizeof I0;
      *(int *)ThreadQ[T] = D0, ThreadQ[T] += sizeof D0;
      Counts[T].QueueN++;
      if (ThreadQ[T] == ThreadEndQ[T]) {
         int Total = ThreadEndQ[T] - ThreadBegQ[T];
         ThreadBegQ[T] = realloc(ThreadBegQ[T], Total << 1);
         ThreadQ[T] = ThreadBegQ[T] + Total;
         ThreadEndQ[T] = ThreadBegQ[T] + (Total << 1);
      }
      Level++;
      return;
   }
   size_t Sup = 0;
   unsigned long *NewIn = Ex + ObjN, *NewEx = NewIn + AtrN;
   for (int Total = (I0 + 1)*DataN - 1 - D0; I0 < AtrN; D0 = DataN - 1, I0++) for (; D0 >= 0; D0--) {
      if (Total++ >= Atrs) goto Break;
      if ((In[I0]&BitU(D0)) || SupTab[I0][D0] < LoSup) continue;
      Closure(NewIn, NewEx, Ex, AtrTab[I0][D0], &Sup);
      Counts[Id].Closures++;
      if ((NewIn[I0] ^ In[I0])&UpToBit[D0]) continue;
      for (int I = 0; I < I0; I++)
         if (NewIn[I] ^ In[I]) goto Continue;
      if (Sup < LoSup) continue;
      Counts[Id].Concepts++;
      PutAtrs(NewIn);
      if (NewIn[AtrN - 1]&BitU(0)) continue;
      bool DoHi = D0 == 0;
      int I1 = DoHi? I0 + 1: I0, D1 = DoHi? DataN: D0;
      ParExpandNode(NewIn, NewEx, I1, D1 - 1, RecLevel + 1, Id);
   Continue: ;
   }
Break:
   if (RecLevel == 0) {
      PutInitialThreadInfo(ParLevel, Counts[0], Level);
      Count = Counts[0], Counts[0].Closures = 0, Counts[0].Concepts = 0;
      for (int T = 1; T < Threads; T++)
         if (ThreadBegQ[T] != ThreadQ[T]) InitThread(ThreadId[T], ThreadOp, &ThreadIx[T]);
      for (; ThreadBegQ[Id] < ThreadQ[Id]; ) {
         memcpy(ThreadIn[Id], ThreadBegQ[Id], (AtrN + ObjN)*sizeof *ThreadIn[Id]);
         ThreadBegQ[Id] += (AtrN + ObjN)*sizeof *ThreadIn[Id];
         ExpandNode(ThreadIn[Id], ThreadIn[Id] + AtrN, *(int *)ThreadBegQ[Id], *(int *)(ThreadBegQ[Id] + IntSize), Id);
         ThreadBegQ[Id] += IntSize << 1;
      }
   }
}

void FindAllIntents(void) {
   if (ParLevel <= 0) ParLevel = 1;
   if (ParLevel > Atrs) ParLevel = Atrs;
   Threads = CPUs; if (Threads <= 0) Threads = 1;
   if (Noise >= 3) fprintf(stderr, "INFO: running in %i threads\n", Threads);
   Counts = calloc(Threads, sizeof *Counts);
   ThreadId = calloc(Threads, sizeof *ThreadId);
   ThreadIx = malloc(Threads*sizeof *ThreadIx);
   ThreadQ = malloc(Threads*sizeof *ThreadQ);
   ThreadBegQ = malloc(Threads*sizeof *ThreadBegQ);
   ThreadEndQ = malloc(Threads*sizeof *ThreadEndQ);
   ThreadIn = malloc(Threads*sizeof *ThreadIn);
   int Qs = Atrs/Threads + 1, As = Atrs - ParLevel + 1;
   for (int T = 0; T < Threads; T++) {
      ThreadIx[T] = T;
      ThreadBegQ[T] = ThreadQ[T] = malloc(Qs*((AtrN + ObjN)*sizeof *ThreadIn[T] + (IntSize << 1)));
      ThreadEndQ[T] = ThreadBegQ[T] + Qs*((AtrN + ObjN)*sizeof *ThreadIn[T] + (IntSize << 1));
      ThreadIn[T] = malloc((AtrN + ObjN)*As*sizeof *ThreadIn[T]);
   }
   Closure(ThreadIn[0], ThreadIn[0] + AtrN, NULL, NULL, NULL);
   Counts[0].Closures++, Counts[0].Concepts++;
   PutAtrs(ThreadIn[0]);
   if (ThreadIn[0][AtrN - 1]&BitU(0)) return;
   ParExpandNode(ThreadIn[0], ThreadIn[0] + AtrN, 0, DataN - 1, 0, 0);
   PutThreadInfo(1, Counts[0]);
   for (int T = 1; T < Threads; T++) {
      if (ThreadId[T] != 0) JoinThread(ThreadId[T]);
      PutThreadInfo(T + 1, Counts[T]);
      Counts[0].Closures += Counts[T].Closures, Counts[0].Concepts += Counts[T].Concepts;
   }
   Counts[0].Closures += Count.Closures, Counts[0].Concepts += Count.Concepts;
   if (Noise >= 3)
      fprintf(stderr, "INFO: total %7i closures\n", Counts[0].Closures),
      fprintf(stderr, "INFO: total %7i concepts\n", Counts[0].Concepts);
}

int main(int AC, char **AV) {
   char *App = AC == 0? NULL: AV[0]; if (App == NULL || *App == '\0') App = "PCbO";
   InF = stdin, ExF = stdout;
   if (AC > 1) {
      int A = 1;
      for (; A < AC; A++) {
         char *Arg = AV[A];
         if (*Arg++ != '-' || *Arg == '\0') break;
         else switch (*Arg) {
            case 'h': fprintf(stderr, "synopsis: %s [-h] [-index] [-Smin-support] [-Vlevel] [-Pcpus] [-LParLev] [INPUT-FILE] [OUTPUT-FILE]\n", App); return EXIT_SUCCESS;
            case 'S': LoSup = atoi(++Arg); break;
            case 'P': CPUs = atoi(++Arg); break;
            case 'L': ParLevel = atoi(++Arg) - 1; break;
            case 'V': Noise = atoi(++Arg); break;
            default:
               Atr0 = atoi(Arg); if (Atr0 < 0) Atr0 = 0;
            break;
         }
      }
      char *InFile = A < AC? AV[A]: NULL;
      char *ExFile = A + 1 < AC? AV[A + 1]: NULL;
      if (InFile != NULL && *InFile != '-') InF = fopen(InFile, "rb");
      if (ExFile != NULL && *ExFile != '-') ExF = fopen(ExFile, "wb");
   }
   if (InF == NULL) { fprintf(stderr, "%s: cannot open input data stream\n", App); return EXIT_FAILURE; }
   if (ExF == NULL) { fprintf(stderr, "%s: open output data stream\n", App); return EXIT_FAILURE; }
   InitMutEx(ExLock);
   GetContext(InF);
   fclose(InF);
   PutContextInfo();
   InitializeAlgorithm();
   FindAllIntents();
   fclose(ExF);
   return EXIT_SUCCESS;
}
