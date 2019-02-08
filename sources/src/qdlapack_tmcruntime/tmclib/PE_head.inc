	BITS 32
	ORG	0
	MY_LOAD_ADDRESS EQU	0x400000


	%define		start	_myentry

;
; MZ header
;
; The only two fields that matter are e_magic and e_lfanew

mzhdr:
    dw "MZ"                       ; e_magic
    dw 0                          ; e_cblp UNUSED
    dw 0                          ; e_cp UNUSED
    dw 0                          ; e_crlc UNUSED
    dw 0                          ; e_cparhdr UNUSED
    dw 0                          ; e_minalloc UNUSED
    dw 0                          ; e_maxalloc UNUSED
    dw 0                          ; e_ss UNUSED
    dw 0                          ; e_sp UNUSED
    dw 0                          ; e_csum UNUSED
    dw 0                          ; e_ip UNUSED
    dw 0                          ; e_cs UNUSED
    dw 0                          ; e_lsarlc UNUSED
    dw 0                          ; e_ovno UNUSED
    times 4 dw 0                  ; e_res UNUSED
    dw 0                          ; e_oemid UNUSED
    dw 0                          ; e_oeminfo UNUSED
    times 10 dw 0                 ; e_res2 UNUSED
    dd pesig                      ; e_lfanew

;
; PE signature
;

pesig:
    dd "PE"

;
; PE header
;

pehdr:
    dw 0x014C                     ; Machine (Intel 386)
    dw 1                          ; NumberOfSections
    dd 0x4545BE5D                 ; TimeDateStamp UNUSED
    dd 0                          ; PointerToSymbolTable UNUSED
    dd 0                          ; NumberOfSymbols UNUSED
    dw opthdrsize                 ; SizeOfOptionalHeader
    dw 0x103                      ; Characteristics (no relocations, executable, 32 bit)

;
; PE optional header
;

filealign equ 200h
mysectalign equ 1000h

%define round(n, r) (((n+(r-1))/r)*r)

opthdr:
    dw 0x10B                      ; Magic (PE32)
    db 8                          ; MajorLinkerVersion UNUSED
    db 0                          ; MinorLinkerVersion UNUSED
    dd round(codesize, filealign) ; SizeOfCode UNUSED
    dd 0                          ; SizeOfInitializedData UNUSED
    dd 0                          ; SizeOfUninitializedData UNUSED
    dd start                      ; AddressOfEntryPoint
    dd code                       ; BaseOfCode UNUSED
    dd round(filesize, mysectalign) ; BaseOfData UNUSED
    dd MY_LOAD_ADDRESS            ; ImageBase
    dd mysectalign                  ; SectionAlignment
    dd filealign                  ; FileAlignment
    dw 4                          ; MajorOperatingSystemVersion UNUSED
    dw 0                          ; MinorOperatingSystemVersion UNUSED
    dw 0                          ; MajorImageVersion UNUSED
    dw 0                          ; MinorImageVersion UNUSED
    dw 4                          ; MajorSubsystemVersion
    dw 0                          ; MinorSubsystemVersion UNUSED
    dd 0                          ; Win32VersionValue UNUSED
    dd filesize ;//round(filesize, mysectalign) ; SizeOfImage
    dd hdrsize			;round(hdrsize, filealign)  ; SizeOfHeaders
    dd 0                          ; CheckSum UNUSED
    dw 2+1                          ; Subsystem (Win32 GUI)
    dw 0x000                      ;IMAGE_DLLCHARACTERISTICS_NO_SEH=0x400 DllCharacteristics
    dd 0x400000                   ; SizeOfStackReserve UNUSED
    dd 0x4000                     ; SizeOfStackCommit
    dd 0x100000                   ; SizeOfHeapReserve
    dd 0x1000                     ; SizeOfHeapCommit UNUSED
    dd 0                          ; LoaderFlags UNUSED
    dd 16                         ; NumberOfRvaAndSizes UNUSED


;
; Data directories
;
    dd 0                                      ; Export Table UNUSED
    dd 0
    dd idata                                  ; Import Table
    dd idatasize

    times 14 dd 0, 0

opthdrsize equ $ - opthdr

;
; PE code section
;

    db ".text", 0, 0, 0           ; Name
    dd codesize                   ; VirtualSize
    dd code_va ; //round(hdrsize, mysectalign)  ; VirtualAddress
    dd codesize ;//round(codesize, filealign) ; SizeOfRawData
    dd code_va ; //code                       ; PointerToRawData
    dd 0                          ; PointerToRelocations UNUSED
    dd 0                          ; PointerToLinenumbers UNUSED
    dw 0                          ; NumberOfRelocations UNUSED
    dw 0                          ; NumberOfLinenumbers UNUSED
    dd 0xE0000020                 ; Characteristics (code, execute, read,write)

;NUMBEROFSECTIONS equ ($ - SectionHeader) / IMAGE_SECTION_HEADER_size
hdrsize equ $ - $$

;
; PE code section data
;

align mysectalign, db 0
code_va	equ	$-$$
code:

;;;;;;;;;;;;;;
; Import table (array of IMAGE_IMPORT_DESCRIPTOR structures)

idata:
    dd ilt                                    ; OriginalFirstThunk UNUSED
    dd 0                                      ; TimeDateStamp UNUSED
    dd 0                                      ; ForwarderChain UNUSED
    dd kernel32                               ; Name
    dd iat                                    ; FirstThunk

 ;   dd iltUser32                                    ; OriginalFirstThunk UNUSED
 ;   dd 0                                      ; TimeDateStamp UNUSED
 ;   dd 0                                      ; ForwarderChain UNUSED
 ;   dd user32                               ; Name
  ;  dd iatUser32                                    ; FirstThunk

    ; empty IMAGE_IMPORT_DESCRIPTOR structure

    dd 0                                      ; OriginalFirstThunk UNUSED
    dd 0                                      ; TimeDateStamp UNUSED
    dd 0                                      ; ForwarderChain UNUSED
    dd 0                                      ; Name UNUSED
    dd 0                                      ; FirstThunk

idatasize equ $ - idata

; Import address table (array of IMAGE_THUNK_DATA structures)

iat:
	%include "iat.inc"

    dd 0									; terminator

; Import lookup table (array of IMAGE_THUNK_DATA structures)

ilt:

	%include "iat.inc"

    dd 0			; terminator


iatUser32:
    dd (0x80000000+98)                             ; Import function 1 by ordinal
    dd 0									; terminator

; Import lookup table (array of IMAGE_THUNK_DATA structures)

iltUser32:
    dd (0x80000000+98)                             ; Import function 1 by ordinal
    dd 0


kernel32:
    db "tmcrtvc8.dll", 0
user32:
    db "user32.dll", 0

;;;;;;;;;;;;;;

	%include "fncc.inc"

;	%define		__imp__CreateWindowExW@48	[iatUser32+MY_LOAD_ADDRESS+0*4]
