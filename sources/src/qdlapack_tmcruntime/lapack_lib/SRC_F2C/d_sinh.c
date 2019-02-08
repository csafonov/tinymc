#include "f2c.h"

#ifdef KR_headers
double sinh();
double d_sinh(x) doublereal *x;
#else
#undef abs
//#include "math.h"
#ifdef __cplusplus
extern "C" {
#endif
doublereal d_sinh(doublereal *x)
#endif
{
return( sinh(*x) );
}
#ifdef __cplusplus
}
#endif
