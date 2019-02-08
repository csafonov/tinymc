_pRefHelper:
	DD	0
_pGetHelper:
	DD	0
_VV:
	DD	0
_tmcInitGlobals:
;	VV=tmcNewMatrix();
	call	___tmcNewMatrix
	mov [_VV+MY_LOAD_ADDRESS], eax
	ret

_tmcFreeGlobals:
;	tmcFreeLocalVar(VV);
	mov	eax,[_VV+MY_LOAD_ADDRESS]
	push	eax
	call	_tmcFreeLocalVar
	add	esp, 4
	ret

