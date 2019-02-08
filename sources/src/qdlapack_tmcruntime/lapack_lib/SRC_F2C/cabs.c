#include "f2c.h"
#ifdef KR_headers
//extern doublereal sqrt();
//double f__cabs(real, imag) double real, imag;
#else
#undef abs
//#include "math.h"
#ifdef __cplusplus
extern "C" {
#endif
doublereal f__cabs(doublereal real, doublereal imag)
#endif
{
doublereal temp;

if(real < 0)
	real = -real;
if(imag < 0)
	imag = -imag;
if(imag > real){
	temp = real;
	real = imag;
	imag = temp;
}
if((real+imag) == real)
	return(real);

temp = imag/real;
temp = real*sqrt(1.0 + temp*temp);  /*overflow!!*/
return(temp);
}
#ifdef __cplusplus
}
#endif
