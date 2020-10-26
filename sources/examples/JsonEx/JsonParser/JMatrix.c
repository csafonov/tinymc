// File: JMatrix.c
#include "JMatrix.h"
#include <string.h>
#include <stdlib.h>


void clear_jobj(JMatrix *jobj)
{
	short n,len;
	JMatrix * jobj_first = jobj;
    JMatrix * next_jval  = jobj;
	len =jobj->len;
	for (n=0;n<len;n++)
	{
				next_jval=next_jval->next;
				free(jobj_first);
				jobj_first=next_jval;
	}
}

/**
	\brief Create scalar value
*/
JMatrix *make_jvalue(double dvalue)
{
	JMatrix * jobj = malloc(sizeof(JMatrix));
	memset(jobj, 0 , sizeof(JMatrix));
	jobj->double_value = dvalue;
	jobj->type = JTYPE_DOUBLE;
	jobj->subtype = JSTYPE_NUMBER;
	jobj->len =1;
	return jobj;
}
JMatrix *make_jstring( char *string_value)
{
	size_t len;
	JMatrix * jobj = malloc(sizeof(JMatrix));
	memset(jobj, 0 , sizeof(JMatrix));

len = strlen(string_value);
string_value[len-1]=0;

	jobj->string_value = &string_value[1]; // hazard
	jobj->type = JTYPE_STRING;
	jobj->len =1;
	return jobj;
}

JMatrix *make_jlogics(short val)
{
	JMatrix * jobj = malloc(sizeof(JMatrix));
	memset(jobj, 0 , sizeof(JMatrix));
	jobj->double_value = val;  
	jobj->type = JTYPE_LOGICS;
	jobj->len =1;
	return jobj;

}

JMatrix *make_null( void )
{
	JMatrix * jobj = malloc(sizeof(JMatrix));
	memset(jobj, 0 , sizeof(JMatrix));
	jobj->type = JTYPE_NULL;
	jobj->len =1;
	return jobj;
}

JMatrix *make_inf( short sgn )
{
	const double zero = 0;
    JMatrix * jobj = malloc(sizeof(JMatrix));
	memset(jobj, 0 , sizeof(JMatrix));
	jobj->type =JTYPE_DOUBLE;
	jobj->subtype = (sgn> 0) ? JSTYPE_VINF: JSTYPE_VNINF;
	jobj->double_value = sgn / zero;
	jobj->len =1;
	return jobj;

}

/**
	\brief Connct values to array
*/
JMatrix *values_add_value(JMatrix *values, JMatrix *value)
{
	if (values == NULL)
	{
		return value;
	}
	else
	{
		if(values->len==1)
		{
				values->next=value;
		}
		else
		{
				values->last->next=value;
		}
		values->last=value;
		values->len++;
		return values;
	}
}

JMatrix *members_add_member(JMatrix *members,JMatrix *member)
{
	if (members == NULL)
	{
		return member;
	}
	else
	{
		if(members->len==1)
		{
				members->next=member;
		}
		else
		{
				members->last->next=member;
		}
		members->last=member;
		members->len++;
		return members;
	}
}

JMatrix *make_member(  char *member_name,JMatrix *value )
{
short len;
	JMatrix * jobj = malloc(sizeof(JMatrix));
	memset(jobj, 0 , sizeof(JMatrix));
	jobj->type = JTYPE_MEMBER;
	jobj->len =1;

len = (short)strlen(member_name);
member_name[len-1]=0;

	jobj->name =& member_name[1];// HAZARD
	jobj->data = value;
	return jobj;
}

JMatrix *make_jobject(JMatrix *members)
{
	return members;
}

JMatrix *make_array(JMatrix *values)
{
	return values;//TODO
}


tmsMatrix * make_tmc_obj(JMatrix * jobj,short jlevel)
{
	short kk,n;
	STRINGCODE hcode;
	tmsMatrix *v;
	JMatrix * next_jval;
	JMatrix * jval;
	JMatrix * next_jobj = jobj;
	tmsMatrix *www=tmcNewMatrix();

	for (kk=0;kk<jobj->len;kk++)
	{
		
		jval=next_jobj->data;
		next_jval = jval;
		
		if (jval->type != JTYPE_MEMBER)
		 v=tmcNewMatrix();


		switch(jval->type)
		{
		case JTYPE_DOUBLE:
			_tmcCreateMatrix(v,1,jval->len,tmcREAL);
			for (n=0;n<jval->len;n++)
			{
				v->value.complx.rData[n]=next_jval->double_value;
				next_jval=next_jval->next;
			}
			
		break;
		case JTYPE_NULL:
			_tmcCreateMatrix(v,0,0,tmcREAL);
		break;
		case JTYPE_STRING:
			tmcCreateString(v,jval->string_value);
		break;
		case JTYPE_MEMBER:
			v = make_tmc_obj(jval,jlevel+1);
		break;
		default:
		tmcScalar(v,kk);
		}
		clear_jobj(jval);
	    hcode= string2hcode(next_jobj->name   );
		_tmcSetByField(www,0,v,hcode);
		next_jobj=next_jobj->next;
	}
	clear_jobj(jobj);
	if (jlevel==0)
	{
	//tmsMatrix *fname=tmcNewMatrix();
	//tmcCreateString(fname,"input.mat");
	//tmcsave(0,2,fname,www,"www");
	}
	return www; 
}


