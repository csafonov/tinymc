// External functions prototypes
void tmcTestO(int nargout, int nargin,tmsMatrix *PropGain,tmsMatrix *IntGain,tmsMatrix *FreqLen,tmsMatrix *FreqHz,tmsMatrix *OL_Mag,tmsMatrix *OL_Ph,tmsMatrix *CL_Mag,tmsMatrix *CL_Ph,tmsMatrix *RespLen,tmsMatrix *RespTime,tmsMatrix *Resp
,tmsMatrix *R,tmsMatrix *L,tmsMatrix *Ts,tmsMatrix *Ovs) ;

void tmcExMex1(int nargout, int nargin,tmsMatrix *mY,
				 tmsMatrix *mX1,tmsMatrix *mX2);

void tmcMPI_Init(int nargout, int nargin, tmsMatrix *mY);
void tmcMPI_Finalize(int nargout, int nargin, tmsMatrix *mY);
void tmcMPI_Comm_Load(int nargout, int nargin, tmsMatrix *mY, tmsMatrix *mD);

void tmcMPI_Comm_size(int nargout, int nargin, tmsMatrix *mY, tmsMatrix *mCOMM);
void tmcMPI_Comm_rank(int nargout, int nargin, tmsMatrix *mY, tmsMatrix *mCOMM);
void tmcMPI_Send(int nargout, int nargin, tmsMatrix *mY, tmsMatrix *mX, tmsMatrix *mRanks,
	tmsMatrix *mTag, tmsMatrix *mCOMM);
void tmcMPI_Recv(int nargout, int nargin, tmsMatrix *mY, tmsMatrix *mStatus, tmsMatrix *mSrc, tmsMatrix *mTag, tmsMatrix *mCOMM);

