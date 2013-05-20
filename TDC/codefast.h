/* tony dee (c) 1992
** 
** fast assembly coding
** 
** 
*/

#ifndef CODEFAST_H
#define	CODEFAST_H	1

#ifndef CODECORE_H
#inclue <codecore.h>
#endif

/* 
** grandezze del MOVE
** 
*/ 

#define	MOS_BYTE	%0001000000000000
#define	MOS_WORD	%0010000000000000
#define	MOS_LONG	%0011000000000000


/*
** Branch control kinds
** 
** $2
** 
*/

#define BRT_NONE	0x0000	/* direct jump				*/
#define	BRT_SUB		0x0100	/* subroutine				*/
#define	BRT_HIGH	0x0200
#define	BRT_LOWEQ	0x0300	/* lower or equal			*/
#define	BRT_CARC	0x0400	/* carry clear				*/
#define	BRT_CARS	0x0500	/* carry set				*/
#define	BRT_NOTEQ	0x0600	/* not equal				*/
#define	BRT_EQUAL	0x0700	/* equal				*/
#define	BRT_OVCLR	0x0800	/* overflow clear			*/
#define	BRT_OVSET	0x0900	/* overflow set				*/
#define	BRT_POS	        0x0A00	/* positive				*/
#define	BRT_NEG		0x0B00	/* negative				*/
#define	BRT_GREATEQ    	0x0C00	/* greater or equal			*/
#define	BRT_MINOR	0x0D00	/* minor (!)				*/
#define	BRT_MAJOR	0x0E00	/* major (!)				*/
#define	BRT_MINEQ	0x0F00	/* minor or equal			*/

#define	BRT_FALSE	0x0100	/* what do they mean??			*/
#define	BRT_TRUE	0x0000


/*
/*
** aliases for above
**
*/

#define	BRT_NOTZERO	BRT_NOTEQ /* also: last operation was not a 0	*/
#define	BRT_ZERO	BRT_EQUAL /* also: last operation was a 0	*/


/* 
** $
** 
** registers
** 
*/

#define	REG_D0		0x0000	/* $1.0	*/
#define	REG_D1		0x0001
#define	REG_D2		0x0002
#define	REG_D3		0x0003
#define	REG_D4		0x0004
#define	REG_D5		0x0005
#define	REG_D6		0x0006
#define	REG_D7		0x0007


#define	REG_A0		0x0000	/* $1.1	*/
#define	REG_A1		0x0001
#define	REG_A2		0x0002
#define	REG_A3		0x0003
#define	REG_A4		0x0004
#define	REG_A5		0x0005
#define	REG_A6		0x0006
#define	REG_A7		0x0007


/* $
** 
** fast instructions
** 
*/

#define	IX_BRANCH	0x6000
#define	IX_BRASUBR	0x6100
#define	IX_DECBRA	0x50C8	/* decrement and branch: for loops	*/
#define	IX_SWAP		0x4840	/* swap the reg words			*/
#define	IX_EXTW		0x4880	/* extend to word			*/
#define	IX_EXTL		0x48C0	/* extend to long			*/
#define	IX_RETURN	0x4E75	/* normal return			*/
#define	IX_IRETURN	0x4E73	/* interrupt (or "exception") return	*/
#define	IX_PRETURN	0x4E77	/* partial int return (??)		*/
#define	IX_SETIF	0x50C0	/* set if... (need $3 and $1)		*/
#define	IX_ZEROTEST	0x4A00	/* test with zero			*/
#define	IX_ROLLSHIFT	0xE000	/* roll and shift basical definition	*/
#define	IX_SUBTRACT	0x9000	/* %1001 need more info about them	*/
#define	IX_ADD		0xD000	/* %1101  "	"   "	  "	"	*/
#define	IX_DIVIDE	0x8000	/* %1000  "	"   "	  "	"	*/
#define	IX_MULTIPLY	0xC000	/* %1100  "	"   "	  "	"	*/
#define	IX_PUSHEA	0x4840	/* push effective address ... -> SWAP	*/
#define	IX_REALADDR	0x41C0	/* LEA ..load effective address		*/
#define	IX_EXG		0xC000	/* EXG inst: alike 'MULTIPLY'...	*/
#define	IX_MOVEQ	0x7000	/* quick moves a signed char to a datreg*/
#define	IX_
#define	IX_


/* $
** 
** test with zero sizes (byte, word, long)
** 
** 
*/ 

#define	TESTBYTE	%0000000000000000
#define	TESTWORD	%0000010000000000
#define	TESTLONG	%0000100000000000
#define	TAS		%0000110000000000 /* I don't know it very well	*/


/* 
** 
** registers as special argument
** 
*/ 

#define	SROF(x)		(x << 9)

#define	SREG_D0		%0000000000000000
#define	SREG_D1		%0000001000000000
#define	SREG_D2		%0000010000000000
#define	SREG_D3		%0000011000000000
#define	SREG_D4		%0000100000000000
#define	SREG_D5		%0000101000000000
#define	SREG_D6		%0000110000000000
#define	SREG_D5		%0000111000000000

#define	SREG_A0		%0000000000000000
#define	SREG_A1		%0000001000000000
#define	SREG_A2		%0000010000000000
#define	SREG_A3		%0000011000000000
#define	SREG_A4		%0000100000000000
#define	SREG_A5		%0000101000000000
#define	SREG_A6		%0000110000000000
#define	SREG_A7		%0000111000000000

/* $
** 
** macros
** 
*/ 

#define	SRCOV			6	/* source offset (in MOVE)...	*/

/* 
** for MOVE instruction...
** 
*/ 

#define	DATA2DATA		AM1_DATREG	|	AM2_DATREG
#define	ADDR2ADDR		AM1_ADDREG	|	AM2_ADDREG
#define	OFFS2OFFS		AM1_OFFADD	|	AM2_OFFADD
#define	ADDR2DATA		AM1_ADDREG	|	AM2_DATREG
#define	ADDR2OFFS		AM1_ADDREG	|	AM2_OFFADD
#define	DATA2ADDR		AM1_DATREG	|	AM2_ADDREG
#define	DATA2OFFS		AM1_DATREG	|	AM2_OFFADD
#define	IMME2DATA		AM1_IMMEDIATE	|	AM2_DATREG
#define	IMME2ADDR		AM1_IMMEDIATE	|	AM2_ADDREG
#define	ADDR2RGPT		AM1_ADDREG	|	AM2_BYAREG
#define	DATA2RGPT		AM1_DATREG	|	AM2_BYAREG
#define	IMME2RGPT		AM1_IMMEDIATE	|	AM2_BYAREG
#define	DATA2STCK		AM1_DATREG	|	AM2_DECREG
#define	STCK2DATA		AM1_INCREG	|	AM2_DATREG
#define	OFFS2STCK		AM1_OFFADD	|	AM2_DECREG
#define	STCK2OFFS		AM1_INCREG	|	AM2_OFFADD


#define	_FARBRA(b,t,o)		W0 (b, IX_BRANCH | t); W1 (b, o)
#define	FARBRA(b,t,o)		(WNO (b, 2); _FARBRA(b,t,o))
#define	_NEARBRA(b,t,o)		W0 (b, IX_BRANCH | t | o)
#define	NEARBRA(b,t,o)		(WNO (b, 1); _NEARBRA(b,t,o))

#define	_FARBSR(b,o)		(_FARBRA (b, BRT_SUB, o))
#define	FARBSR(b,o)		(FARBRA (b, BRT_SUB, o))
#define	_NEARBSR(b,o)		(_NEARBRA (b, BRT_SUB, o))
#define	NEARBSR(b,o)		(NEARBRA (b, BRT_SUB, o))

#define	MOVEB_D2D(b,x,y)	W0 (b, MOS_BYTE | (y << SRCOV) | x | DATA2DATA)
#define	MOVEW_D2D(b,x,y)	W0 (b, MOS_WORD | (y << SRCOV) | x | DATA2DATA)
#define	MOVEL_D2D(b,x,y)	W0 (b, MOS_LONG | (y << SRCOV) | x | DATA2DATA)

#define	MOVEB_A2A(b,x,y)	W0 (b, MOS_BYTE | (y << SRCOV) | x | ADDR2ADDR)
#define	MOVEW_A2A(b,x,y)	W0 (b, MOS_WORD | (y << SRCOV) | x | ADDR2ADDR)
#define	MOVEL_A2A(b,x,y)	W0 (b, MOS_LONG | (y << SRCOV) | x | ADDR2ADDR)

#define	MOVEB_OF2OF(b,x,y)	W0 (b, MOS_BYTE | (y << SRCOV) | x | OFFS2OFFS)
#define	MOVEW_OF2OF(b,x,y)	W0 (b, MOS_WORD | (y << SRCOV) | x | OFFS2OFFS)
#define	MOVEL_OF2OF(b,x,y)	W0 (b, MOS_LONG | (y << SRCOV) | x | OFFS2OFFS)

#define	MOVEB_A2D(b,x,y)	W0 (b, MOS_BYTE | (y << SRCOV) | x | ADDR2DATA)
#define	MOVEW_A2D(b,x,y)	W0 (b, MOS_WORD | (y << SRCOV) | x | ADDR2DATA)
#define	MOVEL_A2D(b,x,y)	W0 (b, MOS_LONG | (y << SRCOV) | x | ADDR2DATA)

#define	MOVEB_A2OFFS(b,x,y)	W0 (b, MOS_BYTE | (y << SRCOV) | x | ADDR2OFFS)
#define	MOVEW_A2OFFS(b,x,y)	W0 (b, MOS_WORD | (y << SRCOV) | x | ADDR2OFFS)
#define	MOVEL_A2OFFS(b,x,y)	W0 (b, MOS_LONG | (y << SRCOV) | x | ADDR2OFFS)

#define	MOVEB_D2A(b,x,y)	W0 (b, MOS_BYTE | (y << SRCOV) | x | DATA2ADDR)
#define	MOVEW_D2A(b,x,y)	W0 (b, MOS_WORD | (y << SRCOV) | x | DATA2ADDR)
#define	MOVEL_D2A(b,x,y)	W0 (b, MOS_LONG | (y << SRCOV) | x | DATA2ADDR)

#define	MOVEB_OFFS2A(b,x,y)	W0 (b, MOS_BYTE | (y << SRCOV) | x | OFFS2ADDR)
#define	MOVEW_OFFS2A(b,x,y)	W0 (b, MOS_WORD | (y << SRCOV) | x | OFFS2ADDR)
#define	MOVEL_OFFS2A(b,x,y)	W0 (b, MOS_LONG | (y << SRCOV) | x | OFFS2ADDR)

/* 
** x = register
** destination (y) not available since $done with a different macro
** 
*/ 

#define	MOVEW_I2A(b,x)		W0 (b, MOS_WORD | (x << SRCOV) | IMME2ADDR)
#define	MOVEL_I2A(b,x)		W0 (b, MOS_LONG | (x << SRCOV) | IMME2ADDR)
#define	MOVEB_I2D(b,x)		W0 (b, MOS_BYTE | (x << SRCOV) | IMME2DATA)
#define	MOVEW_I2D(b,x)		W0 (b, MOS_WORD | (x << SRCOV) | IMME2DATA)
#define	MOVEL_I2D(b,x)		W0 (b, MOS_LONG | (x << SRCOV) | IMME2DATA)

/* 
** RP stands for 'register as pointer', otherwise (Ax)
** esample: move.w d1,(a4) (-> -> MOVEW_D2RP (the_bunch, REG_D1, REG_A4))
** 
*/ 

#define	MOVEB_A2RP(b,x,y)	W0 (b, MOS_BYTE | (y << SRCOV) | x | ADDR2RGPT)
#define	MOVEW_A2RP(b,x,y)	W0 (b, MOS_WORD | (y << SRCOV) | x | ADDR2RGPT)
#define	MOVEL_A2RP(b,x,y)	W0 (b, MOS_LONG | (y << SRCOV) | x | ADDR2RGPT)

#define	MOVEB_D2RP(b,x,y)	W0 (b, MOS_BYTE | (y << SRCOV) | x | DATA2RGPT)
#define	MOVEW_D2RP(b,x,y)	W0 (b, MOS_WORD | (y << SRCOV) | x | DATA2RGPT)
#define	MOVEL_D2RP(b,x,y)	W0 (b, MOS_LONG | (y << SRCOV) | x | DATA2RGPT)

#define	MOVEB_I2RP(b,x,y)	W0 (b, MOS_BYTE | (y << SRCOV) | x | IMME2RGPT)
#define	MOVEW_I2RP(b,x,y)	W0 (b, MOS_WORD | (y << SRCOV) | x | IMME2RGPT)
#define	MOVEL_I2RP(b,x,y)	W0 (b, MOS_LONG | (y << SRCOV) | x | IMME2RGPT)

/* 
** PUSHes end POPs
** 
*/ 

#define	MOVEB_D2STK(b,x,y)	W0 (b, MOS_BYTE | (y << SRCOV) | x | DATA2STCK)
#define	MOVEW_D2STK(b,x,y)	W0 (b, MOS_WORD | (y << SRCOV) | x | DATA2STCK)
#define	MOVEL_D2STK(b,x,y)	W0 (b, MOS_LONG | (y << SRCOV) | x | DATA2STCK)

#define	MOVEB_STK2D(b,x,y)	W0 (b, MOS_BYTE | (y << SRCOV) | x | STCK2DATA)
#define	MOVEW_STK2D(b,x,y)	W0 (b, MOS_WORD | (y << SRCOV) | x | STCK2DATA)
#define	MOVEL_STK2D(b,x,y)	W0 (b, MOS_LONG | (y << SRCOV) | x | STCK2DATA)

#define	MOVEB_A2STK(b,x,y)	W0 (b, MOS_BYTE | (y << SRCOV) | x | ADDR2STCK)
#define	MOVEW_A2STK(b,x,y)	W0 (b, MOS_WORD | (y << SRCOV) | x | ADDR2STCK)
#define	MOVEL_A2STK(b,x,y)	W0 (b, MOS_LONG | (y << SRCOV) | x | ADDR2STCK)

#define	MOVEB_STK2A(b,x,y)	W0 (b, MOS_BYTE | (y << SRCOV) | x | STCK2ADDR)
#define	MOVEW_STK2A(b,x,y)	W0 (b, MOS_WORD | (y << SRCOV) | x | STCK2ADDR)
#define	MOVEL_STK2A(b,x,y)	W0 (b, MOS_LONG | (y << SRCOV) | x | STCK2ADDR)

#define	MOVEB_OFF2STK(b,x,y)	W0 (b, MOS_BYTE | (y << SRCOV) | x | OFFS2STCK)
#define	MOVEW_OFF2STK(b,x,y)	W0 (b, MOS_WORD | (y << SRCOV) | x | OFFS2STCK)
#define	MOVEL_OFF2STK(b,x,y)	W0 (b, MOS_LONG | (y << SRCOV) | x | OFFS2STCK)

#define	MOVEB_STK2OFF(b,x,y)	W0 (b, MOS_BYTE | (y << SRCOV) | x | STCK2OFFS)
#define	MOVEW_STK2OFF(b,x,y)	W0 (b, MOS_WORD | (y << SRCOV) | x | STCK2OFFS)
#define	MOVEL_STK2OFF(b,x,y)	W0 (b, MOS_LONG | (y << SRCOV) | x | STCK2OFFS)


#define	SWAPL_D(b,x)		W0 (b, IX_SWAP | x)

#define	EXTW_D(b,x)		W0 (b, IX_EXTW | x)
#define	EXTL_D(b,x)		W0 (b, IX_EXTL | x)
#define	RETURN(b)		W0 (b, IX_RETURN)


#define	TESTB_DR(b,x)		W0 (b, IX_ZEROTEST | TESTBYTE | AM1_DATREG | x)
#define	TESTW_DR(b,x)		W0 (b, IX_ZEROTEST | TESTWORD | AM1_DATREG | x)
#define	TESTL_DR(b,x)		W0 (b, IX_ZEROTEST | TESTLONG | AM1_DATREG | x)

#define	TESTB_AR(b,x)		W0 (b, IX_ZEROTEST | TESTBYTE | AM1_ADDREG | x)
#define	TESTW_AR(b,x)		W0 (b, IX_ZEROTEST | TESTWORD | AM1_ADDREG | x)
#define	TESTL_AR(b,x)		W0 (b, IX_ZEROTEST | TESTLONG | AM1_ADDREG | x)

#define	TESTB_PR(b,x)		W0 (b, IX_ZEROTEST | TESTBYTE | AM1_BYAREG | x)
#define	TESTW_PR(b,x)		W0 (b, IX_ZEROTEST | TESTWORD | AM1_BYAREG | x)
#define	TESTL_PR(b,x)		W0 (b, IX_ZEROTEST | TESTLONG | AM1_BYAREG | x)

#define	TESTB_STK(b,x)		W0 (b, IX_ZEROTEST | TESTBYTE | AM1_INCREG | x)
#define	TESTW_STK(b,x)		W0 (b, IX_ZEROTEST | TESTWORD | AM1_INCREG | x)
#define	TESTL_STK(b,x)		W0 (b, IX_ZEROTEST | TESTLONG | AM1_INCREG | x)

#define	TEST_RES(b)		TESTL_DR (b, REG_D0)

/* 
** offset is put down by a different macro (W1 ())
** 
*/ 

#define	TESTB_OFF(b,x)		W0 (b, IX_ZEROTEST | TESTBYTE | AM1_INCREG | x)
#define	TESTW_OFF(b,x)		W0 (b, IX_ZEROTEST | TESTWORD | AM1_INCREG | x)
#define	TESTL_OFF(b,x)		W0 (b, IX_ZEROTEST | TESTLONG | AM1_INCREG | x)


/* 
** load effective address macros
** many of them could/should be removed
** 
** x --> object to load
** y --> addresss register where to load
** 
*/ 

#define	LOADEFF_DR(b,x,y)	W0 (b, IX_REALADDR | AM1_DATREG | SROF (y) | x)
#define	LOADEFF_AR(b,x,y)	W0 (b, IX_REALADDR | AM1_ADDREG | SROF (y) | x)
#define	LOADEFF_AP(b,x,y)	W0 (b, IX_REALADDR | AM1_BYAREG | SROF (y) | x)
#define	LOADEFF_SN(b,x,y)	W0 (b, IX_REALADDR | AM1_INCREG | SROF (y) | x)
#define	LOADEFF_OR(b,x,y)	W0 (b, IX_REALADDR | AM1_OFFADD | SROF (y) | x)
#define	LOADEFF_XA(b,x,y)	W0 (b, IX_REALADDR | AM1_IDXADD | SROF (y) | x)
#define	LOADEFF_SA(b,x,y)	W0 (b, IX_REALADDR | AM1_SHRTAB | SROF (y) | x)
#define	LOADEFF_LA(b,x,y)	W0 (b, IX_REALADDR | AM1_LNGABS | SROF (y) | x)
#define	LOADEFF_PC(b,x,y)	W0 (b, IX_REALADDR | AM1_PCREL  | SROF (y) | x)
#define	LOADEFF_PX(b,x,y)	W0 (b, IX_REALADDR | AM1_PCRELX | SROF (y) | x)
#define	LOADEFF_IM(b,x,y)	W0 (b, IX_REALADDR | AM1_IMMED  | SROF (y) | x)

#define	_LOADEFF_DR(b,x,y)	W0 (b, IX_REALADDR | AM1_DATREG | y | x)
#define	_LOADEFF_AR(b,x,y)	W0 (b, IX_REALADDR | AM1_ADDREG | y | x)
#define	_LOADEFF_AP(b,x,y)	W0 (b, IX_REALADDR | AM1_BYAREG | y | x)
#define	_LOADEFF_SN(b,x,y)	W0 (b, IX_REALADDR | AM1_INCREG | y | x)
#define	_LOADEFF_OR(b,x,y)	W0 (b, IX_REALADDR | AM1_OFFADD | y | x)
#define	_LOADEFF_XA(b,x,y)	W0 (b, IX_REALADDR | AM1_IDXADD | y | x)
#define	_LOADEFF_SA(b,x,y)	W0 (b, IX_REALADDR | AM1_SHRTAB | y | x)
#define	_LOADEFF_LA(b,x,y)	W0 (b, IX_REALADDR | AM1_LNGABS | y | x)
#define	_LOADEFF_PC(b,x,y)	W0 (b, IX_REALADDR | AM1_PCREL  | y | x)
#define	_LOADEFF_PX(b,x,y)	W0 (b, IX_REALADDR | AM1_PCRELX | y | x)
#define	_LOADEFF_IM(b,x,y)	W0 (b, IX_REALADDR | AM1_IMMED  | y | x)


/* 
** Clear instruction
** 
*/ 

#define	CLR_BYTE	%0000000000000000
#define	CLR_WORD	%0000000001000000
#define	CLR_LONG	%0000000010000000

#define	CLRB_D(b,x)	W0 (b, AM1_DATREG | CLR_BYTE | x)
#define	CLRW_D(b,x)	W0 (b, AM1_DATREG | CLR_WORD | x)
#define	CLRL_D(b,x)	W0 (b, AM1_DATREG | CLR_LONG | x)

#define	CLRB_A(b,x)	W0 (b, AM1_ADDREG | CLR_BYTE | x)
#define	CLRW_A(b,x)	W0 (b, AM1_ADDREG | CLR_WORD | x)
#define	CLRL_A(b,x)	W0 (b, AM1_ADDREG | CLR_LONG | x)

#define	CLRB_PR(b,x)	W0 (b, AM1_BYAREG | CLR_BYTE | x)
#define	CLRW_PR(b,x)	W0 (b, AM1_BYAREG | CLR_WORD | x)
#define	CLRL_PR(b,x)	W0 (b, AM1_BYAREG | CLR_LONG | x)

#define	CLRB_STK(b,x)	W0 (b, AM1_INCREG | CLR_BYTE | x)
#define	CLRW_STK(b,x)	W0 (b, AM1_INCREG | CLR_WORD | x)
#define	CLRL_STK(b,x)	W0 (b, AM1_INCREG | CLR_LONG | x)

#define	CLRB_OFR(b,x)	W0 (b, AM1_OFFADD | CLR_BYTE | x)
#define	CLRW_OFR(b,x)	W0 (b, AM1_OFFADD | CLR_WORD | x)
#define	CLRL_OFR(b,x)	W0 (b, AM1_OFFADD | CLR_LONG | x)

#define	CLRB_OFX(b,x)	W0 (b, AM1_IDXADD | CLR_BYTE | x)
#define	CLRW_OFX(b,x)	W0 (b, AM1_IDXADD | CLR_WORD | x)
#define	CLRL_OFX(b,x)	W0 (b, AM1_IDXADD | CLR_LONG | x)

/* 
** SAD : short address, put place in W1
** ADD : 32bit address, put place in W1 and W2
** OFP : offset address from PC, put offset in W1
** OFX : offset address from PC plus 
** 
** 
*/ 

#define	CLRB_SAD(b,x)	W0 (b, AM1_SHRTAB | CLR_BYTE | x)
#define	CLRW_SAD(b,x)	W0 (b, AM1_SHRTAB | CLR_WORD | x)
#define	CLRL_SAD(b,x)	W0 (b, AM1_SHRTAB | CLR_LONG | x)

#define	CLRB_ADD(b,x)	W0 (b, AM1_LNGABS | CLR_BYTE | x)
#define	CLRW_ADD(b,x)	W0 (b, AM1_LNGABS | CLR_WORD | x)
#define	CLRL_ADD(b,x)	W0 (b, AM1_LNGABS | CLR_LONG | x)

#define	CLRB_OFP(b)	W0 (b, AM1_PCREL  | CLR_BYTE)
#define	CLRW_OFP(b)	W0 (b, AM1_PCREL  | CLR_WORD)
#define	CLRL_OFP(b)	W0 (b, AM1_PCREL  | CLR_LONG)

#define	CLRB_OFX(b,x)	W0 (b, AM1_PCRELX | CLR_BYTE | x)
#define	CLRW_OFX(b,x)	W0 (b, AM1_PCRELX | CLR_WORD | x)
#define	CLRL_OFX(b,x)	W0 (b, AM1_PCRELX | CLR_LONG | x)

/* 
** move quickly in 'immediate' value to a data reg
** 
** 
*/ 

#define	MOVEQ_D(b,x,y)		W0 (b, IX_MOVEQ | SROF (x) | y)
#define	_MOVEQ_D(b,x,y)		W0 (b, IX_MOVEQ | x | y)

#define	CLEAN_D0(b)		_MOVE_Q (b, SREG_D0, 0)
#define	CLEAN_D1(b)		_MOVE_Q (b, SREG_D1, 0)
#define	CLEAN_D2(b)		_MOVE_Q (b, SREG_D2, 0)
#define	CLEAN_D3(b)		_MOVE_Q (b, SREG_D3, 0)
#define	CLEAN_D4(b)		_MOVE_Q (b, SREG_D4, 0)
#define	CLEAN_D5(b)		_MOVE_Q (b, SREG_D5, 0)
#define	CLEAN_D6(b)		_MOVE_Q (b, SREG_D6, 0)
#define	CLEAN_D7(b)		_MOVE_Q (b, SREG_D7, 0)

/* 
** push effective address
** 
*/ 

#define	PUSHEA_RP(b,x)		W0 (b, IX_PUSHEA | AM1_BYAREG | x)
#define	PUSHEA_ROFF(b,x)	W0 (b, IX_PUSHEA | AM1_OFFADD | x)
#define	PUSHEA_ROFX(b,x)	W0 (b, IX_PUSHEA | AM1_IDXADD | x)
#define	PUSHEA_SHAD(b)		W0 (b, IX_PUSHEA | AM1_SHRTAB)
#define	PUSHEA_LGAD(b)		W0 (b, IX_PUSHEA | AM1_LNGAB)
#define	PUSHEA_PCOF(b)		W0 (b, IX_PUSHEA | AM1_PCREL)
#define	PUSHEA_PCFX(b)		W0 (b, IX_PUSHEA | AM1_PCRELX)

#endif
