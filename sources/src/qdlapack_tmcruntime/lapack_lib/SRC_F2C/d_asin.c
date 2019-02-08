#include "f2c.h"

#ifdef KR_headers
//doublereal asin();
//double d_asin(x) doublereal *x;
#else
#undef abs
//#include "math.h"
#ifdef __cplusplus
extern "C" {
#endif
doublereal d_asin(doublereal *x)
#endif
{
return( asin(*x) );
}
#ifdef __cplusplus
}
#endif
