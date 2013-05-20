/* tony dee © 1992
** 
** functions access definitions 
** 
*/ 

#ifndef	FUNCTIONS_H
#define FUNCTIONS_H

#ifndef CODE_H
#include <code.h>
#endif


/* # Function
** # FUNCTION
** 
*/ 

typedef struct Function
{
UWORD	 fun_id;
UWORD	 fun_offset;		/* place in block		*/
UWORD	 fun_size;
UWORD	 fun_headsize;
} FUNCTION;


/* # LibCall
** # LIBFUN
** 
*/ 

typedef struct LibCall
{
FUNCTION	lc_Head;	/* function identifier		*/
WPTR		lc_LibraryName; /* shared library name		*/
WPTR		lc_CallName;	/* function name		*/
SHORT		lc_Offset;	/* its offset in library	*/
USHORT		lc_ArgsIn;	/* arguments to pass		*/
BOOL		lc_ArgOut;	/* is there any arg out?	*/
} LIBFUN;			/* to complete or change	*/


/*
**
**

|
|
| header della funzione
|
|
 |
 |
 | descrizione dei registri degli argomenti in entrata
 |
 |
  |
  |
  | variabile di descrizione del argomento di uscita
  | (se definito)
  |
  |
   |
   |
   | variabili di descrizione degli argomenti in entrata
   |
   |

**
**
*/


/* # BinaryFunction
** # BFUN
** 
*/ 

typedef	struct BinaryFunction
{
FUNCTION	bf_Head;	/* function id		*/
WPTR		bf_Place;	/* its place in pmap	*/
USHORT		bf_ArgsIn;	/* arguments in		*/
BOOL		bf_ArgOut;	/* is there arg out?	*/
USHORT		bf_ArgType;	/* register or stack	*/
} BFUN;

#define	AT_STACK	0x0000
#define	AT_REGISTER	0x0001


/* # IntFunction
** # INFUN
** 
*/ 

typedef struct IntFunction
{
FUNCTION	if_Head;	/* function identifier	*/
UBYTE		if_IntLevel;	/* interrupt level	*/
WORD		if_Args;	/* arguments in		*/
BOOL		if_ArgOut;	/* argument out ?	*/
} INFUN;

#define	ID_LIBCALL	0x0000	/* shared library call	*/
#define	ID_BINFN	0x0001	/* raw ml function	*/
#define	ID_INTCALL	0x0002	/* for 8086 family	*/


#define	LIBCALSIZE	(UWORD) sizeof (LIBFUN)
#define	BINFUNSIZE	(UWORD) sizeof (BFUN)
#define	INTERRSIZE	(UWORD) sizeof (INFUN)


#define	FUNCTIONS	3


/* $next structures are used for
** 'parsing' of function definition
** file, so to traslate into pmap file
** 
** 
*/ 


/* # _fs_vec
** # FS
** 
*/

typedef struct _fs_vec
{
UWORD	fs_Id;
UWORD	fs_Size;
} FS;

#define	FSSIZE		OBSIZE (FS)


/* # _line_parser_item
** # LPI
** 
*/ 

typedef struct  _line_parser_item
{
UBYTE	*lpi_str;
UWORD	 lpi_size;
} LPI;

#define	LPISIZE		OBSIZE (LPI)
#define LPARSE		struct _line_parser


/* # _line_parser
** # LP
** 
*/ 

typedef struct _line_parser
{
LPARSE	*lp_next;
LPARSE	*lp_last;
UWORD	 lp_parses;
UWORD	 lp_used;
} LP;

#define	LPSIZE		OBSIZE (LP)
#define	GETLPI(x,y)	(LPI *) ((ULONG) x + LPSIZE + (LPISIZE * ((ULONG) y--)))
#define	NEXTLPI(x)	(LPI *) ((ULONG) x + LPISIZE)


/* # _line
** # LIN
** 
*/ 

typedef struct _line
{
UBYTE	*linebuf;
UWORD	 bufsize;
UWORD	 linsize;
UWORD	 lincnt;
} LIN;

#define	LINSIZE		OBSIZE (LIN)

#endif
