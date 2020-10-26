// File: JMatrix.h
#ifndef _JMatrix_h_
#define _JMatrix_h_

#include "tmc.h"
enum JMATRIX_TYPES
{
	JTYPE_NULL  =-1,
	JTYPE_DOUBLE=0,
	JTYPE_STRING=1,
	JTYPE_LOGICS=2,
	JTYPE_OBJECT=3,
	JTYPE_MEMBER=4
};
enum JMATRIX_SUB_TYPES
{
	JSTYPE_NUMBER =0,
	JSTYPE_VINF   =1,
	JSTYPE_VNINF  =2
};
struct CJMatrix
{
enum JMATRIX_TYPES type;
enum JMATRIX_SUB_TYPES subtype;
struct CJMatrix *next;
struct CJMatrix *last;
struct CJMatrix *data;
char *name;
const char *string_value;
double double_value;
short len;
};
typedef struct CJMatrix JMatrix;

JMatrix *make_jvalue(double dvalue);
JMatrix *make_jstring( char *string_value);
JMatrix *make_jlogics(short val);
JMatrix *make_null( void );
JMatrix *make_inf( short sgn );
JMatrix *values_add_value(JMatrix *vals, JMatrix *val);
JMatrix *make_member(  char *member_name,JMatrix *value );
JMatrix *make_jobject(JMatrix *members);
JMatrix *make_array(JMatrix *values);
JMatrix *members_add_member(JMatrix *members,JMatrix *member);

tmsMatrix * make_tmc_obj(JMatrix * jobj,short jlevel);
#endif