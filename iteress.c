// FCALGS: Formal Concept Analysis (FCA) Algorithms
// Copyright (C) 2007
// Jan Outrata, <jan.outrata@upol.cz>
// Vilem Vychodil, <vilem.vychodil@gmail.com>
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

// Basic data types.
typedef long CountT;
typedef char ClassT;

// Error handling.
char *App = NULL;

void Error(char *Format, ...) {
   fprintf(stderr, "%s: ", App);
   va_list AP; va_start(AP, Format), vfprintf(stderr, Format, AP), va_end(AP);
   fputc('\n', stderr);
}

#ifdef STATS
// Counters and times.
// For boolean factors as formal concepts.
CountT Factors = 0, Closures = 0, UnCovered = 0, OverCovered = 0;
// For the IterEss algorithm.
CountT EssContexts = 0;
#   define MaxTimes 10
struct timeval Time[MaxTimes];
char *TimeText[MaxTimes];
int Times = 0;
#   define SaveTime(Text) if (Times < MaxTimes) (gettimeofday(&Time[Times], NULL), TimeText[Times++] = Text)
#else
#   define SaveTime(Text)
#endif

// Input/Output interface.
const size_t IoBufMax = 0x100000;

typedef enum { SepOaIO = -3, SepClassIO = -2, EndSetIO = -1 } IoCharT;

typedef enum { ExFL = 1, InFL = 2 } IoFlagT;

typedef struct IoBufT {
   CountT *PutP; int PutN;
   CountT *GetP; int GetN;
   CountT *Buf; int BufN;
} *IoBufT;

typedef struct IoT *IoT;
typedef void (*IoOpT)(IoT Io, void *X, IoFlagT Flags);
struct IoT {
   struct IoBufT Buf;
   IoOpT Op; void *Arg;
};

IoBufT MakeIoBuf(IoT Io, int N) {
   if (Io->Buf.Buf != NULL) {
      CountT *ExBase = Io->Buf.Buf;
      Io->Buf.Buf = realloc(Io->Buf.Buf, N*sizeof *Io->Buf.Buf);
      if (Io->Buf.Buf != NULL && Io->Buf.Buf != ExBase) Io->Buf.PutP += Io->Buf.Buf - ExBase, Io->Buf.GetP += Io->Buf.Buf - ExBase;
   } else Io->Buf.Buf = Io->Buf.PutP = Io->Buf.GetP = malloc(N*sizeof *Io->Buf.Buf);
   if (Io->Buf.Buf == NULL) { Error("Cannot allocate I/O buffer"); return NULL; }
   Io->Buf.PutN += N - Io->Buf.BufN, Io->Buf.BufN = N;
   return &Io->Buf;
}

static inline void PutIO(IoT Io, CountT Value) {
   if (Io->Buf.PutN == 0) MakeIoBuf(Io, Io->Buf.BufN + IoBufMax);
   *Io->Buf.PutP++ = Value, Io->Buf.PutN--, Io->Buf.GetN++;
}

static inline CountT GetIO(IoT Io) {
   Io->Buf.GetN--;
   return *Io->Buf.GetP++;
}

static inline void OpIO(IoT Io, IoFlagT Flags) {
   if (Io->Op != NULL) Io->Op(Io, Io->Arg, Flags);
}

void MakeIO(IoT Io, IoOpT Op, void *Arg) {
   Io->Buf.PutP = Io->Buf.GetP = Io->Buf.Buf = NULL;
   Io->Buf.PutN = Io->Buf.GetN = Io->Buf.BufN = 0;
   Io->Op = Op, Io->Arg = Arg;
}

void FreeIO(IoT Io) {
   if (Io->Buf.Buf != NULL) free(Io->Buf.Buf), Io->Buf.Buf = NULL;
   MakeIO(Io, NULL, NULL);
}

// File input.
bool GetNumber(FILE *InF, CountT *ValueP) {
   *ValueP = EndSetIO;
   int Ch = ' ';
   while (Ch != EOF && !isdigit(Ch))
      if ((Ch = fgetc(InF)) == '\n') return true;
      else if (Ch == '|') { *ValueP = SepClassIO; return true; }
   if (Ch == EOF) return false;
   for (*ValueP = 0; isdigit(Ch); Ch = fgetc(InF)) *ValueP *= 10, *ValueP += Ch - '0';
   ungetc(Ch, InF);
   return true;
}

void ReadIO(IoT Io, FILE *InF, IoFlagT Flags) {
   CountT Obj = 0;
   PutIO(Io, Obj);
   CountT Atr = 0;
   if (!(Flags&InFL)) PutIO(Io, Atr);
   CountT Value = 0;
   ClassT ExClass = 0, Classes = 0;
   if (Flags&ExFL) PutIO(Io, Classes);
   int Labels = Flags&InFL;
   while (GetNumber(InF, &Value)) {
      if (Value == EndSetIO) {
         PutIO(Io, EndSetIO), Obj++;
         if (ExClass > Classes) Classes = ExClass;
         ExClass = 0, Labels = Flags&InFL;
      } else if (Value == SepClassIO) {
         Labels = InFL | ExFL;
         if (Flags&ExFL) PutIO(Io, SepClassIO);
      } else if (Labels != 0) {
         ExClass++;
         if (Flags&ExFL) PutIO(Io, Value);
      } else {
         if (Value >= Atr) Atr = Value + 1;
         PutIO(Io, Value);
      }
   }
   if (Value >= 0) {
      PutIO(Io, EndSetIO), Obj++;
      if (ExClass > Classes) Classes = ExClass;
   }
   *Io->Buf.GetP = Obj;
   if (Flags&InFL) Io->Buf.GetP[1] = Classes;
   else {
      Io->Buf.GetP[1] = Atr;
      if (Flags&InFL) Io->Buf.GetP[2] = Classes;
   }
}

// File output.
const size_t ExBufMax = 0x400;

void WriteIO(IoT Io, FILE *ExF, IoFlagT Flags) {
   if (Io->Buf.GetN < ExBufMax && !(Flags&ExFL)) return;
   bool First = true;
   while (Io->Buf.GetN != 0) {
      CountT Value = GetIO(Io);
      if (Value == EndSetIO) fprintf(ExF, "\n"), First = true;
      else {
         if (!First) fprintf(ExF, " "); else First = false;
         switch (Value) {
            case SepClassIO: case SepOaIO: fprintf(ExF, "|"); break;
            default: fprintf(ExF, "%li", Value);
         }
      }
   }
   Io->Buf.PutP = Io->Buf.GetP = Io->Buf.Buf;
   Io->Buf.PutN = Io->Buf.BufN, Io->Buf.GetN = 0;
}

// Formal Context.
typedef unsigned long DataT;
#define BitU(D)	((DataT)(1UL << (D)))
const DataT NilU = (DataT)0UL, AllU = (DataT)~(unsigned long)NilU;
#define DataN	(8*sizeof(DataT))
#define DataA	(Ctx->AtrN*sizeof(DataT))
#define DataO	((Ctx->Objs + 1)*sizeof(DataT *))
#define DataOx(X)	((CountT)((X) + 1)*sizeof(DataT *))

typedef struct ContextT {
   CountT Atrs, *AtrNum, AtrN;
   CountT Objs, *ObjNum;
   CountT Entries, *Sup;
   DataT *Table, **Row;
} *ContextT;

ContextT SortedCtx = NULL;

void MakeContext(ContextT Ctx, CountT Objs, CountT Atrs) {
   Ctx->Entries = 0;
   Ctx->Atrs = Atrs;
   Ctx->Sup = calloc(Atrs, sizeof *Ctx->Sup);
   Ctx->AtrNum = malloc(Atrs*sizeof *Ctx->AtrNum);
   for (CountT A = 0; A < Atrs; A++) Ctx->AtrNum[A] = A;
   Ctx->AtrN = Atrs/DataN + 1;
   Ctx->Table = calloc(Objs*Ctx->AtrN, sizeof *Ctx->Table);
   if (Ctx->Table == NULL) Error("Cannot allocate context");
   Ctx->Objs = Objs;
   Ctx->Row = malloc(Objs*sizeof *Ctx->Row);
   for (CountT O = 0; O < Objs; O++) Ctx->Row[O] = Ctx->Table + O*Ctx->AtrN;
   Ctx->ObjNum = malloc(Objs*sizeof *Ctx->ObjNum);
   for (CountT O = 0; O < Objs; O++) Ctx->ObjNum[O] = O;
}

void FreeContext(ContextT Ctx) {
   if (Ctx->Table != NULL) free(Ctx->Table);
   if (Ctx->Row != NULL) free(Ctx->Row);
   if (Ctx->Sup != NULL) free(Ctx->Sup);
   if (Ctx->AtrNum != NULL) free(Ctx->AtrNum);
   if (Ctx->ObjNum != NULL) free(Ctx->ObjNum);
}

void CopyContext(ContextT Ad, ContextT De) {
   MakeContext(Ad, De->Objs, De->Atrs);
   memcpy(Ad->Table, De->Table, Ad->AtrN*Ad->Objs*sizeof *Ad->Table);
   memcpy(Ad->Sup, De->Sup, Ad->Atrs*sizeof *Ad->Sup);
   Ad->Entries = De->Entries;
   memcpy(Ad->AtrNum, De->AtrNum, Ad->Atrs*sizeof *Ad->AtrNum);
   memcpy(Ad->ObjNum, De->ObjNum, Ad->Objs*sizeof *Ad->ObjNum);
}

void IoToContext(ContextT Ctx, IoT Io, CountT Atr0) {
   OpIO(Io, 0);
   CountT Obj = GetIO(Io), Val = GetIO(Io); MakeContext(Ctx, Obj, Val);
   Obj = 0;
   while (Io->Buf.GetN != 0) {
      Val = GetIO(Io);
      if (Val == EndSetIO) Obj++;
      else if ((Val -= Atr0) < 0) Error("Invalid input value %li (minimum value is %li)", Val + Atr0, Atr0);
      else
         Ctx->Row[Obj][Val/DataN] |= BitU(DataN - 1 - Val%DataN),
         Ctx->Sup[Val]++, Ctx->Entries++;
   }
}

int DiffAtr(const void *XP, const void *YP) {
   CountT X = SortedCtx->Sup[*(CountT const *)XP];
   CountT Y = SortedCtx->Sup[*(CountT const *)YP];
   return X < Y? -1: X > Y? +1: 0;
}

int DiffObj(const void *XP, const void *YP) {
   DataT const *Xr = SortedCtx->Row[*(CountT const *)XP];
   DataT const *Yr = SortedCtx->Row[*(CountT const *)YP];
   for (CountT A = 0; A < SortedCtx->AtrN; A++)
      if (Xr[A] < Yr[A]) return -1; else if (Xr[A] > Yr[A]) return +1;
   return 0;
}

int DiffItem(const void *XP, const void *YP) {
   DataT const *Xr = (DataT const *)XP;
   DataT const *Yr = (DataT const *)YP;
   for (CountT A = 0; A < SortedCtx->AtrN; A++)
      if (Xr[A] < Yr[A]) return -1; else if (Xr[A] > Yr[A]) return +1;
   return 0;
}

void SortContextAtr(ContextT Ctx, CountT *AtrNum) {
   DataT *Table = malloc(Ctx->AtrN*Ctx->Objs*sizeof *Table);
   memcpy(Table, Ctx->Table, Ctx->AtrN*Ctx->Objs*sizeof *Table);
   memset(Ctx->Table, 0, Ctx->AtrN*Ctx->Objs*sizeof *Ctx->Table);
   CountT *Sup = malloc(Ctx->Atrs*sizeof *Sup);
   memcpy(Sup, Ctx->Sup, Ctx->Atrs*sizeof *Sup);
   for (CountT N = 0, A = 0; N < Ctx->AtrN; N++) for (int D = DataN - 1; D >= 0; D--, A++) {
      if (A >= Ctx->Atrs) goto Break;
      for (CountT O = 0; O < Ctx->Objs; O++)
         if (Table[O*Ctx->AtrN + AtrNum[A]/DataN]&BitU(DataN - 1 - AtrNum[A]%DataN)) Ctx->Row[O][N] |= BitU(D);
      Ctx->Sup[A] = Sup[AtrNum[A]];
   }
Break:
   if (Ctx->AtrNum != AtrNum) memcpy(Ctx->AtrNum, AtrNum, Ctx->Atrs*sizeof *Ctx->AtrNum);
   free(Sup);
   free(Table);
}

typedef enum { SortByX = 1 << 0, SortByY = 1 << 1 } SortModeT;
SortModeT SortBy = 0;

void SortContext(ContextT Ctx, SortModeT SortBy) {
   if (SortBy&SortByX) {
      SortedCtx = Ctx;
      qsort(Ctx->AtrNum, Ctx->Atrs, sizeof *Ctx->AtrNum, DiffAtr);
      SortContextAtr(Ctx, Ctx->AtrNum);
   }
   if (SortBy&SortByY) {
      SortedCtx = Ctx;
      qsort(Ctx->ObjNum, Ctx->Objs, sizeof *Ctx->ObjNum, DiffObj);
      qsort(Ctx->Table, Ctx->Objs, Ctx->AtrN*sizeof *Ctx->Table, DiffItem);
   }
}

void PruneContextAtrs(ContextT Ctx, CountT LoSup) {
   CountT Atrs = 0;
   for (CountT A = 0; A < Ctx->Atrs; A++)
      if (Ctx->Sup[A] >= LoSup) Atrs++;
   struct ContextT Context; MakeContext(&Context, Ctx->Objs, Atrs);
   int D1 = DataN - 1;
   for (CountT N = 0, N1 = 0, A1 = 0, A = 0; N < Ctx->AtrN; N++) for (int D = DataN - 1; D >= 0; D--, A++) {
      if (A >= Ctx->Atrs) goto Break;
      else if (Ctx->Sup[A] < LoSup) continue;
      for (CountT O = 0; O < Ctx->Objs; O++)
         if (Ctx->Row[O][N]&BitU(D)) Context.Row[O][N1] |= BitU(D1);
      Context.Sup[A1] = Ctx->Sup[A];
      Context.Entries += Ctx->Sup[A];
      Context.AtrNum[A1++] = Ctx->AtrNum[A];
      if (--D1 < 0) N1++, D1 = DataN - 1;
   }
Break:
   memcpy(Context.ObjNum, Ctx->ObjNum, Ctx->Objs*sizeof *Context.ObjNum);
   FreeContext(Ctx), *Ctx = Context;
}

void FlipContext(ContextT Ctx) {
   struct ContextT Context; MakeContext(&Context, Ctx->Atrs, Ctx->Objs);
   for (CountT N = 0, A = 0; N < Ctx->AtrN; N++) for (int D = DataN - 1; D >= 0; D--, A++) {
      if (A >= Ctx->Atrs) goto Break;
      for (CountT O = 0; O < Ctx->Objs; O++)
         if (Ctx->Row[O][N]&BitU(D)) Context.Row[A][O/DataN] |= BitU(DataN - 1 - O%DataN), Context.Sup[O]++;
   }
Break:
   memcpy(Context.ObjNum, Ctx->AtrNum, Ctx->Atrs*sizeof *Context.ObjNum);
   memcpy(Context.AtrNum, Ctx->ObjNum, Ctx->Objs*sizeof *Context.AtrNum);
   FreeContext(Ctx), *Ctx = Context;
}

void MakeEssContext(ContextT EssCtx, ContextT Ctx) {
   CopyContext(EssCtx, Ctx);
   struct ContextT Context; CopyContext(&Context, Ctx), FlipContext(&Context);
   struct ContextT EssContext; CopyContext(&EssContext, &Context);
   ContextT CurCtx = Ctx, CurEssCtx = EssCtx;
   for (int N = 0; N < 2; N++) {
      for (CountT O0 = 0; O0 < CurCtx->Objs; O0++) for (CountT O1 = O0 + 1; O1 < CurCtx->Objs; O1++) {
         bool IsLt = false, IsGt = false;
         for (CountT A = 0; (!IsLt || !IsGt) && A < CurCtx->AtrN; A++)
            IsLt = IsLt || (~CurCtx->Row[O0][A]&CurCtx->Row[O1][A]),
            IsGt = IsGt || (CurCtx->Row[O0][A]&~CurCtx->Row[O1][A]);
         if (IsGt > IsLt)
            for (CountT A = 0; A < CurCtx->AtrN; A++) CurEssCtx->Row[O0][A] &= ~CurCtx->Row[O1][A];
         else if (IsLt > IsGt)
            for (CountT A = 0; A < CurCtx->AtrN; A++) CurEssCtx->Row[O1][A] &= ~CurCtx->Row[O0][A];
      }
      CurCtx = &Context, CurEssCtx = &EssContext;
   }
   FreeContext(&Context);
   FlipContext(&EssContext);
   memset(EssCtx->Sup, 0, Ctx->Atrs*sizeof *EssCtx->Sup);
   EssCtx->Entries = 0;
   for (CountT O = 0; O < Ctx->Objs; O++) {
      for (CountT N = 0, A = 0; N < Ctx->AtrN; N++) {
         EssCtx->Row[O][N] &= EssContext.Row[O][N];
         for (int D = DataN - 1; D >= 0; D--, A++) {
            if (A >= Ctx->Atrs) goto Break;
            if (EssCtx->Row[O][N]&BitU(D)) EssCtx->Sup[A]++, EssCtx->Entries++;
         }
      }
   Break: ;
   }
   FreeContext(&EssContext);
}

void ObjToContext(DataT **ObjsP, DataT **DeObj, ContextT Ctx, ContextT DeCtx) {
   *ObjsP = NULL;
   for (CountT O = (CountT)*DeObj++; O > 0; DeObj++, O--)
      if ((*DeObj - *DeCtx->Row)/DeCtx->AtrN < Ctx->Objs)
         *ObjsP = (DataT *)((CountT)*ObjsP + 1),
         ObjsP[(CountT)*ObjsP] = Ctx->Row[(*DeObj - *DeCtx->Row)/DeCtx->AtrN];
}

CountT TableEntriesPercent(CountT Entries, int Percent) { return Percent/10*Entries/10 + Percent%10*Entries/100; }

// Formal concept and concepts.
typedef enum { NewCP = 1 << 0, AtrOnlyCP = 1 << 1, ObjOnlyCP = 1 << 2 } ConceptFlagT;
typedef struct ConceptList { DataT *Beg, *Cur, *End; } *ConceptList;
typedef void (*SaveConceptOpT)(DataT *In, DataT **Ex, ContextT Ctx, IoT X, ConceptFlagT Flags);
typedef void (*InfoConceptOpT)(DataT *In, DataT **Ex, ContextT Ctx, ConceptFlagT Flags);

typedef struct ConceptT {
   CountT LoSup;
   SaveConceptOpT SaveOp;
   IoT SaveArg;
   InfoConceptOpT InfoOp;
   ConceptFlagT Flags;
} *ConceptT;

void ClosurePlusAtr(DataT *In, DataT **Ex, DataT **ExEx, DataT *ExIn, ContextT Ctx, CountT AtrData, DataT AtrMask, CountT LoSup) {
#ifdef STATS
   Closures++;
#endif
   DataT Data = 0;
   memset(In, 0xff, DataA);
   if (ExEx != NULL) {
      for (CountT O1 = (CountT)*ExEx++, O = O1; O > 0; ExEx++, O--)
         if ((*ExEx)[AtrData]&AtrMask) Ex[(CountT)++Data] = *ExEx;
         else if (--O1 < LoSup) { *Ex = (DataT *)Data; return; }
      *Ex = (DataT *)Data;
      for (CountT A = 0; A < Ctx->AtrN; A++, In++) {
         Data = *In;
         if (Data != 0 && (ExIn[A] ^ AllU)) for (CountT O = (CountT)*Ex; Data && O > 0; O--) Data &= Ex[O][A];
         *In = Data;
      }
   } else {
      *Ex = (DataT *)Ctx->Objs;
      for (CountT O = 0; O < Ctx->Objs; O++) {
         Ex[O + 1] = Ctx->Row[O];
         for (CountT A = 0; A < Ctx->AtrN; A++) In[A] &= Ctx->Row[O][A];
      }
   }
}

void AtrToEx(DataT **Ex, DataT *Atr, ContextT Ctx) {
   DataT Data = 0;
   for (CountT O = 0; O < Ctx->Objs; O++) {
      for (CountT A = 0; A < Ctx->AtrN; A++)
         if (Atr[A]&~(Ctx->Row[O][A])) goto Continue;
      Ex[(CountT)++Data] = Ctx->Row[O];
   Continue: ;
   }
   *Ex = (DataT *)Data;
}

void ObjToIn(DataT *In, DataT **Objs, ContextT Ctx) {
   memset(In, 0xff, DataA);
   for (CountT A = 0; A < Ctx->AtrN; A++, In++) {
      DataT Data = *In;
      if (Data != 0)
         for (CountT O = (CountT)*Objs; Data && O > 0; O--) Data &= Objs[O][A];
      *In = Data;
   }
}

static inline void ClosureFromAtr(DataT *In, DataT **Ex, DataT *Atrs, ContextT Ctx) {
#ifdef STATS
   Closures++;
#endif
   AtrToEx(Ex, Atrs, Ctx), ObjToIn(In, Ex, Ctx);
}

static inline void ClosureFromObj(DataT *In, DataT **Ex, DataT **Objs, ContextT Ctx) {
#ifdef STATS
   Closures++;
#endif
   ObjToIn(In, Objs, Ctx), AtrToEx(Ex, In, Ctx);
}

void AtrConcepts(DataT *In, ContextT Ctx, CountT LoSup) {
   DataT *MaxIn = malloc(DataA + DataO);
   DataT **MaxEx = (DataT **)(MaxIn + Ctx->AtrN);
   ClosurePlusAtr(MaxIn, MaxEx, NULL, NULL, Ctx, 0, 0, LoSup);
   DataT **Ex = (DataT **)(In + Ctx->AtrN);
   for (CountT N = 0, A = 0; N < Ctx->AtrN; N++) for (int D = DataN - 1; D >= 0; A++, D--) {
      if (A >= Ctx->Atrs) goto Break;
      ClosurePlusAtr(In, Ex, MaxEx, MaxIn, Ctx, N, BitU(D), LoSup);
      In = (DataT *)(Ex + Ctx->Objs + 1), Ex = (DataT **)(In + Ctx->AtrN);
   }
Break:
   free(MaxIn);
}

void AtrsToIO(DataT *Set, ContextT Ctx, IoT Io) {
   for (CountT N = 0, A = 0; N < Ctx->AtrN; N++) for (DataT D = BitU(DataN - 1); D; D >>= 1) {
      if (Set[N]&D) PutIO(Io, Ctx->AtrNum[A]);
      if (++A >= Ctx->Atrs) goto Break;
   }
Break: ;
}

void ObjsToIO(DataT **Set, ContextT Ctx, IoT Io) {
   for (CountT O = (CountT)*Set++; O > 0; Set++, O--) PutIO(Io, Ctx->ObjNum[(CountT)(*Set - *Ctx->Row)/Ctx->AtrN]);
}

void ListConcepts(DataT *In, DataT **Ex, ContextT Ctx, ConceptList List, ConceptFlagT Flags) {
   if (List->Cur + Ctx->AtrN + (CountT)*Ex + 1 > List->End) {
      CountT Length = List->Cur - List->Beg;
      List->Beg = realloc(List->Beg, (Length << 1)*sizeof *List->Beg);
      List->Cur = List->Beg + Length;
      List->End = List->Beg + (Length << 1);
   }
   if (!(Flags&ObjOnlyCP)) memcpy(List->Cur, In, DataA), List->Cur += Ctx->AtrN;
   if (!(Flags&AtrOnlyCP)) memcpy(List->Cur, Ex, DataOx((CountT)*Ex)), List->Cur += (CountT)*Ex + 1;
}

// Boolean factors as formal concepts.
void MaskedSizeClosure(DataT *In, DataT **Ex, ContextT Ctx, ContextT MaskCtx, CountT *NP, CountT *OverNP) {
   *NP = 0;
   if (OverNP != NULL) *OverNP = 0;
   for (CountT O = (CountT)*Ex++; O > 0; Ex++, O--) {
      CountT N = 0, OverN = 0;
      for (CountT A = 0; A < Ctx->AtrN; A++) {
         DataT Cell = In[A]&MaskCtx->Row[(*Ex - *Ctx->Row)/Ctx->AtrN][A];
         for (int D = 0; D < DataN && Cell; Cell >>= BitU(0), D++)
            if (Cell&BitU(0)) {
               if (Ctx->Row[(*Ex - *Ctx->Row)/Ctx->AtrN][A]&BitU(D)) N++; else OverN++;
            }
      }
      *NP += N;
      if (OverNP != NULL) *OverNP += OverN;
   }
}

void FactorToIO(DataT *In, DataT **Ex, ContextT Ctx, IoT Io, ConceptFlagT Flags) {
   if (!(Flags&ObjOnlyCP)) AtrsToIO(In, Ctx, Io);
   if (!(Flags&AtrOnlyCP)) {
      if (!(Flags&ObjOnlyCP)) PutIO(Io, SepOaIO);
      ObjsToIO(Ex, Ctx, Io);
   }
   PutIO(Io, EndSetIO), OpIO(Io, 0);
}

// IterEss algorithm.
int EssN = 1;

static inline void SwapIntent(DataT **AP, DataT **BP) {
   DataT *A = *AP, *B = *BP;
   *AP = B, *BP = A;
}

static inline void SwapExtent(DataT ***AP, DataT ***BP) {
   DataT **A = *AP, **B = *BP;
   *AP = B, *BP = A;
}

static inline void SwapConcepts(ConceptList *AP, ConceptList *BP) {
   ConceptList A = *AP, B = *BP;
   *AP = B, *BP = A;
}

void FindFactors(ContextT Ctx, int Tiny, ConceptT Cpt) {
   CountT Percent = TableEntriesPercent(Ctx->Entries, 100 - Tiny);
   int ContextN = 8;
   ContextT *CtxTab = malloc(ContextN*sizeof *CtxTab);
   *CtxTab = Ctx;
   CountT C = 0;
   do {
      if (++C == ContextN) ContextN <<= 1, CtxTab = realloc(CtxTab, ContextN*sizeof *CtxTab);
      CtxTab[C] = malloc(sizeof *CtxTab[C]);
      MakeEssContext(CtxTab[C], CtxTab[C - 1]);
   } while ((EssN == 0 || C < EssN) && CtxTab[C]->Entries != CtxTab[C - 1]->Entries);
   if (CtxTab[C]->Entries == CtxTab[C - 1]->Entries && C > 1) C--;
   CountT ExC = C;
#ifdef STATS
   SaveTime("Ess contexts time");
   EssContexts = ExC;
#endif
   DataT *AtrInBeg = malloc((DataA + DataO)*(Ctx->Atrs + 12) + DataO), *AtrInCur = AtrInBeg;
   DataT *In = (DataT *)(AtrInBeg + (Ctx->AtrN + Ctx->Objs + 1)*Ctx->Atrs), **Ex = (DataT **)(In + Ctx->AtrN);
   DataT *NewIn = (DataT *)(Ex + Ctx->Objs + 1), **NewEx = (DataT **)(NewIn + Ctx->AtrN);
   DataT *OptIn = (DataT *)(NewEx + Ctx->Objs + 1), **OptEx = (DataT **)(OptIn + Ctx->AtrN);
   DataT *InIn = (DataT *)(OptEx + Ctx->Objs + 1), **InEx = (DataT **)(InIn + Ctx->AtrN);
   DataT *NewInIn = (DataT *)(InEx + Ctx->Objs + 1), **NewInEx = (DataT **)(NewInIn + Ctx->AtrN);
   DataT *OptInIn = (DataT *)(NewInEx + Ctx->Objs + 1), **OptInEx = (DataT **)(OptInIn + Ctx->AtrN);
   DataT *ExIn = (DataT *)(OptInEx + Ctx->Objs + 1), **ExEx = (DataT **)(ExIn + Ctx->AtrN);
   DataT *NewExIn = (DataT *)(ExEx + Ctx->Objs + 1), **NewExEx = (DataT **)(NewExIn + Ctx->AtrN);
   DataT *OptExIn = (DataT *)(NewExEx + Ctx->Objs + 1), **OptExEx = (DataT **)(OptExIn + Ctx->AtrN);
   DataT *FacIn = (DataT *)(OptExEx + Ctx->Objs + 1), **FacEx = (DataT **)(FacIn + Ctx->AtrN);
   DataT *FacInIn = (DataT *)(FacEx + Ctx->Objs + 1), **FacInEx = (DataT **)(FacInIn + Ctx->AtrN);
   DataT *FacExIn = (DataT *)(FacInEx + Ctx->Objs + 1), **FacExEx = (DataT **)(FacExIn + Ctx->AtrN);
   DataT **ObjTab = (DataT **)(FacExEx + Ctx->Objs + 1);
   struct ConceptList ConceptsPair[2];
   ConceptList FacCpt = &ConceptsPair[0];
   FacCpt->Cur = FacCpt->Beg = malloc(DataA + DataO);
   FacCpt->End = FacCpt->Beg + Ctx->AtrN + Ctx->Objs + 1;
//(@) Closures++; was not executed with this, in the original.
   ClosurePlusAtr(FacCpt->Beg, (DataT **)(FacCpt->Beg + Ctx->AtrN), NULL, NULL, Ctx, 0, 0, Cpt->LoSup);
   memset(FacCpt->Beg, 0xff, DataA);
   FacCpt->Beg[Ctx->AtrN - 1] &= ~BitU(0);
   ConceptList NewCpt = &ConceptsPair[1];
   NewCpt->Cur = NewCpt->Beg = malloc((DataA + DataO)*Ctx->Atrs);
   NewCpt->End = NewCpt->Beg + (Ctx->AtrN + Ctx->Objs + 1)*Ctx->Atrs;
#ifdef STATS
   Factors = 0, UnCovered = Ctx->Entries;
#endif
   DataT *FactorConcept = NULL;
   for (; C >= 0; C--) {
      if (C == 0) SaveTime("Ess factors time");
      struct ContextT NewContext; CopyContext(&NewContext, CtxTab[C]);
      if (C == ExC)
         AtrConcepts(AtrInBeg, CtxTab[C], Cpt->LoSup);
      else
         ClosurePlusAtr(AtrInBeg, (DataT **)(AtrInBeg + Ctx->AtrN), NULL, NULL, CtxTab[C], 0, 0, Cpt->LoSup);
      while (true) {
         CountT FactorN = 0;
         DataT **FacCptEx;
         for (FacCpt->Cur = FacCpt->Beg; FacCpt->Cur < FacCpt->End; FacCpt->Cur = (DataT *)(FacCptEx + (CountT)*FacCptEx + 1)) {
            FacCptEx = (DataT **)(FacCpt->Cur + Ctx->AtrN);
            if (C == ExC) memset(In, 0, DataA + DataO);
            else if (FacCpt->Cur[Ctx->AtrN - 1]&BitU(0)) continue;
            else memcpy(In, AtrInBeg, DataA), memcpy(Ex, (DataT *)FacCptEx, DataOx((CountT)*FacCptEx));
            CountT F = 0, OptF = F;
            AtrInCur = AtrInBeg;
            while (true) {
               for (CountT N = 0, A = 0; N < Ctx->AtrN; N++) for (int D = DataN - 1; D >= 0; A++, D--) {
                  if (A >= Ctx->Atrs) goto Break;
                  else if ((In[N] | ~FacCpt->Cur[N])&BitU(D)) continue;
                  if (F == 0 && C == ExC)
                     memcpy(NewIn, AtrInCur, DataA + DataO), AtrInCur += Ctx->AtrN + Ctx->Objs + 1;
                  else
                     ClosurePlusAtr(NewIn, NewEx, Ex, In, CtxTab[C], N, BitU(D), Cpt->LoSup);
                  CountT NewF;
                  if (C > 0) {
                     ClosureFromAtr(NewInIn, NewInEx, NewIn, CtxTab[C - 1]);
                     ObjToContext(ObjTab, NewEx, CtxTab[C - 1], CtxTab[C]);
                     ClosureFromObj(NewExIn, NewExEx, ObjTab, CtxTab[C - 1]);
                     MaskedSizeClosure(NewInIn, NewExEx, CtxTab[C - 1], &NewContext, &NewF, NULL);
                  } else MaskedSizeClosure(NewIn, NewEx, Ctx, &NewContext, &NewF, NULL);
                  if (NewF > OptF) {
                     OptF = NewF;
                     SwapIntent(&NewIn, &OptIn), SwapExtent(&NewEx, &OptEx);
                     if (C > 0)
                        SwapIntent(&NewInIn, &OptInIn), SwapExtent(&NewInEx, &OptInEx),
                        SwapIntent(&NewExIn, &OptExIn), SwapExtent(&NewExEx, &OptExEx);
                  }
               }
            Break:
               if (OptF > F) {
                  F = OptF;
                  SwapIntent(&In, &OptIn), SwapExtent(&Ex, &OptEx);
                  if (C > 0)
                     SwapIntent(&InIn, &OptInIn), SwapExtent(&InEx, &OptInEx),
                     SwapIntent(&ExIn, &OptExIn), SwapExtent(&ExEx, &OptExEx);
               } else break;
            }
            if (F > FactorN) {
               FactorN = F;
               SwapIntent(&FacIn, &In), SwapExtent(&FacEx, &Ex);
               if (C > 0)
                  SwapIntent(&FacInIn, &InIn), SwapExtent(&FacInEx, &InEx),
                  SwapIntent(&FacExIn, &ExIn), SwapExtent(&FacExEx, &ExEx);
               FactorConcept = FacCpt->Cur;
            }
         }
         if (FactorN == 0) break;
         NewContext.Entries -= FactorN;
         if (C > 0) ListConcepts(FacExIn, FacInEx, CtxTab[C - 1], NewCpt, 0);
         else {
#ifdef STATS
            UnCovered += -FactorN;
#endif
            if ((Cpt)->SaveOp != NULL) (Cpt)->SaveOp(FacIn, FacEx, Ctx, (Cpt)->SaveArg, (Cpt)->Flags | NewCP);
            if ((Cpt)->InfoOp != NULL) (Cpt)->InfoOp(FacIn, FacEx, Ctx, (Cpt)->Flags | NewCP);
#ifdef STATS
            Factors++;
#endif
         }
         if (C > 0? NewContext.Entries == 0: NewContext.Entries <= Percent) break;
         if (C != ExC) FactorConcept[Ctx->AtrN - 1] |= BitU(0);
         DataT *TmpIn, **TmpEx;
         if (C > 0) {
            TmpIn = FacIn, FacIn = FacInIn;
            TmpEx = FacEx, FacEx = FacExEx;
            Ctx = CtxTab[C - 1];
         }
         for (CountT O = (CountT)*FacEx; O > 0; O--) for (int N = 0; N < Ctx->AtrN; N++)
            NewContext.Row[(FacEx[O] - *Ctx->Row)/Ctx->AtrN][N] &= ~FacIn[N];
         if (C > 0) FacIn = TmpIn, FacEx = TmpEx, Ctx = *CtxTab;
      }
      NewCpt->End = NewCpt->Cur;
      SwapConcepts(&FacCpt, &NewCpt);
      FacCpt->Cur = FacCpt->Beg;
      NewCpt->Cur = NewCpt->Beg;
   }
}

// CLI prints.
int Tiny = 100;
CountT LoSup = 0;
ConceptFlagT FactorMode = AtrOnlyCP;
FILE *InF = NULL, *ExF = NULL;
CountT Atr0 = 0;

typedef enum { ExV = 1 << 0, StatV = 1 << 1, InfoV = 1 << 2 } NoiseModeT;
NoiseModeT Noise = ExV;

NoiseModeT CharToNoiseMode(char Ch) {
   return !isdigit(Ch) || Ch > '5'? 0: Ch - '0';
}

void PutContextInfo(ContextT Ctx, char *Id) {
   fprintf(stderr, "%s objects: %li\n%s attributes: %li\n%s table entries: %li\n%s fill ratio: %.3f%%\n", Id, Ctx->Objs, Id, Ctx->Atrs, Id, Ctx->Entries, Id, 100.0*Ctx->Entries/(Ctx->Objs*Ctx->Atrs));
}

#ifdef STATS
void PutStats() {
   fprintf(stderr, "factors: %li\n", Factors);
   fprintf(stderr, "closures: %li\n", Closures);
   fprintf(stderr, "uncovered entries: %li\n", UnCovered);
   fprintf(stderr, "overcovered entries: %li\n", OverCovered);
   fprintf(stderr, "Ess contexts: %li\n", EssContexts);
   for (int T = 1; T < Times; T++) {
      int usec_less = Time[T].tv_usec < Time[T - 1].tv_usec? 1: 0;
      fprintf(stderr, "%s: %li.%06li s\n", TimeText[T], Time[T].tv_sec - Time[T - 1].tv_sec - usec_less, usec_less*1000000 + Time[T].tv_usec - Time[T - 1].tv_usec);
   }
   int T = Times > 0? Times - 1: 0;
   int usec_less = Time[T].tv_usec < Time[0].tv_usec? 1: 0;
   fprintf(stderr, "total time: %li.%06li s\n", Time[T].tv_sec - Time[0].tv_sec - usec_less, usec_less*1000000 + Time[T].tv_usec - Time[0].tv_usec);
}
#endif

// CLI Boolean factors as formal concepts finding main, prints and help.
#ifdef STATS
void PutFactorInfo(DataT *In, DataT **Ex, ContextT Ctx, ConceptFlagT Flags) {
   fprintf(stderr, "factor %li: covered %li = %.3f%%", Factors, Ctx->Entries - UnCovered, 100.0 - 100.0*UnCovered/Ctx->Entries);
   if (OverCovered > 0) fprintf(stderr, ", overcovered %li = %.3f%%", OverCovered, 100.0*OverCovered/(Ctx->Objs*Ctx->Atrs - Ctx->Entries));
   fprintf(stderr, "\n");
}
#else
void PutFactorInfo(DataT *In, DataT **Ex, ContextT Ctx, ConceptFlagT Flags) {
   static CountT F = 1;
   fprintf(stderr, "factor %li\n", F++);
}
#endif

void Usage(bool DoExit) {
   fprintf(stderr,
      "%s [-Vlevel] [-attr_offset] [-Tthreshold] [-Smin_support] [-Oa|-Oo|-Of] [-sc|-sr|-sb] [-ness_iters] [input_file [output_file]]\n"
      "Options:"
      "-h          help (display this message)\n"
      "-Vn         verbosity level n = 0-5, 0 = no output, 1/3/5 = factors output, 2/3 = counters & time stderr output, 4/5 = info stderr output, default 1\n"
      "-n          the first attribute in the input, n = 0+, default 0\n"
      "-Tn         sufficient factorization threshold in %%, n = 0-100, default 100\n"
      "-Sn         minimal support of factors, n = 0+, default 0\n"
      "-Oa|-Oo|-Of output attributes | objects | factors (attributes | objects), default -Oa\n"
      "-sc|-sr|-sb sort columns by support | rows lexicaly | both prior to computation\n"
      "-nn         maximal number of Ess context iterations, n = 0+, 0 = while changes, default 1\n\n"
      "input_file  input context data file name\n"
      "output_file output context data file name\n",
      App
   );
   if (DoExit) exit(EXIT_SUCCESS);
#if 0 //(@) Present in the original, possibly by mistake.
   exit(EXIT_FAILURE);
#endif
}

bool GetArg(char *Arg) {
   if (Arg[0] == '-') switch (Arg[1]) {
      case 'T': Tiny = atoi(&Arg[2]); break;
      case 'S': LoSup = atoi(&Arg[2]); break;
      case 'O': switch (Arg[2]) {
         case 'a': FactorMode = AtrOnlyCP; break;
         case 'o': FactorMode = ObjOnlyCP; break;
         case 'f': FactorMode = 0; break;
         default: return false;
      }
      break;
      case 's': switch (Arg[2]) {
         case 'c': SortBy = SortByX; break;
         case 'r': SortBy = SortByY; break;
         case 'b': SortBy = SortByX | SortByY; break;
         default: return false;
      }
      break;
      case 'n': EssN = atoi(&Arg[2]); break;
      default: return false;
   }
   return true;
}

// CLI main.
int main(int AC, char **AV) {
   App = AC == 0? NULL: AV[0]; if (App == NULL || *App == '\0') App = "IterEss";
   bool IsStdIn = false;
   InF = stdin, ExF = stdout;
   for (int A = 1; A < AC; ) {
      char *Arg = AV[A];
      if (Arg[0] == '-') switch (Arg[1]) {
         case '\0': IsStdIn = true, A++; break;
         case 'h': Usage(true); break;
         case 'V': Noise = CharToNoiseMode(Arg[2]), A++; break;
         case '0': case '1': case '2': case '3': case '4':
         case '5': case '6': case '7': case '8': case '9':
            Atr0 = atoi(&Arg[1]), A++;
         break;
         default:
            if (!GetArg(Arg)) Usage(false);
            A++;
         break;
      } else if (InF == stdin && !IsStdIn) InF = fopen(Arg, "rb"), A++;
      else if (ExF == stdout) {
         if (InF != NULL) ExF = fopen(Arg, "wb"), A++;
      } else {
         if (!GetArg(Arg)) Usage(false);
         A++;
      }
   }
   if (InF == NULL) { Error("Cannot open input data stream"); return EXIT_FAILURE; }
   if (ExF == NULL) { Error("Cannot open output data stream"); return EXIT_FAILURE; }
   SaveTime("");
   struct IoT Io; MakeIO(&Io, (IoOpT)ReadIO, InF);
   struct ContextT Context; IoToContext(&Context, &Io, Atr0);
   if (Noise&InfoV) PutContextInfo(&Context, "input");
   SaveTime("input read time");
   if (SortBy != 0) SortContext(&Context, SortBy);
   if (LoSup != 0) {
      PruneContextAtrs(&Context, LoSup);
      if (Noise&InfoV) PutContextInfo(&Context, "preprocessed");
   }
   SaveTime("preprocessing time");
   FreeIO(&Io);
   MakeIO(&Io, (IoOpT)WriteIO, ExF);
   InfoConceptOpT ICOp = Noise&InfoV? PutFactorInfo: NULL;
   struct ConceptT Concepts = Noise&ExV?
      (struct ConceptT){ LoSup, FactorToIO, &Io, ICOp, FactorMode }:
      (struct ConceptT){ LoSup, NULL, NULL, ICOp, 0 };
   FindFactors(&Context, Tiny, &Concepts);
   OpIO(&Io, ExFL);
   SaveTime("find time");
   FreeIO(&Io);
#ifdef STATS
   if (Noise&(StatV | InfoV)) PutStats();
#endif
   FreeContext(&Context);
   fclose(InF), fclose(ExF);
   return EXIT_SUCCESS;
}
