/* tony dee © 1992
** 
** extended definitions	
** 
*/ 

#ifndef TONYEXTEND_H
#define	TONYEXTEND_H 1

#ifndef WSYSTEM_H
#include <wsystem.h>
#endif


#define	FLAG			UWORD
#define	flag			UWORD
#define	ON			1
#define	OFF			0
#define	BITMODE(x, y, z)	AND (AND (NOT (BIT (y)), z), x)

#define	NOT(x)			!x
#define	AND(x, y)		(x & y)
#define	OR(x,y)			(x | y)
#define	EOR(x,y)		(x ^ y)
#define	BIT(x)			(1 << x)
#define SHIFTL(x, y)		(x << y)
#define	SHIFTR(x, y)		(x >> y)
#define	SETNIBBLE(x, y)		AND (x, y + 0xfff0)
/* older version
#define	SETBIT(x, b)		OR (x, BIT (b))
#define	CLRBIT(x, b)		AND (x, NOT (BIT (b)))
#define	GETBIT(x, b)		AND (SHIFTR (x, b), 1)
*/
#define	SETBIT(x, b)		_set_bit (x, b)
#define	CLRBIT(x, b)		_clear_bit (x, b)
#define	GETBIT(x, b)		_get_bit (x, b)
#define	GetBit(x, b)		_get_bit (x, b)
#define	SETBIZZ(x, y)		OR (x, y)

#define	ISZERO(x)		(x == 0)
#define	ISNOTZERO(x)		(x != 0)
#define	ISFALSE(x)		(x == FALSE)
#define	ISTRUE(x)		(x == TRUE)
#define	ISONE(x)		(x == 1)

#define	call(x)			_call_sub (x)
#define	subreturn		_sub_return ()
#define	_subreturn()		_sub_return ()

#define	FOREVER			for (;;)
#define	REG			register
#define	reg			REG
#define	WPTR			UWORD

ULONG	_BUILTIN_strlen ();

#define	strlen			_BUILTIN_strlen
#define	STRLEN			_BUILTIN_strlen
#define	strcmp			__far_strcmp
#define	STRCMP			__far_strcmp
#define	NEXT(x, y)		((ULONG) x + (ULONG) sizeof (y))
#define	NEXTBY(x, y)		((ULONG) x + (ULONG) y)
#define	FOREVER			for (;;)


#endif
