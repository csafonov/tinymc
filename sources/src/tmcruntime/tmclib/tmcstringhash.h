/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 File may be used in the generated application
  *****************************************************************************/

#ifndef tmcstringhash_h_
#define tmcstringhash_h_

	typedef unsigned long STRINGCODE;

	/*  the structure of a symbol table entry  */
	struct bucket
	{
		struct bucket *link;
		struct bucket *next;
		char *name;
		STRINGCODE hcode;
	};
	typedef struct bucket bucket;


	struct CInitHashData
	{
		const char *str;
		const STRINGCODE	hc;
	};
//	extern const struct CInitHashData InitHashData[];
//	extern const long InitHashDataLen;

	STRINGCODE string2hcode(const char *name);
	STRINGCODE dstring2hcode(const double *buf,long len);
#ifndef  _TMC_EMBEDDED_
	void print_hash_table(FILE *fp);
	short load_hash_table(FILE *fp);
#endif
	short load_hash_table_const(const struct CInitHashData* pInitHashData,const long  initHashDataLen);

	void InitStringHash(void);
	void DestroyStringHash(void);
	const char * hcode2string(STRINGCODE hcode);
	bucket ** GetSymbolTableAddr();
#endif
