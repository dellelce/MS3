/* tony dee (c) 1992
** 
** fast coding
** 
** 
*/

#ifndef CODECORE_H
#define CODECORE_H

#ifndef	TONYEXTEND_H
#include <tonyextend.h>
#endif
#ifndef CODE_H
#include <code.h>
#endif


/* %%
** 
** A 'bunch' handliung macros
** 
*/ 

#define	WNO(b,c)		(b->b_cnum = c)
#define	W0(b,x)			(b->b_code [0] = x)
#define	W1(b,x)			(b->b_code [1] = x)
#define	W2(b,x)			(b->b_code [2] = x)
#define	W3(b,x)			(b->b_code [3] = x)
#define	W4(b,x)			(b->b_code [4] = x)
#define	W5(b,x)			(b->b_code [5] = x)

#define	WONE(b)			(WNO (b, 1))

/* 
** that's the basical for amiga....
** 
*/ 

#define	GET_EXECBASE(b)		(WNO (b, 2); W0 (b, 0x27C8); W1 (b, 4))
#define	LIBCALL(b)		(WONE (b); W0 (b, 0x4eae))
#define	LIBJUMP(b)		(WONE (b); W0 (b, 0x4eee))


/* %%
** 
** 68k address modes (DESTination type)
** 
** 
*/ 

#define	AM1_DATREG	%000000		/* Dn				*/
#define	AM1_ADDREG	%001000		/* An				*/
#define	AM1_BYAREG	%010000		/* (An)				*/
#define	AM1_INCREG	%011000		/* (An)+			*/
#define	AM1_DECREG	%100000		/* -(An)			*/
#define	AM1_OFFADD	%101000		/* d(An)			*/
#define	AM1_IDXADD	%110000		/* d(An, Ri)			*/

#define	AM1_SHRTAB	%111000		/* $XXXX			*/
#define	AM1_LNGABS	%111001		/* $XXXXXXXX			*/
#define	AM1_PCREL	%111010		/* off(PC)			*/
#define	AM1_PCRELX	%111011		/* off(PC, Ri)			*/
#define	AM1_IMMEDIATE	%111100		/* #$XXXX			*/

#define	AM1_IMMED	AM1_IMMEDIATE

#define	EXT_AM (x)	(x<<6)	/* $ address extension	*/

#define	AM2_DATREG	%000000000000	/* Dn				*/
#define	AM2_ADDREG	%001000000000	/* An				*/
#define	AM2_BYAREG	%010000000000	/* (An)				*/
#define	AM2_INCREG	%011000000000	/* (An)+			*/
#define	AM2_DECREG	%100000000000	/* -(An)			*/
#define	AM2_OFFADD	%101000000000	/* d(An)			*/
#define	AM2_IDXADD	%110000000000	/* d(An, Ri), how to do	it???	*/

#define	AM2_SHORTABS	%111000000000	/* $XXXX			*/
#define	AM2_LONGABS	%111001000000	/* $XXXXXXXX			*/
#define	AM2_PCREL	%111010000000	/* off(PC)			*/
#define	AM2_PCREGREL	%111011000000	/* off(PC, Ri)			*/
#define	AM2_IMMEDIATE	%111100000000	/* #$XXXX			*/

/* 
** Far away register map
** 
*/ 

#define	CLEANDEST(x)		AND (0xfff8, x)
#define	_SETDEST(x, y)		OR (x, y)
#define	SETDEST(x, y)		OR (CLEANDEST (x), y)

#endif
