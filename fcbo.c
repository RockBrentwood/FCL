// FCbO: Fast Close-by-One (INS Version; http://fcalgs.sourceforge.net/)
//
// Copyright (C) 2007-2010
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
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>

#define BitU(D)	(1UL << (D))
const unsigned long NilU = 0UL;
#define DataN	(8*sizeof(unsigned long))

int Atrs = 0, AtrN = 0;
int Objs = 0, ObjN = 0;
int Entries = 0;
int LoSup = 0;
unsigned long *Context, **AtrTab;
int *SupTab, *AtrNum;
unsigned long UpToBit[DataN];
int Atr0 = 0;
FILE *InF, *ExF;

int Noise = 1;

// Performance statistics.
int CurTotal = 0, CurClosures = 0;
int BadCanon = 0, BadFcbo = 0, BadSupport = 0;

struct timeval BegTime, CurTime, EndTime;

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
   SupTab = calloc(Atrs, sizeof *SupTab);
   for (int n = 0, Row = 0; n < CurN; n++)
      if (CurBuf[n] < 0) Row++;
      else
         Context[Row*AtrN + CurBuf[n]/DataN] |= BitU(DataN - 1 - CurBuf[n]%DataN),
         SupTab[CurBuf[n]]++, Entries++;
   free(CurBuf);
}

void MakeAtrs(void) {
   AtrNum = malloc(Atrs*sizeof *AtrNum);
   for (int A = 0; A < Atrs; A++) AtrNum[A] = A;
}

void PutAtrs(unsigned long *Set) {
   if (Noise < 1) return;
   bool First = true;
   for (int A = 0, C = 0; A < AtrN; A++) for (int D = DataN - 1; D >= 0; D--) {
      if (Set[A]&BitU(D)) {
         if (!First) fprintf(ExF, " "); else First = false;
         fprintf(ExF, "%i", AtrNum[C]);
      }
      if (++C >= Atrs) goto Break;
   }
Break:
   fprintf(ExF, "\n");
}

void PutContextInfo(void) {
   if (Noise >= 2) fprintf(stderr, "(:objects %6i :attributes %4i :entries %8i)\n", Objs, Atrs, Entries);
}

int DiffAtr(const void *XP, const void *YP) {
   int X = SupTab[*(int const *)XP]; bool LoX = X < LoSup;
   int Y = SupTab[*(int const *)YP]; bool LoY = Y < LoSup;
   return LoX != LoY? (LoY? -1: +1): X < Y? -1: X > Y? +1: 0;
}

int DiffObj(const void *XP, const void *YP) {
   unsigned long *X = (unsigned long *)XP, *Y = (unsigned long *)YP;
   for (int A = 0; A < AtrN; A++)
      if (X[A] < Y[A]) return -1; else if (X[A] > Y[A]) return +1;
   return 0;
}

void SortContext(void) {
   int ExAtrs = Atrs;
   Atrs = 0;
   for (int A = 0; A < ExAtrs; A++)
      if (SupTab[A] >= LoSup) Atrs++;
   qsort(AtrNum, ExAtrs, sizeof *AtrNum, DiffAtr);
   int ExAtrN = AtrN;
   AtrN = Atrs/DataN + 1;
   unsigned long *NewContext = calloc(AtrN*Objs, sizeof *NewContext);
   for (int A = 0, Z0 = 0, D1 = DataN - 1; A < ExAtrs; A++)
      if (SupTab[AtrNum[A]] >= LoSup) {
         int D = DataN - 1 - AtrNum[A]%DataN;
         for (int X = 0, Y = AtrNum[A]/DataN, Z = Z0; X < Objs; X++, Y += ExAtrN, Z += AtrN)
            if (Context[Y]&BitU(D)) NewContext[Z] |= BitU(D1);
         if (D1 > 0) D1--; else D1 = DataN - 1, Z0++;
      }
   free(Context), Context = NewContext;
   qsort(Context, Objs, AtrN*sizeof *Context, DiffObj);
}

void InitializeAlgorithm(void) {
   for (int D0 = 0; D0 < DataN; D0++) {
      UpToBit[D0] = NilU;
      for (int D1 = DataN - 1; D1 > D0; D1--) UpToBit[D0] |= BitU(D1);
   }
   unsigned long *ColBuf = calloc(ObjN*Atrs, sizeof *ColBuf), *ColP = ColBuf;
   AtrTab = malloc(Atrs*sizeof *AtrTab);
   for (int N = 0, A = 0; N < AtrN; N++) for (int D = DataN - 1; D >= 0; ColP += ObjN, A++, D--) {
      if (A >= Atrs) return;
      unsigned long Mask = BitU(D);
      AtrTab[A] = ColP;
      for (int O = 0, ON = N; O < Objs; O++, ON += AtrN)
         if (Context[ON]&Mask) ColP[O/DataN] |= BitU(O%DataN);
   }
}

void Closure(unsigned long *In, unsigned long *Ex, unsigned long *ExEx, unsigned long *AtrEx, int *SupP) {
   CurClosures++;
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

void ExpandNode(unsigned long *In, unsigned long *Ex, int I0, int D0, int *Starts, unsigned long **Imp, unsigned long ***ImpStack) {
   int Sup = 0;
   unsigned long ***ImpSP = ImpStack;
   int *StartP = Starts;
   int Total = (I0 + 1)*DataN - 1 - D0;
   unsigned long *NewInBase = malloc((AtrN + ObjN)*(Atrs - Total)*sizeof *NewInBase);
   unsigned long *NewIn = NewInBase, *NewEx = NewInBase + AtrN;
   for (; I0 < AtrN; D0 = DataN - 1, I0++) for (; D0 >= 0; Total++, D0--) {
      if (Total >= Atrs) goto Break;
      if (In[I0]&BitU(D0)) continue;
      if (Imp[Total] != NULL) {
         if (Imp[Total][I0]&~In[I0]&UpToBit[D0]) { BadFcbo++; continue; }
         for (int I = 0; I < I0; I++)
            if (Imp[Total][I]&~In[I]) { BadFcbo++; goto Continue0; }
      }
      Closure(NewIn, NewEx, Ex, AtrTab[Total], &Sup);
      if (Sup < LoSup) { BadSupport++; continue; }
      if ((NewIn[I0] ^ In[I0])&UpToBit[D0]) { BadCanon++; goto Continue1; }
      for (int I = 0; I < I0; I++)
         if (NewIn[I] ^ In[I]) { BadCanon++; goto Continue1; }
      PutAtrs(NewIn);
      CurTotal++;
      *StartP++ = I0, *StartP++ = D0;
      goto SkipOverElse;
   Continue1:
      *ImpSP++ = &Imp[Total], *ImpSP++ = (unsigned long **)Imp[Total];
      Imp[Total] = NewIn, NewIn[AtrN - 1] |= BitU(0);
   SkipOverElse:
      NewIn = NewEx + ObjN, NewEx = NewIn + AtrN;
   Continue0: ;
   }
Break:
   for (unsigned long *NewInP = NewInBase; NewInP != NewIn; NewInP += AtrN + ObjN)
      if (!(NewInP[AtrN - 1]&BitU(0))) {
         int S0 = *Starts++, S1 = *Starts++;
         bool DoHi = S1 == 0;
         int I1 = DoHi? S0 + 1: S0, D1 = DoHi? DataN: S1;
         ExpandNode(NewInP, NewInP + AtrN, I1, D1 - 1, StartP, Imp, ImpSP);
      }
   for (; ImpStack != ImpSP; ImpStack += 2) **ImpStack = (unsigned long *)*(ImpStack + 1);
   free(NewInBase);
}

void FindAllIntents(void) {
   unsigned long *In = malloc((AtrN + ObjN)*sizeof *In);
   unsigned long *Ex = In + AtrN;
   Closure(In, Ex, NULL, NULL, NULL);
   PutAtrs(In);
   CurTotal++;
   if (In[AtrN - 1]&BitU(0)) return;
   int *Starts = malloc((Atrs + 1)*Atrs*sizeof *Starts);
   unsigned long **Imp = calloc(Atrs, sizeof *Imp);
   unsigned long ***ImpStack = malloc((Atrs + 1)*Atrs*sizeof *ImpStack);
   ExpandNode(In, Ex, 0, DataN - 1, Starts, Imp, ImpStack);
}

int main(int AC, char **AV) {
   char *App = AC == 0? NULL: AV[0]; if (App == NULL || *App == '\0') App = "FCbO";
   InF = stdin, ExF = stdout;
   if (AC > 1) {
      int A = 1;
      for (; A < AC; A++) {
         char *Arg = AV[A];
         if (*Arg++ != '-' || *Arg == '\0') break;
         else switch (*Arg) {
            case 'h': fprintf(stderr, "synopsis: %s [-h] [-index] [-Smin-support] [-Vlevel] [INPUT-FILE] [OUTPUT-FILE]\n", App); return EXIT_SUCCESS;
            case 'S': LoSup = atoi(++Arg); break;
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
   if (Noise >= 3) gettimeofday(&BegTime, NULL);
   GetContext(InF);
   fclose(InF);
   PutContextInfo();
   if (Noise >= 3) gettimeofday(&CurTime, NULL);
   MakeAtrs();
   SortContext();
   InitializeAlgorithm();
   FindAllIntents();
   if (Noise >= 3) {
      gettimeofday(&EndTime, NULL);
      long dT = EndTime.tv_usec < CurTime.tv_usec? 1L: 0L;
      fprintf(stderr, "Inner time: %li.%06li s\n", EndTime.tv_sec - CurTime.tv_sec - dT, dT*1000000 + EndTime.tv_usec - CurTime.tv_usec);
      dT = EndTime.tv_usec < BegTime.tv_usec? 1L: 0L;
      fprintf(stderr, "Total time: %li.%06li s\n", EndTime.tv_sec - BegTime.tv_sec - dT, dT*1000000 + EndTime.tv_usec - BegTime.tv_usec);
   }
   if (Noise >= 2) fprintf(stderr, "(total: %i closures: %i fail_canon: %i fail_fcbo: %i fail_support: %i)\n", CurTotal, CurClosures, BadCanon, BadFcbo, BadSupport);
   fclose(ExF);
   return EXIT_SUCCESS;
}
