/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
//#include <list>
#include <stack>
//#include <string>

#include "tmc_string_hash.h"
#include "tmcpar_env.h"

CStringHash::HASHCODE CStringHash::hash(const char *name)
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
{		Compiler.LogErr(101, "cant allocate string in hash table,internal error","<>", 1,true);
}
CStringHash::bucket * CStringHash::make_bucket(const char *name,STRINGCODE hcode)
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

STRINGCODE CStringHash::string2hcode(const char *name)
{
//	register bucket *bp=string_hash_lookup(name);
//	return bp->hcode;

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
const char * CStringHash::hcode2string(STRINGCODE hcode)
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
	if (bp==NULL)
	{
		//	_tmcRaiseException(err_bad_init,s_module,"no_string","Cant find string in hash table",0,NULL);
		char sbuf[200];
		sprintf(sbuf,"0x%08x",hcode);
		Compiler.LogErr(103, "cant find string hash code in hash table,internal error",sbuf, 1,true);
		//fprintf(stderr,"Cant found string\n,hc=0x%08x",hcode);
		//throw(CCompilerExcpt());
	}
	return "?error";
}

CStringHash::bucket * CStringHash::string_hash_lookup(const char *name)
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


void CStringHash::create_string_hash_table(void)
{
    register int i;
    register bucket *bp;

    symbol_table = (bucket **) MALLOC(TABLE_SIZE*sizeof(bucket *));
    if (symbol_table == 0) no_space();
    for (i = 0; i < TABLE_SIZE; i++)
	symbol_table[i] = 0;

    bp = make_bucket("?error",((STRINGCODE)hash("?error")<<16));

    first_symbol = bp;
    last_symbol = bp;
    symbol_table[hash("?error")] = bp;
}


void CStringHash::free_string_hash_table(void)
{
    FREE(symbol_table);
    symbol_table = 0;
}


void CStringHash::free_hash_strings(void)
{
    register bucket *p, *q;

    for (p = first_symbol; p; p = q)
    {
	q = p->next;
	FREE(p);
    }
}



void CStringHash::print_hash_table(FILE *fp)
{
    register bucket *p, *q;
	int cnt,len;

    for (p = first_symbol; p; p = q)
    {
	 q = p->next;
	 //fprintf(fp,"\"%s\",0x%08x,\n",p->name,p->hcode);
		fprintf(fp,"\"");
		len = strlen(p->name);
		for (cnt=0;cnt<len;cnt++)
		{
			fprintf(fp,"%c",p->name[cnt]);
			if (p->name[cnt] == '\\')
				fprintf(fp,"%c",p->name[cnt]);
		}
		fprintf(fp,"\",0x%08x,\n",p->hcode);
    }
}
void CStringHash::print_hash_table_asm(FILE *fp)
{//HAZARD: must remove '
/*
_InitHashData:
    DD .LCerror+MY_LOAD_ADDRESS
	DD	0x0d2080000
    DD .LCx+MY_LOAD_ADDRESS
	DD	0x00780000
    DD .LCy+MY_LOAD_ADDRESS
	DD	0x00790000
    DD .LCz+MY_LOAD_ADDRESS
	DD	0x007a0000
    DD .LCeggog+MY_LOAD_ADDRESS
	DD	0xa89d0000
*/


    register bucket *p, *q;
	//int cnt,len;
	int nsym;
	//char buf[2]={0,0};
	//std::list<std::string> LC_list;
	//std::string x;
	//std::list<std::string>::iterator itLC_list;

		fprintf(fp,"_InitHashData:\n");

	nsym=0;
    for (p = first_symbol; p; p = q)
    {
	 q = p->next;
		//x = ".HLC";
		/*
		len = strlen(p->name);
		for (cnt=0;cnt<len;cnt++)
		{
			

			if (p->name[cnt] == '\\')
			{
				buf[0]='$';
			}
			else
			{
				buf[0]=p->name[cnt];
			}
		x.append(buf);
		}
		
		fprintf(fp,"\tDD\t%s",x.c_str());
		LC_list.push_back(x);
		*/
		fprintf(fp,"\tDD\t.HLC%d",nsym);

		fprintf(fp,"+MY_LOAD_ADDRESS\n\tDD\t0x%08x\n",p->hcode);
		nsym++;
    }
/*
.LCerror DB 'error', 0x0
.LCx DB 'x', 0x0
.LCy DB 'y', 0x0
.LCz DB 'z', 0x0
.LCeggog DB 'eggog',0x0,

_InitHashDataLen:
    DD 0x5
*/	   
	//itLC_list = LC_list.begin();
	nsym=0;
	for (p = first_symbol; p; p = q)
    {
	 //x = *itLC_list;
	 //itLC_list++;

	 q = p->next;
	 //fprintf(fp,"%s\tDB\t'%s',0x0\n",x.c_str(),p->name);
	 fprintf(fp,".HLC%d\tDB\t'%s',0x0\n",nsym,p->name);
	 nsym++;
    }
	 fprintf(fp,"_InitHashDataLen:\n\tDD\t%d\n",nsym);

}

short CStringHash::load_hash_table(FILE *fp)
{
	STRINGCODE nHcode;
	char *pStringName;
	char buf[2020];
	int k,n1;
    register bucket *bp;

		while (fgets(buf,2002,fp) !=NULL)
		{
//fprintf(stderr,"%s\n",buf);

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
				if (Compiler.verbose==true)
				fprintf(stderr,"Loaded: %s %08x\n",pStringName,nHcode);
			}
			else
			{
				fprintf(stderr,"Ignored string\n");
			}
		}
		return 0;
}
void  CStringHash::sym_hash_insert(const char *name,void *_pItem)
{
	bucket * b = string_hash_lookup(name);
	if (b)
	{
		b->pItem=_pItem;
	}

}