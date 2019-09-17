//#include "forcelib.h" // to assure MFC linked before CRT
#include <stdio.h>
#include "tmc.h"

//#include "tmc.h"
//#include "TestM.globals.h"
const struct CInitHashData InitHashData[]={
#include "hash_init.dat"
};

tmsMatrix	*pRefHelper;
tmsMatrix	*pGetHelper;
tmsMatrix *ComStruct;
void tmcInitGlobals(void)
{
}
void tmcFreeGlobals(void)
{
}

const long InitHashDataLen=sizeof(InitHashData)/sizeof(struct CInitHashData);
const struct CInit_funcs_table Init_funcs_table = { InitHashData,&InitHashDataLen,tmcInitGlobals,tmcFreeGlobals,&pRefHelper,&pGetHelper  };
