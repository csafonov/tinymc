/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC Runtime software is covered under covered by simplified BSD 2-Clause license.
 * 
  *****************************************************************************/
//#include <windows.h>
#include "tmc.h"
#include <stdlib.h>
#include <string.h>
void Char2Uni(wchar_t	**ustr,char *str)
{
	size_t len = strlen(str);
	size_t cnt;
	*ustr = (wchar_t*)malloc((len+1)*sizeof(wchar_t));
	for (cnt=0;cnt<len;cnt++)
	{
		(*ustr)[cnt]=str[cnt];
	}
	(*ustr)[cnt]=0;
}
