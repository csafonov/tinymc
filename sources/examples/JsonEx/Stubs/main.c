#define _CRT_SECURE_NO_DEPRECATE
// Close the following define to hide the parser ouput:
#define YYDEBUG 1
// c file: main.c
#include <stdio.h>
#include <stdlib.h>
#include "../JsonParser/JsonRead.tab.h"

#include "../JsonParser/JMatrix.h"

extern FILE* Json_in;
extern int yylineno;
extern tmsMatrix * head_tmc_obj;


void tmctestm1(int nargout, int nargin, tmsMatrix *x, tmsMatrix *y, tmsMatrix *fn);

/**
	Read json-file and save it as matlab workspace (.mat)
	Usage: ReadJson <filename>
	       ReadJson  (input from stdin)

		   The example demonstrated usage of CMAke for the project building.
		   See also the sources JsonRead.Y,JsonRead.L 
		   that demonstrate how to use  bison/flex with TMC runtime
		   to create JSON parser (based on example given in
		   Lloyd Rochester "Parse JSON with Flex and Bison" article
		   (https://lloydrochester.com/post/flex-bison/json-parse/)
*/
int main(int argc, char *argv[])
{
	tmsMatrix *fname;
	tmsMatrix *mJsonFile = 0;
	tmsMatrix *www;
	tmsMatrix *x;
	tmsMatrix *y;
	// This code must be in the server application
	tmcInitLib(&Init_funcs_table);

	x = tmcNewMatrix();
	y = tmcNewMatrix();

	www = tmcNewMatrix();
	mJsonFile = tmcNewMatrix();

	if (argc == 2)
	{
		tmcCreateString(mJsonFile, argv[1]);
	}
	else
	{
		tmcCreateMatrixEmpty(mJsonFile);
	}
	tmctestm1(2,1,www,y, mJsonFile);

	//tmcjson_read(1, argc - 1, www, mJsonFile);
	/*
	int stat;

	// if a file is given read from it
	// otherwise we'll read from STDIN
	if(argc == 2)
	{
	if(!(Json_in = fopen(argv[1],"r")))
	{
	perror(argv[1]);
	return EXIT_FAILURE;
	}
	}



	stat =  Json_parse();
	*/

	fname = tmcNewMatrix();
	tmcCreateString(fname, "input.mat");
	tmcsave(0, 1+2, fname, www, "www",y,"filename");// ninput is number of saved matrices plus one

	tmcFreeLocalVar(fname);
	tmcFreeLocalVar(www);
	tmcFreeLocalVar(y);
	tmcFreeLocalVar(x);

	tmcFreeLib();

	return 0;
}
