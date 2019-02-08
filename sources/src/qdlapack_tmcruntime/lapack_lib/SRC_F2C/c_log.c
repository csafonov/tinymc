#include "f2c.h"

#ifdef KR_headers
//extern double log(), f__cabs(), atan2();
//VOID c_log(r, z) complex *r, *z;
#else
#undef abs
//#include "math.h"
#ifdef __cplusplus
extern "C" {
#endif
extern doublereal f__cabs(doublereal, doublereal);

void c_log(complex *r, complex *z)
#endif
{
	doublereal zi, zr;
	r->i = atan2(zi = z->i, zr = z->r);
	r->r = log( f__cabs(zr, zi) );
	}
#ifdef __cplusplus
}
#endif