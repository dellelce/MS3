; tony dee © 1992
; 
; for the future
; 
	
	include "ms3base.i"
	include "variables.i"
	include "offsets.i"
	
	ROUTINE _getexpression
	ROUTINE _getexpr
	
	
	; input:
	; A1 --> group
	; A2 --> block
	; A3 --> first varend
	; A4 --> second varend
	
	; variables and special registers:
	; 
	; D7 --> save register
	; D6 --> item
	; D5 --> current varinfo
	; A5 --> pointer to name (from 'GROUP')
	; D3 --> EXPRESSION DATA
	; D2 --> 
	; 
	
REGS	.regs	D1-D7/A5-A6
	
	MOVEM.L	REGS,-(A7)	; 
	MOVEQ	#0,D7		; 
	MOVEQ	#0,D6		; 
	MOVEQ	#0,D5		; 
	MOVEQ	#0,D4		; 
	MOVEM.L	D4-D7,-(A7)	; 
	MOVEM.L (A7)+,D0-D3	; clean all data regs (are you sure of this?)
	MOVEA.L	gr_ghandle(A1),A0 ; get the global handle
	MOVEA.L	gr_name(A1),A5	  ; get 'name' structure address
	LEA	gh_exprdata(A0),A0 ; put expression data address to A0
	MOVE.L	A0,D3		   ; put it away to D3
	MOVE.L	ed_vardefsdata(A0),D4
	
	MOVE.L	A0,D5		;
	MOVE.L	A1,D2		;
	MOVE.L	A1,-(A7)	; for getname arguments to stack
	JSR	_getname	;
	MOVEA.L	D2,A1		;
	ADDA.W	#4,A7		;
	CMP.W	#TRUE,D0	;
	BNE	noname		;
	CMP.W	nd_type(A5),nd_type(A3)	;
	BNE.S	sekcheck		;
	CMP.L	nd_subtype(A5),nd_subtype(A3)	;
	MOVE.L	A3,gr_couple+cp_Big(A1)		;
sekcheck:					;
	CMP.W	nd_type(A5),nd_type(A4)		;
	BNE.S	nocloser			;
	CMP.L	nd_subtype(A5),nd_subtype(A4)	;
	MOVE.L	A4,gr_couple+cp_Big(A1)		;
nocloser:			;
				;
noname:				;
	MOVEA.L	gr_ghandle(A1),A0		;
	MOVE.L	#EN_NONAME,gh_lasterror(A0)	;
	BRA.S	getexprcloseup			;
						;
getexprcloseup:			;
	MOVE	(A7)+,REGS	;
	RTS			;
				;
	OFFBASE _start		;
				;

	ROUTINE _getname

; 
; still to come!
; 

	RTS			; it ain't very big, is it?
