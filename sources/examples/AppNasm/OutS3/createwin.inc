; 67   :    hWnd=CreateWindow(
; 68   :   L"edit",  // pointer to registered class name
; 69   :   L"tmcdebug", // pointer to window name
; 70   :   WS_DISABLED,        // window style
; 71   :   0,                // horizontal position of window
; 72   :   0,                // vertical position of window
; 73   :   1,           // window width
; 74   :   1,          // window height
; 75   :   NULL,      // handle to parent or owner window
; 76   :   0,          // handle to menu or child-window identifier
; 77   :   NULL,     // handle to application instance
; 78   :   NULL        // pointer to window-creation data
; 79   : );

strEdit:
	DB 'e', 00H, 'd', 00H, 'i', 00H
	DB	't', 00H, 00H, 00H
strDebug:					
    DB 't'
	DB	00H, 'm', 00H, 'c', 00H, 'd', 00H, 'e', 00H, 'b', 00H, 'u', 00H
	DB	'g', 00H, 00H, 00H			

_debug:
	 mov	 esi, esp
	 push	 0
	 push	 0
	 push	 0
	 push	 0
	 push	 1
	 push	 1
	 push	 0
	 push	 0
	 push	 134217728		; 08000000H
	 push	 MY_LOAD_ADDRESS+strEdit
	 push	 MY_LOAD_ADDRESS+strDebug
 	 push	 0
;;	 call	 DWORD PTR __imp__CreateWindowExW@48
;     mov	 DWORD PTR _hWnd, eax
	ret
