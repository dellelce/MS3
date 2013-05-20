;:ts=8
; 
; tony dee creation of a string comparer
; 
; remarks:
; 
; a3 may be turned in an 'a1'
; 'link a5,#.2' (#.2 == 0) may be turned in 'lea a0,a7' (more effective)
; 'unlk a5' may be turned in 'lea a7,a0' (so all calls to a5 are changed to a0)
; 
; 
	public	__far_strcmp
__far_strcmp:
	movea.l	a7,a0
	movem.l	a2,-(sp)
	move.l	4(a0),a2
	move.l	8(a0),a1
	move.l	#0,d1
	move.l	(a2),d0
	cmp.l	(a1),d0
	bne	.4
	bra	.5
.4
	move.w	(a2),d0
	cmp.w	(a1),d0
	bne	.6
	bra	.7
.6
	bra	.8
.5
	add.l	#4,a1
.9
	add.l	#1,d1
	add.l	#1,a2
	tst.b	(a2)
	bne	.10
	bra	.7
.10
	cmp.l	#3,d1
	bne	.11
	add.l	#1,a2
	bra	.12
.11
	bra	.9
.12
.13
	move.b	(a2),d0
	cmp.b	(a1),d0
	bne	.14
	tst.b	(a2)
	bne	.15
	bra	.7
.15
	add.l	#1,a2
	add.l	#1,a1
	bra	.13
.14
	bra	.8
.7
	move.l	#1,d0
.16
	movem.l	(sp)+,.3
	movea.l	a0,a7
	rts
.8
	move.l	#0,d0
	bra	.16		; shouldn't it better to copy .16-.18 here
	public	.begin		; it would enlarge a little things but that's
	dseg			; just quicker.
	end			; 
				; the aztec assembler doesn't really need this
				; but some'un else does...
