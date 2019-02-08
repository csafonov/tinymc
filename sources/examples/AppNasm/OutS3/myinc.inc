	%define	FINALLY
	%define TRY
	%define PTR
	%define DWORD
	%define ENDFINALLY


;	%include "createwin.inc"


_Init_funcs_table:
    DD _InitHashData+MY_LOAD_ADDRESS
	DD	_InitHashDataLen+MY_LOAD_ADDRESS
	DD	_tmcInitGlobals+MY_LOAD_ADDRESS
	DD	_tmcFreeGlobals+MY_LOAD_ADDRESS
	DD	_pRefHelper+MY_LOAD_ADDRESS
	DD	_pGetHelper+MY_LOAD_ADDRESS


_myentry:





	push ebp
	mov ebp,esp
	sub esp,2000
	push ebx
	push esi
	push edi
	lea	edi,DWORD PTR [ebp-2000]

	;call	_debug

	push    _Init_funcs_table+MY_LOAD_ADDRESS
	call	_tmcconnectdebugger
	add	esp,4

	push    _Init_funcs_table+MY_LOAD_ADDRESS
	call	_tmcInitLib
	add	esp,4


;//function [ztmc_,y_]=TestM(a_,b_)

	;void tmcTestM(int nargout, int nargin,tmsMatrix *ztmc_,tmsMatrix *y_
	;,tmsMatrix *a_,tmsMatrix *b_	;) {




	push	0
	push	0
	push	0
	push	0
	push	dword 77
	push	dword 87
	call	MAIN_ENTRY
	add	esp,(4*6)

	call	_tmcFreeLib


	pop edi
	pop esi
	pop ebx
	add esp,2000
	mov esp,ebp
	pop ebp
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;_tmcfigure:
;	ret