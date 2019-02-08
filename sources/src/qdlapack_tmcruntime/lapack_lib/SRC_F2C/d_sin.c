#include "f2c.h"

#ifdef KR_headers
double sin();
double d_sin(x) doublereal *x;
#else
#undef abs
//#include "math.h"
#ifdef __cplusplus
extern "C" {
#endif
doublereal d_sin(doublereal *x)
#endif
{
return( sin(*x) );
}
#ifdef __cplusplus
}
#endif
