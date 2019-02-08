#include "f2c.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef KR_headers
double r_sign(a,b) real *a, *b;
#else
doublereal r_sign(real *a, real *b)
#endif
{
doublereal x;
x = (*a >= 0 ? *a : - *a);
return( *b >= 0 ? x : -x);
}
#ifdef __cplusplus
}
#endif
