/*
** tony dee 
** code writing	definitions (code still to make)
** 
*/ 

#ifndef CODEF_H
#define	CODEF_H		1


#ifndef	WSYSTEM_H
#include <wsystem.h>
#endif


/* very old and useless macros
** 
*/ 

#define	kputl(c,l)	_far_writecode (c, &l, 2)
#define	kputw(c,w)	_far_writecode (c, &w, 1)


/* newer macros
** 
** so new that I have still to find
** what routines will use them
** 
*/ 

#define	writeprg(f,p)		_far_writeprogram (f,p)
#define	writehunk(f,k)		_far_writehunk (f,k)
#define	writehunktype(h,t)	_far_writehunktype (h,t)
#define	closedown(h)		_far_closedown (h)


#define	FHANDLE		ULONG

/* # prgwritehandle
** # PRGWH 
** 
*/

typedef struct prgwritehandle
{
UBYTE		*pwh_Name;
FHANDLE		 pwh_File;
UWORD		 pwh_WrittenHunks;
UWORD		 pwh_Pad;
PROGRAM		*pwh_Program;
} PRGWH;


#endif
