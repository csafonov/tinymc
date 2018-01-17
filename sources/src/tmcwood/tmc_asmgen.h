//File: tmc_asmgen.h
/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/
#ifndef _tmc_asmgen_h_
#define _tmc_asmgen_h_

// local variable presentation at stack
// the variables are only tmsMatrix * 
// Two first parameters are longs

#define ASM_NARGOUT_SIZE			4 // long par
#define ASM_PTR_TMCMATRIX_SIZE		4 // void*
#define ASM_RIP_SIZE				4 // reutrn instruction pointer size (placed at ebp-4..ebp
#define ASM_DOUBLE_SIZE				8
#define ASM_LONG_SIZE				4
#define ASM_PCHAR_SIZE				4
#define ASM_FNCADDR_SIZE			4

#define	max_stack_frame_size	0x200 // hazard
#define REG_SIZE		    4        // sizeof(reg[0])


class CAsmStrRec
{
public:
	long	str_ord;
	std::string strtext;
};

class CAsmVarRec
{
public:
	long		stack_offset;
	std::string varname;
};

#define REG_NARGIN	-3
#define REG_NARGOUT -4

class	CAsmSymTable
{
private:
	std::list<CAsmVarRec>  varlist;// variables to be allocated in stack
public:
	std::list<CAsmStrRec>  strpool;// constant strings used in the function strings
	
public:
	enum ERegVarTypes
	{
		REGVAR_VAR=0,
		REGVAR_REGISTER=1,
		REGVAR_P_REF_HELPER=2,
		REGVAR_NARGIN=3,
		REGVAR_NARGOUT=4,
		REGVAR_GLOBAL=5
	};
	typedef std::list<CAsmVarRec>::iterator VarRec_iterator;
	typedef std::list<CAsmStrRec>::iterator StrRec_iterator;

	long	stack_frame_size;// is positive
	long	strpool_size;
	void clear()
	{
		varlist.clear();
		stack_frame_size=ASM_RIP_SIZE;
		strpool.clear();
		strpool_size=0;
	};
	long get_reg_offset()
	{
		// get offset of reg[]
		// this must be first variable

		return -ASM_PTR_TMCMATRIX_SIZE-ASM_RIP_SIZE;
	}
	//long get_pRefHelper_offset()
	//{
	//	// get pRefHelper offset. Now it is local variable and must be secind one.
	//	return -ASM_PTR_TMCMATRIX_SIZE*2-ASM_RIP_SIZE;
	//}
	long lookup(std::string vname)
	{
		// return the offset in the stack frame
			 for (VarRec_iterator p=varlist.begin();p!=varlist.end();p++)
			 {
				if (p->varname.compare(vname)==0 )
				{
					return p->stack_offset;
				}
			 }
	return 0;//abnormal or maybe this is a global variable
	}
	long addstring(std::string strtext)
	{	CAsmStrRec s;
		s.str_ord = ++strpool_size;
		s.strtext = strtext;
		strpool.push_back(s);
		return s.str_ord;
	}
	long addvar(short ParamOrd,std::string vname)
	{// ParamOrd=1..N. If 0 is not parameter. 
/* E.g.:
[ztmc,y]=testM(a,b)

void tmctestM(int nargout, int nargin,tmsMatrix *ztmc,tmsMatrix *y
,tmsMatrix *a,tmsMatrix *b) {
tmsMatrix **reg=tmcCreateRegFrame(54);
tmsMatrix *p=tmcNewMatrix();

_p$ = -44						; size = 4
_reg$ = -32						; size = 4
__$SEHRec$ = -24					; size = 24
_nargout$ = 8						; size = 4
_nargin$ = 12						; size = 4
_ztmc$ = 16						; size = 4
_y$ = 20						; size = 4
_a$ = 24						; size = 4
_b$ = 28						; size = 4

*/

		// only add the var to list
		CAsmVarRec v;
		if (ParamOrd==0) // local var
		{
			v.stack_offset = -stack_frame_size-ASM_PTR_TMCMATRIX_SIZE;
			stack_frame_size += ASM_PTR_TMCMATRIX_SIZE;
		}
		else
		{
			if (ParamOrd<3) // first two input parameters
				v.stack_offset =8+ (ParamOrd-1)*ASM_NARGOUT_SIZE ;
			else
				v.stack_offset =8+ 1*ASM_NARGOUT_SIZE + (ParamOrd-2)*ASM_PTR_TMCMATRIX_SIZE;
		}
		v.varname  = vname;
		varlist.push_back(v);
		return v.stack_offset;
	}
	enum ERegVarTypes is_register_var(long *ofs,CIReg reg,std::string & varname)
	{ // if reg[ind] return 1. ofs = reg is ind
	  // otherwise  return  0. ofs is offset in stack.
      // return 2 if pRefHelper
	  // special cases: reg=-1: nargin
	  //				reg=-2: nargout			

			if (reg==REG_NARGIN)
			{
				*ofs=lookup("nargin");
				varname = "";//not used
				return REGVAR_NARGIN;
			}
			else if (reg==REG_NARGOUT)
			{
				*ofs=lookup("nargout");
				varname = "";//not used
				return REGVAR_NARGOUT;
			}


			if (CInstrList::RegDescr[reg].m_reg_type==REG_TYPE_IDENT)
			{ // this is a local variable
				varname = CInstrList::RegDescr[reg].varname;
				*ofs=lookup(CInstrList::RegDescr[reg].varname);
				if (*ofs==0)
				{
					return REGVAR_GLOBAL;
				}
				else
				return REGVAR_VAR;
			}
			else if (reg==Set_Helper_Reg)
			{
					//retval="pRefHelper";
					//*ofs=get_pRefHelper_offset();
					varname ="pRefHelper";
					return REGVAR_P_REF_HELPER;
			}
			//else if (reg==Get_Helper_Reg)
			//{
			//		retval="pGetHelper";
			//}
			else
			{
					*ofs=reg;
					varname ="";
					return REGVAR_REGISTER;
			}
	};

};
//////////////////////////////
extern CAsmSymTable	AsmSymTable;

class CAsmGenIntel
{
public:

	void asmdouble2hex(unsigned long *hdw,unsigned long *ldw,double dVal)
	{
		union Udouble
		{
			unsigned long   hl[2];
			double x;
		} val;
		val.x  = dVal;
		*hdw=val.hl[0];
		*ldw=val.hl[1];
	};
	std::string asm_gen_push_var(CIReg r)
	{// generate code for pushing reg[n] or local var  before calling a function
	char buff[300];
	std::string retval;
	std::string varname;
	long ofs;

		switch (AsmSymTable.is_register_var(&ofs,r,varname) )
		{
		case CAsmSymTable::REGVAR_REGISTER://1
	/*	00346	8b 45 e0					mov	 eax, DWORD PTR _reg$[ebp]
		00349	8b 88 c8 00 00	00			mov	 ecx, DWORD PTR [eax+200]
		0034f	51							push	 ecx
	*/
				sprintf(buff,	"\tmov\teax, DWORD PTR [ebp-%d]\n"
									"\tmov\tecx, DWORD PTR [eax+%d]\n"
									"\tpush\tecx\n",-AsmSymTable.get_reg_offset(),REG_SIZE*r);
				break;
		case CAsmSymTable::REGVAR_VAR://0
	/*
	  00362	8b 45 18					mov	 eax, DWORD PTR _a$[ebp]
	  00365	50							push	 eax
	*/
				sprintf(buff,	"\tmov\teax, DWORD PTR [ebp+%d]\n"
									"\tpush\teax\n",ofs);
				break;
		case CAsmSymTable::REGVAR_P_REF_HELPER://2
				sprintf(buff,	"\tmov\teax, _pRefHelper+MY_LOAD_ADDRESS\n"
									"\tpush\teax\n");
				break;
		case CAsmSymTable::REGVAR_GLOBAL://5
				sprintf(buff,	"\tmov\teax, [_%s+MY_LOAD_ADDRESS]\n"
					"\tpush\teax\n",varname.c_str());
				break;
		
		case CAsmSymTable::REGVAR_NARGIN://3
		case CAsmSymTable::REGVAR_NARGOUT://4

	/*
	sub		esp,8
	fild	qword  [ebp+12]
	fstp	qword  [esp]
	*/

				sprintf(buff,	"\tsub\tesp, 8\n"
									"\tfild\tdword PTR [ebp+%d]\n"
									"\tfstp\tQWORD PTR [esp]\n",ofs);

				break;

		}
		retval=buff;
		return retval;
	};

	std::string asm_gen_push_var_s(std::string varname)
	{// generate code for pushing reg[n] or local var  before calling a function
	char buff[300];
	std::string retval;
	long ofs;

	ofs = AsmSymTable.lookup(varname);

	/*
	  00362	8b 45 18					mov	 eax, DWORD PTR _a$[ebp]
	  00365	50							push	 eax
	*/
	if (ofs)
	{
		sprintf(buff,	"\tmov\teax, DWORD PTR [ebp+%d]\n"
									"\tpush\teax\n",ofs);
	}
	else // only global varible
	{
				sprintf(buff,	"\tmov\teax, [_%s+MY_LOAD_ADDRESS]\n"
					"\tpush\teax\n",varname.c_str());

	}

		retval=buff;
		return retval;
	};

	std::string asm_gen_call(const char *fn,long stack_to_clear)
	{
		char buff[300];
		std::string retval="";

		sprintf(buff,"\tcall %s\n",fn);
		retval.append(buff);
		if (stack_to_clear)
		{
			sprintf(buff,"\tadd\tesp,%d\n",stack_to_clear);
			retval.append(buff);
		}

		return retval;
	};
	std::string asm_gen_push_double(double x)
	{
					std::string retval;
					char buf[300];
					unsigned long hdw,ldw;
					asmdouble2hex(&hdw,&ldw,x);
					sprintf(buf,"\tpush\t0x%x\n"
									  "\tpush\t0x%x\n",ldw,hdw);
					retval = buf;
					return retval;
	};
	std::string asm_gen_push_long(long x)
	{
					std::string retval;
					char buf[30];
					sprintf(buf,"\tpush\t%d\n",x);
					retval = buf;
					return retval;
	};

	std::string asm_gen_fnc_enter(std::string fn,long f_stack_frame_size)
	{
					std::string retval;
					char buf[300];

			sprintf(buf,"\n_tmc%s:\n",fn.c_str());
			retval=std::string().append(buf);
			retval.append("\tpush ebp\n");
			retval.append("\tmov ebp,esp\n");

			sprintf(buf,"\tsub esp,%d\n",f_stack_frame_size);
			retval.append(buf);
			retval.append("\tpush ebx\n");
			retval.append("\tpush esi\n");
			retval.append("\tpush edi\n");
			sprintf(buf,"\tlea\tedi,DWORD PTR [ebp-%d]\n",f_stack_frame_size);
			retval.append(buf);
			return retval;
	}
	std::string asm_gen_fnc_leave(std::string fn,long f_stack_frame_size)
	{
					std::string retval;
					char buf[300];

			retval=std::string();
			retval.append("\tpop edi\n");
			retval.append("\tpop esi\n");
			retval.append("\tpop ebx\n");

			sprintf(buf,"\tadd esp,%d\n",f_stack_frame_size);
			retval.append(buf);
			retval.append("\tmov esp,ebp\n");
			retval.append("\tpop ebp\n");
			retval.append("\tret\n");

			sprintf(buf,"\t;end\t _tmc%s\n",fn.c_str());
			retval.append(buf);
			return retval;
	}
	std::string asm_store_longretval_in_frame(long frame_ofs)
	{
					std::string retval=std::string();
					char buf[300];

			sprintf(buf,"\tmov\tDWORD PTR [ebp-%d],eax\n",-frame_ofs);
			retval.append(buf);
			return retval;
	}
	std::string asm_bf_ne(CILabel igoto_label)
	{
/*
  00372	0f bf d0	 movsx	 edx, ax
  00375	85 d2		 test	 edx, edx
  00377	74 02		 je	 SHORT $LN1@tmcTestM
  00379	eb 32		 jmp	 SHORT $label_3$4501
$LN1@tmcTestM:
*/
					std::string retval=std::string();
					char buf[300];
			sprintf(buf,"\tmovsx\t edx,ax\n\ttest\tedx, edx\n\tjne .label_%d\n",igoto_label);
			retval.append(buf);
			return retval;
	}
	std::string asm_bf_unc(CILabel igoto_label)
	{
					std::string retval=std::string();
					char buf[300];
			sprintf(buf,"\tjmp .label_%d\n",igoto_label);
			retval.append(buf);
			return retval;
	}
	std::string asm_bf_eq(CILabel igoto_label,char labsuff=0)
	{
			std::string retval=std::string();
			char buf[300];
			if (labsuff)
			sprintf(buf,"\tmovsx\t edx,ax\n\ttest\tedx, edx\n\tje .label_%dx%c\n",igoto_label,labsuff);
			else
			sprintf(buf,"\tmovsx\t edx,ax\n\ttest\tedx, edx\n\tje .label_%d\n",igoto_label);
			retval.append(buf);
			return retval;
	}
	std::string asm_label(CILabel igoto_label,char labsuff=0)
	{
			std::string retval=std::string();
			char buf[300];
			if (labsuff)
				sprintf(buf,".label_%dx%c:\n",igoto_label,labsuff);
			else
				sprintf(buf,".label_%d:\n",igoto_label);
			retval.append(buf);
			return retval;
	}
	std::string asm_gen_push_str(long strord)
	{
			std::string retval=std::string();
			char buf[300];
			sprintf(buf,"\tmov\teax, .LC$%d+MY_LOAD_ADDRESS\n",strord);
			retval.append(buf);
			retval.append("\tpush eax\n");

			return retval;
	}
	std::string asm_gen_push_fncaddr_s(std::string fncname)
	{
			std::string retval=std::string();
			char buf[300];
			sprintf(buf,"\tmov\teax, %s+MY_LOAD_ADDRESS\n",fncname.c_str());
			retval.append(buf);
			retval.append("\tpush eax\n");

			return retval;
	}
	std::string asm_gen_strpool()
	{
			std::string retval=std::string();
			char buf[300];

		for (CAsmSymTable::StrRec_iterator p=AsmSymTable.strpool.begin();p!=AsmSymTable.strpool.end();p++)
			 {//HAZARD: must remove '
				CAsmStrRec StrRec = *p;
				sprintf(buf,".LC$%d:\t DB '%s', 0x0\n",StrRec.str_ord,StrRec.strtext.c_str());
				retval.append(buf);
			 }
		return retval;
	}

	std::string asm_try_catch_begin(CILabel ilabel)
	{
			std::string retval=std::string();
			char buf[300];
/*
    pushad										;;Save Current State  
    mov esi, .ExcHandler+MY_LOAD_ADDRESS         ;;Address of New Exception Handler  
    push esi									;;Save Old Exception Handler  
    push dword [fs:0]							;;Install New Handler  
    mov dword  [fs:0], esp 
*/
			retval.append("\tpushad\n");
			sprintf(buf,"\tmov esi, .ExcHandler_label_%d+MY_LOAD_ADDRESS\n",ilabel);
			retval.append(buf);
			retval.append("\tpush esi\n");
			retval.append("\tpush dword [fs:0]\n");
			retval.append("\tmov dword  [fs:0], esp\n");
			return retval;
	}
	std::string asm_try_catch_catch(CILabel ilabel,CILabel igoto_label)
	{
			std::string retval=std::string();
			char buf[300];
/*
    jmp .NoExceptionExcHandler    ;;No Exception Occured, so jump over Handler: 
.ExcHandler:
    mov esp, [esp + 8]              ;;Exception Occured, Get old ESP  
    pop dword  [fs:0]            ;;Restore Old Exception Handler  
    add esp, 4                      ;;ESP value before SEH was set  
    popad                           ;;Restore Old State  
*/
			sprintf(buf,"\tjmp .NoExceptionExcHandler_label_%d\n"
				".ExcHandler_label_%d:\n",igoto_label,ilabel);
			retval.append(buf);

			retval.append("\tmov esp, [esp + 8]\n");
			retval.append("\tpop dword  [fs:0]\n");
			retval.append("\tadd esp, 4\n");
			retval.append("\tpopad\n");
			return retval;
	}
	std::string asm_try_catch_end(CILabel ilabel,CILabel igoto_label)
	{
			std::string retval=std::string();
			char buf[300];
/*
    jmp .ExceptionHandledExcHandler    ;;Exception was handled by @TRY_EXCEPT
.NoExceptionExcHandler:                ;;No Exception Occured  
    pop dword  [fs:0]            ;;Restore Old Exception Handler  
    add esp, 32 + 4                 ;;ESP value before SEH was set. 32 for pushad and ...  
.ExceptionHandledExcHandler:           ;;...4 for push offset Handler. (No Restore State)  
*/
			sprintf(buf,"\tjmp .ExceptionHandledExcHandler_label_%d\n"
				".NoExceptionExcHandler_label_%d:\n",igoto_label,ilabel);
			retval.append(buf);

			retval.append("\tpop dword  [fs:0]\n");
			retval.append("\tadd esp, 32 + 4\n");
			sprintf(buf,".ExceptionHandledExcHandler_label_%d:\n",igoto_label);
			retval.append(buf);

			return retval;
	}


};

#endif
