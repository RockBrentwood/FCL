#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// A concept-attribute pair table is set up with a neighbor list in a way similar to how the pairs list is set up.
// Convert
// ∙	(OText, AText)*
// to:
// ∙	Obj	(O, OText) × Objs
// ∙	Atr	(A, AText) × Atrs
// ∙	Pairs	(O, A)*
// ∙	Table	(O, bool:Atrs) × Objs
// Convert
// ∙	Table	(O, bool:Atrs) × Objs
// to:
// ∙	Item	(I, bool:(Objs + Atrs))×Items
// ∙	AMatch	(Affinity)×Atrs×Atrs
// ∙	OMatch	(Affinity)×Objs×Objs
// and, using a combined power-rotate method for factor-analysis, to:
// ∙	Factor	(F,Var)×Factors
// ∙	Common	(C)×Objs
// ∙	Loads	(L)×(Objs + Atrs)×Factors

char *App;
bool DoV = false, DoQ = false, DoF = false, DoN = false, DoC = true, DidH = false;

void *CAllocate(size_t N, size_t dN) {
   void *X = calloc(N, dN);
   if (X == NULL) fprintf(stderr, "Out of memory during CAllocate().\n"), exit(EXIT_FAILURE);
   return X;
}

void *Allocate(size_t N, size_t dN) {
   void *X = malloc(N*dN);
   if (X == NULL) fprintf(stderr, "Out of memory during Allocate().\n"), exit(EXIT_FAILURE);
   return X;
}

void *ReAllocate(void *X, size_t N, size_t dN) {
   X = X == NULL? malloc(N*dN): realloc(X, N*dN);
   if (X == NULL) fprintf(stderr, "Out of memory during ReAllocate().\n"), exit(EXIT_FAILURE);
   return X;
}

// Sets
typedef unsigned Item;
typedef unsigned char *Set;

Set MoveSet(Set A, Set B, size_t Bits) {
   size_t Bytes = (Bits + 7)/8;
   if (A == NULL) A = B == NULL? CAllocate(Bytes, sizeof *A): Allocate(Bytes, sizeof *A);
   if (B != NULL) for (size_t Eq = 0; Eq < Bytes; Eq++) A[Eq] = B[Eq];
   return A;
}
#define CopySet(B, N) MoveSet(NULL, B, N)
#define ClearSet(A, N) MoveSet(A, NULL, N)
#define EmptySet(N) MoveSet(NULL, NULL, N)

void FreeSet(Set A) { free(A); }

Set AddSet(Set A, Item I, size_t Bits) { // A ∪= {I}
   if (A != NULL && I < Bits) A[I/8] |= 1 << (I%8);
   return A;
}

Set JoinSet(Set A, Set B, size_t Bits) { // A ∪= B
   size_t Bytes = (Bits + 7)/8;
   for (size_t Eq = 0; Eq < Bytes; Eq++) A[Eq] |= B[Eq];
   return A;
}

Set MeetSet(Set A, Set B, size_t Bits) { // A ∩= B
   size_t Bytes = (Bits + 7)/8;
   for (size_t Eq = 0; Eq < Bytes; Eq++) A[Eq] &= B[Eq];
   return A;
}

#if 0 //(@) Not yet used.
// { x ∈ [0,strlen(S)), S[x] ≡ Type }
Set StrToSet(char *S, char Type) {
   size_t Bits = strlen(S);
   Set A = EmptySet(Bits);
   for (size_t I = 0; I < Bits; I++) if (S[I] == Type) A = AddSet(A, I, Bits);
   return A;
}
#endif

void SetToStr(char *S, Set A, char Type, size_t Bits) {
   char Blank = Type == ','? ' ': '.';
   for (size_t I = 0; I < Bits; I++) S[I] = A[I/8]&(1 << (I%8))? Type: Blank;
}

void ShowSet(FILE *ExF, Set A, char Type, size_t Bits) {
   fputc('\t', ExF);
   char Blank = Type == ','? ' ': '.';
   for (size_t I = 0; I < Bits; I++) fputc(A[I/8]&(1 << (I%8))? Type: Blank, ExF);
   fputc('\n', ExF);
}

size_t SizeSet(Set A, size_t Bits) {
   size_t N = 0;
   for (size_t I = 0; I < Bits; I++) if (A[I/8]&(1 << (I%8))) N++;
   return N;
}

size_t DiffSet(Set A, Set B, size_t Bits) {
   size_t Bytes = (Bits + 7)/8;
   for (size_t Eq = 0; Eq < Bytes; Eq++) {
      int Diff = (int)A[Eq] - (int)B[Eq]; if (Diff != 0) return Diff;
   }
   return 0;
}

bool SameSet(Set A, Set B, size_t Bits) { // Equivalent to DiffSet(A, B, Bits) == 0.
   size_t Bytes = (Bits + 7)/8;
   for (size_t Eq = 0; Eq < Bytes; Eq++) if (A[Eq] != B[Eq]) return false;
   return true;
}

typedef struct Object { char *Id; Set Atr; } *Object;
Object ObjTab = NULL; size_t Objs = 0;

size_t GetObj(char *Id) {
   for (size_t x = 0; x < Objs; x++) if (strcmp(Id, ObjTab[x].Id) == 0) return x;
   if (Objs%0x100 == 0) ObjTab = ReAllocate(ObjTab, Objs + 0x100, sizeof *ObjTab);
   ObjTab[Objs].Id = strdup(Id); return Objs++;
}

// Concepts
typedef struct Concept { Set Xs, Ys; size_t Xn, Yn; } *Concept;

Concept CnTab; unsigned Cns;

Concept GetConcept(Set Ys, size_t Atrs) {
   for (unsigned C = 0; C < Cns; C++) if (SameSet(CnTab[C].Ys, Ys, Atrs)) return &CnTab[C];
   if (Cns%0x100 == 0) CnTab = ReAllocate(CnTab, Cns + 0x100, sizeof *CnTab);
   Concept Cn = &CnTab[Cns++];
   Cn->Xs = EmptySet(Objs), Cn->Ys = CopySet(Ys, Atrs); return Cn;
}

int DiffConcept(const void *Ax, const void *Bx) {
   Concept A = (Concept)Ax, B = (Concept)Bx;
   int Diff = A->Xn - B->Xn;
   return Diff != 0? Diff: DiffSet(A->Xs, B->Xs, Objs);
}

// Factor analysis ― as singular value decomposition + varimax rotation.
void SwapR(double *AP, double *BP) { double a = *AP, b = *BP; *AP = b, *BP = a; }

const size_t Fs = 15;
const int CutOff = 100;
double **E, *E0;

#define Cvt(Z) ((int)(1000.0*Z + 0.5))
bool IsBig(int Z) { return Z >= +CutOff || Z < -CutOff; }

bool Rotate(void) {
   const unsigned Steps = 300;
   const double Tiny = 0.000001;
   for (Item x = 0; x < Objs; x++) {
      double Z = 0.0;
      for (int f = 0; f < Fs; f++) Z += E[f][x]*E[f][x];
      E0[x] = sqrt(Z);
   }
   for (int Step = 0; Step < Steps; Step++) {
      if (!DoQ) fprintf(stderr, "   [%d]\n", Step);
      int LL = 0; double MaxS = 0.0;
      for (int f0 = 0; f0 < Fs - 1; f0++) for (int f1 = f0 + 1; f1 < Fs; f1++, LL++) {
         double *Ef0 = E[f0], *Ef1 = E[f1];
         double n = 0.0, x = 0.0, y = 0.0, xx = 0.0, xy = 0.0, yy = 0.0;
         for (Item X = 0; X < Objs; X++) {
            double a1 = Ef0[X], a2 = Ef1[X];
            double dx = a1*a1 - a2*a2, dy = 2.0*a1*a2;
            n++, x += dx, y += dy, xx += dx*dx, xy += dx*dy, yy += dy*dy;
         }
         x /= n, y /= n; xx /= n, xy /= n, yy /= n;
         double cc = (xx - x*x) - (yy - y*y), ss = 2.0*(xy - x*y);
         double c4 = cc/sqrt(cc*cc + ss*ss), c2 = sqrt((1.0 + c4)/2.0);
         double c = sqrt((1.0 + c2)/2.0), s = sqrt((1.0 - c2)/2.0);
         if (MaxS < s) {
            if (!DoQ) fprintf(stderr, " %d(%7.6f)", LL, s);
            MaxS = s;
         }
         if (fabs(s) < Tiny) continue;
         if (ss < 0.0) s = -s;
         for (Item X = 0; X < Objs; X++) {
            double LL = c*Ef0[X] + s*Ef1[X];
            Ef1[X] = c*Ef1[X] - s*Ef0[X]; Ef0[X] = LL;
         }
      }
      if (!DoQ) fprintf(stderr, "=> %7.6f\n", MaxS);
      if (MaxS < Tiny) return true;
   }
   return false;
}

void Factorize(FILE *ExF, char **XY, size_t Xs, size_t Ys) {
// Initialize the factor arrays.
// double XX[Xs][Xs];
   double **XX = Allocate(Xs, sizeof *XX); XX[0] = Allocate(Xs*Xs, sizeof *XX[0]);
   for (Item x = 1; x < Xs; x++) XX[x] = XX[x - 1] + Xs;
// double E[Fs][Xs];
   E = Allocate(Fs, sizeof *E), E[0] = Allocate(Fs*Xs, sizeof *E[0]);
   for (size_t f = 1; f < Fs; f++) E[f] = E[f - 1] + Xs;
// double E0[Xs];
   E0 = Allocate(Xs, sizeof *E0);
// double Val[Fs];
   double *Val = Allocate(Fs, sizeof *Val);
   double ys = (double)Ys;
   for (size_t x0 = 0; x0 < Xs; x0++) for (size_t x1 = 0; x1 < Xs; x1++)
      if (x0 > x1) XX[x0][x1] = XX[x1][x0];
      else {
         int n = 0;
         for (char *S0 = XY[x0], *S1 = XY[x1]; *S0 != '\0' && *S1 != '\0'; S0++, S1++) if (*S0 == *S1) n++;
         XX[x0][x1] = n/ys;
      }
   for (size_t x = 0; x < Xs; x++) for (size_t f = 0; f < Fs; f++) E[f][x] = f == x? 1.0: 0.0;
   double Error;
   do {
      Error = 0.0;
      for (size_t f = 0; f < Fs; f++) {
         double *Ef = E[f];
      // E0 = E[f]
         for (size_t x = 0; x < Xs; x++) E0[x] = Ef[x];
      // E[f] = XX E0
         for (size_t x = 0; x < Xs; x++) {
            double Efx = 0.0, *Xx = XX[x];
            for (size_t x1 = 0; x1 < Xs; x1++) Efx += Xx[x1]*E0[x1];
            Ef[x] = Efx;
         }
         for (size_t f1 = 0; f1 < f; f1++) {
            double *Ef1 = E[f1], Eff1 = 0.0;
            for (size_t x = 0; x < Xs; x++) Eff1 += Ef[x]*Ef1[x];
            for (size_t x = 0; x < Xs; x++) Ef[x] -= Eff1*Ef1[x];
         }
         double Eff = 0.0;
         for (size_t x = 0; x < Xs; x++) Eff += Ef[x]*Ef[x];
         Eff = sqrt(Eff);
         if (Eff < -0.001 || Eff > 0.001) for (size_t x = 0; x < Xs; x++) Ef[x] /= Eff;
         Eff -= Val[f]; Val[f] += Eff;
         if (Eff < 0.0) Eff = -Eff;
         if (Error < Eff) Error = Eff;
         if (!DoQ) fprintf(stderr, "%d ", Cvt(Val[f]));
      }
      for (size_t f = 0; f < Fs; f++) {
         double *Ef = E[f];
         for (size_t f1 = f + 1; f1 < Fs; f1++) {
            double *Ef1 = E[f1];
            if (Val[f] >= Val[f1]) continue;
            SwapR(&Val[f1], &Val[f]);
            for (size_t x = 0; x < Xs; x++) SwapR(&Ef1[x], &Ef[x]);
         }
      }
      if (!DoQ) fprintf(stderr, "%d\n", Cvt(Error));
   } while (Error >= 0.001);
   for (size_t f = 0; f < Fs; f++) {
      double Lam = sqrt(Val[f]); double *Ef = E[f];
      for (size_t x = 0; x < Xs; x++) Ef[x] *= Lam;
   }
   for (size_t f = 0; f < Fs; f++) fprintf(ExF, "F%02u: %10.6f\n", (unsigned)f, Val[f]);
   bool Rotated = Rotate();
   fprintf(ExF, "Rotation %s.\n", Rotated? "finished": "failed");
   fprintf(ExF, "Commonalities:\n");
   for (size_t x = 0; x < Xs; x++) fprintf(ExF, "CC  %4d O%03u\n", Cvt(E0[x]), (unsigned)x);
   for (size_t f = 0; f < Fs; f++) {
      double *Ef = E[f], Total = 0.0;
      for (size_t x = 0; x < Xs; x++) Total += Ef[x];
      if (Total < 0.0) for (size_t x = 0; x < Xs; x++) Ef[x] = -Ef[x];
      fprintf(ExF, "\nF%02u:\n", (unsigned)f);
      for (size_t x = 0; x < Xs; x++) {
         int L = Cvt(Ef[x]);
         if (IsBig(L)) fprintf(ExF, "\tF%02u O %4d O%03u\n", (unsigned)f, L, (unsigned)x);
      }
      for (size_t y = 0; y < Ys; y++) {
         double Z = 0.0;
         for (size_t x = 0; x < Xs; x++) if (XY[x][y] != '.') Z += E[f][x];
         fprintf(ExF, "\tF%02u A %4d A%03u\n", (unsigned)f, Cvt(Z), (unsigned)y);
      }
   }
}

char **AtrTab = NULL; size_t Atrs = 0;

size_t GetAtr(char *Id) {
   for (size_t y = 0; y < Atrs; y++) if (strcmp(Id, AtrTab[y]) == 0) return y;
   if (Atrs%0x100 == 0) AtrTab = ReAllocate(AtrTab, Atrs + 0x100, sizeof *AtrTab);
   AtrTab[Atrs] = strdup(Id); return Atrs++;
}

char **SeparateObjs(Object ObjTab, size_t Objs, size_t Atrs) {
// For each object x and attribute y: Context[x][y] = (x,y) ∈ PairTab? 'x': ' ';
// where (x,y) ∈ PairTab ⇔ y ∈ ObjTab[x].Atr.
   char *Ctx = Allocate(Objs*(Atrs + 1), sizeof *Ctx);
   char **Context = Allocate(Objs, sizeof *Context);
   for (size_t x = 0; x < Objs; Ctx += Atrs + 1, x++) SetToStr(Context[x] = Ctx, ObjTab[x].Atr, 'x', Atrs);
   return Context;
}

#if 0 //(@) Not yet used.
void CountAtrs(char **Context, size_t Objs) {
// Count the attributes.
   for (Item x = 0; x < Objs; x++) {
      unsigned L = strlen(Context[x]);
      if (x == 0) Atrs = L;
      else if (Atrs != L) fprintf(stderr, "Mismatched length in the context table with object %03u\n", x), exit(EXIT_FAILURE);
   }
   if (Atrs < 1) fprintf(stderr, "No attributes were listed.\n"), exit(EXIT_FAILURE);
}

void CollateObjs(char **Context, size_t Objs) {
// For each object x: ObjTab[x].Atr = { y: (x,y) ∈ PairTab };
// where (x,y) ∈ PairTab ⇔ Context[x][y] ≡ 'x'
   ObjTab = Allocate(Objs, sizeof *ObjTab);
   for (Item x = 0; x < Objs; x++) ObjTab[x].Atr = StrToSet(Context[x], 'x');
}
#endif

typedef struct Pair { size_t x, y; } *Pair;
Pair PairTab = NULL; size_t Pairs = 0;

void AddPair(size_t x, size_t y) {
   if (Pairs%0x100 == 0) PairTab = ReAllocate(PairTab, Pairs + 0x100, sizeof *PairTab);
   Pair P = &PairTab[Pairs++]; P->x = x, P->y = y;
}

bool GetNumber(FILE *InF, int *ValueP) {
   *ValueP = -1;
   int Ch = fgetc(InF);
   for (; !isdigit(Ch); Ch = fgetc(InF))
      if (Ch == EOF) return false;
      else if (Ch == '\n') return true;
   for (*ValueP = 0; isdigit(Ch); Ch = fgetc(InF)) *ValueP = 10*(*ValueP) + Ch - '0';
   ungetc(Ch, InF);
   if (*ValueP < 0) fprintf(stderr, "Invalid input value: %i, quitting.\n", *ValueP), exit(EXIT_FAILURE);
   return true;
}

// A list of lines for Attributes by Object, each assumed to be of the form Attribute Attribute ⋯ Attribute. \n
void GetPairsByObj(FILE *InF) {
// Read in the file.
   Atrs = 0, Objs = 0;
   int ExAtr = -1;
   for (int Atr; GetNumber(InF, &Atr); ExAtr = Atr)
      if (Atr >= 0) {
         if (Atrs <= Atr) Atrs = Atr + 1;
         AddPair(Objs, Atr);
      } else if (ExAtr >= 0) Objs++;
   if (ExAtr >= 0) Objs++;
   ObjTab = Allocate(Objs, sizeof *ObjTab);
}

// A list of lines for (Object, Attribute) pairs, each assumed to be of the form ObjectName \t AttributeName \n
void GetPairs(FILE *InF) {
   while (true) {
      static char Buf[0x1000]; static char *BufEnd = Buf + sizeof Buf/sizeof Buf[0];
      char *BP = Buf; int Ch;
      for (; BP < BufEnd; BP++) {
         if ((Ch = fgetc(InF)) == '\t' || Ch == '\n' || Ch == EOF) break;
         *BP = Ch;
      }
      if (Ch == EOF && BP == Buf) break;
      if (Ch != '\t') fprintf(stderr, "Missing attribute name"), exit(EXIT_FAILURE);
      if (BP >= BufEnd) fprintf(stderr, "Long object name\n"), exit(EXIT_FAILURE); else *BP++ = '\0';
      size_t x = GetObj(Buf);
      for (BP = Buf; BP < BufEnd; BP++) {
         if ((Ch = fgetc(InF)) == '\n' || Ch == EOF) break;
         *BP = Ch;
      }
      if (BP >= BufEnd) fprintf(stderr, "Long attribute name\n"), exit(EXIT_FAILURE); else *BP++ = '\0';
      AddPair(x, GetAtr(Buf));
      if (Ch == EOF) break;
   }
}

void Usage(bool DoExit) {
   if (!DidH) DidH = true;
   else fprintf(stderr,
      "%s [-h][-v][-f][-n][InF [ExF]]\n"
      "Options:\n"
      "-h:  help (display this message)\n"
      "-q:  quiet mode (no status messages), currently only used with -f\n"
      "-v:  verbose mode\n"
      "-f:  factor analysis\n"
      "-n:  named objects and attributes\n"
#if 0
      "-yM:  output mode M: (string-sets, values, pairs) by (object, attribute)\n"
      "-xM:  input mode M: (string-sets, values, pairs) by (object, attribute)\n"
#else
      "-c:  don't compile the concept lattice (just show pairs)\n"
#endif
      "Arguments:\n"
      "InF: input context data file name (default: standard input)\n"
      "ExF: output context data file name (default: standard output)\n",
      App
   );
   if (DoExit) exit(EXIT_SUCCESS);
#if 0
   exit(EXIT_FAILURE);
#endif
}

int main(int AC, char **AV) {
   App = AC == 0? NULL: AV[0]; if (App == NULL || *App == '\0') App = "FCbO";
   int A = 1;
   for (; A < AC; A++) {
      char *Arg = AV[A];
      if (*Arg++ != '-' || *Arg == '\0') break;
      else switch (*Arg) {
         case 'h': Usage(true); break;
         case 'q': DoQ = true; break;
         case 'v': DoV = true; break;
         case 'f': DoF = true; break;
         case 'n': DoN = true; break;
         case 'c': DoC = false; break;
	 default: fprintf(stderr, "Undefined option: -%s.\n", Arg), Usage(false); break;
      }
   }
   char *InFile = A < AC? AV[A]: NULL;
   char *ExFile = A + 1 < AC? AV[A + 1]: NULL;
   FILE *InF = InFile != NULL && *InFile != '-'? fopen(InFile, "rb"): stdin;
   FILE *ExF = ExFile != NULL && *ExFile != '-'? fopen(ExFile, "wb"): stdout;
   if (InF == NULL) { fprintf(stderr, "%s: cannot open input data stream\n", App); return EXIT_FAILURE; }
   if (ExF == NULL) { fprintf(stderr, "%s: open output data stream\n", App); return EXIT_FAILURE; }
   if (DoN) GetPairs(InF); else GetPairsByObj(InF);
   for (Item x = 0; x < Objs; x++) ObjTab[x].Atr = EmptySet(Atrs);
   for (size_t P = 0; P < Pairs; P++) {
      Item x = PairTab[P].x; Object Obj = &ObjTab[x];
      Obj->Atr = AddSet(Obj->Atr, PairTab[P].y, Atrs);
   }
   char **Context = SeparateObjs(ObjTab, Objs, Atrs);
   if (DoV && DoN) {
      fprintf(ExF, "Obj [%u]\n", (unsigned)Objs);
      for (Item x = 0; x < Objs; x++) fprintf(ExF, "\tO%03u\t%s\n", (unsigned)x, ObjTab[x].Id);
      fprintf(ExF, "Atr [%u]\n", (unsigned)Atrs);
      for (Item y = 0; y < Atrs; y++) fprintf(ExF, "\tA%03u\t%s\n", (unsigned)y, AtrTab[y]);
      fprintf(ExF, "Pairs [%u]\n", (unsigned)Pairs);
      for (size_t P = 0; P < Pairs; P++) { Item x = PairTab[P].x, y = PairTab[P].y; fprintf(ExF, "\tO%03u\tA%03u\n", (unsigned)x, (unsigned)y); }
      fprintf(ExF, "Table [%u x %u]\n", (unsigned)Objs, (unsigned)Atrs);
      for (Item x = 0; x < Objs; x++) fprintf(ExF, "\tO%03u", (unsigned)x), ShowSet(ExF, ObjTab[x].Atr, 'x', Atrs);
   }
   if (DoC) {
   // Compile the concept list.
      Set CurXs = EmptySet(Objs), CurYs = EmptySet(Atrs);
   // For each object x: ObjTab[x].Atr = { y: (x,y) ∈ PairTab };
      for (Item x = 0; x < Objs; x++) {
         Set Yx = ObjTab[x].Atr;
      // for all ((Xs,Ys) ∈ CnTab) { Update the entry (X,Yx∩Ys) in CnTab to (X∪Xs∪{x},Yx∩Ys); }
         for (unsigned C = 0; C < Cns; C++) {
            Concept Cn = &CnTab[C]; CurXs = MoveSet(CurXs, Cn->Xs, Objs), CurYs = MoveSet(CurYs, Cn->Ys, Atrs);
            Concept Cxy = GetConcept(MeetSet(CurYs, Yx, Atrs), Atrs); Cxy->Xs = JoinSet(Cxy->Xs, AddSet(CurXs, x, Objs), Objs);
         }
      // Update the entry (Xs,Yx) in CnTab to (Xs∪{x},Ys);
         Concept Cxy = GetConcept(Yx, Atrs); Cxy->Xs = AddSet(Cxy->Xs, x, Objs);
      }
   // Find an entry (X,Ys) in CnTab or add (∅,Ys) to CnTab;
      ClearSet(CurYs, Atrs);
      for (Item y = 0; y < Atrs; y++) CurYs = AddSet(CurYs, y, Atrs);
      (void)GetConcept(CurYs, Atrs);
      fprintf(ExF, "Items [%u]\n", (unsigned)Cns);
      for (unsigned C = 0; C < Cns; C++) {
         Concept Cn = &CnTab[C]; Cn->Xn = SizeSet(Cn->Xs, Objs), Cn->Yn = SizeSet(Cn->Ys, Atrs);
      }
      qsort(CnTab, Cns, sizeof *CnTab, DiffConcept);
      for (unsigned C = 0; C < Cns; C++) {
         Concept Cn = &CnTab[C];
         fprintf(ExF, "I%03u:", C);
         ShowSet(ExF, Cn->Xs, 'x', Objs);
         ShowSet(ExF, Cn->Ys, 'o', Atrs);
      }
      FreeSet(CurYs), FreeSet(CurXs);
      if (DoV && !DoN) {
         for (Item x0 = 0; x0 < Objs; x0++) for (Item x1 = x0 + 1; x1 < Objs; x1++) {
            int Del = 0;
            for (int y = 0; y < Atrs; y++) if (Context[x0][y] == Context[x1][y]) Del++; else Del--;
            fprintf(ExF, "O%10.6f O%03u O%03u\n", 0.5*((double)Del/(double)Atrs) + 0.5, (unsigned)x0, (unsigned)x1);
         }
         for (Item y0 = 0; y0 < Atrs; y0++) for (Item y1 = y0 + 1; y1 < Atrs; y1++) {
            int Del = 0;
            for (int x = 0; x < Objs; x++) if (Context[x][y0] == Context[x][y1]) Del++; else Del--;
            fprintf(ExF, "A%10.6f A%03u A%03u\n", 0.5*((double)Del/(double)Objs) + 0.5, (unsigned)y0, (unsigned)y1);
         }
      }
   }
   if (DoF) Factorize(ExF, Context, Objs, Atrs);
   return EXIT_SUCCESS;
}
