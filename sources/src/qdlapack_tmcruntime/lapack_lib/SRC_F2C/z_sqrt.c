#include "f2c.h"

#ifdef KR_headers
double sqrt(), f__cabs();
VOID z_sqrt(r, z) doublecomplex *r, *z;
#else
#undef abs
//#include "math.h"
#ifdef __cplusplus
extern "C" {
#endif
extern doublereal f__cabs(doublereal, doublereal);
void z_sqrt(doublecomplex *r, doublecomplex *z)
#endif
{
	doublereal mag, zi = z->i, zr = z->r;

	if( (mag = f__cabs(zr, zi)) == 0.)
		r->r = r->i = 0.;
	else if(zr > 0)
		{
		r->r = sqrt(0.5 * (mag + zr) );
		r->i = zi / r->r / 2;
		}
	else
		{
		r->i = sqrt(0.5 * (mag - zr) );
		if(zi < 0)
			r->i = - r->i;
		r->r = zi / r->i / 2;
		}
	}
#ifdef __cplusplus
}
#endif
