/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/
#ifndef tmc_string_hash_h_
#define tmc_string_hash_h_

/* TABLE_SIZE is the number of entries in the symbol table. */
/* TABLE_SIZE must be a power of two.			    */

#define	TABLE_SIZE 65536L

#define	FREE(x)		(free((char*)(x)))
#define MALLOC(n)	(malloc((unsigned)(n)))
/*  the structure of a symbol table entry  */
typedef unsigned long STRINGCODE;

class CStringHash
{
private:
	struct bucket
	{
		struct bucket *link;
		struct bucket *next;
		char *name;
		STRINGCODE hcode;
		void* pItem;// for converter
	};
	typedef unsigned long HASHCODE;
	typedef struct bucket bucket;
	bucket **symbol_table;
	bucket *first_symbol;
	bucket *last_symbol;
	HASHCODE hash(const char *name);
	bucket * make_bucket(const char *name,STRINGCODE hcode);
	void create_string_hash_table(void);
	void free_string_hash_table(void);
	void free_hash_strings(void);
	bucket *string_hash_lookup(const char *name);
public:
	STRINGCODE string2hcode(const char *name);
	const char * hcode2string(STRINGCODE hcode);
	void print_hash_table(FILE *fp);
	short load_hash_table(FILE *fp);
	void print_hash_table_asm(FILE *fp);
	void sym_hash_insert(const char *name,void *_pItem);
	CStringHash()
	{
		create_string_hash_table();
	}
	~CStringHash()
	{
		free_hash_strings();
		free_string_hash_table();
	}
};

extern class CStringHash StringHash;






#endif