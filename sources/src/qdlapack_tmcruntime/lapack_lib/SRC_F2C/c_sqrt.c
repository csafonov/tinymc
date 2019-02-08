#include "f2c.h"

#ifdef KR_headers
//extern doublereal sqrt(), f__cabs();

VOID c_sqrt(r, z) complex *r, *z;
#else
#undef abs
//#include "math.h"
#ifdef __cplusplus
extern "C" {
#endif
extern doublereal f__cabs(doublereal, doublereal);

void c_sqrt(complex *r, complex *z)
#endif
{
	doublereal mag, t;
	doublereal zi = z->i, zr = z->r;

	if( (mag = f__cabs(zr, zi)) == 0.)
		r->r = r->i = 0.;
	else if(zr > 0)
		{
		r->r = t = sqrt(0.5 * (mag + zr) );
		t = zi / t;
		r->i = 0.5 * t;
		}
	else
		{
		t = sqrt(0.5 * (mag - zr) );
		if(zi < 0)
			t = -t;
		r->i = t;
		t = zi / t;
		r->r = 0.5 * t;
		}
	}
#ifdef __cplusplus
}
#endif
