; tony dee © 1992
; 
; basical assembly definitions for MS3 language
; F  U  T  U  R  E
; 
; 
	
	include "exec/types.i"
	
	
ROUTINE		MACRO
		PUBLIC	\1
1\:		
		MEND
		
		
MB		MACRO
		MOVE.B	\1,\2
		MEND
		
		
MW		MACRO
		MOVE.W	\1,\2
		MEND
		
		
ML		MACRO
		MOVE.L	\1,\2
		MEND
		
ENDROUTINE	MACRO	; empty macro
		MEND

;
; sets offset base
; 

OFFBASE		MACRO
_OFFBASE	SET	\1
		MEND
		
; 
; sets a word with an object (\1) offset from the base
; 

SOFFSET		MACRO
		DC.W	\1-_OFFBASE
		MEND
		
; 
; points out a new program
; 
		
PROGRAM		MACRO
		PUBLIC \1
1\:
		MEND
		
		
STR		MACRO
		PUBLIC	\1
1\:		
		DC.B \2
		MEND
		
PUSHALL		MACRO
		MOVEM.L	A0-A6/D1-D7,-(SP)
		MEND
	
POPALL		MACRO
		MOVE.L	(SP)+,A0-A6/D1-D7
		MEND
