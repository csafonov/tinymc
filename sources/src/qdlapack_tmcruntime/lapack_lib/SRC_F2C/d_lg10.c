#include "f2c.h"


#ifdef KR_headers
double log();
double d_lg10(x) doublereal *x;
#else
#undef abs
//#include "math.h"
#ifdef __cplusplus
extern "C" {
#endif
doublereal d_lg10(doublereal *x)
#endif
{
return( log10e * log(*x) );
}
#ifdef __cplusplus
}
#endif
