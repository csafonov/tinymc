//File: TestO.globals.c 
//Generated by TMC Converter(C)2009-2016
#include "tmc.h"
#include "TestO.globals.h"

tmsMatrix	*pRefHelper;
tmsMatrix	*pGetHelper;
tmsMatrix *ite;
void tmcInitGlobals(void)
{
ite=tmcNewMatrix();
}
void tmcFreeGlobals(void)
{
tmcFreeLocalVar(ite);
}