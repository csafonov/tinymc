/// \file intel_quad.h
#ifndef _intel_quad_h_
#ifdef USE_QDMATH
#ifdef __INTEL_COMPILER

#define __float128	_Quad
typedef _Quad real;
typedef _Quad doublereal;


_Quad __logq(_Quad x);
_Quad __sqrtq(_Quad x);
long  __floorq(_Quad x);
_Quad 	__sinq(_Quad x);
_Quad  __cosq(_Quad x);
_Quad  __tanq(_Quad x);
_Quad  __tanhq(_Quad x);
_Quad 	__sinhq(_Quad x);
_Quad  __coshq(_Quad x);
_Quad  __tanhq(_Quad x);
_Quad  __acosq(_Quad x);
_Quad  __asinq(_Quad x);
_Quad  __atanq(_Quad x);
_Quad  __atan2q(_Quad y, _Quad x);
_Quad  __powq(_Quad x, _Quad n);
_Quad  __expq(_Quad x);

#define sqrt __sqrtq
#define log __logq
#define log __logq
#define floor __floorq
#define	sin	__sinq
#define cos __cosq
#define tan __tanq
#define tanh __tanhq
#define	sinh	__sinhq
#define cosh __coshq
#define tanh __tanhq
#define acos __acosq
#define asin __asinq
#define atan __atanq
#define atan2 __atan2q
#define log10e   0.43429448190325182765112891891660505q
#define pow __powq
#define exp __expq
#endif
#endif


#endif
