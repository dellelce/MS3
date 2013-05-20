/*
** structure definitions
**
*/

#define	STRUCTURES_H	1

#ifndef WSYSTEM_H
#include <wsystem.h>
#endif
#ifndef TONYEXTEND_H
#include <tonyextend.h>
#endif
#ifndef BLOCKS_H
#include <blocks.h>
#endif
#ifndef	 MAGICS_H
#include <magics.h>
#endif


/* # Structure
** # STRUCT
** 
*/ 

typedef	struct Structure
{
MAGIC		st_Magic;	/* identifier				*/
USHORT		st_Items;	/* structure items			*/
USHORT		st_Bytes;	/* bytes size				*/
USHORT		st_SelfCall;	/* (at least one) pointer to itself	*/
} STRUCT;

#define	SHSIZE	(ULONG) sizeof (STRUCT)
typedef STRUCT	STRUCTURE;

/* following structures
** are used when an expressions
** includes a structure
** (you gotta know if a structure item
**  exists or not!!)
** 
** Anyway, I think this stuff will be changed. (--> improved)
*/


/* # wstructitemname
** # WSINAME
** 
*/ 

#define	WSINAME		struct wstructitemname
#define	WSISIZE		OBSIZE (WSINAME)

struct wstructitemname
{
WSINAME		*next;
UWORD		 room;
UWORD		 touse;
};


/* # wstruct
** # WSTRUCT
** 
*/ 

#define	WSTRUCT		struct wstruct
#define	WSTRUCTSIZE	OBSIZE (WSTRUCT)

struct wstruct
{
WSTRUCT		*next;
PMAP		*pmapfather;
WORD		 items;
WSINAME		*firstitem;
UBYTE		*structname;
STRUCT		*definition;
};

#define	MAKEWSTRUCT()	Alloc (WSTRUCTSIZE)
#define	FREEWSTRUCT(x)	Free (x, WSTRUCTSIZE)

#define	SPSIZE		OBSIZE (UBYTE *)

#define	MAKEWSI(x)	Alloc (WSINAME + SPSIZE * (ULONG) x)
#define	FREEWSI(x)	Free (x, WSINAME + SPSIZE * x->room)
#define	INITWSI(x, y)	x->room = x->touse = y
#define	NEXTSTR(x)	NEXT (x, UBYTE *)
#define	VARNAME(b,x)	BSTRING (b, * (UWORD *) (x + 2))

#endif
