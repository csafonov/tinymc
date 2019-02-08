_pRefHelper:
	DD	0
_pGetHelper:
	DD	0
_ite:
	DD	0
_ite:
	DD	0
_tmcInitGlobals:
;	ite=tmcNewMatrix();
	call	___tmcNewMatrix
	mov [_ite+MY_LOAD_ADDRESS], eax
	ret
;	ite=tmcNewMatrix();
	call	___tmcNewMatrix
	mov [_ite+MY_LOAD_ADDRESS], eax
	ret

_tmcFreeGlobals:
;	tmcFreeLocalVar(ite);
	mov	eax,[_ite+MY_LOAD_ADDRESS]
	push	eax
	call	_tmcFreeLocalVar
	add	esp, 4
	ret
;	tmcFreeLocalVar(ite);
	mov	eax,[_ite+MY_LOAD_ADDRESS]
	push	eax
	call	_tmcFreeLocalVar
	add	esp, 4
	ret

