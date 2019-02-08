#include "f2c.h"

#ifdef KR_headers
double tan();
double d_tan(x) doublereal *x;
#else
#undef abs
//#include "math.h"
#ifdef __cplusplus
extern "C" {
#endif
doublereal d_tan(doublereal *x)
#endif
{
return( tan(*x) );
}
#ifdef __cplusplus
}
#endif
