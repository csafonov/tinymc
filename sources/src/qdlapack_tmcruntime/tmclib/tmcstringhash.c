/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC Runtime software is covered under covered by simplified BSD 2-Clause license. 
  *****************************************************************************/


#include "tmc.h"
#include "tmcstringhash.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#ifndef  _TMC_EMBEDDED_
#include <memory.h>
#endif

#include <stdio.h>


//extern const struct CInitHashData InitHashData[];

static char *s_module="tmcstringhash.c";

/* TABLE_SIZE is the number of entries in the symbol table. */
/* TABLE_SIZE must be a power of two.			    */

#define	TABLE_SIZE 65536L
	typedef unsigned long HASHCODE;

#define	FREE(x)		(MYFREE((char*)(x)))
#define MALLOC(n)	(MYMALLOC((unsigned)(n)))
#define true	1
#define false   0

/*  the structure of a symbol table entry  */

	struct bucket
	{
		struct bucket *link;
		struct bucket *next;
		char *name;
		STRINGCODE hcode;
	};
	typedef struct bucket bucket;

// private members:
//static		bucket **symbol_table;
bucket		*symbol_table[TABLE_SIZE];

static		bucket *first_symbol;
static		bucket *last_symbol;


static		HASHCODE hash(const char *name);
static		HASHCODE dhash(const double *dname,long len);

static		bucket * make_bucket(const char *name,STRINGCODE hcode);
static		bucket * dmake_bucket(const double *dname,long len,STRINGCODE hcode);

static		void create_string_hash_table(void);
static		void free_string_hash_table(void);
static		void free_hash_strings(void);
static		bucket *string_hash_lookup(const char *name);

void InitStringHash()
{
	create_string_hash_table();
}
void DestroyStringHash()
{
		free_hash_strings();
		free_string_hash_table();
}
STRINGCODE string2hcode(const char *name)
{
	register bucket *bp;
	
	if (name[0])
	{
	bp=string_hash_lookup(name);
	return bp->hcode;
	}
	else
	{
		return 0; // for empty string
	}
}

short _dstrcmp(const double *x,long xlen,const char *fn)
{// return 0 is string matrix == fn
	short k;
	short stat=-1;
	const char *p = fn;

	for (k=0; k<xlen;k++)
	{
		if (*p==0)
			return -1;
		if (*p !=(char)x[k])
			return -1;
		p++;
	}
	if (*p == 0)
		return 0;
	else
		return -1;
}

long _dstrlen(const double *x,long maxlen)
{ // find strlen() of double-string
long k;
	for (k=0;k<maxlen;k++)
	{
		if (x[k]==0)
		{
			return k;
		}
	}
	return maxlen; // cut 
}


STRINGCODE dstring2hcode(const double *buf,long len)
{
    register bucket *bp, **bpp;
	HASHCODE hashcode;
	short n;

	hashcode=dhash(buf,len);
    bpp = symbol_table + hashcode;
    bp = *bpp;

	n=0;
    while (bp)
    {
	if (_dstrcmp(buf,len, bp->name) == 0) return (bp->hcode);
	n++;
	bpp = &bp->link;
	bp = *bpp;
    }
    *bpp = bp = dmake_bucket(buf,len,((STRINGCODE)hashcode<<16)+n);
    last_symbol->next = bp;
    last_symbol = bp;
    return (bp->hcode);

}
char buff_notsring[1000];
const char * hcode2string(STRINGCODE hcode)
{
    register bucket *bp, **bpp;
	short n;
	unsigned long hashcode=((hcode>>16) & 0x0000FFFF);
	


    bpp = symbol_table + hashcode;
    bp = *bpp;

	n=0;
    while (bp)
    {
	if (bp->hcode == hcode) return (bp->name);
	n++;
	bpp = &bp->link;
	bp = *bpp;
    }
	buff_notsring[0]=0;
	if (bp==NULL)
	{
		fprintf(stderr,"\nHCODE=0x%x:no_string",hcode);
		sprintf(buff_notsring,"HCODE_0x%x",hcode);
		//	_tmcRaiseException(err_bad_init,s_module,"no_string","Cant find string in hash table",0,NULL);
	}
	return (const char *)&buff_notsring[0];
}



short load_hash_table_const(const struct CInitHashData* pInitHashData,const long  initHashDataLen)
{
	STRINGCODE nHcode;
	STRINGCODE hc;
	const char *pStringName;
	long k;
	char buffer[2000];
	long m,n;
	long len;
	char c;
	//  register bucket *bp;
	long numerr=0;

	for (k=0;k< initHashDataLen;k++)
	{
			pStringName=pInitHashData[k].str;
			nHcode=pInitHashData[k].hc;
			len=(long)strlen(pStringName);//x64
			if (len==0)
					nHcode  = 0;
			n=0;
			for (m=0;m<len;m++)
			{
				c=pStringName[m];
				// Matlab strings don't contain escapes.
				// length('\r')=2. But C string support escapes: strlen("\r")=1
				if (c =='\n')
				{
					buffer[n++]='\\';buffer[n++]='n';
				}
				else if (c =='\t')
				{
					buffer[n++]='\\';buffer[n++]='t';
				}
				else if (c =='\r')
				{
					buffer[n++]='\\';buffer[n++]='r';
				}
				else
				{
					buffer[n++]=c;
				}
			}
			buffer[n]=0;
				//bp = string_hash_lookup(pStringName);
				//if (bp->hcode != nHcode)
				hc=string2hcode(buffer);
				if (hc !=nHcode)
				{
					//if(pStringName[strlen(pStringName)-1]!='\n')
					{
						fprintf(stderr,"**FATAL ERROR** CAN'T INITIALIZE APPLICATION: string=%s,hcode=%08x,updated=%08x ERROR !!!!\n",
						pStringName,nHcode,hc);
					}
				numerr++;
				}

	}
	if (numerr>0)
		return -1;
	else
		return 0;//ok
	
}

#ifndef  _TMC_EMBEDDED_

void print_hash_table(FILE *fp)
{
    register bucket *p, *q;
    for (p = first_symbol; p; p = q)
    {
	 q = p->next;
	 fprintf(fp,"\"%s\",0x%08x,\n",p->name,p->hcode);
     }
}

short load_hash_table(FILE *fp)
{
	STRINGCODE nHcode;
	char *pStringName;
	char buf[2020];
	int k,n1;
    register bucket *bp;

		while (fgets(buf,2002,fp) !=NULL)
		{
			k=1;
			pStringName=&buf[k];
			while (buf[k] != '"' && k<2000)
			{
				k++;
			}
			if (buf[k]=='"')// end of string
			{
				buf[k++]=0;
				k++; // skip ,
				n1=k;
				while (buf[k] != ',' && k<2000)
				{
					k++;
				}
				if (buf[k]==',') // end of heshcode
				{
					buf[k++]=0;
					nHcode=atol(&buf[n1]);
					n1=k;
				}
				bp = string_hash_lookup(pStringName);
				if (bp->hcode != nHcode)
				{
				//HAZARD: must test
				//fprintf(stderr,"string=%s,heshcode=%08x,updated=%08x ERROR !!!!\n",
				//	pStringName,nHeshcode,bp->hashcode);
				}
			}
			if (k<2000)
			{
			//	if (Compiler.verbose==true)
			//	fprintf(stderr,"Loaded: %s %08x\n",pStringName,nHeshcode);
			}
			else
			{
			_tmcRaiseException(err_bad_init,s_module,"load_hash_table","Invalid data file",0,NULL);
			}
		}
		return 0;
}
#endif

/////////////// private //////////////////////////
static	HASHCODE dhash(const double *dname,long len)
{
    register const double *s;
    register int c, k;
	long m;

    assert(len>0 && *dname);
    s = dname;
    k = (int)(*s);
    for(m=1;m<len;m++)
	{
		c = (int)(*++s);
	    k = (31*k + c) & (TABLE_SIZE - 1);
	}
    return (HASHCODE)k;
}
static	HASHCODE hash(const char *name)
{
    register const char *s;
    register int c, k;

    assert(name && *name);
    s = name;
    k = *s;
    while (c = *++s)
	k = (31*k + c) & (TABLE_SIZE - 1);

    return (HASHCODE)k;
}

void no_space()
{
			_tmcRaiseException(err_bad_init,s_module,"no_space","Cant allocate memory for hash table",0,NULL);
}
static	bucket * make_bucket(const char *name,STRINGCODE hcode)
{
    register bucket *bp;

    assert(name);
    bp = (bucket *) MALLOC(sizeof(bucket));
    if (bp == 0) no_space();
    bp->link = 0;
    bp->next = 0;
    bp->name = (char*)MALLOC(strlen(name) + 1);
    if (bp->name == 0) no_space();
	bp->hcode = hcode;
    if (bp->name == 0) no_space();
    strcpy(bp->name, name);

    return (bp);
}

static	bucket * dmake_bucket(const double *dname,long len,STRINGCODE hcode)
{
    register bucket *bp;
	register long k;
	

//    assert(dname);
    bp = (bucket *) MALLOC(sizeof(bucket));
    if (bp == 0) no_space();
    bp->link = 0;
    bp->next = 0;
    bp->name = (char*)MALLOC(len + 1);
    if (bp->name == 0) no_space();
	bp->hcode = hcode;

	for (k=0;k<len;k++)
		bp->name[k]=(char)dname[k];
	bp->name[k]=0;

    return (bp);
}

static	bucket * string_hash_lookup(const char *name)
{
    register bucket *bp, **bpp;
	HASHCODE hashcode;
	short n;

	hashcode=hash(name);
    bpp = symbol_table + hashcode;
    bp = *bpp;

	n=0;
    while (bp)
    {
	if (strcmp(name, bp->name) == 0) return (bp);
	n++;
	bpp = &bp->link;
	bp = *bpp;
    }

    *bpp = bp = make_bucket(name,((STRINGCODE)hashcode<<16)+n);
    last_symbol->next = bp;
    last_symbol = bp;

    return (bp);
}


static void create_string_hash_table(void)
{
    register int i;
    register bucket *bp;

    //symbol_table = (bucket **) MALLOC(TABLE_SIZE*sizeof(bucket *));
    //if (symbol_table == 0) no_space();
    for (i = 0; i < TABLE_SIZE; i++)
	symbol_table[i] = 0;

    bp = make_bucket("error",((STRINGCODE)hash("error")<<16));

    first_symbol = bp;
    last_symbol = bp;
    symbol_table[hash("error")] = bp;
}


static void free_string_hash_table(void)
{
    //FREE(symbol_table);
    //symbol_table = 0;
}


static void free_hash_strings(void)
{
    register bucket *p, *q;

    for (p = first_symbol; p; p = q)
    {
	q = p->next;
	FREE(p->name);
	FREE(p);
    }
}
