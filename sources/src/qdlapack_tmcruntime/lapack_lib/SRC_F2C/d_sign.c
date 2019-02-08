#include "f2c.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef KR_headers
double d_sign(a,b) doublereal *a, *b;
#else
doublereal d_sign(doublereal *a, doublereal *b)
#endif
{
doublereal x;
x = (*a >= 0 ? *a : - *a);
return( *b >= 0 ? x : -x);
}
#ifdef __cplusplus
}
#endif
