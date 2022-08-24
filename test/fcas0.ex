Obj [149]
	O000	Affine.c
	O001	Alpha.c
	O002	Banner.c
	O003	Bleach.c
	O004	Blur.c
	O005	BMP3to3.c
	O006	BMP4to3.c
	O007	Cast.c
	O008	Classify.c
	O009	Cluster3.c
	O010	CntX.c
	O011	Color.c
	O012	CompareBMP.c
	O013	Contour.c
	O014	Cool.c
	O015	Cross.c
	O016	CvtBMP.c
	O017	Cvt.c
	O018	Cy.c
	O019	DeBias.c
	O020	DeBleach.c
	O021	DeBMP.c
	O022	DeColor.c
	O023	Delta1.c
	O024	Delta.c
	O025	DelU.c
	O026	DeMix.c
	O027	Depth.c
	O028	DeX.c
	O029	DeY.c
	O030	DeZ0.c
	O031	DeZ1.c
	O032	DeZ.c
	O033	Do3D.c
	O034	Edge.c
	O035	Edit.c
	O036	EnBMP.c
	O037	EnDepth.c
	O038	EnMask.c
	O039	EnZ.c
	O040	Extract0.c
	O041	Extract2.c
	O042	Extract.c
	O043	FillBMP.c
	O044	Flow1.c
	O045	Flow.c
	O046	Focal.c
	O047	Font.c
	O048	Glow.c
	O049	GM.c
	O050	Graft.c
	O051	HalveBMP.c
	O052	Holo0.c
	O053	Holo1.c
	O054	Holo2.c
	O055	Holo.c
	O056	Interp.c
	O057	InvertBMP.c
	O058	Invert.c
	O059	JoinBMP.c
	O060	KeyStone.c
	O061	Lay2.c
	O062	Lay.c
	O063	Layer.c
	O064	Line.c
	O065	M1.c
	O066	Make3D.c
	O067	Mask0.c
	O068	Mask1.c
	O069	Mask2.c
	O070	Mask3.c
	O071	Mask4.c
	O072	Mask.c
	O073	MaskJoin.c
	O074	MaskSmear.c
	O075	M.c
	O076	Min.c
	O077	Mix1.c
	O078	Mix2a.c
	O079	Mix2.c
	O080	Mix3.c
	O081	Mono.c
	O082	Mx1.c
	O083	Mx3.c
	O084	Mx.c
	O085	Negate.c
	O086	NormU.c
	O087	OverCross.c
	O088	Overlay2.c
	O089	OverLay.c
	O090	Overlay.c
	O091	Overlayer.c
	O092	Pl0.c
	O093	Pl1.c
	O094	Pl2.c
	O095	PlumbLine.c
	O096	Poster.c
	O097	Project.c
	O098	Pyth.c
	O099	Ray.c
	O100	ReC.c
	O101	ReColor.c
	O102	ReJoin.c
	O103	ReLight.c
	O104	ReMap.c
	O105	ReNorm.c
	O106	RePaint2.c
	O107	RePaint.c
	O108	Repair.c
	O109	ReRed.c
	O110	ReScale.c
	O111	ReSpeck.c
	O112	ReSprite0.c
	O113	ReSprite1.c
	O114	ReSprite2.c
	O115	ReSt.c
	O116	ReStereo.c
	O117	ReT.c
	O118	ReTex.c
	O119	ReX.c
	O120	Rotate.c
	O121	Saturate.c
	O122	ScaleEx.c
	O123	ScaleIn.c
	O124	ScaleInM.c
	O125	Sched.c
	O126	Seg3Da.c
	O127	Seg3D.c
	O128	Seg.c
	O129	SegMix.c
	O130	Shade.c
	O131	Shadow.c
	O132	Shape.c
	O133	Show.c
	O134	ShowPCX.c
	O135	Sigma.c
	O136	SmearJoin.c
	O137	Speck2.c
	O138	Sprite.c
	O139	Stats.c
	O140	Stereo.c
	O141	StripeBMP.c
	O142	StSrc.c
	O143	TemMatch.c
	O144	UnMix.c
	O145	UnRGB.c
	O146	Wipe0.c
	O147	Wipe.c
	O148	XorBMP.c
Atr [510]
	A000	GradeImage GetImage(char *Path);
	A001	GradeImage NewGradeImage(long Xs, long Ys);
	A002	#include "DeBMP.h"
	A003	#include "EnBMP.h"
	A004	#include <math.h>
	A005	#include <stdio.h>
	A006	#include <stdlib.h>
	A007	int main(int AC, char *AV[]);
	A008	int PutImage(GradeImage Im, char *Path);
	A009	long RoundTo(double X);
	A010	typedef struct Grade { double R, G, B, W; } *Grade;
	A011	typedef struct GradeImage { Grade *Frame; long Xs, Ys; } *GradeImage;
	A012	void FreeGradeImage(GradeImage Im);
	A013	byte CharOf(byte X);
	A014	byte Font16[CHARS][0x20];
	A015	byte Font32[CHARS][0x80];
	A016	byte Font8[CHARS][8];
	A017	byte GetB(byte *Dst, int N, int X, int Y);
	A018	const long Xs = 640;
	A019	const long Ys = 480;
	A020	#define CHARS 28
	A021	double H = 160.0;
	A022	FILE *ExF;
	A023	FILE *OpenF(char *Path);
	A024	#include <bios.h>
	A025	#include <ctype.h>
	A026	#include <graph.h>
	A027	int CurFont;
	A028	int GetDot(int X, int Y);
	A029	int Keyboard(void);
	A030	int KeyHit(void);
	A031	int main(void);
	A032	int SizeTab[28];
	A033	int X0 = Xs/2;
	A034	int Y0 = Ys/2;
	A035	long Color[0x10];
	A036	typedef unsigned char byte;
	A037	void CloseF(FILE **ExFP);
	A038	void Double(size_t N, byte *Src, byte *Dst);
	A039	void LoadFont(void);
	A040	void PutB(byte *Dst, size_t N, int X, int Y, int B);
	A041	void PutC(FILE *ExF, byte B);
	A042	void PutL(FILE *ExF, unsigned long L);
	A043	void PutS(FILE *ExF, char *Str);
	A044	void PutW(FILE *ExF, unsigned W);
	A045	void ScrInit(void);
	A046	void ScrReset(void);
	A047	void SetDot(int X, int Y);
	A048	void Show16(int X0, int Y0);
	A049	void Show32(int X0, int Y0);
	A050	void Show8(int X0, int Y0);
	A051	void ShowB(byte *Src, size_t N, int X, int Y, byte H);
	A052	void ShowStr(int X, int Y, char *S);
	A053	byte Font16[CHARS][0x20], Font32[CHARS][0x80];
	A054	byte Region(int X, int Y);
	A055	#define CHARS 9
	A056	#define NN 32
	A057	double Random(double Max);
	A058	int Mag(int X, int Y);
	A059	Grade *GetImage(char *Path, long *XsP, long *YsP);
	A060	Grade *NewGradeImage(long Xs, long Ys);
	A061	#include <string.h>
	A062	int PutImage(char *Path, Grade *Frame, long Xs, long Ys);
	A063	typedef struct Grade { double B, G, R; } *Grade;
	A064	void Blur(Grade *FrX, Grade *FrY, long Xs, long Ys, double Diag);
	A065	void FreeGradeImage(Grade *Frame);
	A066	int Combine(int Sc[3], int B, int G, int R);
	A067	bool Combine4(int Sc[4], int B, int G, int R, int A);
	A068	bool GetHeader4(FILE *InF, long *XP, long *YP);
	A069	bool GetL(FILE *InF, long *LP);
	A070	bool GetW(FILE *InF, short *WP);
	A071	FILE *GetFile4(char *Path, long *XP, long *YP);
	A072	ColorImage GetImage(char *Path);
	A073	ColorImage NewColorImage(long Xs, long Ys);
	A074	const long Alp = 0x80;
	A075	const long Bet = 0xff;
	A076	#define HI 0x700
	A077	#define HW (6*Alp + 7*Bet + 1)
	A078	double DeColor(Color C);
	A079	int PutImage(ColorImage Im, char *Path);
	A080	long BGRtoH(long B, long G, long R);
	A081	typedef struct ColorImage { Color *Frame; long Xs, Ys; } *ColorImage;
	A082	void FreeColorImage(ColorImage Im);
	A083	int Convert(Color *IF, long Xs, long Ys);
	A084	long DeRef(long *Tab, long Ts, long T);
	A085	struct Item Tab[];
	A086	typedef struct Item { char *Name; double dX0, dY0, X0, Y0, U0; char Layer0; long cX0, cY0; double dX1, dY1, X1, Y1, U1; char Layer1; long cX1, cY1; } *Item;
	A087	unsigned Ts = sizeof Tab/sizeof Tab[0];
	A088	Cluster CTab[KS];
	A089	const double Mag = 200.0;
	A090	#define ColorMapped 1
	A091	#define KS 12
	A092	#define XS 6
	A093	double DelErr(Cluster *C0, Cluster *C1, double *V);
	A094	double Err(Grade *IF, Color *OF, unsigned Xs, unsigned Ys);
	A095	double Far = 2000.0;
	A096	double Scaling = 0.1;
	A097	double Square(double D);
	A098	#else
	A099	#endif
	A100	#if ColorMapped
	A101	#include <stdarg.h>
	A102	#include <time.h>
	A103	long GetClass(Color *OF, long X, long Y);
	A104	long RandomClass(void);
	A105	long SetClass(Color *OF, long X, long Y, long K);
	A106	typedef double Vector[XS];
	A107	typedef struct Grade { long B, G, R; double U; } *Grade;
	A108	typedef struct { int N; Vector Mu; } Cluster;
	A109	unsigned Ks = 4;
	A110	void AddC(Cluster *CP, double *V);
	A111	void EnXY(Grade G, Color C);
	A112	void EnZ(Grade G, Color C);
	A113	void GetVec(double *V, unsigned X, unsigned Y, Grade IC);
	A114	void MapColor(Color OC, unsigned K);
	A115	void Objectify(Grade *IF, Color *OF, long Xs, long Ys);
	A116	void SubC(Cluster *CP, double *V);
	A117	long BTab[0x100], GTab[0x100], RTab[0x100];
	A118	FILE *PutHeader(char *Path, unsigned Xs, unsigned Ys);
	A119	void Convert(int X, int Y, int *BP, int *GP, int *RP);
	A120	double Compare(Color *IF0, Color *IF1, long Xs, long Ys);
	A121	long DeColor(long B, long G, long R);
	A122	void Quantize(Color CP, long RadY, long MinY, long DelY);
	A123	typedef struct ColorImage { Color Map, *Frame; long Xs, Ys; } *ColorImage;
	A124	void Convert(Color *IF, Color *OF, long Xs, long Ys, double P0, double P1);
	A125	bool GetHeader(FILE *InF, long *XP, long *YP, int *BitsP);
	A126	bool GetRow(FILE *InF, Color Row, long Xs, int Alpha, int GetAlpha);
	A127	bool PutHeader(FILE *ExF, long Xs, long Ys, int Bits);
	A128	bool PutImage(ColorImage Im, char *Path);
	A129	bool PutL(FILE *ExF, long L);
	A130	bool PutRow(FILE *ExF, Color Row, long Xs, int Alpha);
	A131	bool PutW(FILE *ExF, short W);
	A132	ColorImage GetImage(char *Path, int GetAlpha);
	A133	FILE *GetFile(char *Path, long *XP, long *YP, int *BitsP);
	A134	FILE *PutFile(char *Path, long Xs, long Ys, int Bits);
	A135	typedef enum { false = 0, true = 1 } bool;
	A136	typedef struct Color { int B, G, R; } *Color;
	A137	typedef struct Grade { double R, G, B; } *Grade;
	A138	const long Radius = 2;
	A139	struct Color CTab[];
	A140	unsigned Cs = sizeof CTab/sizeof CTab[0];
	A141	void Convert(Color *IF, Color *OF, long Xs, long Ys);
	A142	void Quantize(Color IC, Color OC);
	A143	double Quad(double A, double B, double C, double X);
	A144	void Convert(Color IR, Color OR, long Xs);
	A145	double DotPi(Vector A, Vector B, double R0, double R1, double R2);
	A146	double DotV(Vector I, Vector J);
	A147	double SinCos(double Om, double *SinP, double *CosP);
	A148	typedef double Vector[3];
	A149	void Compose(Vector I, Vector J, Vector K, double X, double Y, double Z, Vector R);
	A150	void GetFrame(double Lg, double Lt, double Ph, Vector I, Vector J, Vector K);
	A151	void GetVector(double Lg, double Lt, double R, Vector A);
	A152	void Resolve(Vector I, Vector J, Vector K, Vector R);
	A153	bool GetHeader(FILE *InF, long *XP, long *YP);
	A154	bool GetRow(FILE *InF, Color Row, long Xs);
	A155	FILE *GetFile(char *Path, long *XP, long *YP);
	A156	bool Match(long B, long G, long R);
	A157	void Convert(Color *IF0, Color *IF1, Color *OF, long Xs, long Ys);
	A158	const double MagO = 200.0;
	A159	const long HI = 0x700;
	A160	double DeColor(Color CP);
	A161	void Convert(Color *IF0, Color *IF1, Color *OF, long Xs, long Ys, double Mix);
	A162	void Compile(Color *F, Color *FX, long Xs, long Ys);
	A163	#define VERSION 1
	A164	#elif VERSION == 1
	A165	#if VERSION == 0
	A166	void Convert(Color *IF, long Xs, long Ys);
	A167	const long Bet = 0xff
	A168	long CTab[][2];
	A169	double Convert(Color *IF, long Xs, long Ys);
	A170	const int Radius = 2;
	A171	struct Item { long X, Y; } Tab[];
	A172	void Extract(Color *IF, long Xs, long Ys);
	A173	struct Item { long X, Y; double U; } Tab[];
	A174	void EnColor(double U, Color C);
	A175	void HtoBGR(long H, int *BP, int *GP, int *RP);
	A176	const unsigned RadR = 60;
	A177	double MakeColor(long X, long Xs, Color CP);
	A178	#elif 0
	A179	#elif 1
	A180	#if 0
	A181	#if 1
	A182	int Convert(Color *IF, Color *OF, long Xs, long Ys);
	A183	double ArgOf(double X, double Y);
	A184	void Convert(Color *IF, Color *OF, long Xs, long Ys, long nB, long nG, long nR);
	A185	void Plot(double X, double Y, int *BP, int *GP, int *RP);
	A186	byte GetB(FILE *InF);
	A187	byte **Table;
	A188	byte xRed[0x10], xGrn[0x10], xBlu[0x10];
	A189	enum { Esc = 0x01b, Fun1 = 0x13b, Fun2 = 0x13c, Fun3 = 0x13d, Fun4 = 0x13e, Fun5 = 0x13f, Fun6 = 0x140, Fun7 = 0x141, Fun8 = 0x142, Fun9 = 0x143, Fun10 = 0x144, Home = 0x147, Up = 0x148, PgUp = 0x149, Left = 0x14b, Right = 0x14d, End = 0x14f, Down = 0x150, PgDn = 0x151, Ins = 0x152, Del = 0x153, SFn1 = 0x154, SFn2 = 0x155, SFn3 = 0x156, SFn4 = 0x157, SFn5 = 0x158, SFn6 = 0x159, SFn7 = 0x15a, SFn8 = 0x15b, SFn9 = 0x15c, SFn10 = 0x15d };
	A190	int X0 = -1;
	A191	int Y0 = -1;
	A192	unsigned GetW(FILE *InF);
	A193	unsigned long Color[0x10];
	A194	unsigned long GetL(FILE *InF);
	A195	unsigned Xs, Ys;
	A196	void Bar(int I);
	A197	void PutB(FILE *ExF, byte B);
	A198	void SetTable(unsigned Xs, unsigned Ys);
	A199	void Show(int X, int Y);
	A200	void Update(int X, int Y, int I);
	A201	bool PutHeader(FILE *ExF, long Xs, long Ys);
	A202	bool PutRow(FILE *ExF, Color Row, long Xs);
	A203	FILE *PutFile(char *Path, long Xs, long Ys);
	A204	double MuU = +0.262771;
	A205	double UA[27];
	A206	double XA = +0.013508;
	A207	double YA = -0.597025;
	A208	const long HW = 6*Alp + 7*Bet + 1;
	A209	int MapDepth(ColorImage Im, double Ovalness, int AtFG, double U0, double Power, ColorImage ImU);
	A210	typedef double *Grade;
	A211	void EnColor(double U, Color CP);
	A212	int Valid(int L);
	A213	void Convert(Color Row, long Xs, long Y);
	A214	double Weight(double R, double HiR, double LoR);
	A215	int Convert(Grade *IF, Grade *IFX, Grade *OF, long Xs, long Ys, double HiR, double LoR);
	A216	Segment PreCompile(double HiR, double LoR, unsigned *SegsP);
	A217	typedef struct Segment { long dX, dY; double W; } *Segment;
	A218	#define Xs 0x3ff
	A219	#define Ys 0x3ff
	A220	void Plot(Color *OF, double xs, double ys);
	A221	const int RDel = 3;
	A222	int Del[] = { -1, 2, -5, 8, -5, 2, -1 };
	A223	byte F0[0x80], F1[0x80], F2[0x80], FA[0x80], Ft[0x80], Fl[0x80], Fa[0x80], Fn[0x80], Fi[0x80], Fs[0x80];
	A224	byte f0[8], f1[8], f2[8], fA[8], ft[8], fl[8], fa[8], fn[8], fi[8], fs[8];
	A225	byte Temp[0x20];
	A226	void ShowB(byte *Src, size_t N, int Y, int X, byte H);
	A227	double Dot(Color *IF1, long Xs, long Ys, int nX, int nY, int mX, int mY);
	A228	double DotFF(Color *IF0, Color *IF1, long Xs, long Ys);
	A229	double InnerFF(double Mu, Color C);
	A230	double Phi(double X, int N);
	A231	double Shade(Color C);
	A232	void AddDotF(Color *IF0, Color *IF1, long Xs, long Ys, Grade G, int nX, int nY);
	A233	void AddInnerF(double Mu, Grade G, Color C, double D);
	A234	const double Bend = 0.5;
	A235	const double Del = 2.0;
	A236	const double TinyMatch = 0.01;
	A237	double Aff[3][3];
	A238	double Alignment(struct Color U[3][3], struct Color V[3][3]);
	A239	double FM[3][3];
	A240	double ReMap(long *XP, long *YP, double *UP);
	A241	double Shift[3];
	A242	int Convert(Color *IF0, long Xs0, long Ys0, Color *IF1, long Xs1, long Ys1, Color *OF, long OXs, long OYs);
	A243	void PreCompile(void);
	A244	int Valid(long L);
	A245	#define Deg 6
	A246	#define Es (1 + 2*Deg)
	A247	#define Es ((Deg + 1)*(Deg + 2)/2)
	A248	Real MulCC(Grade A, Grade B);
	A249	Real NormC(struct Grade A);
	A250	Real N, XX[Es][Es]; struct Grade XY[Es]; Real YY;
	A251	typedef double Real;
	A252	typedef struct Grade { Real B, G, R; } *Grade;
	A253	void AddMulC(Grade A, Real B, struct Grade C);
	A254	void BegStat(void);
	A255	void DeGrade(Color C, Grade A);
	A256	void DivC(Grade A, Real N);
	A257	void EndStat(void);
	A258	void EnGrade(Grade A, Color C);
	A259	void MidStat(Real X, Real Y, Real P, Color C);
	A260	void Mul2(Real *XP, Real *YP, Real X1, Real Y1);
	A261	void PowerUp(Real *A, Real X, Real Y);
	A262	void WriteC(Grade A);
	A263	void ZeroC(Grade A);
	A264	double aVX, aVY, aWX, aWY, bV, bW;
	A265	typedef struct Item { long X, Y, V, W; } *Item;
	A266	unsigned GetItem(FILE *InF, Item It);
	A267	unsigned GetNum(FILE *InF, long *LP);
	A268	void UpSt(int Op, double dX, double dY, double dV, double dW);
	A269	double MX, MV, SX, SV, MW, MY, SW, SY;
	A270	int Compile(void);
	A271	int Zero2(Number2 A);
	A272	long N; Number2 *X, Y, **XX, *XY, YY, *DelX;
	A273	Number2 By, *Mxy;
	A274	Number2 **CMake2C(int Xs, int Ys);
	A275	Number2 Comp2(long double X, long double Y);
	A276	Number2 **Make2C(int Xs, int Ys);
	A277	size_t Es = 4;
	A278	typedef struct { long double X, Y; } Number2;
	A279	void Add2(Number2 *AP, Number2 B);
	A280	void AddCorr2(Number2 *AP, Number2 B, Number2 C);
	A281	void AddMul2(Number2 *AP, Number2 B, Number2 C);
	A282	void *Allocate(size_t N, size_t dN);
	A283	void *CAllocate(size_t N, size_t dN);
	A284	void Div2(Number2 *AP, Number2 B);
	A285	void DivR2(Number2 *AP, long double R);
	A286	void Free2C(Number2 **XY);
	A287	void Mul2(Number2 *AP, Number2 B);
	A288	void Sub2(Number2 *AP, Number2 B);
	A289	void SubCorr2(Number2 *AP, Number2 B, Number2 C);
	A290	void SubMul2(Number2 *AP, Number2 B, Number2 C);
	A291	void UpSt(int Op, long double dX, long double dY, long double dV, long double dW);
	A292	double NearItem(Color CP, Item IP);
	A293	struct Item { long B, G, R, Rho; };
	A294	typedef struct Item *Item;
	A295	void ClearItem(Item IP);
	A296	int IsNumeral(char *S);
	A297	int Threshold = 0xff;
	A298	const unsigned RadR = 20;
	A299	void Convert(Color *IF, Color *IFM, Color *OF, long Xs, long Ys);
	A300	void Convert(Color *IF, Color *OF, long Xs, long Ys, int BgB, int BgG, int BgR);
	A301	void Convert(Color *IF0, Color *IF1, Color *IF2, Color *OF, long Xs, long Ys);
	A302	void Mix(int *BP, int *GP, int *RP, int Ratio);
	A303	long Round(double D);
	A304	void Convert(Color *IF, Color *IF1, Color *OF, long Xs, long Ys);
	A305	const long Xs1 = 116;
	A306	const long Ys1 = 10;
	A307	int Mix(double P, int A, int B);
	A308	double pA = 1.0;
	A309	double pB = 0.25;
	A310	int Mix(int A, int B);
	A311	void Convert(Color IR0, Color IR1, Color OR, long Xs);
	A312	void Negate(Color Row, unsigned Xs);
	A313	#define Chicago0
	A314	#elif defined(Chicago0)
	A315	#elif defined(Chicago1)
	A316	#if defined(Railroad)
	A317	void Convert(Color *IF, Color *OF, long Xs, long Ys, double P);
	A318	void Overlay(Color *IF, Color *IFY, long IXs, long IYs, Color *OF, long OXs, long OYs, long X0, long Y0);
	A319	int CharToHex(char Ch);
	A320	void GetColor(Color C, char *S);
	A321	void Overlayer(Color *IF0, Color *IF1, Color *OF, long Xs0, long Ys0, long Xs1, long Ys1, long dX, long dY);
	A322	struct { double U; unsigned B, G, R; } Tab[];
	A323	struct { unsigned B0, G0, R0, B1, G1, R1; } Tab[];
	A324	char *Poster[];
	A325	const int Xs = 6;
	A326	const int Ys = 6;
	A327	#define Black 0
	A328	#define Brown 9
	A329	#define DarkBlue 7
	A330	#define DarkGreen 6
	A331	#define DarkRed 1
	A332	#define EndPoster (Poster + sizeof Poster/sizeof Poster[0])
	A333	#define EndTab (ColorTab + sizeof ColorTab/sizeof ColorTab[0])
	A334	#define LightBlue  10
	A335	#define LightGreen  5
	A336	#define LightRed 2
	A337	#define Orange 3
	A338	#define Purple 8
	A339	#define White 11
	A340	#define Yellow 4
	A341	#include <conio.h>
	A342	#include "screen.h"
	A343	int GetColor(char Sym);
	A344	struct ColorItem { char Sym, Color; };
	A345	struct ColorItem ColorTab[];
	A346	void NewColors(void);
	A347	const double Degree = M_PI/180.0;
	A348	const double DelR = 0.5;
	A349	const int Radius = 25;
	A350	double Absorb(double DelX, double DelY, double DelU, double dU);
	A351	int Convert(Color *IF, Color *IFX, double IX0, double IY0, long IXs, long IYs, Color *OF, double OX0, double OY0, long OXs, long OYs, double Ax, double Ay, double Az, double Bearing, double Pitch, double Yaw, double Zoom);
	A352	int PreCompile(double Radius);
	A353	Segment SegTab = 0; unsigned Segs = 0;
	A354	typedef struct Segment { long dX, dY; } *Segment;
	A355	void Clip(double Lo, double Hi, double Off, double Div, double *LoP, double *HiP);
	A356	#define MAG 4
	A357	int Color[6] = { 14, 10, 11, 9, 13, 12 };
	A358	int Line(point A, point B, unsigned Color);
	A359	int Test(int x, int y);
	A360	int Tri(point A, point B, point C, point X);
	A361	long Hue[0x10];
	A362	long X1s, Y1s;
	A363	long Xs, Ys;
	A364	point A = {  0,  0 };
	A365	point B = { 12,  0 };
	A366	point C = { 16,  0 };
	A367	point D = { 28,  0 },
	A368	typedef struct { int x, y; } point;
	A369	void Convert(int *XP, int *YP);
	A370	void Mag(point *AP, unsigned Scale);
	A371	void Rescale(void);
	A372	struct Item { double W, X, Y, Z, Mask; int Skip; };
	A373	void Compile(Color *IFX, Color *IFY, Item *OF, long Xs, long Ys, double Nx, double Ny, double Nz);
	A374	void Convert(Item *AdSF, Item *DeSF, Color *ExCF, long Xs, long Ys, double MinB, double MinG, double MinR);
	A375	double gX[3], bX[3], gXX[3], bXX[3];
	A376	void Compile(Color *IF, Color *OF, long Xs, long Ys);
	A377	void DeColor(double H[3], double *BP, double *GP, double *RP);
	A378	void EnColor(double B, double G, double R, double H[3]);
	A379	void ReColor(double *BP, double *GP, double *RP);
	A380	void GetF(Color R, double *F, long Xs);
	A381	void MixRow(Color R0, double *FR0, Color R1, double *FR1, long Xs);
	A382	int Compile(Color *IF, Color *OF, long Xs, long Ys);
	A383	unsigned ReY[0x100];
	A384	void DeColor(double Y, double *BP, double *GP, double *RP);
	A385	void EnColor(double B, double G, double R, double *YP);
	A386	void Convert(Color *F, long Xs, long Ys);
	A387	const double UMin = 0.223214;
	A388	const double Z1 = 200.0;
	A389	double Grad(double T);
	A390	void GetU(Color R, double *U, long Xs);
	A391	void MixRow(Color R0, double *UR0, Color R1, double *UR1, long Xs, unsigned Method);
	A392	bool Tiny(double X);
	A393	#define FS 3
	A394	#define NS 3
	A395	int AddStats(ColorImage Im, ColorImage ImY, Stat SG, Stat SB);
	A396	int CompileStat(Stat S);
	A397	int Convert(ColorImage Im, ColorImage ImY, Stat SG, Stat SB);
	A398	typedef struct ColorImage { unsigned Xs, Ys; Color *Frame; } *ColorImage;
	A399	typedef struct Stat { double nN, nB, nG, nR, nBB, nBG, nBR, nGG, nGR, nRR; double Mu[NS], Lam[FS], Vec[FS][NS]; } *Stat;
	A400	void AddStat(Stat S, double dN, double B, double G, double R);
	A401	void ClearStat(Stat S);
	A402	void Extract(double Sig[NS][NS], double EVal[FS], double EVec[FS][NS]);
	A403	void NormalizeStat(Stat SG, Stat SB);
	A404	void ReColor(Stat SG, Stat SB, double *BP, double *GP, double *RP);
	A405	bool Match(Color C0, Color C1);
	A406	double MuB[NS], LamB[FS], VecB[FS][NS];
	A407	double MuG[NS], LamG[FS], VecG[FS][NS];
	A408	void Adjust(double LamG[FS], double VecG[FS][NS], double LamB[FS], double VecB[FS][NS]);
	A409	void *Allocate(size_t M, size_t N);
	A410	void Compile(Color *IF, Color *OF, long Xs, long Ys, Color Mask, double Mu[NS], double Lam[FS], double Vec[FS][NS]);
	A411	int DTab[][2];
	A412	unsigned Ds = sizeof DTab/sizeof DTab[0];
	A413	double Rail01(double X);
	A414	int ReScale(Color *IF, long IXs, long IYs, Color *OF, long OXs, long OYs, double Xs, double Ys);
	A415	long Max(long A, long B);
	A416	long Min(long A, long B);
	A417	long RoundDn(double X);
	A418	long RoundUp(double X);
	A419	unsigned ReX[3][0x100];
	A420	bool AddLayer(char *PathY, char *PathFG, char *PathBG, ColorImage ImBG, int Map, char Layer);
	A421	bool AddStats(ColorImage Im, ColorImage ImY, long *Class, int Src, int Map, char Layer);
	A422	bool Convert(char *PathIn, char *PathY, char *PathEx, int Map, char Layer, int Red);
	A423	#ifdef CCIR601_1
	A424	long *Classify(ColorImage Im, int Map, char Layer);
	A425	typedef struct Item { char *Name; double dX0, dY0, X0, Y0, U0; char Layer0; long cX0, cY0; double dX1, dY1, X1, Y1, U1; char Layer1; long cX1, cY1; struct Stat BBuf, GBuf; } *Item;
	A426	typedef struct Stat { double N, X[3], XX[3]; } *Stat;
	A427	const unsigned NS = 3;
	A428	typedef struct Stat { double ReX[3][0x100]; } *Stat;
	A429	const double TwoPi = 2.0*M_PI;
	A430	int Convert(Color *IF, Color *IFX, long IXs, long IYs, Color *OF, Color *OFX, long OXs, long OYs, double oX0, double oY0, int DepthMap, double Yaw, double Bearing, double Scale, double Ax, double Ay, double Az);
	A431	int ReMap(double *XP, double *YP, double *UP, double SnY, double CsY, double SnB, double CsB, double Scale, double Ax, double Ay, double Az);
	A432	Item PreCompile(long *DsP);
	A433	long BGRtoH(int B, int G, int R);
	A434	struct Item { long X, Y; };
	A435	struct Item { long X, Y; double W; };
	A436	void ReSize(Color *IFX, long IXs, long IYs, double *LoXP, double *LoYP, double *HiXP, double *HiYP, double Yaw, double Bearing, double Scale, double Ax, double Ay, double Az);
	A437	const double Rough = 0.5;
	A438	const double Tiny = 0.0000001;
	A439	#define ELEMS (4*WIDTH*(WIDTH + 1) + 1)
	A440	#define MID_EL (2*WIDTH*(WIDTH + 1))
	A441	#define WIDTH 3
	A442	double mXY[3][ELEMS], bY[3], delY[3];
	A443	void DeColor(double C[3], double *BP, double *GP, double *RP);
	A444	void EnColor(double B, double G, double R, double C[3]);
	A445	void InitRandom(void);
	A446	void ReColor(Color *IF, long X, long Y, long Xs, long Ys, double *BP, double *GP, double *RP);
	A447	const double Rough = 0.25;
	A448	double gX[3], gXX[3];
	A449	void Convert(Color *IF0, Color *IF1, long Xs, long Ys);
	A450	int ScaleEx(Color *IF, long IXs, long IYs, Color *OF, long OXs, long OYs, double X0, double Y0, double Xs, double Ys);
	A451	int ScaleIn(Color *IF, long IXs, long IYs, Color *OF, long OXs, long OYs, double OX0, double OX1, double OY0, double OY1);
	A452	int ScaleIn(ColorImage Im0, ColorImage Im1, double OX0, double OX1, double OY0, double OY1);
	A453	const int Rate = 25;
	A454	int ReScale(char Lab, int F, Color *IF, long IXs, long IYs, double IX0, double IX1, double IY0, double IY1, Color *OF, double *OS, long OXs, long OYs);
	A455	int ScheduleB(Color *IF, Color *OF, double *OS, long IXs, long IYs, long OXs, long OYs);
	A456	int ScheduleC(Color *IF, Color *OF, double *OS, long IXs, long IYs, long OXs, long OYs);
	A457	long BGRtoH(Color C);
	A458	double Sn(double U0, double U1);
	A459	void Convert(Color *Frame, long Xs, long Ys);
	A460	double Nx = -0.8;
	A461	double Ny = -0.85;
	A462	double Nz = 0.8;
	A463	void MixRow(Color R, long Xs, long Y, double dN, double N0);
	A464	void MixRow(Color R0, double *UR0, Color R1, double *UR1, long Xs, long Y, double dN, double N0);
	A465	void Analyse(Color *IF, Color *OF, long Xs, long Ys, long X0, long Y0, long dX, long dY);
	A466	ColorVec Map[0x100];
	A467	#define Down  0x150
	A468	#define Left  0x14b
	A469	#define Right 0x14d
	A470	#define Stop 3
	A471	#define Up 0x148
	A472	#include <dos.h>
	A473	int Light, Dark;
	A474	typedef struct ColorVec { word R, G, B; } ColorVec;
	A475	typedef unsigned int word;
	A476	typedef unsigned long dword;
	A477	void Border(int Y0, int Y1, int X0, int X1, int C);
	A478	void Box(int Y0, int Y1, int X0, int X1, int C);
	A479	void Cursor(int On, int Hue);
	A480	void Error(char *Msg);
	A481	void FindExtremes(void);
	A482	byte Row[0x400];
	A483	int GET(FILE *InF);
	A484	void PutString(int Y, int X, int Hue, const char *Format, ...);
	A485	void Show(char *File, int Back);
	A486	word Expand[0x10];
	A487	word GetW(FILE *InF);
	A488	void AddSprite(Color *IF, Color *IFM, Color *IFX, long IXs, long IYs, Color *OF, Color *OFX, long OXs, long OYs, double X0, double Y0, double U0);
	A489	void AverageC(Color C0, Color C1, double R);
	A490	void AverageH(Color C0, Color C1, double R);
	A491	void Analyse(Color *IF, long Xs, long Ys, long X0, long Y0, long dX, long dY);
	A492	const double MagI = 200.0;
	A493	int Convert(Color *IF, Color *IFX, double IX0, double IY0, long IXs, long IYs, Color *OF, Color *OFX, double OX0, double OY0, long OXs, long OYs, double Ax, double Ay, double Az, double Zoom);
	A494	Segment PreCompile(double Radius, unsigned *SegsP);
	A495	bool DoX = false;
	A496	bool DoY = false;
	A497	int Fs = 1;
	A498	int Split(GradeImage ImA, char *Path);
	A499	void EnColor(Color C, double Rho, double Lam);
	A500	int Convert(Color *IF, Color *IFX, long IXs, long IYs, Color *OF, long OX0, long OY0, long OXs, long OYs, double Ax, double Ay, double Az, double Zoom);
	A501	int DelColor(Color C0, Color C1);
	A502	void Match(Color *IF0, long Xs0, long Ys0, Color *IF1, long Xs1, long Ys1, double Min);
	A503	int Convert(Color *IF, Color *IFX, Grade *Map0, Grade *Map1, long Xs, long Ys, double HiR, double LoR);
	A504	int PutGrade(long Xs, long Ys, Grade *Frame0, Grade *Frame1, char *Path0, char *Path1, char *PathX);
	A505	typedef struct Grade { double B, G, R, W; } *Grade;
	A506	void Convert(Color IR, Color OR0, Color OR1, Color OR2, long Xs);
	A507	void MixRow(Color IR, double *IU, Color OR, double *OU, long Xs, double ThU, double dU);
	A508	void PutU(Color R, double *U, long Xs);
	A509	void Convert(Color *IF, long IXs, long IYs, Color *OF, long OXs, long OYs);
Pairs [1906]
	O000	A000
	O000	A001
	O000	A002
	O000	A003
	O000	A004
	O000	A005
	O000	A006
	O000	A007
	O000	A008
	O000	A009
	O000	A010
	O000	A011
	O000	A012
	O001	A013
	O001	A014
	O001	A015
	O001	A016
	O001	A017
	O001	A018
	O001	A019
	O001	A020
	O001	A021
	O001	A022
	O001	A023
	O001	A024
	O001	A025
	O001	A026
	O001	A004
	O001	A005
	O001	A006
	O001	A027
	O001	A028
	O001	A029
	O001	A030
	O001	A031
	O001	A032
	O001	A033
	O001	A034
	O001	A035
	O001	A036
	O001	A037
	O001	A038
	O001	A039
	O001	A040
	O001	A041
	O001	A042
	O001	A043
	O001	A044
	O001	A045
	O001	A046
	O001	A047
	O001	A048
	O001	A049
	O001	A050
	O001	A051
	O001	A052
	O002	A053
	O002	A016
	O002	A017
	O002	A054
	O002	A018
	O002	A019
	O002	A055
	O002	A056
	O002	A021
	O002	A057
	O002	A022
	O002	A024
	O002	A026
	O002	A004
	O002	A005
	O002	A006
	O002	A029
	O002	A030
	O002	A058
	O002	A031
	O002	A033
	O002	A034
	O002	A035
	O002	A036
	O002	A038
	O002	A039
	O002	A040
	O002	A041
	O002	A042
	O002	A044
	O002	A045
	O002	A046
	O002	A051
	O003	A002
	O003	A003
	O003	A005
	O003	A006
	O003	A007
	O004	A059
	O004	A060
	O004	A025
	O004	A002
	O004	A003
	O004	A004
	O004	A005
	O004	A006
	O004	A061
	O004	A007
	O004	A062
	O004	A063
	O004	A036
	O004	A064
	O004	A065
	O005	A002
	O005	A003
	O005	A005
	O005	A006
	O005	A066
	O005	A007
	O006	A067
	O006	A068
	O006	A069
	O006	A070
	O006	A071
	O006	A025
	O006	A003
	O006	A004
	O006	A005
	O006	A006
	O006	A061
	O006	A007
	O007	A072
	O007	A073
	O007	A074
	O007	A075
	O007	A076
	O007	A077
	O007	A078
	O007	A002
	O007	A003
	O007	A004
	O007	A005
	O007	A006
	O007	A007
	O007	A079
	O007	A080
	O007	A081
	O007	A082
	O008	A002
	O008	A003
	O008	A004
	O008	A005
	O008	A006
	O008	A083
	O008	A007
	O008	A084
	O008	A085
	O008	A086
	O008	A087
	O009	A088
	O009	A089
	O009	A074
	O009	A075
	O009	A090
	O009	A076
	O009	A077
	O009	A091
	O009	A092
	O009	A078
	O009	A093
	O009	A094
	O009	A095
	O009	A096
	O009	A097
	O009	A098
	O009	A099
	O009	A100
	O009	A002
	O009	A003
	O009	A004
	O009	A101
	O009	A005
	O009	A006
	O009	A102
	O009	A007
	O009	A080
	O009	A103
	O009	A104
	O009	A105
	O009	A106
	O009	A107
	O009	A108
	O009	A109
	O009	A110
	O009	A111
	O009	A112
	O009	A113
	O009	A114
	O009	A115
	O009	A116
	O010	A002
	O010	A005
	O010	A006
	O010	A007
	O010	A117
	O011	A118
	O011	A004
	O011	A005
	O011	A006
	O011	A031
	O011	A119
	O011	A042
	O012	A120
	O012	A002
	O012	A005
	O012	A006
	O012	A007
	O013	A002
	O013	A003
	O013	A005
	O013	A006
	O013	A007
	O013	A121
	O013	A122
	O014	A002
	O014	A003
	O014	A004
	O014	A005
	O014	A006
	O014	A007
	O015	A072
	O015	A073
	O015	A002
	O015	A003
	O015	A004
	O015	A005
	O015	A006
	O015	A007
	O015	A079
	O015	A123
	O015	A124
	O015	A082
	O016	A125
	O016	A069
	O016	A126
	O016	A070
	O016	A127
	O016	A128
	O016	A129
	O016	A130
	O016	A131
	O016	A132
	O016	A073
	O016	A133
	O016	A134
	O016	A004
	O016	A005
	O016	A006
	O016	A007
	O016	A135
	O016	A081
	O016	A136
	O016	A137
	O016	A082
	O017	A138
	O017	A002
	O017	A003
	O017	A005
	O017	A006
	O017	A007
	O017	A139
	O017	A140
	O017	A141
	O017	A142
	O018	A143
	O018	A002
	O018	A003
	O018	A004
	O018	A005
	O018	A006
	O018	A007
	O018	A144
	O019	A072
	O019	A073
	O019	A145
	O019	A146
	O019	A147
	O019	A002
	O019	A003
	O019	A004
	O019	A005
	O019	A006
	O019	A007
	O019	A079
	O019	A148
	O019	A123
	O019	A149
	O019	A082
	O019	A150
	O019	A151
	O019	A152
	O020	A002
	O020	A003
	O020	A005
	O020	A006
	O020	A007
	O021	A153
	O021	A069
	O021	A154
	O021	A070
	O021	A155
	O021	A002
	O021	A004
	O021	A005
	O021	A006
	O022	A156
	O022	A002
	O022	A003
	O022	A005
	O022	A006
	O022	A007
	O022	A141
	O023	A002
	O023	A003
	O023	A005
	O023	A006
	O023	A007
	O023	A157
	O024	A002
	O024	A003
	O024	A005
	O024	A006
	O024	A007
	O024	A157
	O025	A158
	O025	A074
	O025	A075
	O025	A159
	O025	A077
	O025	A160
	O025	A002
	O025	A004
	O025	A005
	O025	A006
	O025	A007
	O025	A080
	O026	A002
	O026	A003
	O026	A004
	O026	A005
	O026	A006
	O026	A007
	O026	A161
	O027	A074
	O027	A075
	O027	A159
	O027	A077
	O027	A078
	O027	A002
	O027	A003
	O027	A005
	O027	A006
	O027	A007
	O027	A080
	O027	A162
	O028	A163
	O028	A164
	O028	A098
	O028	A099
	O028	A165
	O028	A002
	O028	A003
	O028	A005
	O028	A006
	O028	A007
	O028	A166
	O029	A074
	O029	A167
	O029	A159
	O029	A077
	O029	A078
	O029	A002
	O029	A005
	O029	A006
	O029	A007
	O029	A080
	O029	A168
	O029	A140
	O030	A158
	O030	A074
	O030	A075
	O030	A159
	O030	A077
	O030	A169
	O030	A160
	O030	A002
	O030	A003
	O030	A004
	O030	A005
	O030	A006
	O030	A102
	O030	A007
	O030	A080
	O031	A170
	O031	A074
	O031	A075
	O031	A159
	O031	A077
	O031	A078
	O031	A002
	O031	A004
	O031	A005
	O031	A006
	O031	A007
	O031	A080
	O031	A171
	O031	A087
	O031	A172
	O032	A170
	O032	A074
	O032	A075
	O032	A159
	O032	A077
	O032	A002
	O032	A003
	O032	A004
	O032	A005
	O032	A006
	O032	A007
	O032	A173
	O032	A087
	O032	A166
	O032	A174
	O032	A175
	O033	A074
	O033	A075
	O033	A176
	O033	A076
	O033	A077
	O033	A177
	O033	A178
	O033	A179
	O033	A098
	O033	A099
	O033	A180
	O033	A181
	O033	A002
	O033	A003
	O033	A004
	O033	A005
	O033	A006
	O033	A182
	O033	A007
	O033	A174
	O033	A175
	O034	A183
	O034	A002
	O034	A003
	O034	A004
	O034	A005
	O034	A006
	O034	A061
	O034	A007
	O034	A184
	O034	A185
	O035	A186
	O035	A187
	O035	A188
	O035	A189
	O035	A024
	O035	A026
	O035	A005
	O035	A006
	O035	A029
	O035	A007
	O035	A190
	O035	A191
	O035	A036
	O035	A192
	O035	A193
	O035	A194
	O035	A195
	O035	A196
	O035	A197
	O035	A042
	O035	A044
	O035	A045
	O035	A046
	O035	A198
	O035	A199
	O035	A200
	O036	A201
	O036	A129
	O036	A202
	O036	A131
	O036	A203
	O036	A003
	O036	A004
	O036	A005
	O036	A006
	O037	A074
	O037	A075
	O037	A159
	O037	A077
	O037	A204
	O037	A205
	O037	A206
	O037	A207
	O037	A002
	O037	A003
	O037	A004
	O037	A005
	O037	A006
	O037	A007
	O037	A141
	O037	A174
	O037	A175
	O038	A002
	O038	A003
	O038	A005
	O038	A006
	O038	A007
	O039	A072
	O039	A073
	O039	A158
	O039	A074
	O039	A075
	O039	A159
	O039	A208
	O039	A078
	O039	A001
	O039	A002
	O039	A003
	O039	A004
	O039	A005
	O039	A006
	O039	A007
	O039	A209
	O039	A079
	O039	A080
	O039	A210
	O039	A081
	O039	A011
	O039	A211
	O039	A082
	O039	A012
	O039	A175
	O040	A002
	O040	A003
	O040	A005
	O040	A006
	O040	A007
	O040	A212
	O040	A213
	O041	A074
	O041	A075
	O041	A159
	O041	A077
	O041	A078
	O041	A002
	O041	A005
	O041	A006
	O041	A007
	O041	A080
	O042	A002
	O042	A003
	O042	A005
	O042	A006
	O042	A007
	O042	A139
	O042	A140
	O042	A141
	O042	A142
	O043	A214
	O043	A000
	O043	A001
	O043	A002
	O043	A003
	O043	A004
	O043	A005
	O043	A006
	O043	A215
	O043	A007
	O043	A008
	O043	A009
	O043	A216
	O043	A010
	O043	A011
	O043	A217
	O043	A012
	O044	A218
	O044	A219
	O044	A003
	O044	A004
	O044	A005
	O044	A006
	O044	A007
	O044	A220
	O045	A218
	O045	A219
	O045	A003
	O045	A004
	O045	A005
	O045	A006
	O045	A007
	O045	A220
	O046	A221
	O046	A074
	O046	A075
	O046	A159
	O046	A077
	O046	A002
	O046	A003
	O046	A004
	O046	A005
	O046	A006
	O046	A222
	O046	A007
	O046	A141
	O046	A211
	O046	A175
	O047	A223
	O047	A224
	O047	A017
	O047	A225
	O047	A024
	O047	A026
	O047	A005
	O047	A006
	O047	A029
	O047	A031
	O047	A036
	O047	A038
	O047	A040
	O047	A045
	O047	A046
	O047	A226
	O048	A089
	O048	A074
	O048	A075
	O048	A159
	O048	A077
	O048	A160
	O048	A002
	O048	A003
	O048	A004
	O048	A005
	O048	A006
	O048	A007
	O048	A080
	O048	A141
	O049	A227
	O049	A228
	O049	A229
	O049	A230
	O049	A231
	O049	A002
	O049	A004
	O049	A005
	O049	A006
	O049	A007
	O049	A063
	O049	A232
	O049	A233
	O050	A234
	O050	A235
	O050	A089
	O050	A236
	O050	A074
	O050	A075
	O050	A159
	O050	A077
	O050	A237
	O050	A238
	O050	A239
	O050	A240
	O050	A241
	O050	A002
	O050	A003
	O050	A004
	O050	A005
	O050	A006
	O050	A242
	O050	A007
	O050	A174
	O050	A175
	O050	A243
	O051	A002
	O051	A003
	O051	A005
	O051	A006
	O051	A007
	O052	A002
	O052	A005
	O052	A006
	O052	A007
	O052	A244
	O053	A245
	O053	A246
	O053	A247
	O053	A098
	O053	A099
	O053	A181
	O053	A002
	O053	A003
	O053	A004
	O053	A005
	O053	A006
	O053	A182
	O053	A007
	O053	A248
	O053	A249
	O053	A250
	O053	A251
	O053	A252
	O053	A253
	O053	A254
	O053	A255
	O053	A256
	O053	A257
	O053	A258
	O053	A259
	O053	A260
	O053	A261
	O053	A262
	O053	A263
	O054	A264
	O054	A025
	O054	A002
	O054	A003
	O054	A004
	O054	A005
	O054	A006
	O054	A007
	O054	A265
	O054	A266
	O054	A267
	O054	A268
	O055	A269
	O055	A025
	O055	A002
	O055	A003
	O055	A004
	O055	A005
	O055	A006
	O055	A270
	O055	A007
	O055	A271
	O055	A272
	O055	A273
	O055	A274
	O055	A275
	O055	A276
	O055	A277
	O055	A265
	O055	A278
	O055	A266
	O055	A267
	O055	A279
	O055	A280
	O055	A281
	O055	A282
	O055	A283
	O055	A284
	O055	A285
	O055	A286
	O055	A287
	O055	A288
	O055	A289
	O055	A290
	O055	A291
	O056	A002
	O056	A003
	O056	A004
	O056	A005
	O056	A006
	O056	A007
	O056	A144
	O057	A002
	O057	A003
	O057	A005
	O057	A006
	O057	A007
	O058	A002
	O058	A003
	O058	A005
	O058	A006
	O058	A007
	O059	A072
	O059	A073
	O059	A002
	O059	A003
	O059	A004
	O059	A005
	O059	A006
	O059	A007
	O059	A079
	O059	A123
	O059	A082
	O060	A072
	O060	A073
	O060	A002
	O060	A003
	O060	A004
	O060	A005
	O060	A006
	O060	A007
	O060	A079
	O060	A009
	O060	A123
	O060	A082
	O061	A002
	O061	A003
	O061	A004
	O061	A005
	O061	A006
	O061	A007
	O062	A074
	O062	A075
	O062	A159
	O062	A077
	O062	A160
	O062	A002
	O062	A003
	O062	A004
	O062	A005
	O062	A006
	O062	A007
	O062	A080
	O063	A292
	O063	A002
	O063	A003
	O063	A004
	O063	A005
	O063	A006
	O063	A182
	O063	A007
	O063	A293
	O063	A294
	O063	A295
	O064	A002
	O064	A003
	O064	A005
	O064	A006
	O064	A061
	O064	A296
	O064	A007
	O064	A297
	O064	A141
	O065	A002
	O065	A003
	O065	A005
	O065	A006
	O065	A007
	O065	A157
	O066	A074
	O066	A075
	O066	A159
	O066	A298
	O066	A077
	O066	A078
	O066	A002
	O066	A003
	O066	A004
	O066	A005
	O066	A006
	O066	A182
	O066	A007
	O066	A080
	O066	A174
	O066	A175
	O067	A002
	O067	A003
	O067	A004
	O067	A005
	O067	A006
	O067	A007
	O067	A141
	O068	A002
	O068	A003
	O068	A004
	O068	A005
	O068	A006
	O068	A007
	O068	A299
	O069	A002
	O069	A003
	O069	A004
	O069	A005
	O069	A006
	O069	A007
	O069	A300
	O070	A002
	O070	A003
	O070	A004
	O070	A005
	O070	A006
	O070	A007
	O070	A141
	O071	A002
	O071	A003
	O071	A004
	O071	A005
	O071	A006
	O071	A007
	O071	A301
	O072	A004
	O072	A005
	O072	A006
	O072	A007
	O072	A302
	O073	A002
	O073	A003
	O073	A005
	O073	A006
	O073	A007
	O073	A303
	O073	A304
	O074	A002
	O074	A003
	O074	A004
	O074	A005
	O074	A006
	O074	A007
	O074	A303
	O075	A002
	O075	A003
	O075	A005
	O075	A006
	O075	A007
	O075	A141
	O076	A002
	O076	A003
	O076	A004
	O076	A005
	O076	A006
	O076	A007
	O076	A124
	O077	A186
	O077	A005
	O077	A006
	O077	A007
	O077	A036
	O077	A192
	O077	A197
	O077	A044
	O078	A305
	O078	A306
	O078	A002
	O078	A003
	O078	A004
	O078	A005
	O078	A006
	O078	A182
	O078	A007
	O079	A004
	O079	A005
	O079	A031
	O079	A307
	O080	A308
	O080	A309
	O080	A005
	O080	A006
	O080	A031
	O080	A310
	O081	A002
	O081	A003
	O081	A005
	O081	A006
	O081	A007
	O081	A141
	O082	A002
	O082	A003
	O082	A005
	O082	A006
	O082	A007
	O082	A157
	O083	A002
	O083	A003
	O083	A004
	O083	A005
	O083	A006
	O083	A102
	O083	A007
	O083	A311
	O084	A002
	O084	A005
	O084	A006
	O084	A007
	O084	A166
	O085	A002
	O085	A003
	O085	A005
	O085	A006
	O085	A007
	O085	A312
	O086	A074
	O086	A075
	O086	A159
	O086	A313
	O086	A077
	O086	A177
	O086	A314
	O086	A315
	O086	A098
	O086	A099
	O086	A316
	O086	A002
	O086	A003
	O086	A004
	O086	A005
	O086	A006
	O086	A007
	O086	A174
	O086	A175
	O087	A002
	O087	A003
	O087	A004
	O087	A005
	O087	A006
	O087	A007
	O087	A317
	O088	A072
	O088	A073
	O088	A002
	O088	A003
	O088	A004
	O088	A005
	O088	A006
	O088	A007
	O088	A079
	O088	A123
	O088	A082
	O088	A318
	O089	A025
	O090	A002
	O089	A002
	O090	A003
	O089	A003
	O090	A005
	O089	A005
	O090	A006
	O089	A006
	O089	A061
	O089	A319
	O090	A007
	O089	A007
	O090	A157
	O089	A320
	O091	A002
	O091	A003
	O091	A004
	O091	A005
	O091	A006
	O091	A007
	O091	A321
	O092	A002
	O092	A004
	O092	A005
	O092	A006
	O092	A007
	O092	A212
	O093	A002
	O093	A003
	O093	A005
	O093	A006
	O093	A007
	O093	A212
	O093	A322
	O093	A087
	O093	A141
	O093	A142
	O094	A002
	O094	A003
	O094	A005
	O094	A006
	O094	A007
	O094	A212
	O094	A323
	O094	A087
	O094	A141
	O094	A142
	O095	A002
	O095	A004
	O095	A005
	O095	A006
	O095	A007
	O095	A212
	O096	A324
	O096	A325
	O096	A326
	O096	A327
	O096	A328
	O096	A329
	O096	A330
	O096	A331
	O096	A332
	O096	A333
	O096	A334
	O096	A335
	O096	A336
	O096	A337
	O096	A338
	O096	A339
	O096	A340
	O096	A341
	O096	A026
	O096	A342
	O096	A343
	O096	A031
	O096	A344
	O096	A345
	O096	A346
	O097	A347
	O097	A348
	O097	A089
	O097	A349
	O097	A074
	O097	A075
	O097	A076
	O097	A077
	O097	A350
	O097	A078
	O097	A147
	O097	A002
	O097	A003
	O097	A004
	O097	A005
	O097	A006
	O097	A351
	O097	A007
	O097	A352
	O097	A080
	O097	A353
	O097	A354
	O097	A355
	O098	A356
	O098	A022
	O098	A024
	O098	A026
	O098	A005
	O098	A006
	O098	A357
	O098	A029
	O098	A358
	O098	A031
	O098	A359
	O098	A360
	O098	A361
	O098	A362
	O098	A363
	O098	A364
	O098	A365
	O098	A366
	O098	A367
	O098	A368
	O098	A036
	O098	A369
	O098	A370
	O098	A041
	O098	A042
	O098	A044
	O098	A371
	O098	A045
	O098	A046
	O099	A089
	O099	A074
	O099	A075
	O099	A159
	O099	A077
	O099	A078
	O099	A002
	O099	A003
	O099	A004
	O099	A005
	O099	A006
	O099	A007
	O099	A080
	O099	A372
	O099	A294
	O099	A373
	O099	A374
	O100	A002
	O100	A003
	O100	A005
	O100	A006
	O100	A007
	O100	A166
	O101	A375
	O101	A002
	O101	A003
	O101	A004
	O101	A005
	O101	A006
	O101	A007
	O101	A376
	O101	A141
	O101	A377
	O101	A378
	O101	A379
	O102	A002
	O102	A003
	O102	A004
	O102	A005
	O102	A006
	O102	A007
	O102	A303
	O102	A380
	O102	A381
	O103	A002
	O103	A003
	O103	A004
	O103	A005
	O103	A006
	O103	A102
	O103	A382
	O103	A007
	O103	A383
	O103	A141
	O103	A384
	O103	A385
	O103	A379
	O104	A074
	O104	A075
	O104	A159
	O104	A077
	O104	A078
	O104	A002
	O104	A003
	O104	A004
	O104	A005
	O104	A006
	O104	A007
	O104	A080
	O104	A386
	O104	A174
	O104	A175
	O105	A387
	O105	A388
	O105	A074
	O105	A075
	O105	A076
	O105	A077
	O105	A078
	O105	A389
	O105	A002
	O105	A003
	O105	A004
	O105	A005
	O105	A006
	O105	A007
	O105	A080
	O105	A303
	O105	A390
	O105	A391
	O106	A392
	O106	A072
	O106	A393
	O106	A394
	O106	A002
	O106	A003
	O106	A004
	O106	A005
	O106	A006
	O106	A395
	O106	A396
	O106	A397
	O106	A007
	O106	A398
	O106	A399
	O106	A400
	O106	A401
	O106	A402
	O106	A082
	O106	A403
	O106	A404
	O107	A405
	O107	A392
	O107	A393
	O107	A394
	O107	A406
	O107	A407
	O107	A002
	O107	A003
	O107	A004
	O107	A005
	O107	A006
	O107	A007
	O107	A408
	O107	A409
	O107	A410
	O107	A141
	O107	A402
	O107	A379
	O108	A002
	O108	A003
	O108	A005
	O108	A006
	O108	A411
	O108	A007
	O108	A412
	O108	A141
	O109	A002
	O109	A003
	O109	A005
	O109	A006
	O109	A007
	O110	A413
	O110	A002
	O110	A003
	O110	A004
	O110	A005
	O110	A006
	O110	A007
	O110	A414
	O110	A415
	O110	A416
	O110	A417
	O110	A009
	O110	A418
	O111	A002
	O111	A003
	O111	A004
	O111	A005
	O111	A006
	O111	A102
	O111	A382
	O111	A007
	O111	A419
	O111	A141
	O111	A377
	O111	A378
	O111	A379
	O112	A420
	O112	A421
	O112	A422
	O112	A072
	O112	A098
	O112	A099
	O112	A423
	O112	A002
	O112	A003
	O112	A004
	O112	A005
	O112	A006
	O112	A396
	O112	A031
	O112	A424
	O112	A084
	O112	A085
	O112	A398
	O112	A425
	O112	A426
	O112	A087
	O112	A400
	O112	A401
	O112	A377
	O112	A378
	O112	A082
	O112	A404
	O113	A420
	O113	A421
	O113	A422
	O113	A392
	O113	A072
	O113	A393
	O113	A394
	O113	A002
	O113	A003
	O113	A004
	O113	A005
	O113	A006
	O113	A396
	O113	A031
	O113	A424
	O113	A084
	O113	A085
	O113	A398
	O113	A425
	O113	A399
	O113	A087
	O113	A400
	O113	A401
	O113	A402
	O113	A082
	O113	A403
	O113	A404
	O114	A420
	O114	A421
	O114	A422
	O114	A072
	O114	A427
	O114	A002
	O114	A003
	O114	A004
	O114	A005
	O114	A006
	O114	A396
	O114	A031
	O114	A424
	O114	A084
	O114	A085
	O114	A398
	O114	A425
	O114	A428
	O114	A087
	O114	A400
	O114	A401
	O114	A377
	O114	A378
	O114	A082
	O114	A403
	O114	A404
	O115	A002
	O115	A003
	O115	A005
	O115	A006
	O115	A007
	O115	A141
	O116	A072
	O116	A073
	O116	A347
	O116	A089
	O116	A429
	O116	A074
	O116	A075
	O116	A076
	O116	A077
	O116	A078
	O116	A147
	O116	A098
	O116	A099
	O116	A181
	O116	A002
	O116	A003
	O116	A004
	O116	A005
	O116	A006
	O116	A430
	O116	A007
	O116	A079
	O116	A431
	O116	A432
	O116	A433
	O116	A434
	O116	A435
	O116	A081
	O116	A294
	O116	A174
	O116	A082
	O116	A175
	O116	A436
	O117	A437
	O117	A438
	O117	A439
	O117	A440
	O117	A441
	O117	A442
	O117	A057
	O117	A002
	O117	A003
	O117	A004
	O117	A005
	O117	A006
	O117	A102
	O117	A007
	O117	A376
	O117	A141
	O117	A443
	O117	A444
	O117	A445
	O117	A446
	O118	A447
	O118	A448
	O118	A057
	O118	A002
	O118	A003
	O118	A004
	O118	A005
	O118	A006
	O118	A102
	O118	A007
	O118	A141
	O118	A377
	O118	A378
	O118	A445
	O118	A379
	O119	A002
	O119	A003
	O119	A005
	O119	A006
	O119	A007
	O120	A186
	O120	A187
	O120	A188
	O120	A024
	O120	A026
	O120	A005
	O120	A006
	O120	A007
	O120	A036
	O120	A192
	O120	A193
	O120	A194
	O120	A197
	O120	A042
	O120	A044
	O120	A198
	O121	A002
	O121	A003
	O121	A004
	O121	A005
	O121	A006
	O121	A102
	O121	A007
	O121	A449
	O122	A002
	O122	A003
	O122	A004
	O122	A005
	O122	A006
	O122	A007
	O122	A450
	O122	A417
	O122	A009
	O122	A418
	O123	A002
	O123	A003
	O123	A004
	O123	A005
	O123	A006
	O123	A007
	O123	A451
	O123	A417
	O123	A009
	O123	A418
	O124	A072
	O124	A073
	O124	A002
	O124	A003
	O124	A004
	O124	A005
	O124	A006
	O124	A007
	O124	A079
	O124	A452
	O124	A417
	O124	A009
	O124	A418
	O124	A123
	O124	A082
	O125	A453
	O125	A002
	O125	A003
	O125	A004
	O125	A005
	O125	A006
	O125	A007
	O125	A454
	O125	A455
	O125	A456
	O126	A074
	O126	A075
	O126	A159
	O126	A002
	O126	A003
	O126	A004
	O126	A005
	O126	A006
	O126	A007
	O126	A457
	O126	A141
	O127	A089
	O127	A074
	O127	A075
	O127	A159
	O127	A077
	O127	A078
	O127	A458
	O127	A002
	O127	A003
	O127	A004
	O127	A005
	O127	A006
	O127	A007
	O127	A080
	O127	A141
	O128	A089
	O128	A074
	O128	A075
	O128	A159
	O128	A077
	O128	A078
	O128	A002
	O128	A003
	O128	A004
	O128	A005
	O128	A006
	O128	A007
	O128	A080
	O128	A459
	O129	A089
	O129	A074
	O129	A075
	O129	A159
	O129	A077
	O129	A160
	O129	A002
	O129	A003
	O129	A004
	O129	A005
	O129	A006
	O129	A007
	O129	A080
	O129	A141
	O130	A388
	O130	A074
	O130	A075
	O130	A159
	O130	A077
	O130	A078
	O130	A460
	O130	A461
	O130	A462
	O130	A002
	O130	A003
	O130	A004
	O130	A005
	O130	A006
	O130	A007
	O130	A080
	O130	A390
	O130	A463
	O131	A388
	O131	A074
	O131	A075
	O131	A076
	O131	A077
	O131	A078
	O131	A389
	O131	A460
	O131	A461
	O131	A462
	O131	A002
	O131	A003
	O131	A004
	O131	A005
	O131	A006
	O131	A007
	O131	A080
	O131	A390
	O131	A464
	O132	A002
	O132	A003
	O132	A004
	O132	A005
	O132	A006
	O132	A007
	O132	A465
	O132	A141
	O133	A186
	O133	A466
	O133	A467
	O133	A468
	O133	A469
	O133	A470
	O133	A471
	O133	A024
	O133	A341
	O133	A472
	O133	A026
	O133	A004
	O133	A005
	O133	A006
	O133	A061
	O133	A029
	O133	A473
	O133	A007
	O133	A474
	O133	A036
	O133	A475
	O133	A476
	O133	A477
	O133	A478
	O133	A479
	O133	A480
	O133	A481
	O133	A045
	O133	A046
	O134	A186
	O134	A482
	O134	A024
	O134	A341
	O134	A472
	O134	A026
	O134	A101
	O134	A005
	O134	A483
	O134	A029
	O134	A007
	O134	A036
	O134	A475
	O134	A484
	O134	A045
	O134	A046
	O134	A485
	O134	A486
	O134	A487
	O135	A002
	O135	A003
	O135	A005
	O135	A006
	O135	A007
	O135	A157
	O136	A072
	O136	A073
	O136	A002
	O136	A003
	O136	A004
	O136	A005
	O136	A006
	O136	A007
	O136	A079
	O136	A081
	O136	A082
	O137	A072
	O137	A427
	O137	A098
	O137	A099
	O137	A423
	O137	A002
	O137	A003
	O137	A004
	O137	A005
	O137	A006
	O137	A395
	O137	A396
	O137	A397
	O137	A007
	O137	A398
	O137	A428
	O137	A400
	O137	A401
	O137	A377
	O137	A378
	O137	A082
	O137	A403
	O137	A404
	O138	A072
	O138	A073
	O138	A158
	O138	A074
	O138	A075
	O138	A076
	O138	A077
	O138	A160
	O138	A002
	O138	A003
	O138	A004
	O138	A005
	O138	A006
	O138	A007
	O138	A079
	O138	A433
	O138	A009
	O138	A418
	O138	A081
	O138	A488
	O138	A489
	O138	A490
	O138	A211
	O138	A082
	O138	A175
	O139	A002
	O139	A004
	O139	A005
	O139	A006
	O139	A007
	O139	A491
	O140	A072
	O140	A073
	O140	A492
	O140	A158
	O140	A074
	O140	A075
	O140	A159
	O140	A077
	O140	A078
	O140	A002
	O140	A003
	O140	A004
	O140	A005
	O140	A006
	O140	A493
	O140	A007
	O140	A079
	O140	A080
	O140	A494
	O140	A081
	O140	A354
	O140	A174
	O140	A082
	O140	A175
	O141	A495
	O141	A496
	O141	A078
	O141	A000
	O141	A001
	O141	A002
	O141	A003
	O141	A004
	O141	A005
	O141	A006
	O141	A061
	O141	A497
	O141	A007
	O141	A498
	O141	A009
	O141	A210
	O141	A011
	O141	A499
	O141	A012
	O142	A492
	O142	A158
	O142	A349
	O142	A074
	O142	A075
	O142	A159
	O142	A077
	O142	A078
	O142	A002
	O142	A003
	O142	A004
	O142	A005
	O142	A006
	O142	A500
	O142	A501
	O142	A007
	O142	A080
	O143	A002
	O143	A003
	O143	A004
	O143	A005
	O143	A006
	O143	A007
	O143	A502
	O144	A072
	O144	A073
	O144	A214
	O144	A001
	O144	A002
	O144	A003
	O144	A004
	O144	A005
	O144	A006
	O144	A503
	O144	A007
	O144	A504
	O144	A079
	O144	A216
	O144	A081
	O144	A505
	O144	A011
	O144	A217
	O144	A082
	O144	A012
	O145	A002
	O145	A003
	O145	A005
	O145	A006
	O145	A007
	O145	A506
	O146	A074
	O146	A075
	O146	A159
	O146	A077
	O146	A160
	O146	A002
	O146	A003
	O146	A004
	O146	A005
	O146	A006
	O146	A007
	O146	A080
	O146	A211
	O146	A390
	O146	A175
	O146	A507
	O146	A508
	O147	A074
	O147	A075
	O147	A159
	O147	A077
	O147	A160
	O147	A002
	O147	A003
	O147	A004
	O147	A005
	O147	A006
	O147	A007
	O147	A080
	O147	A390
	O147	A507
	O148	A002
	O148	A003
	O148	A005
	O148	A006
	O148	A007
	O148	A303
	O148	A509
Table [149 x 510]
	O000	xxxxxxxxxxxxx.................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
	O001	....xxx......xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.........................................................................................................................................................................................................................................................................................................................................................................................................................................................................
	O002	....xxx.........xxxx.xx.x.x..xxx.xxxx.xxxxx.xxx....x.xxxxxx...................................................................................................................................................................................................................................................................................................................................................................................................................................................................
	O003	..xx.xxx......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
	O004	..xxxxxx.................x..........x......................xxxxxxx............................................................................................................................................................................................................................................................................................................................................................................................................................................................
	O005	..xx.xxx..........................................................x...........................................................................................................................................................................................................................................................................................................................................................................................................................................................
	O006	...xxxxx.................x...................................x.....xxxxx......................................................................................................................................................................................................................................................................................................................................................................................................................................................
	O007	..xxxxxx................................................................xxxxxxxxxxx...........................................................................................................................................................................................................................................................................................................................................................................................................................................
	O008	..xxxxxx...........................................................................xxxxx......................................................................................................................................................................................................................................................................................................................................................................................................................................
	O009	..xxxxxx..................................................................xxxxx.x.......xxxxxxxxxxxxxxxxxxxxxxxxxxxxx.........................................................................................................................................................................................................................................................................................................................................................................................................
	O010	..x..xxx.............................................................................................................x........................................................................................................................................................................................................................................................................................................................................................................................................
	O011	....xxx........................x..........x...........................................................................xx......................................................................................................................................................................................................................................................................................................................................................................................................
	O012	..x..xxx................................................................................................................x.....................................................................................................................................................................................................................................................................................................................................................................................................
	O013	..xx.xxx.................................................................................................................xx...................................................................................................................................................................................................................................................................................................................................................................................................
	O014	..xxxxxx......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
	O015	..xxxxxx................................................................xx.....x..x........................................xx.................................................................................................................................................................................................................................................................................................................................................................................................
	O016	....xxxx.............................................................xx..x.......xx..........................................xxxxxxxxxxxxx....................................................................................................................................................................................................................................................................................................................................................................................
	O017	..xx.xxx..................................................................................................................................xxxxx...............................................................................................................................................................................................................................................................................................................................................................................
	O018	..xxxxxx.......................................................................................................................................xx.............................................................................................................................................................................................................................................................................................................................................................................
	O019	..xxxxxx................................................................xx.....x..x........................................x.....................xxxxxxxx.....................................................................................................................................................................................................................................................................................................................................................................
	O020	..xx.xxx......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
	O021	..x.xxx..............................................................xx..................................................................................xxx..................................................................................................................................................................................................................................................................................................................................................................
	O022	..xx.xxx.....................................................................................................................................x..............x.................................................................................................................................................................................................................................................................................................................................................................
	O023	..xx.xxx.....................................................................................................................................................x................................................................................................................................................................................................................................................................................................................................................................
	O024	..xx.xxx.....................................................................................................................................................x................................................................................................................................................................................................................................................................................................................................................................
	O025	..x.xxxx..................................................................xx.x..x.............................................................................xxx.............................................................................................................................................................................................................................................................................................................................................................
	O026	..xxxxxx.........................................................................................................................................................x............................................................................................................................................................................................................................................................................................................................................................
	O027	..xx.xxx..................................................................xx.xx.x..............................................................................x..x...........................................................................................................................................................................................................................................................................................................................................................
	O028	..xx.xxx..........................................................................................xx...............................................................xxxx.......................................................................................................................................................................................................................................................................................................................................................
	O029	..x..xxx..................................................................x..xx.x...........................................................x..................x.......xx.....................................................................................................................................................................................................................................................................................................................................................
	O030	..xxxxxx..................................................................xx.x..x.....................x.......................................................xxx........x....................................................................................................................................................................................................................................................................................................................................................
	O031	..x.xxxx..................................................................xx.xx.x......x.......................................................................x..........xxx.................................................................................................................................................................................................................................................................................................................................................
	O032	..xxxxxx..................................................................xx.x.........x.......................................................................x......x...x..xxx..............................................................................................................................................................................................................................................................................................................................................
	O033	..xxxxxx..................................................................xxxx....................xx..........................................................................xxxxxxxxx.......................................................................................................................................................................................................................................................................................................................................
	O034	..xxxxxx.....................................................x.........................................................................................................................xxx....................................................................................................................................................................................................................................................................................................................................
	O035	.....xxx................x.x..x......x.....x.xxx...........................................................................................................................................xxxxxxxxxxxxxxx.....................................................................................................................................................................................................................................................................................................................
	O036	...xxxx..........................................................................................................................x.x.....................................................................xxx..................................................................................................................................................................................................................................................................................................................
	O037	..xxxxxx..................................................................xx.x...............................................................x.................x..............xx............................xxxx..............................................................................................................................................................................................................................................................................................................
	O038	..xx.xxx......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
	O039	.xxxxxxx...xx...........................................................xxxx..xxxxx...........................................................................xx...............x................................xxxx..........................................................................................................................................................................................................................................................................................................
	O040	..xx.xxx............................................................................................................................................................................................................xx........................................................................................................................................................................................................................................................................................................
	O041	..x..xxx..................................................................xx.xx.x..............................................................................x..............................................................................................................................................................................................................................................................................................................................................................
	O042	..xx.xxx...................................................................................................................................xxxx...............................................................................................................................................................................................................................................................................................................................................................................
	O043	xxxxxxxxxxxxx.........................................................................................................................................................................................................xxxx....................................................................................................................................................................................................................................................................................................
	O044	...xxxxx..................................................................................................................................................................................................................xxx.................................................................................................................................................................................................................................................................................................
	O045	...xxxxx..................................................................................................................................................................................................................xxx.................................................................................................................................................................................................................................................................................................
	O046	..xxxxxx..................................................................xx.x...............................................................x.................x...............x...................................x.........xx...............................................................................................................................................................................................................................................................................................
	O047	.....xx..........x......x.x..x.x....x.x.x....xx................................................................................................................................................................................xxxx...........................................................................................................................................................................................................................................................................................
	O048	..xxxxxx..................................................................xx.x..x........x...................................................x.................xx.............................................................................................................................................................................................................................................................................................................................................................
	O049	..x.xxxx.......................................................x...................................................................................................................................................................xxxxxxx....................................................................................................................................................................................................................................................................................
	O050	..xxxxxx..................................................................xx.x...........x.....................................................................x..............xx..........................................................xxxxxxxxxx..........................................................................................................................................................................................................................................................................
	O051	..xx.xxx......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
	O052	..x..xxx............................................................................................................................................................................................................................................x.........................................................................................................................................................................................................................................................................
	O053	..xxxxxx..........................................................................................xx.................................................................................xx..............................................................xxxxxxxxxxxxxxxxxxx......................................................................................................................................................................................................................................................
	O054	..xxxxxx.................x..............................................................................................................................................................................................................................................xxxxx.................................................................................................................................................................................................................................................
	O055	..xxxxxx.................x...............................................................................................................................................................................................................................................xxx.xxxxxxxxxxxxxxxxxxxxxxx..........................................................................................................................................................................................................................
	O056	..xxxxxx........................................................................................................................................x.............................................................................................................................................................................................................................................................................................................................................................................
	O057	..xx.xxx......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
	O058	..xx.xxx......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
	O059	..xxxxxx................................................................xx.....x..x........................................x..................................................................................................................................................................................................................................................................................................................................................................................................
	O060	..xxxxxx.x..............................................................xx.....x..x........................................x..................................................................................................................................................................................................................................................................................................................................................................................................
	O061	..xxxxxx......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
	O062	..xxxxxx..................................................................xx.x..x..............................................................................xx.............................................................................................................................................................................................................................................................................................................................................................
	O063	..xxxxxx..............................................................................................................................................................................x.............................................................................................................xxxx......................................................................................................................................................................................................................
	O064	..xx.xxx.....................................................x...............................................................................x..........................................................................................................................................................xx....................................................................................................................................................................................................................
	O065	..xx.xxx.....................................................................................................................................................x................................................................................................................................................................................................................................................................................................................................................................
	O066	..xxxxxx..................................................................xx.xx.x..............................................................................x..............xx......x...................................................................................................................x...................................................................................................................................................................................................................
	O067	..xxxxxx.....................................................................................................................................x................................................................................................................................................................................................................................................................................................................................................................................
	O068	..xxxxxx...................................................................................................................................................................................................................................................................................................x..................................................................................................................................................................................................................
	O069	..xxxxxx....................................................................................................................................................................................................................................................................................................x.................................................................................................................................................................................................................
	O070	..xxxxxx.....................................................................................................................................x................................................................................................................................................................................................................................................................................................................................................................................
	O071	..xxxxxx.....................................................................................................................................................................................................................................................................................................x................................................................................................................................................................................................................
	O072	....xxxx......................................................................................................................................................................................................................................................................................................x...............................................................................................................................................................................................................
	O073	..xx.xxx.......................................................................................................................................................................................................................................................................................................xx.............................................................................................................................................................................................................
	O074	..xxxxxx.......................................................................................................................................................................................................................................................................................................x..............................................................................................................................................................................................................
	O075	..xx.xxx.....................................................................................................................................x................................................................................................................................................................................................................................................................................................................................................................................
	O076	..xxxxxx....................................................................................................................x.................................................................................................................................................................................................................................................................................................................................................................................................
	O077	.....xxx............................x.......x.............................................................................................................................................x.....x....x........................................................................................................................................................................................................................................................................................................................
	O078	..xxxxxx..............................................................................................................................................................................x..........................................................................................................................xx...........................................................................................................................................................................................................
	O079	....xx.........................x...................................................................................................................................................................................................................................................................................x..........................................................................................................................................................................................................
	O080	.....xx........................x....................................................................................................................................................................................................................................................................................xxx.......................................................................................................................................................................................................
	O081	..xx.xxx.....................................................................................................................................x................................................................................................................................................................................................................................................................................................................................................................................
	O082	..xx.xxx.....................................................................................................................................................x................................................................................................................................................................................................................................................................................................................................................................
	O083	..xxxxxx..............................................................................................x................................................................................................................................................................................................................x......................................................................................................................................................................................................
	O084	..x..xxx..............................................................................................................................................................x.......................................................................................................................................................................................................................................................................................................................................................
	O085	..xx.xxx................................................................................................................................................................................................................................................................................................................x.....................................................................................................................................................................................................
	O086	..xxxxxx..................................................................xx.x....................xx...........................................................x..............xx.x.......................................................................................................................................xxxx.................................................................................................................................................................................................
	O087	..xxxxxx.....................................................................................................................................................................................................................................................................................................................x................................................................................................................................................................................................
	O088	..xxxxxx................................................................xx.....x..x........................................x..................................................................................................................................................................................................x...............................................................................................................................................................................................
	O089	..xx.xxx.................x...................................x.................................................................................................................................................................................................................................................................xx.............................................................................................................................................................................................
	O090	..xx.xxx.....................................................................................................................................................x................................................................................................................................................................................................................................................................................................................................................................
	O091	..xxxxxx.........................................................................................................................................................................................................................................................................................................................x............................................................................................................................................................................................
	O092	..x.xxxx............................................................................................................................................................................................................x.........................................................................................................................................................................................................................................................................................................
	O093	..xx.xxx...............................................................................x.....................................................xx.....................................................................x.............................................................................................................x...........................................................................................................................................................................................
	O094	..xx.xxx...............................................................................x.....................................................xx.....................................................................x..............................................................................................................x..........................................................................................................................................................................................
	O095	..x.xxxx............................................................................................................................................................................................................x.........................................................................................................................................................................................................................................................................................................
	O096	..........................x....x....................................................................................................................................................................................................................................................................................................xxxxxxxxxxxxxxxxxxxxxxx...................................................................................................................................................................
	O097	..xxxxxx..................................................................xxxxx.x........x.........................................................x.......................................................................................................................................................................................................xxxxxxxxx..........................................................................................................................................................
	O098	.....xx...............x.x.x..x.x....x....xx.xxx.....................................................................................................................................................................................................................................................................................................................xxxxxxxxxxxxxxxx..........................................................................................................................................
	O099	..xxxxxx..................................................................xx.xx.x........x.....................................................................x......................................................................................................................................x.............................................................................xxx.......................................................................................................................................
	O100	..xx.xxx..............................................................................................................................................................x.......................................................................................................................................................................................................................................................................................................................................................
	O101	..xxxxxx.....................................................................................................................................x.........................................................................................................................................................................................................................................xxxxx..................................................................................................................................
	O102	..xxxxxx.......................................................................................................................................................................................................................................................................................................x............................................................................xx................................................................................................................................
	O103	..xxxxxx..............................................................................................x......................................x.............................................................................................................................................................................................................................................x..xxxx............................................................................................................................
	O104	..xxxxxx..................................................................xx.xx.x..............................................................................x..............xx..................................................................................................................................................................................................................x...........................................................................................................................
	O105	..xxxxxx..................................................................xxxxx.x..............................................................................................................................................................................................................................x...................................................................................xxxxx......................................................................................................................
	O106	..xxxxxx................................................................x.........x.....................................................................................................................................................................................................................................................................................................................xxxxxxxxxxxxx.........................................................................................................
	O107	..xxxxxx.....................................................................................................................................x.............................................................................................................................................................................................................................................x............xxx.......x..xxxxxx...................................................................................................
	O108	..xx.xxx.....................................................................................................................................x.............................................................................................................................................................................................................................................................................xx.................................................................................................
	O109	..xx.xxx......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
	O110	..xxxxxx.x...................................................................................................................................................................................................................................................................................................................................................................................................................xxxxxx...........................................................................................
	O111	..xxxxxx..............................................................................................x......................................x...........................................................................................................................................................................................................................................xxx..x....................................x..........................................................................................
	O112	..xxxxx........................x........................................x.........x.xx.x..........xx.....................................................................................................................................................................................................................................................................................xx.................x.x.xx..x...............xxxxxxx...................................................................................
	O113	..xxxxx........................x........................................x.........x.xx.x................................................................................................................................................................................................................................................................................................................xxx.x.xxxxxxx...............xxx.xx....................................................................................
	O114	..xxxxx........................x........................................x.........x.xx.x.................................................................................................................................................................................................................................................................................................xx.................x.x.xx.xx...............xxx.xx.xx.................................................................................
	O115	..xx.xxx.....................................................................................................................................x................................................................................................................................................................................................................................................................................................................................................................................
	O116	..xxxxxx................................................................xxxxxxxx.xx......x........xx...............................................x..........................xx.....x................................................................................................................x....................................................x.................................................................................xxxxxxxx.........................................................................
	O117	..xxxxxx.................................................x............................................x......................................x..........................................................................................................................................................................................................................................x............................................................xxxxxxxxxx...............................................................
	O118	..xxxxxx.................................................x............................................x......................................x...........................................................................................................................................................................................................................................xxx.................................................................x.xx.............................................................
	O119	..xx.xxx......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
	O120	.....xxx................x.x.........x.....x.x.............................................................................................................................................xxx...xxx..xx.......................................................................................................................................................................................................................................................................................................................
	O121	..xxxxxx..............................................................................................x..........................................................................................................................................................................................................................................................................................................................................................x............................................................
	O122	..xxxxxx.x.......................................................................................................................................................................................................................................................................................................................................................................................................................xx...............................x...........................................................
	O123	..xxxxxx.x.......................................................................................................................................................................................................................................................................................................................................................................................................................xx................................x..........................................................
	O124	..xxxxxx.x..............................................................xx.....x..x........................................x.....................................................................................................................................................................................................................................................................................................xx.................................x.........................................................
	O125	..xxxxxx.............................................................................................................................................................................................................................................................................................................................................................................................................................................................xxxx.....................................................
	O126	..xxxxxx..................................................................xx.................................................................x.................x.........................................................................................................................................................................................................................................................................................................x....................................................
	O127	..xxxxxx..................................................................xx.xx.x........x...................................................x.................x..........................................................................................................................................................................................................................................................................................................x...................................................
	O128	..xxxxxx..................................................................xx.xx.x........x.....................................................................x...........................................................................................................................................................................................................................................................................................................x..................................................
	O129	..xxxxxx..................................................................xx.x..x........x...................................................x.................xx.............................................................................................................................................................................................................................................................................................................................................................
	O130	..xxxxxx..................................................................xx.xx.x..............................................................................x....................................................................................................................................................................................................................................x.x.....................................................................xxxx..............................................
	O131	..xxxxxx..................................................................xxxxx.x...................................................................................................................................................................................................................................................................................................................xxx.....................................................................xxx.x.............................................
	O132	..xxxxxx.....................................................................................................................................x...................................................................................................................................................................................................................................................................................................................................x............................................
	O133	....xxxx................x.x..x......x........xx..............x............................................................................................................................x..........................................................................................................................................................x............................................................................................................................xxxxxxxxxxxxxxxx............................
	O134	.....x.x................x.x..x......x........xx......................................................x....................................................................................x..........................................................................................................................................................x..................................................................................................................................x..x......xxxxxx......................
	O135	..xx.xxx.....................................................................................................................................................x................................................................................................................................................................................................................................................................................................................................................................
	O136	..xxxxxx................................................................xx.....x.xx...........................................................................................................................................................................................................................................................................................................................................................................................................................................
	O137	..xxxxxx................................................................x.........x...............xx.....................................................................................................................................................................................................................................................................................xx................xxxx.xx.xx..................x...xx.................................................................................
	O138	..xxxxxx.x..............................................................xxxxxx.x.xx...........................................................................x.x..............x...................................x..............................................................................................................................................................................................................x..............x......................................................xxx...................
	O139	..x.xxxx...................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................x..................
	O140	..xxxxxx................................................................xxxx.xxxxxx...........................................................................xx..............xx..................................................................................................................................................................................x.........................................................................................................................................xxx...............
	O141	xxxxxxxx.x.xx................................................x................x...................................................................................................................................x............................................................................................................................................................................................................................................................................................xxxxx..........
	O142	..xxxxxx..................................................................xx.xx.x.............................................................................xx.............................................................................................................................................................................................x..............................................................................................................................................x.......xx........
	O143	..xxxxxx..............................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................x.......
	O144	.xxxxxxx...xx...........................................................xx.....x.xx...................................................................................................................................x.xx.............................................................................................................................................................................................................................................................................................xxx....
	O145	..xx.xxx..................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................x...
	O146	..xxxxxx..................................................................xx.x..x..............................................................................xx..............x...................................x..................................................................................................................................................................................x....................................................................................................................xx.
	O147	..xxxxxx..................................................................xx.x..x..............................................................................xx.....................................................................................................................................................................................................................................x....................................................................................................................x..
	O148	..xx.xxx.......................................................................................................................................................................................................................................................................................................x.............................................................................................................................................................................................................x
Items [434]
I000:	.....................................................................................................................................................
	oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
I001:	................................................................................................................................................x....
	.ooooooo...oo...........................................................oo.....o.oo...................................................................................................................................o.oo.............................................................................................................................................................................................................................................................................................ooo....
I002:	.................................................................................................................................................x...
	..oo.ooo..................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................o...
I003:	..................................................................................................................................................x..
	..oooooo..................................................................oo.o..o..............................................................................oo..............o...................................o..................................................................................................................................................................................o....................................................................................................................oo.
I004:	....................................................................................................................................................x
	..oo.ooo.......................................................................................................................................................................................................................................................................................................o.............................................................................................................................................................................................................o
I005:	.........................................................................................................................................x...........
	..oooooo................................................................o.........o...............oo.....................................................................................................................................................................................................................................................................................oo................oooo.oo.oo..................o...oo.................................................................................
I006:	..........................................................................................................................................x..........
	..oooooo.o..............................................................oooooo.o.oo...........................................................................o.o..............o...................................o..............................................................................................................................................................................................................o..............o......................................................ooo...................
I007:	...........................................................................................................................................x.........
	..o.oooo...................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................o..................
I008:	............................................................................................................................................x........
	..oooooo................................................................oooo.oooooo...........................................................................oo..............oo..................................................................................................................................................................................o.........................................................................................................................................ooo...............
I009:	.............................................................................................................................................x.......
	oooooooo.o.oo................................................o................o...................................................................................................................................o............................................................................................................................................................................................................................................................................................ooooo..........
I010:	..............................................................................................................................................x......
	..oooooo..................................................................oo.oo.o.............................................................................oo.............................................................................................................................................................................................o..............................................................................................................................................o.......oo........
I011:	...............................................................................................................................................x.....
	..oooooo..............................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................o.......
I012:	................................................................................................................................x....................
	..oooooo..................................................................oo.oo.o........o.....................................................................o...........................................................................................................................................................................................................................................................................................................o..................................................
I013:	..................................................................................................................................x..................
	..oooooo..................................................................oo.oo.o..............................................................................o....................................................................................................................................................................................................................................o.o.....................................................................oooo..............................................
I014:	...................................................................................................................................x.................
	..oooooo..................................................................ooooo.o...................................................................................................................................................................................................................................................................................................................ooo.....................................................................ooo.o.............................................
I015:	....................................................................................................................................x................
	..oooooo.....................................................................................................................................o...................................................................................................................................................................................................................................................................................................................................o............................................
I016:	.....................................................................................................................................x...............
	....oooo................o.o..o......o........oo..............o............................................................................................................................o..........................................................................................................................................................o............................................................................................................................oooooooooooooooo............................
I017:	......................................................................................................................................x..............
	.....o.o................o.o..o......o........oo......................................................o....................................................................................o..........................................................................................................................................................o..................................................................................................................................o..o......oooooo......................
I018:	.........................................................................................................................x...........................
	..oooooo..............................................................................................o..........................................................................................................................................................................................................................................................................................................................................................o............................................................
I019:	..........................................................................................................................x..........................
	..oooooo.o.......................................................................................................................................................................................................................................................................................................................................................................................................................oo...............................o...........................................................
I020:	...........................................................................................................................x.........................
	..oooooo.o.......................................................................................................................................................................................................................................................................................................................................................................................................................oo................................o..........................................................
I021:	............................................................................................................................x........................
	..oooooo.o..............................................................oo.....o..o........................................o.....................................................................................................................................................................................................................................................................................................oo.................................o.........................................................
I022:	.............................................................................................................................x.......................
	..oooooo.............................................................................................................................................................................................................................................................................................................................................................................................................................................................oooo.....................................................
I023:	..............................................................................................................................x......................
	..oooooo..................................................................oo.................................................................o.................o.........................................................................................................................................................................................................................................................................................................o....................................................
I024:	...............................................................................................................................x.....................
	..oooooo..................................................................oo.oo.o........o...................................................o.................o..........................................................................................................................................................................................................................................................................................................o...................................................
I025:	................................................................................................................x....................................
	..ooooo........................o........................................o.........o.oo.o..........oo.....................................................................................................................................................................................................................................................................................oo.................o.o.oo..o...............ooooooo...................................................................................
I026:	.................................................................................................................x...................................
	..ooooo........................o........................................o.........o.oo.o................................................................................................................................................................................................................................................................................................................ooo.o.ooooooo...............ooo.oo....................................................................................
I027:	..................................................................................................................x..................................
	..ooooo........................o........................................o.........o.oo.o.................................................................................................................................................................................................................................................................................................oo.................o.o.oo.oo...............ooo.oo.oo.................................................................................
I028:	....................................................................................................................x................................
	..oooooo................................................................oooooooo.oo......o........oo...............................................o..........................oo.....o................................................................................................................o....................................................o.................................................................................oooooooo.........................................................................
I029:	.....................................................................................................................x...............................
	..oooooo.................................................o............................................o......................................o..........................................................................................................................................................................................................................................o............................................................oooooooooo...............................................................
I030:	......................................................................................................................x..............................
	..oooooo.................................................o............................................o......................................o...........................................................................................................................................................................................................................................ooo.................................................................o.oo.............................................................
I031:	........................................................................................................x............................................
	..oooooo..................................................................oo.oo.o..............................................................................o..............oo..................................................................................................................................................................................................................o...........................................................................................................................
I032:	.........................................................................................................x...........................................
	..oooooo..................................................................ooooo.o..............................................................................................................................................................................................................................o...................................................................................ooooo......................................................................................................................
I033:	..........................................................................................................x..........................................
	..oooooo................................................................o.........o.....................................................................................................................................................................................................................................................................................................................ooooooooooooo.........................................................................................................
I034:	...........................................................................................................x.........................................
	..oooooo.....................................................................................................................................o.............................................................................................................................................................................................................................................o............ooo.......o..oooooo...................................................................................................
I035:	............................................................................................................x........................................
	..oo.ooo.....................................................................................................................................o.............................................................................................................................................................................................................................................................................oo.................................................................................................
I036:	..............................................................................................................x......................................
	..oooooo.o...................................................................................................................................................................................................................................................................................................................................................................................................................oooooo...........................................................................................
I037:	...............................................................................................................x.....................................
	..oooooo..............................................................................................o......................................o...........................................................................................................................................................................................................................................ooo..o....................................o..........................................................................................
I038:	................................................................................................x....................................................
	..........................o....o....................................................................................................................................................................................................................................................................................................ooooooooooooooooooooooo...................................................................................................................................................................
I039:	.................................................................................................x...................................................
	..oooooo..................................................................ooooo.o........o.........................................................o.......................................................................................................................................................................................................ooooooooo..........................................................................................................................................................
I040:	..................................................................................................x..................................................
	.....oo...............o.o.o..o.o....o....oo.ooo.....................................................................................................................................................................................................................................................................................................................oooooooooooooooo..........................................................................................................................................
I041:	...................................................................................................x.................................................
	..oooooo..................................................................oo.oo.o........o.....................................................................o......................................................................................................................................o.............................................................................ooo.......................................................................................................................................
I042:	.....................................................................................................x...............................................
	..oooooo.....................................................................................................................................o.........................................................................................................................................................................................................................................ooooo..................................................................................................................................
I043:	......................................................................................................x..............................................
	..oooooo.......................................................................................................................................................................................................................................................................................................o............................................................................oo................................................................................................................................
I044:	.......................................................................................................x.............................................
	..oooooo..............................................................................................o......................................o.............................................................................................................................................................................................................................................o..oooo............................................................................................................................
I045:	........................................................................................x............................................................
	..oooooo................................................................oo.....o..o........................................o..................................................................................................................................................................................................o...............................................................................................................................................................................................
I046:	.........................................................................................x...........................................................
	..oo.ooo.................o...................................o.................................................................................................................................................................................................................................................................oo.............................................................................................................................................................................................
I047:	...........................................................................................x.........................................................
	..oooooo.........................................................................................................................................................................................................................................................................................................................o............................................................................................................................................................................................
I048:	.............................................................................................x.......................................................
	..oo.ooo...............................................................................o.....................................................oo.....................................................................o.............................................................................................................o...........................................................................................................................................................................................
I049:	..............................................................................................x......................................................
	..oo.ooo...............................................................................o.....................................................oo.....................................................................o..............................................................................................................o..........................................................................................................................................................................................
I050:	................................................................................x....................................................................
	.....oo........................o....................................................................................................................................................................................................................................................................................ooo.......................................................................................................................................................................................................
I051:	...................................................................................x.................................................................
	..oooooo..............................................................................................o................................................................................................................................................................................................................o......................................................................................................................................................................................................
I052:	.....................................................................................x...............................................................
	..oo.ooo................................................................................................................................................................................................................................................................................................................o.....................................................................................................................................................................................................
I053:	......................................................................................x..............................................................
	..oooooo..................................................................oo.o....................oo...........................................................o..............oo.o.......................................................................................................................................oooo.................................................................................................................................................................................................
I054:	.......................................................................................x.............................................................
	..oooooo.....................................................................................................................................................................................................................................................................................................................o................................................................................................................................................................................................
I055:	........................................................................x............................................................................
	....oooo......................................................................................................................................................................................................................................................................................................o...............................................................................................................................................................................................................
I056:	.........................................................................x...........................................................................
	..oo.ooo.......................................................................................................................................................................................................................................................................................................oo.............................................................................................................................................................................................................
I057:	..............................................................................x......................................................................
	..oooooo..............................................................................................................................................................................o..........................................................................................................................oo...........................................................................................................................................................................................................
I058:	...............................................................................x.....................................................................
	....oo.........................o...................................................................................................................................................................................................................................................................................o..........................................................................................................................................................................................................
I059:	................................................................x....................................................................................
	..oo.ooo.....................................................o...............................................................................o..........................................................................................................................................................oo....................................................................................................................................................................................................................
I060:	..................................................................x..................................................................................
	..oooooo..................................................................oo.oo.o..............................................................................o..............oo......o...................................................................................................................o...................................................................................................................................................................................................................
I061:	....................................................................x................................................................................
	..oooooo...................................................................................................................................................................................................................................................................................................o..................................................................................................................................................................................................................
I062:	.....................................................................x...............................................................................
	..oooooo....................................................................................................................................................................................................................................................................................................o.................................................................................................................................................................................................................
I063:	.......................................................................x.............................................................................
	..oooooo.....................................................................................................................................................................................................................................................................................................o................................................................................................................................................................................................................
I064:	...............................................................x.....................................................................................
	..oooooo..............................................................................................................................................................................o.............................................................................................................oooo......................................................................................................................................................................................................................
I065:	.................................................x...................................................................................................
	..o.oooo.......................................................o...................................................................................................................................................................ooooooo....................................................................................................................................................................................................................................................................................
I066:	..................................................x..................................................................................................
	..oooooo..................................................................oo.o...........o.....................................................................o..............oo..........................................................oooooooooo..........................................................................................................................................................................................................................................................................
I067:	....................................................x................................................................................................
	..o..ooo............................................................................................................................................................................................................................................o.........................................................................................................................................................................................................................................................................
I068:	.....................................................x...............................................................................................
	..oooooo..........................................................................................oo.................................................................................oo..............................................................ooooooooooooooooooo......................................................................................................................................................................................................................................................
I069:	......................................................x..............................................................................................
	..oooooo.................o..............................................................................................................................................................................................................................................ooooo.................................................................................................................................................................................................................................................
I070:	.......................................................x.............................................................................................
	..oooooo.................o...............................................................................................................................................................................................................................................ooo.ooooooooooooooooooooooo..........................................................................................................................................................................................................................
I071:	........................................x............................................................................................................
	..oo.ooo............................................................................................................................................................................................................oo........................................................................................................................................................................................................................................................................................................
I072:	...........................................x.........................................................................................................
	ooooooooooooo.........................................................................................................................................................................................................oooo....................................................................................................................................................................................................................................................................................................
I073:	..............................................x......................................................................................................
	..oooooo..................................................................oo.o...............................................................o.................o...............o...................................o.........oo...............................................................................................................................................................................................................................................................................................
I074:	...............................................x.....................................................................................................
	.....oo..........o......o.o..o.o....o.o.o....oo................................................................................................................................................................................oooo...........................................................................................................................................................................................................................................................................................
I075:	................................x....................................................................................................................
	..oooooo..................................................................oo.o.........o.......................................................................o......o...o..ooo..............................................................................................................................................................................................................................................................................................................................................
I076:	.................................x...................................................................................................................
	..oooooo..................................................................oooo....................oo..........................................................................ooooooooo.......................................................................................................................................................................................................................................................................................................................................
I077:	..................................x..................................................................................................................
	..oooooo.....................................................o.........................................................................................................................ooo....................................................................................................................................................................................................................................................................................................................................
I078:	...................................x.................................................................................................................
	.....ooo................o.o..o......o.....o.ooo...........................................................................................................................................ooooooooooooooo.....................................................................................................................................................................................................................................................................................................................
I079:	....................................x................................................................................................................
	...oooo..........................................................................................................................o.o.....................................................................ooo..................................................................................................................................................................................................................................................................................................................
I080:	.....................................x...............................................................................................................
	..oooooo..................................................................oo.o...............................................................o.................o..............oo............................oooo..............................................................................................................................................................................................................................................................................................................
I081:	.......................................x.............................................................................................................
	.ooooooo...oo...........................................................oooo..ooooo...........................................................................oo...............o................................oooo..........................................................................................................................................................................................................................................................................................................
I082:	..........................x..........................................................................................................................
	..oooooo.........................................................................................................................................................o............................................................................................................................................................................................................................................................................................................................................................
I083:	...........................x.........................................................................................................................
	..oo.ooo..................................................................oo.oo.o..............................................................................o..o...........................................................................................................................................................................................................................................................................................................................................................
I084:	............................x........................................................................................................................
	..oo.ooo..........................................................................................oo...............................................................oooo.......................................................................................................................................................................................................................................................................................................................................................
I085:	.............................x.......................................................................................................................
	..o..ooo..................................................................o..oo.o...........................................................o..................o.......oo.....................................................................................................................................................................................................................................................................................................................................................
I086:	..............................x......................................................................................................................
	..oooooo..................................................................oo.o..o.....................o.......................................................ooo........o....................................................................................................................................................................................................................................................................................................................................................
I087:	...............................x.....................................................................................................................
	..o.oooo..................................................................oo.oo.o......o.......................................................................o..........ooo.................................................................................................................................................................................................................................................................................................................................................
I088:	................x....................................................................................................................................
	....oooo.............................................................oo..o.......oo..........................................ooooooooooooo....................................................................................................................................................................................................................................................................................................................................................................................
I089:	.................x...................................................................................................................................
	..oo.ooo..................................................................................................................................ooooo...............................................................................................................................................................................................................................................................................................................................................................................
I090:	..................x..................................................................................................................................
	..oooooo.......................................................................................................................................oo.............................................................................................................................................................................................................................................................................................................................................................................
I091:	...................x.................................................................................................................................
	..oooooo................................................................oo.....o..o........................................o.....................oooooooo.....................................................................................................................................................................................................................................................................................................................................................................
I092:	.....................x...............................................................................................................................
	..o.ooo..............................................................oo..................................................................................ooo..................................................................................................................................................................................................................................................................................................................................................................
I093:	......................x..............................................................................................................................
	..oo.ooo.....................................................................................................................................o..............o.................................................................................................................................................................................................................................................................................................................................................................
I094:	........x............................................................................................................................................
	..oooooo...........................................................................ooooo......................................................................................................................................................................................................................................................................................................................................................................................................................................
I095:	.........x...........................................................................................................................................
	..oooooo..................................................................ooooo.o.......ooooooooooooooooooooooooooooo.........................................................................................................................................................................................................................................................................................................................................................................................................
I096:	..........x..........................................................................................................................................
	..o..ooo.............................................................................................................o........................................................................................................................................................................................................................................................................................................................................................................................................
I097:	...........x.........................................................................................................................................
	....ooo........................o..........o...........................................................................oo......................................................................................................................................................................................................................................................................................................................................................................................................
I098:	............x........................................................................................................................................
	..o..ooo................................................................................................................o.....................................................................................................................................................................................................................................................................................................................................................................................................
I099:	.............x.......................................................................................................................................
	..oo.ooo.................................................................................................................oo...................................................................................................................................................................................................................................................................................................................................................................................................
I100:	...............x.....................................................................................................................................
	..oooooo................................................................oo.....o..o........................................oo.................................................................................................................................................................................................................................................................................................................................................................................................
I101:	.x...................................................................................................................................................
	....ooo......oooooooooooooooooooooooooooooooooooooooo.........................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I102:	..x..................................................................................................................................................
	....ooo.........oooo.oo.o.o..ooo.oooo.ooooo.ooo....o.oooooo...................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I103:	....x................................................................................................................................................
	..oooooo.................o..........o......................ooooooo............................................................................................................................................................................................................................................................................................................................................................................................................................................................
I104:	.....x...............................................................................................................................................
	..oo.ooo..........................................................o...........................................................................................................................................................................................................................................................................................................................................................................................................................................................
I105:	......x..............................................................................................................................................
	...ooooo.................o...................................o.....ooooo......................................................................................................................................................................................................................................................................................................................................................................................................................................................
I106:	.......x.............................................................................................................................................
	..oooooo................................................................ooooooooooo...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I107:	..................................................................................................................................................xx.
	..oooooo..................................................................oo.o..o..............................................................................oo.....................................................................................................................................................................................................................................o....................................................................................................................o..
I108:	..........................................................................................................................................x.......x..
	..oooooo..................................................................oo.o..................................................................................o..............o...................................o..........................................................................................................................................................................................................................................................................................................
I109:	..........................................................................................................................................x.x........
	..oooooo................................................................oooo.o.o.oo...........................................................................o................o..............................................................................................................................................................................................................................................................................................................................................
I110:	............................................................................................................................................x.x......
	..oooooo..................................................................oo.oo.o.............................................................................oo............................................................................................................................................................................................................................................................................................................................................o.................
I111:	..................................................................................................................................xx.................
	..oooooo..................................................................oo.oo.o...................................................................................................................................................................................................................................................................................................................o.o.....................................................................ooo...............................................
I112:	.....................................................................................................................................xx..............
	.....o.o................o.o..o......o........oo...........................................................................................................................................o..........................................................................................................................................................o..................................................................................................................................o..o..................................
I113:	............................................................................................................................x.............x..........
	..oooooo.o..............................................................oo.....o..o...............................................................................................................................................................................................................................................................................................................................................o...........................................................................................
I114:	................................................................................................................x........................x...........
	..ooooo.................................................................o.........o...............oo.....................................................................................................................................................................................................................................................................................oo.................o.o.oo..o..................o......................................................................................
I115:	..................................................................................................................x......................x...........
	..ooooo.................................................................o.........o......................................................................................................................................................................................................................................................................................................oo.................o.o.oo.oo......................oo.................................................................................
I116:	................................................................................................................x.x..................................
	..ooooo........................o........................................o.........o.oo.o.................................................................................................................................................................................................................................................................................................oo.................o.o.oo..o...............ooo.oo....................................................................................
I117:	.................................................................................................................xx..................................
	..ooooo........................o........................................o.........o.oo.o....................................................................................................................................................................................................................................................................................................................o.o.oo.oo...............ooo.oo....................................................................................
I118:	....................................................................................................................x....................x...........
	..oooooo................................................................o.........o...............oo..........................................................................................................................................................................................................................................................................................................................................................................................................................
I119:	....................................................................................................................x.....................x..........
	..oooooo................................................................oooooo.o.oo............................................................................................o.................................................................................................................................................................................................................................................................o............................................................................
I120:	....................................................................................................................x.......................x........
	..oooooo................................................................oooo.ooo.oo...........................................................................................oo..............................................................................................................................................................................................................................................................................................................................................
I121:	.....................................................................................................................xx..............................
	..oooooo.................................................o............................................o......................................o...............................................................................................................................................................................................................................................................................................................o................................................................
I122:	.........................................................................................................x.........................x.................
	..oooooo..................................................................ooooo.o...................................................................................................................................................................................................................................................................................................................ooo.......................................................................................................................
I123:	..........................................................................................................x..............................x...........
	..oooooo................................................................o.........o........................................................................................................................................................................................................................................................................................................................oooo.oo.oo.........................................................................................................
I124:	..........................................................................................................x......x...................................
	..ooooo.................................................................o.........o.....................................................................................................................................................................................................................................................................................................................ooo.o.ooooooo.........................................................................................................
I125:	..........................................................................................................xx.........................................
	..oooooo................................................................................................................................................................................................................................................................................................................................................................................................ooo.......o...........................................................................................................
I126:	...............................................................................................................x......x..............................
	..oooooo..............................................................................................o......................................o...........................................................................................................................................................................................................................................ooo..................................................................................................................................
I127:	.................................................................................................x..........................................x........
	..oooooo..................................................................oo.oo.o.................................................................................................................................................................................................................................................................................o...........................................................................................................................................................
I128:	.................................................................................................x............................................x......
	..oooooo..................................................................oo.oo.o............................................................................................................................................................................................................................................................................o................................................................................................................................................................
I129:	.................................................................................................x..................x................................
	..oooooo..................................................................ooooo..........o.........................................................o.......................................................................................................................................................................................................o..................................................................................................................................................................
I130:	...................................................................................................x................x................................
	..oooooo..................................................................oo.oo..........o............................................................................................................................................................................................................o.......................................................................................................................................................................................................................
I131:	.....................................................................................................x...............x...............................
	..oooooo.....................................................................................................................................o..........................................................................................................................................................................................................................................o.....................................................................................................................................
I132:	.......................................................................................................x.......x.....................................
	..oooooo..............................................................................................o......................................o.............................................................................................................................................................................................................................................o..o...............................................................................................................................
I133:	.............................................................................................xx......................................................
	..oo.ooo...............................................................................o.....................................................oo.....................................................................o.........................................................................................................................................................................................................................................................................................................
I134:	............................................................................................x..x.....................................................
	..o.oooo............................................................................................................................................................................................................o.........................................................................................................................................................................................................................................................................................................
I135:	............................................................x...............................................................x........................
	..oooooo.o..............................................................oo.....o..o........................................o..................................................................................................................................................................................................................................................................................................................................................................................................
I136:	................................................x................................................................................x...................
	..oooooo..................................................................oo.o..o........o...................................................o.................oo.............................................................................................................................................................................................................................................................................................................................................................
I137:	..................................................x.................................................................x................................
	..oooooo..................................................................oo.o...........o....................................................................................oo..............................................................................................................................................................................................................................................................................................................................................
I138:	......................................................xx.............................................................................................
	..oooooo.................o...............................................................................................................................................................................................................................................ooo..................................................................................................................................................................................................................................................
I139:	...........................................x....................................................................................................x....
	.ooooooo...oo.........................................................................................................................................................................................................o.oo....................................................................................................................................................................................................................................................................................................
I140:	............................................xx.......................................................................................................
	...ooooo..................................................................................................................................................................................................................ooo.................................................................................................................................................................................................................................................................................................
I141:	..............................................x...................................................................................................x..
	..oooooo..................................................................oo.o.................................................................................o...............o...................................o..........................................................................................................................................................................................................................................................................................................
I142:	.................................x..................................................................................x................................
	..oooooo..................................................................oooo....................oo..........................................................................oo.....o........................................................................................................................................................................................................................................................................................................................................
I143:	.................................x....................................................x..............................................................
	..oooooo..................................................................oo.o....................oo..........................................................................oo.o............................................................................................................................................................................................................................................................................................................................................
I144:	.................................x................................x..................................................................................
	..oooooo..................................................................oo.o................................................................................................oo......o.......................................................................................................................................................................................................................................................................................................................................
I145:	.................................x...................x...............................................................................................
	..oooooo..........................................................................................oo.................................................................................oo.......................................................................................................................................................................................................................................................................................................................................
I146:	...................................x.................................................................................................x...............
	.....ooo................o.o..o......o........oo...........................................................................................................................................o...................................................................................................................................................................................................................................................................................................................................
I147:	...................................x....................................................................................x............................
	.....ooo................o.o.........o.....o.o.............................................................................................................................................ooo...ooo..oo.......................................................................................................................................................................................................................................................................................................................
I148:	.....................................x........x......................................................................................................
	..oooooo..................................................................oo.o...............................................................o.................o...............o..............................................................................................................................................................................................................................................................................................................................................
I149:	.......................................x........................................................................................................x....
	.ooooooo...oo...........................................................oo.....o.oo...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I150:	.......................................x..........................................................................................................x..
	..oooooo..................................................................oo....o..............................................................................o...............o...................................o..........................................................................................................................................................................................................................................................................................................
I151:	.......................................x..................................................................................................x..........
	..oooooo................................................................oooo...o.oo...........................................................................o................o...................................o..........................................................................................................................................................................................................................................................................................................
I152:	.......................................x....................................................................................................x........
	..oooooo................................................................oooo..ooooo...........................................................................oo...............o..............................................................................................................................................................................................................................................................................................................................................
I153:	.......................................x.....................................................................................................x.......
	.ooooooo...oo.................................................................o...................................................................................................................................o...........................................................................................................................................................................................................................................................................................................
I154:	..............................x...........................................................................................................x..........
	..oooooo..................................................................oo.o................................................................................o.o.............................................................................................................................................................................................................................................................................................................................................................
I155:	.........................x....x......................................................................................................................
	..o.oooo..................................................................oo.o..o.............................................................................ooo.............................................................................................................................................................................................................................................................................................................................................................
I156:	...............................xx....................................................................................................................
	..o.oooo..................................................................oo.o.........o.......................................................................o..........o...................................................................................................................................................................................................................................................................................................................................................
I157:	................x...................x................................................................................................................
	....ooo..........................................................................................................................o.o..........................................................................................................................................................................................................................................................................................................................................................................................
I158:	.................x........................x..........................................................................................................
	..oo.ooo...................................................................................................................................oooo...............................................................................................................................................................................................................................................................................................................................................................................
I159:	..................x.....................................x............................................................................................
	..oooooo........................................................................................................................................o.............................................................................................................................................................................................................................................................................................................................................................................
I160:	...................x................................................................................................x................................
	..oooooo................................................................oo.....o..o................................................................o..........................................................................................................................................................................................................................................................................................................................................................................
I161:	........x.......................x....................................................................................................................
	..oooooo...............................................................................o......................................................................................................................................................................................................................................................................................................................................................................................................................................
I162:	.........x............................................................................................................................x..............
	.....o.o.............................................................................................o........................................................................................................................................................................................................................................................................................................................................................................................................................
I163:	.........x..........................................................................................................x................................
	..oooooo..................................................................ooooo..........o........oo..........................................................................................................................................................................................................................................................................................................................................................................................................................
I164:	.........x.......................................................................................x...................................................
	..oooooo..................................................................ooooo.o........o....................................................................................................................................................................................................................................................................................................................................................................................................................................
I165:	.........x....................x......................................................................................................................
	..oooooo..................................................................oo.o..o.....................o.......................................................................................................................................................................................................................................................................................................................................................................................................................
I166:	...............x............................................................x........................................................................
	..oooooo....................................................................................................................o.................................................................................................................................................................................................................................................................................................................................................................................................
I167:	x..........................................x.........................................................................................................
	ooooooooooooo.................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I168:	.xx..................................................................................................................................................
	....ooo.........oooo.oo.o.o..ooo.oooo.ooooo.ooo....o..........................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I169:	....x................................................................................................................................x...............
	....oooo............................o........................o................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I170:	....x....................................................................................x...........................................................
	..oo.ooo.................o...................................o................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I171:	....x............................................x...................................................................................................
	..o.oooo.......................................................o..............................................................................................................................................................................................................................................................................................................................................................................................................................................................
I172:	.x..x................................................................................................................................................
	....ooo..................o..........o.........................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I173:	......x.........x....................................................................................................................................
	....oooo.............................................................oo.......................................................................................................................................................................................................................................................................................................................................................................................................................................................
I174:	....x.x..............................................................................................................................................
	...ooooo.................o...................................o................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I175:	.......x....................................................................................................................................x........
	..oooooo................................................................oooo.oooooo...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I176:	.......x............................................................................................................x................................
	..oooooo................................................................oooooooo.oo...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I177:	..................................................................................................................................x...............xx.
	..oooooo..................................................................oo.o..o..............................................................................o......................................................................................................................................................................................................................................o.......................................................................................................................
I178:	................................................................................................................x.x......................x...........
	..ooooo.................................................................o.........o......................................................................................................................................................................................................................................................................................................oo.................o.o.oo..o.........................................................................................................
I179:	................................................................................................................xxx..................................
	..ooooo........................o........................................o.........o.oo.o....................................................................................................................................................................................................................................................................................................................o.o.oo..o...............ooo.oo....................................................................................
I180:	....................................................................................................................x.....................x.x........
	..oooooo................................................................oooo.o.o.oo............................................................................................o..............................................................................................................................................................................................................................................................................................................................................
I181:	................................................................................................................x...x....................x...........
	..ooooo.................................................................o.........o...............oo..........................................................................................................................................................................................................................................................................................................................................................................................................................
I182:	.........................................................................................................x........................xx.................
	..oooooo..................................................................oo.oo.o...................................................................................................................................................................................................................................................................................................................o.o.......................................................................................................................
I183:	..........................................................................................................xx.....x...................................
	..ooooo.................................................................................................................................................................................................................................................................................................................................................................................................ooo.......o...........................................................................................................
I184:	................................................................................................x....................................xx..............
	..........................o..........................................................................................................................................................................................................................................................................................................................o........................................................................................................................................................................
I185:	...................................................................................................x...........................xx....................
	..oooooo..................................................................oo.oo.o........o.....................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I186:	.....................................................................................................x.........x......x..............................
	..oooooo.....................................................................................................................................o...........................................................................................................................................................................................................................................ooo..................................................................................................................................
I187:	.......................................................................................................x.......x......x..............................
	..oooooo..............................................................................................o......................................o.............................................................................................................................................................................................................................................o..................................................................................................................................
I188:	..........................................................................x...........................x..x...........................................
	..oooooo.......................................................................................................................................................................................................................................................................................................o..............................................................................................................................................................................................................
I189:	..................................................................x.....................................x...................................x........
	..oooooo..................................................................oo.oo.o..............................................................................o..............oo..............................................................................................................................................................................................................................................................................................................................................
I190:	............................................................x...............................................................x.............x..........
	..oooooo.o..............................................................oo.....o..o...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I191:	...............................................................x...................................x................x................................
	..oooooo..............................................................................................................................................................................................................................................................................................o.......................................................................................................................................................................................................................
I192:	................................................x..............................................................................x.x...................
	..oooooo..................................................................oo.o..o........o...................................................o.................o..............................................................................................................................................................................................................................................................................................................................................................
I193:	........................................x....................................................xx......................................................
	..oo.ooo............................................................................................................................................................................................................o.........................................................................................................................................................................................................................................................................................................
I194:	..............................................x...........................................................................................x.......x..
	..oooooo..................................................................oo.o.................................................................................................o...................................o..........................................................................................................................................................................................................................................................................................................
I195:	.................................x..................................................................................x.....................x..........
	..oooooo..................................................................oooo.................................................................................................o..............................................................................................................................................................................................................................................................................................................................................
I196:	.................................x....................................................x.............................x................................
	..oooooo..................................................................oo.o....................oo..........................................................................oo..............................................................................................................................................................................................................................................................................................................................................
I197:	.................................x...................x..............................................................x................................
	..oooooo..........................................................................................oo.................................................................................o........................................................................................................................................................................................................................................................................................................................................
I198:	...................................x.................................................................................................xx..............
	.....o.o................o.o..o......o........oo...........................................................................................................................................o...................................................................................................................................................................................................................................................................................................................................
I199:	...................................x....................................................................................x............x...............
	.....ooo................o.o.........o.....................................................................................................................................................o...................................................................................................................................................................................................................................................................................................................................
I200:	...................................x.........................................x..........................................x............................
	.....ooo............................o.......o.............................................................................................................................................o.....o....o........................................................................................................................................................................................................................................................................................................................
I201:	.......................................x..................................................................................................x.x........
	..oooooo................................................................oooo...o.oo...........................................................................o................o..............................................................................................................................................................................................................................................................................................................................................
I202:	.......................................x....................................................................................................x.x......
	..oooooo..................................................................oo..o.o.............................................................................oo..............................................................................................................................................................................................................................................................................................................................................................
I203:	.......................................x............................................................................x.......................x........
	..oooooo................................................................oooo..oo.oo............................................................................................o..............................................................................................................................................................................................................................................................................................................................................
I204:	.......................................x......x...................................................................................................x..
	..oooooo..................................................................oo...................................................................................o...............o...................................o..........................................................................................................................................................................................................................................................................................................
I205:	............................x...x...................................................................x................................................
	..oo.ooo..............................................................................................................................................................o.......................................................................................................................................................................................................................................................................................................................................................
I206:	..............................x.............................................................................................................x.x......
	..oooooo..................................................................oo.o..o.............................................................................oo..............................................................................................................................................................................................................................................................................................................................................................
I207:	.........................x....x...........................................................................................................x..........
	..o.oooo..................................................................oo.o................................................................................o.o.............................................................................................................................................................................................................................................................................................................................................................
I208:	.................x...........x............x..........................................................................................................
	..o..ooo....................................................................................................................................o.................................................................................................................................................................................................................................................................................................................................................................................
I209:	...................x.............................................................................x..................x................................
	..oooooo...........................................................................................................................................o..........................................................................................................................................................................................................................................................................................................................................................................
I210:	........x......................xx....................................................................................................................
	..o.oooo...............................................................................o......................................................................................................................................................................................................................................................................................................................................................................................................................................
I211:	.........x.......................................................................................x..................x................................
	..oooooo..................................................................ooooo..........o....................................................................................................................................................................................................................................................................................................................................................................................................................................
I212:	.........x.......................x..................................................................................x................................
	..oooooo..................................................................oooo....................oo..........................................................................................................................................................................................................................................................................................................................................................................................................................
I213:	x..........................................x.................................................................................................x.......
	oooooooo.o.oo.................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I214:	..x..................................................................................................................xx..............................
	....ooo..................................................o....................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I215:	.xx..................................................................................................................................x...............
	....ooo.................o.o..o......o........oo...............................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I216:	.xx...............................................................................................x..................................................
	.....oo...............o.o.o..o.o....o....oo.ooo...............................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I217:	.xx............................................x.....................................................................................................
	.....oo..........o......o.o..o.o....o.o.o....oo...............................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I218:	.xx........x.........................................................................................................................................
	....ooo........................o..........o...................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I219:	....x.................................................xx.............................................................................................
	..oooooo.................o....................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I220:	....x.............................x..........................................................................................................x.......
	..oooooo.....................................................o................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I221:	......x.........x....x...............................................................................................................................
	....ooo..............................................................oo.......................................................................................................................................................................................................................................................................................................................................................................................................................................................
I222:	....x.x..................................................................................x...........................................................
	...o.ooo.................o...................................o................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I223:	.......x............................................................................................................x.....................x..........
	..oooooo................................................................oooooo.o.oo...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I224:	.......x............................................................................................................x.......................x........
	..oooooo................................................................oooo.ooo.oo...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I225:	.......x...............................x....................................................................................................x........
	..oooooo................................................................oooo..ooooo...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I226:	..........................................................................................................x......xx......................x...........
	..ooooo.................................................................o.........o.........................................................................................................................................................................................................................................................................................................................o.o.oo.oo.........................................................................................................
I227:	..............................................................................................................x...........xxx........................
	..oooooo.o.......................................................................................................................................................................................................................................................................................................................................................................................................................oo...........................................................................................
I228:	.....................................................................................................x.........x......x..................x...........
	..oooooo.................................................................................................................................................................................................................................................................................................................................................................................oo...................................................................................................................................
I229:	.......................................................................................................x.......x.....xx..............................
	..oooooo..............................................................................................o......................................o................................................................................................................................................................................................................................................................................................................................................................................
I230:	..................................................................x.....................................x...................................x.....x..
	..oooooo..................................................................oo.o..o..............................................................................o...............o..............................................................................................................................................................................................................................................................................................................................................
I231:	..................................................................x.....................................x...........x.......................x........
	..oooooo..................................................................oo.oo...............................................................................................oo..............................................................................................................................................................................................................................................................................................................................................
I232:	...................................x....................................................................................x............xx..............
	.....o.o................o.o.........o.....................................................................................................................................................o...................................................................................................................................................................................................................................................................................................................................
I233:	...................................x.........................................x..........................................x............x...............
	.....ooo............................o.....................................................................................................................................................o...................................................................................................................................................................................................................................................................................................................................
I234:	.......................................x............................................................................x.....................x.x........
	..oooooo................................................................oooo...o.oo............................................................................................o..............................................................................................................................................................................................................................................................................................................................................
I235:	.......................................x..........................x.....................................x...................................x........
	..oooooo..................................................................oo..o.o..............................................................................o...............o..............................................................................................................................................................................................................................................................................................................................................
I236:	.......................................x......x...........................................................................................x.......x..
	..oooooo..................................................................oo...................................................................................................o...................................o..........................................................................................................................................................................................................................................................................................................
I237:	............................x...x...................................................x...............x................................................
	..o..ooo..............................................................................................................................................................o.......................................................................................................................................................................................................................................................................................................................................................
I238:	..............................x...........................................................................................................x.x.x......
	..oooooo..................................................................oo.o................................................................................o...............................................................................................................................................................................................................................................................................................................................................................
I239:	..............................x........x....................................................................................................x.x......
	..oooooo..................................................................oo....o.............................................................................oo..............................................................................................................................................................................................................................................................................................................................................................
I240:	.........................x....x.............................................................................................................x.x......
	..o.oooo..................................................................oo.o..o.............................................................................oo..............................................................................................................................................................................................................................................................................................................................................................
I241:	.................x........................x..................................................xx......................................................
	..oo.ooo.....................................................................................................................................oo...............................................................................................................................................................................................................................................................................................................................................................................
I242:	........x.......................................................................................................xxx..................................
	..ooooo.............................................................................oo.o......................................................................................................................................................................................................................................................................................................................................................................................................................................
I243:	........x.......................x............................................................xx......................................................
	..oo.ooo...............................................................................o......................................................................................................................................................................................................................................................................................................................................................................................................................................
I244:	.........x.......................x....................................................x.............................x................................
	..oooooo..................................................................oo.o....................oo..........................................................................................................................................................................................................................................................................................................................................................................................................................
I245:	.xx............................................x..................................................x..................................................
	.....oo.................o.o..o.o....o........oo...............................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I246:	.xx................................x..............................................................x..................................................
	.....oo.................o.o..o......o.....o.ooo...............................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I247:	.xx........x......................................................................................x..................................................
	.....oo........................o..........o...................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I248:	....x.................................................xx.................................x...........................................................
	..oo.ooo.................o....................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I249:	.xx.x................................................................................................................................x...............
	....ooo.............................o.........................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I250:	....x.x...............................................xx.............................................................................................
	...ooooo.................o....................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I251:	....x.x...........................x..........................................................................................................x.......
	...ooooo.....................................................o................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I252:	.......x............................................................................................................x.....................x.x........
	..oooooo................................................................oooo.o.o.oo...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I253:	.......x...............................x............................................................................x.......................x........
	..oooooo................................................................oooo..oo.oo...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I254:	.........................................................................................................x........................xx..............xx.
	..oooooo..................................................................oo.o..o.....................................................................................................................................................................................................................................................................................................................o.......................................................................................................................
I255:	..........................................................................................................x.....xxx......................x...........
	..ooooo.................................................................o.........o.........................................................................................................................................................................................................................................................................................................................o.o.oo..o.........................................................................................................
I256:	..............................................................................................................x...........xxx.............x..........
	..oooooo.o........................................................................................................................................................................................................................................................................................................................................................................................................................o...........................................................................................
I257:	.....................................................................................................x.x...x...x......x..............................
	..oooooo.....................................................................................................................................o.............................................................................................................................................................................................................................................o..................................................................................................................................
I258:	.........................................................................xx...........................x..x..........................................x
	..oo.ooo.......................................................................................................................................................................................................................................................................................................o..............................................................................................................................................................................................................
I259:	................................................x..................................................x...........................xxx...................
	..oooooo..................................................................oo.o..o........o.....................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I260:	........................................x...................................................xxxx.....................................................
	..o..ooo............................................................................................................................................................................................................o.........................................................................................................................................................................................................................................................................................................
I261:	.................................x...................x.........x..x...........x......................................................................
	..oooooo..............................................................................................................................................................................o.......................................................................................................................................................................................................................................................................................................................................
I262:	...................................x.........................................x..........................................x............xx..............
	.....o.o............................o.....................................................................................................................................................o...................................................................................................................................................................................................................................................................................................................................
I263:	.....................................x........x.x..............................................................................x.x...................
	..oooooo..................................................................oo.o...............................................................o.................o..............................................................................................................................................................................................................................................................................................................................................................
I264:	.......................................x..........................x.....................................x...................................x.....x..
	..oooooo..................................................................oo....o..............................................................................o...............o..............................................................................................................................................................................................................................................................................................................................................
I265:	.......................................x..........................x.....................................x...........x.......................x........
	..oooooo..................................................................oo..o................................................................................................o..............................................................................................................................................................................................................................................................................................................................................
I266:	..............................x........x..................................................................................................x.x.x......
	..oooooo..................................................................oo..................................................................................o...............................................................................................................................................................................................................................................................................................................................................................
I267:	.........................x....x...........................................................................................................x.x.x......
	..o.oooo..................................................................oo.o................................................................................o...............................................................................................................................................................................................................................................................................................................................................................
I268:	.........................x....x........x....................................................................................................x.x......
	..o.oooo..................................................................oo....o.............................................................................oo..............................................................................................................................................................................................................................................................................................................................................................
I269:	........x.......................x...............................................................................xxx..................................
	..ooooo................................................................................o......................................................................................................................................................................................................................................................................................................................................................................................................................................
I270:	........x......................xx............................................................xx......................................................
	..o..ooo...............................................................................o......................................................................................................................................................................................................................................................................................................................................................................................................................................
I271:	.........x.......................................................................................x.x...........................xx....................
	..oooooo..................................................................oo.oo.o........o....................................................................................................................................................................................................................................................................................................................................................................................................................................
I272:	x......................................x...x.................................................................................................x..x....
	.ooooooo...oo.................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I273:	.xx............................................x................................................x.x..................................................
	..........................o....o..............................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I274:	.xx................................x..............................................................x.....................x............................
	.....oo.................o.o.........o.....o.o.................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I275:	....x.............................x.............................x........................x...................................................x.......
	..oo.ooo.....................................................o................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I276:	....x..............................x.........................................x..........................................x............x...............
	.....ooo............................o.........................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I277:	....x.x...............................................xx.................................x...........................................................
	...o.ooo.................o....................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I278:	....x.x...........................x..................................................................................................x.......x.......
	....oooo.....................................................o................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I279:	.x..x.x...............................................xx.............................................................................................
	....ooo..................o....................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I280:	.......x...............................x............................................................................x.....................x.x........
	..oooooo................................................................oooo...o.oo...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I281:	.......x.x.......................................................................................x.......x.........................x.................
	..oooooo..................................................................ooooo.o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I282:	.....................................................................................................x.........xx.x...x..................x...........
	..ooooo..................................................................................................................................................................................................................................................................................................................................................................................oo...................................................................................................................................
I283:	................................................x.x................................................x...........................xxx...................
	..oooooo..................................................................oo.o...........o.....................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I284:	.....................................x........x.x.............................................................................xx.x...................
	..oooooo..................................................................oo.................................................................o.................o..............................................................................................................................................................................................................................................................................................................................................................
I285:	..............................x.................x.............x..................................................................x................xx.
	..oooooo..................................................................oo.o..o..............................................................................oo.............................................................................................................................................................................................................................................................................................................................................................
I286:	.........................x....x........x..................................................................................................x.x.x......
	..o.oooo..................................................................oo..................................................................................o...............................................................................................................................................................................................................................................................................................................................................................
I287:	.......................xx........................................x................x.......x............................................x.............
	..oo.ooo.....................................................................................................................................................o................................................................................................................................................................................................................................................................................................................................................................
I288:	........x......................xx...............................................................................xxx..................................
	..o.ooo................................................................................o......................................................................................................................................................................................................................................................................................................................................................................................................................................
I289:	.........x.......................................................................................x.x................x..........xx....................
	..oooooo..................................................................oo.oo..........o....................................................................................................................................................................................................................................................................................................................................................................................................................................
I290:	.........x.......................x...................x................................x.............................x....................x...........
	..oooooo..........................................................................................oo..........................................................................................................................................................................................................................................................................................................................................................................................................................
I291:	...............x...x.......................................xx...........................x...................................x........................
	..oooooo................................................................oo.....o..o........................................o..................................................................................................................................................................................................................................................................................................................................................................................................
I292:	.xx................................x.........................................x....................x.....................x............................
	.....oo.............................o.......o.................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I293:	.xx................................x...........x..................................................x..................................x...............
	.....oo.................o.o..o......o........oo...............................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I294:	.xx........x....................................................................................................xxx..................................
	....ooo........................o..............................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I295:	.xx........x.......................x..............................................................x.....................x............................
	.....oo...................................o...................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I296:	....x..............................x.........................................x..........................................x............xx..............
	.....o.o............................o.........................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I297:	....x.x...........................x.............................x........................x...................................................x.......
	...o.ooo.....................................................o................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I298:	.x..x.x...............................................xx.................................x...........................................................
	.....oo..................o....................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I299:	.......x.x.......................................................................................x.......x..........x..............x.................
	..oooooo..................................................................ooooo...............................................................................................................................................................................................................................................................................................................................................................................................................................................
I300:	................................x....x............x...............x...................x.................x...................................x........
	..oooooo..................................................................oo.o.................................................................................o..............oo..............................................................................................................................................................................................................................................................................................................................................
I301:	..............................x.................x.............x..................................................................x........x.......xx.
	..oooooo..................................................................oo.o..................................................................................o.............................................................................................................................................................................................................................................................................................................................................................
I302:	.........................x....x.................x.............x..................................................................x................xx.
	..o.oooo..................................................................oo.o..o..............................................................................oo.............................................................................................................................................................................................................................................................................................................................................................
I303:	........x.......................x............................................................xx.................xxx..................................
	..oo.oo................................................................................o......................................................................................................................................................................................................................................................................................................................................................................................................................................
I304:	.........x......................................x................................................x.x...........................xxx...................
	..oooooo..................................................................oo.o..o........o....................................................................................................................................................................................................................................................................................................................................................................................................................................
I305:	.........x.......................x...................x................................x.........................x...x....................x...........
	..ooooo...........................................................................................oo..........................................................................................................................................................................................................................................................................................................................................................................................................................
I306:	.........x..................x....x...................x................................x.............................x....................x...........
	..oo.ooo..........................................................................................oo..........................................................................................................................................................................................................................................................................................................................................................................................................................
I307:	.xx................................x...........x..................................................x..................................xx..............
	.....o..................o.o..o......o........oo...............................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I308:	.xx................................x...........x..................................................x.....................x............x...............
	.....oo.................o.o.........o.........................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I309:	.xx........x...................................................................x................................xxx..................................
	....oo.........................o..............................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I310:	....x.x...........................x.............................x........................x...........................................x.......x.......
	.....ooo.....................................................o................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I311:	.......x...............................x............................................................................x...................x.x.x...x....
	..oooooo................................................................oo.....o.oo...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I312:	..................................................................x................................x....x......................xx.x.........x.x......
	..oooooo..................................................................oo.oo.o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I313:	.........................x....x.................x.............x..................................................................x........x.......xx.
	..o.oooo..................................................................oo.o..................................................................................o.............................................................................................................................................................................................................................................................................................................................................................
I314:	........x......................xx............................................................xx.................xxx..................................
	..o..oo................................................................................o......................................................................................................................................................................................................................................................................................................................................................................................................................................
I315:	.........x..................x....x...................x................................x.........................x...x....................x...........
	..oo.oo...........................................................................................oo..........................................................................................................................................................................................................................................................................................................................................................................................................................
I316:	.........x....................x....................................................x...................x.......x.....xx..x...........................
	..oooooo..............................................................................................o.......................................................................................................................................................................................................................................................................................................................................................................................................................
I317:	.xx................................x...........x..................................................x.....................x............xx..............
	.....o..................o.o.........o.........................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I318:	.......x........x......................x............................................................................x...................x.x.x...x....
	....oooo.................................................................o.......oo...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I319:	.......x.x.......................x...............................................................x.......x..........x..............x......x..........
	..oooooo..................................................................oooo................................................................................................................................................................................................................................................................................................................................................................................................................................................
I320:	................................x....x........x...x...............x...................x.................x...................................x.....x..
	..oooooo..................................................................oo.o.................................................................................o...............o..............................................................................................................................................................................................................................................................................................................................................
I321:	................................xx...x............x...............x...................x.................x...........x.......................x........
	..oooooo..................................................................oo.o................................................................................................oo..............................................................................................................................................................................................................................................................................................................................................
I322:	.......................................x..........................x................................x....x......................xx.x.........x.x......
	..oooooo..................................................................oo..o.o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I323:	...........................x......................................x................................x....x......................xx.x.........x.x......
	..oo.ooo..................................................................oo.oo.o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I324:	...............................x..................................x................................x....x......................xx.x.........x.x......
	..o.oooo..................................................................oo.oo.o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I325:	.........x......................................x.x..............................................x.x................x..........xxx...................
	..oooooo..................................................................oo.o...........o....................................................................................................................................................................................................................................................................................................................................................................................................................................
I326:	x..........................................x................x.................................................x...........xxx.............x..x.......
	..oooooo.o....................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I327:	.xx................................x...........x................................................x.x.....................x............xx..............
	..........................o...................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I328:	.xx........x...................................x................................x.................x.............xxx..................................
	.....oo........................o..............................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I329:	.xx.x..............................x...........x.............................x....................x.....................x............x...............
	.....oo.............................o.........................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I330:	................................x....x.x......x...x...............x...................x.................x...................................x.....x..
	..oooooo..................................................................oo...................................................................................o...............o..............................................................................................................................................................................................................................................................................................................................................
I331:	...........................x...........x..........................x................................x....x......................xx.x.........x.x......
	..oo.ooo..................................................................oo..o.o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I332:	...............................x.......x..........................x................................x....x......................xx.x.........x.x......
	..o.oooo..................................................................oo..o.o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I333:	.xx........x...................................x...............................xx.................x.............xxx..................................
	.....o.........................o..............................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I334:	.xx.x..............................x...........x.............................x....................x.....................x............xx..............
	.....o..............................o.........................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I335:	...........................x...x.........x........................x................................x....x......................xx.x.........x.x......
	..o..ooo..................................................................oo.oo.o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I336:	.xx........x...................................x...............................xx...............x.x.............xxx..................................
	...............................o..............................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I337:	................................xx...x........x...x...............x...................x.................x...........x.....................x.x.....x..
	..oooooo..................................................................oo.o.................................................................................................o..............................................................................................................................................................................................................................................................................................................................................
I338:	...........................x...x.......x.x........................x................................x....x......................xx.x.........x.x......
	..o..ooo..................................................................oo..o.o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I339:	...........................x.x.x.........x........................x................................x....x......................xx.x.........x.x......
	..o..ooo..................................................................o..oo.o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I340:	................................xx...x.x......x...x...............x...................x.................x...........x.....................x.x.....x..
	..oooooo..................................................................oo...................................................................................................o..............................................................................................................................................................................................................................................................................................................................................
I341:	...........................x.x.x.......x.x........................x................................x....x......................xx.x.........x.x......
	..o..ooo..................................................................o...o.o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I342:	.......x.x........................................................x..............................x.x....xx.....................xx.xx........x.x......
	..oooooo..................................................................oo.oo.o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I343:	.......x.......x...x...................x...................xx...........................x...........................x.......x...........x.x.x...x....
	..oooooo................................................................oo.....o..o...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I344:	..............................x.................x.............x...x................................x....x......................xxxx.........x.x...xx.
	..oooooo..................................................................oo.o..o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I345:	.......x.x........................................................x..............................x.x....xx..........x..........xx.xx........x.x......
	..oooooo..................................................................oo.oo...............................................................................................................................................................................................................................................................................................................................................................................................................................................
I346:	.......x.x.............................x..........................x..............................x.x....xx.....................xx.xx........x.x......
	..oooooo..................................................................oo..o.o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I347:	.......x.x.................x......................................x..............................x.x....xx.....................xx.xx........x.x......
	..oo.ooo..................................................................oo.oo.o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I348:	.......x.x.....................x..................................x..............................x.x....xx.....................xx.xx........x.x......
	..o.oooo..................................................................oo.oo.o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I349:	.......x.......xx..x...................x...................xx...........................x...........................x.......x...........x.x.x...x....
	....oooo.................................................................o........o...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I350:	.....................................x........x.x..................x..x..............................x.x...x...x.....xx.......xx.x..x................
	..oooooo.....................................................................................................................................o................................................................................................................................................................................................................................................................................................................................................................................
I351:	..............................x........x........x.............x...x................................x....x......................xxxx.........x.x...xx.
	..oooooo..................................................................oo....o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I352:	...........................x..x.................x.............x...x................................x....x......................xxxx.........x.x...xx.
	..oo.ooo..................................................................oo.o..o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I353:	.......x.x.............................x..........................x..............................x.x....xx..........x..........xx.xx........x.x......
	..oooooo..................................................................oo..o...............................................................................................................................................................................................................................................................................................................................................................................................................................................
I354:	.......x.x.................x......................................x..............................x.x....xx..........x..........xx.xx........x.x......
	..oo.ooo..................................................................oo.oo...............................................................................................................................................................................................................................................................................................................................................................................................................................................
I355:	.......x.x.................x...........x..........................x..............................x.x....xx.....................xx.xx........x.x......
	..oo.ooo..................................................................oo..o.o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I356:	.......x.x.....................x..................................x..............................x.x....xx..........x..........xx.xx........x.x......
	..o.oooo..................................................................oo.oo...............................................................................................................................................................................................................................................................................................................................................................................................................................................
I357:	.......x.x.....................x.......x..........................x..............................x.x....xx.....................xx.xx........x.x......
	..o.oooo..................................................................oo..o.o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I358:	.......x.......x...x...................x...................xx...........................x.................x.........x.......x...........xxx.x...x....
	..oooooo................................................................o.........o...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I359:	...........................x..x........x........x.............x...x................................x....x......................xxxx.........x.x...xx.
	..oo.ooo..................................................................oo....o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I360:	.........................x....xx................x.............x...x................................x....x......................xxxx.........x.x...xx.
	..o.oooo..................................................................oo.o..o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I361:	.......x.x.............................x..........................x..............................x.x....xx..........x..........xx.xx........xxx......
	..oooooo......................................................................o...............................................................................................................................................................................................................................................................................................................................................................................................................................................
I362:	.......x.x.................x...........x..........................x..............................x.x....xx..........x..........xx.xx........x.x......
	..oo.ooo..................................................................oo..o...............................................................................................................................................................................................................................................................................................................................................................................................................................................
I363:	.......x.x.....................x.......x..........................x..............................x.x....xx..........x..........xx.xx........x.x......
	..o.oooo..................................................................oo..o...............................................................................................................................................................................................................................................................................................................................................................................................................................................
I364:	.......x.x.................x...x.........x........................x..............................x.x....xx.....................xx.xx........x.x......
	..o..ooo..................................................................oo.oo.o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I365:	.......x.......xx..x...................x...................xx...........................x.................x.........x.......x...........xxx.x...x....
	....oooo..........................................................................o...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I366:	.........................x....xx.......x........x.............x...x................................x....x......................xxxx.........x.x...xx.
	..o.oooo..................................................................oo....o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I367:	.......x.x.................x...........x..........................x..............................x.x....xx..........x..........xx.xx........xxx......
	..oo.ooo......................................................................o...............................................................................................................................................................................................................................................................................................................................................................................................................................................
I368:	.......x.x.....................x.......x..........................x..............................x.x....xx..........x..........xx.xx........xxx......
	..o.oooo......................................................................o...............................................................................................................................................................................................................................................................................................................................................................................................................................................
I369:	.......x.x.................x...x.........x........................x..............................x.x....xx..........x..........xx.xx........x.x......
	..o..ooo..................................................................oo.oo...............................................................................................................................................................................................................................................................................................................................................................................................................................................
I370:	.......x.x.................x...x.......x.x........................x..............................x.x....xx.....................xx.xx........x.x......
	..o..ooo..................................................................oo..o.o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I371:	.......x.x.................x.x.x.........x........................x..............................x.x....xx.....................xx.xx........x.x......
	..o..ooo..................................................................o..oo.o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I372:	.........................x.x..xx.........x......x.............x...x................................x....x......................xxxx.........x.x...xx.
	..o..ooo..................................................................oo.o..o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I373:	.......x.x.................x...x.......x.x........................x..............................x.x....xx..........x..........xx.xx........x.x......
	..o..ooo..................................................................oo..o...............................................................................................................................................................................................................................................................................................................................................................................................................................................
I374:	.......x.x.................x.x.x.........x........................x..............................x.x....xx..........x..........xx.xx........x.x......
	..o..ooo..................................................................o..oo...............................................................................................................................................................................................................................................................................................................................................................................................................................................
I375:	.......x.x.................x.x.x.......x.x........................x..............................x.x....xx.....................xx.xx........x.x......
	..o..ooo..................................................................o...o.o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I376:	.......x.......x...x...................x...................xx...........................x.................x.....xxx.x.......x...........xxx.x...x....
	..ooooo.................................................................o.........o...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I377:	..............................x.x....x........x.x.x...........x...x...................x............x....x......................xxxx.........x.x...xx.
	..oooooo..................................................................oo.o.................................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I378:	.........................x.x..xx.......x.x......x.............x...x................................x....x......................xxxx.........x.x...xx.
	..o..ooo..................................................................oo....o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I379:	.........................x.x.xxx.........x......x.............x...x................................x....x......................xxxx.........x.x...xx.
	..o..ooo..................................................................o..o..o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I380:	.......x.x....................x.................x.............x...x..............................x.x....xx.....................xxxxx........x.x...xx.
	..oooooo..................................................................oo.o..o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I381:	.......x.x.................x.x.x.......x.x........................x..............................x.x....xx..........x..........xx.xx........x.x......
	..o..ooo..................................................................o...o...............................................................................................................................................................................................................................................................................................................................................................................................................................................
I382:	.......x.......xx..x...................x...................xx...........................x.................x.....xxx.x.......x...........xxx.x...x....
	....ooo...........................................................................o...........................................................................................................................................................................................................................................................................................................................................................................................................................................
I383:	...........................x..x.x....x........x.x.x...........x...x...................x............x....x......................xxxx.........x.x...xx.
	..oo.ooo..................................................................oo.o.................................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I384:	.........................x.x.xxx.......x.x......x.............x...x................................x....x......................xxxx.........x.x...xx.
	..o..ooo..................................................................o.....o..............................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I385:	.......x.x....................x........x........x.............x...x..............................x.x....xx.....................xxxxx........x.x...xx.
	..oooooo..................................................................oo....o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I386:	.......x.x.................x..x.................x.............x...x..............................x.x....xx.....................xxxxx........x.x...xx.
	..oo.ooo..................................................................oo.o..o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I387:	.......x.x.................x.x.x.......x.x........................x..............................x.x....xx..........x..........xx.xx........xxx......
	..o..ooo......................................................................o...............................................................................................................................................................................................................................................................................................................................................................................................................................................
I388:	..............................x.x....x.x......x.x.x...........x...x...................x............x....x.....................xxxxx.........x.x...xx.
	..oooooo..................................................................oo...................................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I389:	.........................x....xxx....x........x.x.x...........x...x...................x............x....x......................xxxx.........x.x...xx.
	..o.oooo..................................................................oo.o.................................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I390:	.......x.x.................x..x........x........x.............x...x..............................x.x....xx.....................xxxxx........x.x...xx.
	..oo.ooo..................................................................oo....o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I391:	.......x.x...............x....xx................x.............x...x..............................x.x....xx.....................xxxxx........x.x...xx.
	..o.oooo..................................................................oo.o..o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I392:	...........................x..x.x....x.x......x.x.x...........x...x...................x............x....x.....................xxxxx.........x.x...xx.
	..oo.ooo..................................................................oo...................................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I393:	.......x.x...............x....xx.......x........x.............x...x..............................x.x....xx.....................xxxxx........x.x...xx.
	..o.oooo..................................................................oo....o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I394:	.........................x....xxx....x.x......x.x.x...........x...x...................x............x....x.....................xxxxx.........x.x...xx.
	..o.oooo..................................................................oo...................................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I395:	.........................x.x..xxx....x...x....x.x.x...........x...x...................x............x....x......................xxxx.........x.x...xx.
	..o..ooo..................................................................oo.o.................................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I396:	.......x.x...............x.x..xx.........x......x.............x...x..............................x.x....xx.....................xxxxx........x.x...xx.
	..o..ooo..................................................................oo.o..o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I397:	.........................x.x.xxxx....x...x....x.x.x...........x...x...................x............x....x......................xxxx.........x.x...xx.
	..o..ooo..................................................................o..o.................................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I398:	.......x.x...............x.x..xx.......x.x......x.............x...x..............................x.x....xx.....................xxxxx........x.x...xx.
	..o..ooo..................................................................oo....o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I399:	.......x.x...............x.x.xxx.........x......x.............x...x..............................x.x....xx.....................xxxxx........x.x...xx.
	..o..ooo..................................................................o..o..o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I400:	.........................x.x..xxx....x.x.x....x.x.x...........x...x...................x............x....x.....................xxxxx.........x.x...xx.
	..o..ooo..................................................................oo...................................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I401:	.................x....x..............x....x...x.x...............x..x..x....x.....x...........xx......x.x...xx..x...x.xx.......xx.x..x................
	..oo.ooo.....................................................................................................................................o................................................................................................................................................................................................................................................................................................................................................................................
I402:	.......x.x...............x.x.xxx.......x.x......x.............x...x..............................x.x....xx.....................xxxxx........x.x...xx.
	..o..ooo..................................................................o.....o.............................................................................................................................................................................................................................................................................................................................................................................................................................................
I403:	.........................x.x.xxxx....x.x.x....x.x.x...........x...x...................x............x....x.....................xxxxx.........x.x...xx.
	..o..ooo..................................................................o....................................................................................o..............................................................................................................................................................................................................................................................................................................................................................
I404:	.......x.x....................x.xx...x........x.x.x...........x...x...................x..........x.x....xx..........x..........xxxxx......x.x.x...xx.
	..oooooo..................................................................oo.o................................................................................................................................................................................................................................................................................................................................................................................................................................................
I405:	.......x.x.................x..x.xx...x........x.x.x...........x...x...................x..........x.x....xx..........x..........xxxxx......x.x.x...xx.
	..oo.ooo..................................................................oo.o................................................................................................................................................................................................................................................................................................................................................................................................................................................
I406:	.......x.x....................x.xx...x.x......x.x.x...........x...x...................x..........x.x....xx..........x.........xxxxxx......x.x.x...xx.
	..oooooo..................................................................oo..................................................................................................................................................................................................................................................................................................................................................................................................................................................
I407:	.......x.x...............x....xxxx...x........x.x.x...........x...x...................x..........x.x....xx..........x..........xxxxx......x.x.x...xx.
	..o.oooo..................................................................oo.o................................................................................................................................................................................................................................................................................................................................................................................................................................................
I408:	.......x.x.................x..x.xx...x.x......x.x.x...........x...x...................x..........x.x....xx..........x.........xxxxxx......x.x.x...xx.
	..oo.ooo..................................................................oo..................................................................................................................................................................................................................................................................................................................................................................................................................................................
I409:	.......x.x...............x....xxxx...x.x......x.x.x...........x...x...................x..........x.x....xx..........x.........xxxxxx......x.x.x...xx.
	..o.oooo..................................................................oo..................................................................................................................................................................................................................................................................................................................................................................................................................................................
I410:	.......x.x...............x.x..xxxx...x...x....x.x.x...........x...x...................x..........x.x....xx..........x..........xxxxx......x.x.x...xx.
	..o..ooo..................................................................oo.o................................................................................................................................................................................................................................................................................................................................................................................................................................................
I411:	.......x.x...............x.x.xxxxx...x...x....x.x.x...........x...x...................x..........x.x....xx..........x..........xxxxx......x.x.x...xx.
	..o..ooo..................................................................o..o................................................................................................................................................................................................................................................................................................................................................................................................................................................
I412:	.......x.x...............x.x..xxxx...x.x.x....x.x.x...........x...x...................x..........x.x....xx..........x.........xxxxxx......x.x.x...xx.
	..o..ooo..................................................................oo..................................................................................................................................................................................................................................................................................................................................................................................................................................................
I413:	.......x.x...............x.x.xxxxx...x.x.x....x.x.x...........x...x...................x..........x.x....xx..........x.........xxxxxx......x.x.x...xx.
	..o..ooo..................................................................o...................................................................................................................................................................................................................................................................................................................................................................................................................................................
I414:	x...x..xxx....xx..xx......x...x.xxx..x.x...x..x.x.x..xxxx..xxxxx..xxxxxx..x.x.x....x..xxx..x.....x.x.xxxxxxx..xx....xxx..xxxxxxxxxxxx...xxx.xxxxx.xx.
	..oooooo......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I415:	x...x..xxx....xx..xx......x...x.xxx..x.x...x..x.x.x..xxxx..xxxxx..xxxxxx..x.x.x....x..xxx..x.....x.x.xxxxxxx..xxxxx.xxx..xxxxxxxxxxxx...xxx.xxxxx.xx.
	..ooooo.......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I416:	x...x.xxxx....xx..xx......x...x.xxx..x.x...xxxx.x.x..xxxx..xxxxx..xxxxxx..x.x.x....x..xxx..x.....x.x.xxxxxxx..xx....xxx..xxxxxxxxxxxx...xxx.xxxxx.xx.
	...ooooo......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I417:	x...x..xxx....xx..xx.....xx...xxxxx..x.x...x..x.xxx..xxxx..xxxxx..xxxxxx..x.x.x....x..xxx..xx..x.x.x.xxxxxxx..xx....xxx..xxxxxxxxxxxx...xxxxxxxxx.xx.
	..o.oooo......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I418:	x...x.xxxx....xx..xx......x...x.xxx.xx.x...xxxx.x.x..xxxx..xxxxx..xxxxxx..x.x.x....x..xxx..x.....x.x.xxxxxxx..xxxxx.xxx..xxxxxxxxxxxx...xxx.xxxxx.xx.
	...oooo.......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I419:	x...x..xxx....xx..xx.x...xx...xxxxx..x.x...x..x.xxx..xxxx..xxxxx..xxxxxx..x.x.x....x..xxx..xx..x.x.x.xxxxxxx..xxxxx.xxx..xxxxxxxxxxxx...xxxxxxxxx.xx.
	..o.ooo.......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I420:	x...x.xxxx....xxx.xx.....xx...xxxxx..x.x...xxxx.xxx..xxxx..xxxxx..xxxxxxx.x.x.x....x..xxx..xx..x.x.x.xxxxxxx..xx....xxx..xxxxxxxxxxxxx..xxxxxxxxx.xx.
	....oooo......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I421:	xxx.x.xxxx.x..xxx.xx.x...xx...xxxxx.xx.x...xxxx.xxx..xxxx..xxxxx..xxxxxxx.x.x.x....x..xxx..xx..x.x.x.xxxxxxx..xxxxx.xxx..xxxxxxxxxxxxx..xxxxxxxxx.xx.
	....ooo.......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I422:	xxx.x.xxxx.x..xxx.xx.x...xx...xxxxx.xx.x...xxxx.xxx..xxxx..xxxxx..xxxxxxx.x.x.xx...x..xxx..xx..x.x.x.xxxxxxx..xxxxx.xxx..xxxxxxxxxxxxx..xxxxxxxxx.xx.
	....oo........................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I423:	x..xxx.xxx...xxx.xxxx.xxx.xxx.x.xxx..xxxx.xx..x.x.xx.xxxxxxxxxxxxxxxxxxx.xxxx.x..xxx.xxxxxxx.xx..x.xxxxxxxxxxxxx...xxxxx.xxxxxxxxxxxx..xxxx.xxxxxxxxx
	..oo.ooo......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I424:	x..xxx.xxx...xxx.xxxx.xxx.xxx.x.xxx..xxxx.xx..x.x.xx.xxxxxxxxxxxxxxxxxxx.xxxx.x..xxx.xxxxxxx.xx..x.xxxxxxxxxxxxxxxxxxxxx.xxxxxxxxxxxx..xxxx.xxxxxxxxx
	..oo.oo.......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I425:	x..xxxxxxx...xxx.xxxx.xxx.xxx.x.xxx..xxxx.xxxxx.x.xx.xxxxxxxxxxxxxxxxxxx.xxxx.x..xxx.xxxxxxx.xx..x.xxxxxxxxxxxxx...xxxxx.xxxxxxxxxxxx..xxxx.xxxxxxxxx
	...o.ooo......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I426:	x..xxxxxxx...xxx.xxxx.xxx.xxx.x.xxx.xxxxx.xxxxx.x.xx.xxxxxxxxxxxxxxxxxxx.xxxx.x..xxx.xxxxxxx.xx..x.xxxxxxxxxxxxxxxxxxxxx.xxxxxxxxxxxx..xxxx.xxxxxxxxx
	...o.oo.......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I427:	x..xxx.xxxx.xxxx.xxxx.xxxxxxxxxxxxx..xxxxxxx..x.xxxxxxxxxxxxxxxxxxxxxxxx.xxxx.x..xxxxxxxxxxxxxxx.x.xxxxxxxxxxxxx...xxxxx.xxxxxxxxxxxx..xxxxxxxxxxxxxx
	..o..ooo......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I428:	x..xxx.xxxx.xxxx.xxxxxxxxxxxxxxxxxx..xxxxxxx..x.xxxxxxxxxxxxxxxxxxxxxxxx.xxxx.x..xxxxxxxxxxxxxxx.x.xxxxxxxxxxxxxxxxxxxxx.xxxxxxxxxxxx..xxxxxxxxxxxxxx
	..o..oo.......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I429:	x..xxxxxxxx.xxxxxxxxx.xxxxxxxxxxxxxx.xxxxxxxxxx.xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx..xxxxxxxxxxxxxxx.x.xxxxxxxxxxxxx...xxxxxxxxxxxxxxxxxxx.xxxxxxxxxxxxxx
	.....ooo......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I430:	x..xxxxxxxx.xxxxxxxxx.xxxxxxxxxxxxxx.xxxxxxxxxx.xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx..xxxxxxxxxxxxxxx.x.xxxxxxxxxxxxx...xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	.....o.o......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I431:	xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.xxxxxxxxxxxxxxxx.xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.xxxxxxxxxxxxxx
	.....oo.......................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I432:	xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	.....o........................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
I433:	xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	..............................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
