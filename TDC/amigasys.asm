; amiga system routines by tony dee
; 
; 
	
	include 'msd3base.i'
	
_LVOAvailMem	EQU	-216
_LVOAllocMem	EQU	-198

	ROUTINE __tot_memory
	
	MOVEQ	#1,D1
	BRA.S	.1

	ROUTINE	__memory
	
	MOVE.L	#$200,D1
.1
	MOVEA.L	4,A6			; we don't care as you can see to
	JMP	_LVOAvailMem(A6)	; the saving and restoring of the
					; A6 reg, since it isn't used
					; by the aztec3.6a compiler...
					; but in 'HUBs'...
					; 
	
	ROUTINE	__alloc
	
	MOVEQ	#1,D1
	BRA.S	.2
	
	ROUTINE	__fast_alloc
	
	MOVE	#101,D1
.2
	MOVE.L	4(A7),D0
	MOVEA.L	4,A6
	JMP	_LVOAllocMem(A6)
	
	
	ROUTINE __set_bit
	
	MOVEM.L	4(A7),D0/D1
	BSET	D1,D0
	RTS
	
	
	ROUTINE __clear_bit
	
	MOVEM.L	4(A7),D0/D1
	BCLR	D1,D0
	RTS
	
	
	ROUTINE __get_bit
	
	; D0 => source object
	; D1 => bit number
	
	MOVEM.L	4(A7),D0/D1	; I am not sure for args placement
	BTST	D1,D0
	BEQ	.3
	MOVEQ	#1,D0		; bit is 1
	RTS
.3
	MOVEQ	#0,D0		; bit is 0
	RTS
	
	
	ROUTINE __var_size
	
	MOVE.L	4(A7),D1	; think it is to change
	MOVEQ	#0,D0
	MOVE.W	#$0300,D0
	AND.W	D1,D0
	ASR.W	#8,D0
	ADD.L	#1,D0
	RTS
	
	
	ROUTINE __next_var
	
	MOVEA.L	4(A7),A0
	MOVEQ	#0,D0
	MOVE.W	(A0),D0
	AND.W	#$0300,D0
	ASR.W	#8,D0
	ADDQ	#1,D0
	ADD.L	A0,D0
	RTS
	
	
	ROUTINE	__call_sub
	
	MOVEA.L	4(A7),A0
	JMP	(A0)		; don't change 
	
	
	ROUTINE	__sub_return
	
	ADD.L	#4,A7
	RTS			; it ain't very long, is it?
; 
; 
; 
; 
	
	public __far_setbizz
	
__far_setbizz:
	
	MOVEA.L	4(A7),A0
	MOVE.W	8(A7),D0
	MOVE.W	(A0),D1
	OR.W	D0,D1
	MOVE.W	D1,(A0)
	RTS
	
; 
; 
; 
	
	ROUTINE __far_copybizz		; what is it?

	MOVEA.L	4(A7),A0
	MOVE.W	8(A7),D0
	MOVE.W	10(A7),D1
	;$
	RTS
	
	
	ROUTINE	__clearmem
	
	; A0 -> place
	; D0 -> size
	
	MOVEM.L	4(A7),A0/D0
	MOVE.L	A0,D1
	BTST	#0,D1
	BEQ	words	; is first BIT zero? YES: go to word
	CLR.B	(A0)+	; clear first byte
	ADDQ	#1,D1	; 
	SUBQ	#1,D0	; decrease size
words:
	BTST	#1,D1	; 
	BEQ	longs	; 
	CLR.W	(A0)+	; 
	ADDQ	#2,D1	; 
	SUBQ	#2,D0	; decrease size
longs:
	MOVE.L	D0,-(A7)
	ASR	#2,D0
clearloop:
	CLR.L	(A0)+
	SUBQ	#1,D0
	TST.L	D0
	BEQ	endloop	; I don't like DBxx istruction at all...
	BRA	clearloop
endloop:
	MOVE.L	(A7)+,D0
	ANDI.L	#3,D0
	BEQ	end
clearloop0:
	CLR.B	(A0)+
	SUBQ	#1,D0
	TST.B	D0
	BEQ	end
	BRA	clearloop0
end:
	RTS
	
	
	ROUTINE __quickclearmem
	
	; that's something quicker isn't it!
	; 
	; 
	
	MOVEM.L	4(A7),A0/D0
	ADD.L	A0,D0
qcmloop:
	CLR.W	(A0)+
	CMP.L	A0,D0
	BNE	qcmloop
	RTS
	
	
	ROUTINE __turboclearmem
	
	; that's something magic!
	; 
	; 
	
	MOVEM.L	4(A7),A0/D0
	ADD.L	A0,D0
tcmloop:
	CLR.L	(A0)+
	CMP.L	A0,D0
	BNE	lcmloop
	RTS
	
; I consider them used as a given
	
	public	_DOSBase
		
	ROUTINE	_Read
	
	MOVEM.L	4(SP),D1-D3
	MOVE.L	_DOSBase,A6
	JMP	-42(A6)
	
	
	ROUTINE	_Write
	
	MOVEM.L	4(SP),D1-D3
	MOVE.L	_DOSBase,A6
	JMP	-48(A6)
	
	
	ROUTINE	_Open
	
	MOVEM.L	4(SP),D1/D2
	MOVE.L	_DOSBase,A6
	JMP	-30(A6)
	
	
	ROUTINE	_Close
	
	MOVE.L	4(SP),D1
	MOVE.L	_DOSBase,A6
	JMP	-36(A6)
	
	ROUTINE	_Output
	
	MOVE.L	_DOSBase,A6
	JMP	-60(A6)
	
	ROUTINE	_Input
	
	MOVE.L	_DOSBase,A6
	JMP	-54(A6)
	
	ROUTINE	_IoErr
	
	MOVE.L	_DOSBase,A6
	JMP	-132(A6)
	
	
	public	_DOSBase
_DOSBase:
	DC.L	0
	
; 
; let's get amiga basical data... "prototype version"
; 
	
	public	__amigarawinit
	
__amigarawinit:
	
	TST.L	_DOSBase
	BEQ	abd_true	; think well about it!
	LEA	A1,.doslib
	MOVEA.L	4,A6
	JSR	_OldOpenLibrary(A6)
	MOVE.L	D0,_DOSBase
	BEQ	abd_false
abd_true:
	MOVE	#1,D0		; TRUE
	RTS
abd_false:
	MOVEQ	#0,D0		; FALSE
	RTS

.doslib	
	DC.B	'dos.library',0		; how many libs do we need?
					; we go for the basical!!
	
	
	END	; A68K (v1.61) seems to need it!
