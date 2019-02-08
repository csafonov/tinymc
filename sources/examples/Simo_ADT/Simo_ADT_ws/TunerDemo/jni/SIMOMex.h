void tmcABCD2DataMex(int nargout, int nargin,tmsMatrix *g
,tmsMatrix *A,tmsMatrix *B,tmsMatrix *C,tmsMatrix *D,tmsMatrix *w,tmsMatrix *Ts) ;
void tmcAddPGMex(int nargout, int nargin,tmsMatrix *PG
,tmsMatrix *P,tmsMatrix *G) ;
void tmcAmp2Mex(int nargout, int nargin,tmsMatrix *AL2
,tmsMatrix *L0) ;
void tmcAmp2RealMex(int nargout, int nargin,tmsMatrix *AL2
,tmsMatrix *L0) ;
void tmcCheck4DenseFreqsLoop1Mex(int nargout, int nargin,tmsMatrix *mSuccess,
				tmsMatrix *mLL,tmsMatrix *mBottom,tmsMatrix *mTop,tmsMatrix *mTop2Bottom,
				tmsMatrix *mnW,tmsMatrix *mnCases) ;

//void tmcCheck4DenseFreqsLoop1Mex(int nargout, int nargin,tmsMatrix *Success
//,tmsMatrix *LL,tmsMatrix *nW,tmsMatrix *nCases,tmsMatrix *TanPM,tmsMatrix *UL0) ;

//void tmcCheck4DenseFreqsLoopA1Mex(int nargout, int nargin,tmsMatrix *Success
//,tmsMatrix *LL,tmsMatrix *TanPM,tmsMatrix *UL0) ;

void tmcCheck4DenseFreqsLoopA1Mex(int nargout, int nargin,tmsMatrix *mSuccess,
								  tmsMatrix *mLL,tmsMatrix *mBottom,
								  tmsMatrix *mTop,tmsMatrix *mFact);

void tmcCrossMarABCD1Mex(int nargout, int nargin,tmsMatrix *I,tmsMatrix *a1,tmsMatrix *a2
,tmsMatrix *A__input__tmc,tmsMatrix *B__input__tmc,tmsMatrix *C__input__tmc,tmsMatrix *D,tmsMatrix *M2,tmsMatrix *a1__input__tmc,tmsMatrix *a2__input__tmc,tmsMatrix *K21,tmsMatrix *Per) ;
void tmcCrossMarLSGMMex(int nargout, int nargin,tmsMatrix *I,tmsMatrix *G
,tmsMatrix *L__input__tmc,tmsMatrix *M,tmsMatrix *UL) ;
void tmcCrossMarLSGM1Mex(int nargout, int nargin,tmsMatrix *I,tmsMatrix *G,tmsMatrix *LL
,tmsMatrix *P1T,tmsMatrix *aa,tmsMatrix *M,tmsMatrix *UL) ;
void tmcCrossMarLSGM4Meas2Mex(int nargout, int nargin,tmsMatrix *I,tmsMatrix *G,tmsMatrix *LL
,tmsMatrix *P1T,tmsMatrix *P2T,tmsMatrix *aa,tmsMatrix *bb,tmsMatrix *M,tmsMatrix *UL) ;
void tmcDeluteSurfaceMex(int nargout, int nargin,tmsMatrix *KI,tmsMatrix *KP,tmsMatrix *UL
,tmsMatrix *KI__input__tmc,tmsMatrix *KP__input__tmc,tmsMatrix *UL__input__tmc,tmsMatrix *Resb,tmsMatrix *MinPer,tmsMatrix *Resa) ;
void tmcFindCOMex(int nargout, int nargin,tmsMatrix *I
,tmsMatrix *L__input__tmc,tmsMatrix *CLevel) ;
void tmcFindCoefErrorCAMex(int nargout, int nargin,tmsMatrix *K0
,tmsMatrix *K,tmsMatrix *NumInt) ;
void tmcIsVectorSortedMex(int nargout, int nargin,tmsMatrix *Success
,tmsMatrix *Freqs) ;
void tmcLeadTFwAMex(int nargout, int nargin,tmsMatrix *Lead
,tmsMatrix *a,tmsMatrix *b,tmsMatrix *s,tmsMatrix *Ts) ;
void tmcLowPassFilterMex(int nargout, int nargin,tmsMatrix *L,tmsMatrix *dL
,tmsMatrix *Ts,tmsMatrix *wn,tmsMatrix *data,tmsMatrix *OrderLP0,tmsMatrix *xi__input__tmc) ;
void tmcMissMatchAMex(int nargout, int nargin,tmsMatrix *w1,tmsMatrix *w2,tmsMatrix *wa,tmsMatrix *wr,tmsMatrix *Ia,tmsMatrix *Ir,tmsMatrix *ph,tmsMatrix *I1,tmsMatrix *I2
,tmsMatrix *win,tmsMatrix *P__input__tmc,tmsMatrix *Fact,tmsMatrix *phmin,tmsMatrix *phmax,tmsMatrix *Fact0,tmsMatrix *PhP0) ;
void tmcModelDataAssMex(int nargout, int nargin,tmsMatrix *P1,tmsMatrix *dP1
,tmsMatrix *A,tmsMatrix *B,tmsMatrix *C,tmsMatrix *D,tmsMatrix *w,tmsMatrix *Ts,tmsMatrix *Delay) ;
void tmcMulPGMex(int nargout, int nargin,tmsMatrix *PG
,tmsMatrix *P,tmsMatrix *G) ;
void tmcNoiseCrlABMex(int nargout, int nargin,tmsMatrix *H
,tmsMatrix *wL,tmsMatrix *s,tmsMatrix *s2,tmsMatrix *Ts,tmsMatrix *OrderLP0) ;
void tmcNotchFilterOnlyMex(int nargout, int nargin,tmsMatrix *N
,tmsMatrix *Ts,tmsMatrix *data,tmsMatrix *Crl) ;
void tmcNotchFilterOnlyAMex(int nargout, int nargin,tmsMatrix *N
,tmsMatrix *Ts,tmsMatrix *s,tmsMatrix *s2,tmsMatrix *w1,tmsMatrix *d1,tmsMatrix *w2,tmsMatrix *d2) ;
void tmcNotchPlantDiscreteMex(int nargout, int nargin,tmsMatrix *P,tmsMatrix *dP
,tmsMatrix *d1,tmsMatrix *d2,tmsMatrix *w1,tmsMatrix *w2,tmsMatrix *Ts,tmsMatrix *z,tmsMatrix *z2) ;
void tmcPDDesignA0ABCD1Mex(int nargout, int nargin,tmsMatrix *amin,tmsMatrix *amax,tmsMatrix *bminmax,tmsMatrix *Iw
,tmsMatrix *Z1,tmsMatrix *Z2,tmsMatrix *B,tmsMatrix *P1,tmsMatrix *P2,tmsMatrix *M,tmsMatrix *S,tmsMatrix *amin__input__tmc,tmsMatrix *amax__input__tmc,tmsMatrix *bminmax__input__tmc,tmsMatrix *K21,tmsMatrix *Per) ;
void tmcPDDesignA0N1Mex(int nargout, int nargin,tmsMatrix *KI,tmsMatrix *KP,tmsMatrix *UL
,tmsMatrix *P1T,tmsMatrix *P2T,tmsMatrix *nCases,tmsMatrix *P1,tmsMatrix *P2,tmsMatrix *dP1,tmsMatrix *dP2,tmsMatrix *M,tmsMatrix *K,tmsMatrix *nW,tmsMatrix *xiMod,tmsMatrix *nP,tmsMatrix *nI,tmsMatrix *PhE) ;
void tmcPDDesignA0N1AMex(int nargout, int nargin,tmsMatrix *CorrectSign
,tmsMatrix *R,tmsMatrix *Lw0,tmsMatrix *NumInt) ;
void tmcPDDesignA0N1MeasMotorMex(int nargout, int nargin,tmsMatrix *KI,tmsMatrix *KP,tmsMatrix *UL,tmsMatrix *Iw
,tmsMatrix *nCases,tmsMatrix *P1,tmsMatrix *P2,tmsMatrix *dP1,tmsMatrix *dP2,tmsMatrix *M,tmsMatrix *K,tmsMatrix *nW,tmsMatrix *xiMod,tmsMatrix *nP,tmsMatrix *nI,tmsMatrix *PhE,tmsMatrix *amin,tmsMatrix *amax,tmsMatrix *aminUL,tmsMatrix *WithLimit__input__tmc,tmsMatrix *IbIe__input__tmc,tmsMatrix *bPos) ;
void tmcPDDesignA0N1MotorMex(int nargout, int nargin,tmsMatrix *KI,tmsMatrix *KP,tmsMatrix *UL,tmsMatrix *Iw
,tmsMatrix *nCases,tmsMatrix *P1,tmsMatrix *P2,tmsMatrix *dP1,tmsMatrix *dP2,tmsMatrix *M,tmsMatrix *K,tmsMatrix *nW,tmsMatrix *xiMod,tmsMatrix *nP,tmsMatrix *nI,tmsMatrix *PhE,tmsMatrix *amin,tmsMatrix *amax,tmsMatrix *aminUL,tmsMatrix *WithLimit__input__tmc,tmsMatrix *IbIe__input__tmc) ;
void tmcPDDesignA0N5Mex(int nargout, int nargin,tmsMatrix *KI,tmsMatrix *KP,tmsMatrix *UL
,tmsMatrix *P0T,tmsMatrix *P1T,tmsMatrix *P2T,tmsMatrix *nCases,tmsMatrix *P0,tmsMatrix *P1,tmsMatrix *P2,tmsMatrix *dP0,tmsMatrix *dP1,tmsMatrix *dP2,tmsMatrix *M,tmsMatrix *K,tmsMatrix *nW,tmsMatrix *xiMod,tmsMatrix *nP,tmsMatrix *nI,tmsMatrix *PhE,tmsMatrix *nc,tmsMatrix *kB,tmsMatrix *IndBottom) ;
void tmcPDDesignA0N5MotorMex(int nargout, int nargin,tmsMatrix *KI,tmsMatrix *KP,tmsMatrix *UL
,tmsMatrix *P0T,tmsMatrix *P1T,tmsMatrix *P2T,tmsMatrix *nCases,tmsMatrix *P0,tmsMatrix *P1,tmsMatrix *P2,tmsMatrix *dP0,tmsMatrix *dP1,tmsMatrix *dP2,tmsMatrix *M,tmsMatrix *K,tmsMatrix *nW,tmsMatrix *nP,tmsMatrix *nI,tmsMatrix *nc,tmsMatrix *Meas,tmsMatrix *WithLimit,tmsMatrix *IbIe__input__tmc,tmsMatrix *aSign) ;
void tmcPDDesignCA2MMex(int nargout, int nargin,tmsMatrix *KI2,tmsMatrix *KP2,tmsMatrix *UL2
,tmsMatrix *KI1__input__tmc,tmsMatrix *KP1__input__tmc,tmsMatrix *UL1__input__tmc,tmsMatrix *M,tmsMatrix *K,tmsMatrix *P1,tmsMatrix *P2,tmsMatrix *MIMO,tmsMatrix *IsSorted,tmsMatrix *nWFull) ;
void tmcPDDesignCA3Mex(int nargout, int nargin,tmsMatrix *KI1,tmsMatrix *KP1,tmsMatrix *UL1
,tmsMatrix *KI1__input__tmc,tmsMatrix *KP1__input__tmc,tmsMatrix *UL1__input__tmc,tmsMatrix *M,tmsMatrix *K,tmsMatrix *P1,tmsMatrix *P2,tmsMatrix *nW,tmsMatrix *nCases,tmsMatrix *NumUnP,tmsMatrix *NumIntP1,tmsMatrix *FirstCases,tmsMatrix *CheckStability,tmsMatrix *IsSorted) ;
void tmcPDesignAMex(int nargout, int nargin,tmsMatrix *KI,tmsMatrix *UL
,tmsMatrix *M,tmsMatrix *K,tmsMatrix *P1,tmsMatrix *nCases,tmsMatrix *nW,tmsMatrix *nP,tmsMatrix *nI,tmsMatrix *CheckStab,tmsMatrix *IbIe__input__tmc) ;
void tmcPDesignA1MMex(int nargout, int nargin,tmsMatrix *KI,tmsMatrix *UL
,tmsMatrix *M,tmsMatrix *K,tmsMatrix *P1,tmsMatrix *KImax__input__tmc,tmsMatrix *KImin,tmsMatrix *FirstDesign) ;
void tmcPIDDesignA2BMex(int nargout, int nargin,tmsMatrix *kis
,tmsMatrix *K0,tmsMatrix *PA__input__tmc,tmsMatrix *PB__input__tmc,tmsMatrix *M0,tmsMatrix *kis__input__tmc) ;
void tmcPIDDesignC1Mex(int nargout, int nargin,tmsMatrix *KI1,tmsMatrix *KP1,tmsMatrix *KD1,tmsMatrix *UL1,tmsMatrix *KM1
,tmsMatrix *Type,tmsMatrix *PInt0,tmsMatrix *P10,tmsMatrix *P20,tmsMatrix *P30,tmsMatrix *M,tmsMatrix *K,tmsMatrix *S,tmsMatrix *xi,tmsMatrix *KI1__input__tmc,tmsMatrix *KP1__input__tmc,tmsMatrix *UL1__input__tmc,tmsMatrix *MoreF,tmsMatrix *kiMax,tmsMatrix *kiMin,tmsMatrix *Fact,tmsMatrix *MinGainFact,tmsMatrix *Meas,tmsMatrix *nW,tmsMatrix *MinLevel,tmsMatrix *Crt,tmsMatrix *MorSolFactNoise,tmsMatrix *MorSolFactPer,tmsMatrix *nI,tmsMatrix *nP,tmsMatrix *CheckStability) ;
void tmcPIDDesignC1Step2Mex(int nargout, int nargin,tmsMatrix *KI1,tmsMatrix *KP1,tmsMatrix *KD1,tmsMatrix *UL1,tmsMatrix *KM1
,tmsMatrix *Model__input__tmc,tmsMatrix *MM,tmsMatrix *KK,tmsMatrix *S,tmsMatrix *xi,tmsMatrix *KI2,tmsMatrix *KP2,tmsMatrix *UL2,tmsMatrix *MoreF,tmsMatrix *kiMax,tmsMatrix *kiMin,tmsMatrix *Fact,tmsMatrix *MinGainFact,tmsMatrix *MinLevel,tmsMatrix *Crt,tmsMatrix *MorSolFactNoise,tmsMatrix *MaxPoints0,tmsMatrix *nI,tmsMatrix *nP,tmsMatrix *CheckStability) ;
void tmcqfdDampMex(int nargout, int nargin,tmsMatrix *damp,tmsMatrix *w
,tmsMatrix *KI,tmsMatrix *KP,tmsMatrix *KD) ;
void tmcQFDunwrapMex(int nargout, int nargin,tmsMatrix *deg
,tmsMatrix *deg__input__tmc,tmsMatrix *a__input__tmc) ;
void tmcSchedulingDesignDMex(int nargout, int nargin,tmsMatrix *Success
,tmsMatrix *L,tmsMatrix *K,tmsMatrix *M) ;
void tmcStabilityCheckByEncM1Mex(int nargout, int nargin,tmsMatrix *I
,tmsMatrix *L,tmsMatrix *nP,tmsMatrix *nI,tmsMatrix *Top,tmsMatrix *Bottom,tmsMatrix *nW,tmsMatrix *nCases,tmsMatrix *UL0) ;
