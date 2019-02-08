#include "f2c.h"

#ifdef KR_headers
doublereal acos();
doublereal d_acos(x) doublereal *x;
#else
#undef abs
//#include "math.h"
#ifdef __cplusplus
extern "C" {
#endif
doublereal d_acos(doublereal *x)
#endif
{
return( acos(*x) );
}
#ifdef __cplusplus
}
#endif
