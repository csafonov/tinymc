#include "f2c.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef KR_headers
extern doublereal f__cabs();

doublereal c_abs(z) complex *z;
#else
extern doublereal f__cabs(doublereal, doublereal);

doublereal c_abs(complex *z)
#endif
{
return( f__cabs( z->r, z->i ) );
}
#ifdef __cplusplus
}
#endif
