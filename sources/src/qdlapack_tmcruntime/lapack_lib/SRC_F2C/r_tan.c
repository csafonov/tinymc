#include "f2c.h"

#ifdef KR_headers
doublereal tan();
doublereal r_tan(x) real *x;
#else
#undef abs
//#include "math.h"
#ifdef __cplusplus
extern "C" {
#endif
doublereal r_tan(real *x)
#endif
{
return( tan(*x) );
}
#ifdef __cplusplus
}
#endif
