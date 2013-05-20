; tony dee © 1992
; 
; faster release for 'blockwrite ()'
; older release
; 
; 
; 
	
	include 'ms3base.i'
	
; I am not sure about these offsets

v_block		EQU	 4
v_buf		EQU	 8
v_size		EQU	12

	ROUTINE _blockwrite

	MOVEA.L	A7,A0
	MOVEM.L	A6/A2,-(A7)
	MOVEA.L	A0,A2
	MOVEA.L	4,A6	
	MOVE.L	v_block(A2),-(A7)
	MOVE	v_size(A2),-(A7)
	JSR	_makeroom
	MOVEA.L	A2,A7
	TST.L	D0			; check if we got the destination
	BEQ	.end
	
	; prepare args for CopyMemQuick.. (it could be replaced...)
	; I could make a '_turbocopymem'... I just don't have the time (?)
	; 
	
	MOVEA.L	v_buf(A2),A0
	MOVEA.L	D0,A1
	MOVE.L	v_size(A2),D0
	JSR	_LVOCopyMemQuick(A6)
.end
	MOVEA.L	A2,A7
	MOVEM.L	(A7)+,A6/A2
	RTS
	
	
	public	_LVOCopyMemQuick
	public	_makeroom
