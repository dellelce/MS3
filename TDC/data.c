/* tony dee © 1991/92
** 
** 
** data.c
** this file contains routines for
** data handling
** 
** 
*/


#include <tonyexend.h>
#include <data.h>
#include <names.h>
#ifdef	 USE_IN_MS3
#include <logics.h>
#endif

#define	DATA_C		1
#include <ms3fn.h>



/* %%
** CreateSingleBuf
** BufOpen
** BufPack
** BufWrite
** NumToA
** shiftleft
** 
** 
*/ 

VOID	 FreeMem  ();
ULONG	 OutPut	  ();

/* # CreateSingleBuf
** 
*/

FB *	
CreateSingleBuf (mode)
UWORD	 mode;
{
FB	*fb;
ULONG	 size;

fb = (FB *) Alloc (FBSIZE);

if (ISZERO (fb))
	{
	return (0L);
	}

size = ((ULONG) mode) * 2048L;

fb->fb_Buffer = (UBYTE *) Alloc (size);

if (ISZERO (fb->fb_Buffer))
	{
	FreeMem (fb, FBSIZE);
	return (0L);
	}

fb->fb_Size = size;

return (fb);
}


/* # BufOpen
** 
*/

FB *
#ifdef USE_IN_MS3
BufOpen (ghandle, name, mode)
GHANDLE *ghandle;
UBYTE	*name;
UWORD	 mode;
#else
BufOpen (fl, name, mode)
TLIST	*fl;
UBYTE	*name;
UWORD	 mode;
#endif
{
REG FB		*fb;
REG BNAME	*bn;

fb = CreateSingleBuf (mode);

if (ISZERO(fb))
	{
	return (0L);
	}

#ifdef USE_IN_MS3
ADDTAIL (ghandle->filebufs, fb);
#else
ADDTAIL (fl, fb);
#endif

if (ISNOTZERO (name))
	{
	bn = (BNAME *) Alloc (BNSIZE);
	
	if (ISZERO (bn))
		{
		BufDelete (fb);
		return (0L);
		}

	bn->bf_Name = name;
	}

bn->bf_Size = strlen (size);

return (fb);
}


/*
** TRUE = FileBuf packed or did not need to be packed
**
** FALSE = FileBuf was not packed
**
** # BufPack Work:
**
** is fb_BufPieces->tl_Last zero?
**	YES:
**	    object does not need to be packed since only
**	    two buffers are contained by the FileBuf
**	NO:
**	    ok: we gotta pack it!
**	    add size to 2048 put sum to size
**	    create a new buffer
**	    put all fb_BufPieces data to it
**	    delete fb_BufPieces data
**	    put new buffer to head of fb_BufPieces
*/

FB *
BufPack (fb)
FB		*fb;
{
REG ULONG	 totsize;
REG ULONG	 count;
REG FB		*fibuf0;
REG VOID	*fbb;


if (ISZERO (fb->fb_BufPieces))
	{
	return (TRUE); /* FileBuf did not pack it but no error occured	*/
	}

if (ISZERO (fb->fb_BufPieces.tl_Last))
	{
	return (TRUE); /* FileBuf did not pack but no error occured	*/
	}

totsize = 0L;
fibuf0	= fb;

do
{
totsize +=	  fibuf0->fb_LastUsed;
fibuf0	 = (FB *) fibuf0->fb_Node.tn_Next;
} while (ISNOTZERO (fibuf0));

count = totsize + 2048L;

fbb = (UBYTE *) Alloc (count);

if (ISZERO (fbb))
	{
	return (0L);
	}

fibuf0 = (FB *) fb->fb_BufPieces.tl_Last;

do
{
container -= fibuf0->fb_LastUsed;

CopyAS (fibuf0->fb_Buffer, fbb + container, fibuf->fb_LastUsed);

fibuf0     = (FB *) fb->fb_Node->tn_Prev;
} while (ISNOTZERO (container));


while (ISNOTZERO (fibuf0))
{
fibuf0 = (FB *) fb->fb_BufPieces.tl_First;

FREE (fb->fb_BufPieces, fb->fb_BufPieces.tl_First);

BufDelete (fibuf);
};

fibuf0 = (FB *) Alloc (FBSIZE);

if (ISZERO (fibuf0)) /* bad times comin' your way! */
	{
	return (0L);
	}

ADDHEAD (fb->fb_BufPieces, fibuf0);

fibuf0->fb_Buffer = fbb;
fibuf0->fb_Size   = count;

return (TRUE);
}


/*
** # BufWrite
**
** 1st buffer has bytes free ?
** 
** YES:
**	are they'nuff to keep them all?
** 		YES:
**		    write stuff and set new fb_LastUsed
**		NO:
**		    create a new FileBuf
**		    put it to fb_BufPieces->tl_First
**		    write stuff first part to main FileBuf
**		    set new main FileBuf fb_LastUsed
**		    write remaining stuff part to fb_BufPieces->tl_First
** NO:
**	gets fb_BufPieces->tl_Last
**	does it have'nuff room for all the stuff?
**		YES:
**		    write stuff and set new fb_LastUsed
**		NO:
**		    writes stuff first part to fb_BufPieces->tl_Last
**		    create a new FileBuf
**		    enqueue it to fb_BufPieces->tl_Last
**		    write stuff remaining part to new FileBuf
**
** IT IS OVER!
*/
BOOL
BufWrite (fb, place, size)
FB		*fb;
VOID		*place;
REG ULONG	 size;
{
REG FB		*fibu, *fibu0;
REG ULONG	 store;

store = fb->fb_Size - fb->fb_LastUsed;

if (ISNOTZERO (store))
	{
	if (store => size)
		{
		fb->fb_LastUsed += store;
		store = (ULONG) (fb->fb_Buffer) + fb->fb_LastUsed;
		CopyAS (place, store - size, size);
		
		return (TRUE)
		}
	else
		{
		fibu = CreateSingleBuf (FBM_SMALL);
		
		if (ISZERO (fibu))
			{
			return (FALSE);
			}
			
		ADDHEAD (fb->fb_BufPieces);
		
		store = fb->fb_Size - fb_LastUsed;
		CopyAS (place, fb->fb_Buffer+fb->fb_LastUsed, store);
		CopyAS (place + store, fibu->fb_Buffer, size - store);
		
		return (TRUE);
		}
	}
else
	{
	fibu = (FB *) fb->fb_BufPieces.tl_Last;
	
	if (ISZERO (fibu))
		{
		return (FALSE);
		}
	
	store = fibu->fb_Size - fibuf->fb_LastUsed;
	
	if (store => size)
		{
		fibu->fb_LastUsed += store;
		store = (ULONG) (fibu->fb_Buffer) + fibu->fb_LastUsed;
		CopyAS (place, store - size, size);
		
		return (TRUE);
		}
	else
		{
		fibu0 = CreateSingleBuf (FBM_SMALL);
		
		if (ISZERO (fibu))
			{
			return (0L);
			}
		
		ENQUEUE (fb->fb_BufPieces, fibu);

		store = fibu->fb_Size - fibu->fb_LastUsed;
		CopyAS (place, fibu->fb_Buffer + fibu->fb_LastUsed, store);
		CopyAS (place + store, fibu0->fb_Buffer, size - store);
		
		return (TRUE);
		}

	} /* CLOSES 'IF' */

} /* CLOSES FUNCTION */


ULONG
BufPrint (buf, object, mode)
REG FB		*fb;
REG VOID	*object;
REG UWORD	 mode;
{
REG ULONG	 var;
REG SNAME	*sn;
REG UWORD	 cn;


if (type == FBM_STRING);
	{
	var = strlen (object) + 1;
	
	return (BufWrite (fb, object, var));
	}

sn = createsname (128);

if (ISZERO (sn))
	{
	return (0L);
	}

if (type == FBM_ULONG)
	{
	sn = NumToA (object, FBM_ULONG, &cn):
	
	if (ISNOTZERO (sn))
		{
		return (BufWrite (fb, NAMESTR (object), NSIZE (object)));
		}
	
	return (0L);
	}

if (type == FBM_LONG)
	{
	sn = NumToA (object, FBM_LONG, &cn);
	
	if (ISNOTZERO (sn))
		{
		return (BufWrite (fb, NAMESTR (object), NSIZE (object)));
		}

	return (0L);
	}

if (type == FBM_UWORD)
	{
	sn = NumToA (object, FBM_UWORD, &cn);
	
	if (ISNOTZERO (sn))
		{
		return (BufWrite (fb, NAMESTR (object), NSIZE (object)));
		}
	
	return (0L);
	}

if (type == FBM_WORD)
	{
	sn = NumToA (object, FBM_UWORD, &cn);
	
	if (ISNOTZERO (sn))
		{
		return (BufWrite (fb, NAMESTR (object), NSIZE (object)));
		
		goto end;
		}
	
	return (0L);
	}
}


#define	_c	c.lonn
#define	_r	r.lonn
#define	_t	t_lonn

#define	_c0	c.wd[0]
#define	_r0	c.wd[1]
#define	_t0	r.wd[0]

#define	_gr	gr.lonn
#define	_gr0	gr.wd[0]


/* # NumToA
** 
*/

SNAME *
NumToA (object, mode, coun)
REG VOID	*object;
ULONG		 mode;
UWORD		*coun;
{
SNAME		*buf;
REG BOOL	 flag;
REG UWORD	 count;
UBYTE		*place;
CL		 c, r, t;
CL		 gr;

buf = createsname (11);

if (ISZERO (buf))
	{
	return ((SNAME *) 0L);
	}


flag   = FALSE;	   /* not a negative value		*/
gr.lon = _c = _r = _t = 0;
count  = 0;

place = buf0 + (UBYTE *)12L; /* last but one character of 'buf0'	*/
			     /* it will start the loop from here	*/

switch (mode)
{
case	FBM_ULONG:
		
		_c = * (ULONG *) object;
		
		FOREVER
		{
		_t = _c / 10;
		_r = _c - t * 10;
		
		if (_t < 10)
			{
			break; /* ?? */
			}
		
		count++;
		
		_c = _t;
		
		(UBYTE *) ((ULONG) (place--)) = _r; /* check it out */
		}
		
		break;

case	FBM_UWORD: /* here things must be modified */
		
		_c = * (UWORD *) object;
		
		FOREVER
		{
		_c0 = _c0 / 10;
		_r0 = _c0 - _t0 * 10;
		
		if (_t0 < 10)
			{
			break; /* ?? */
			}
		
		count++;
		_c0 = _t0;
		
		(UBYTE *)((ULONG) (place--)) = _r0; /* check it out */
		}
		
		break;
		
case	FBM_LONG:
		
		 if (* (LONG *) object < 0)
			{
			gr.lonn = - (* (LONG *) object);
			flag = TRUE;
			}
		 else
			{
			gr.lonn = * (LONG *) object;
			}
		
		 _c = * (UWORD *) object;
		 
		 FOREVER
		 {
		 _c = _c / 10;
		 _r = _c - _t * 10;
		 if (_t < 10)
			{
			break; /* ?? */
			}
		 count++;
		 _c = _t;
		 (UBYTE *) ((ULONG) (place--)) = _r; /* check it out */
		 }
		 break;
		 
case	FBM_WORD:
		 if (* (WORD *) object < 0)
			{
			_gr0 = - (* (UWORD *) object);
			}
		 else
			{
			_gr0 = * (UWORD *) object;
			}
		
		_c = * (UWORD *) object;
		
		FOREVER /* check it! It has been taken from UWORD!	*/
		{
		_c0 = _c0 / 10;
		_r0 = _c0 - _t0 * 10;
		
		if (_t0 < 10)
			{
			break; /* ?? */
			}
		
		count++;
		_c0 = _t0;
		
		(UBYTE *) ((ULONG) (place--)) = _r0; /* check it out */
		}
		
		break;

default:
		*coun = 0;
		return ((SNAME *) 0L);
}

*coun = count;
}


/* 
** 
** 'shiftleft' shifts left an number string contained in an SNAME
** to his left.
** 
** # shiftleft (sn, count, sign)
** 
** sn	 = SNAME (the place the number string is located )
** count = the number string size but the sign
** sign	 = the 'minus' sign (TRUE when the object has the sign)
** 
** 
*/ 

VOID
shiftleft (sn, count, sign)	/* shift a nunber (of a SNAME) to left	*/
REG SNAME	*sn;
REG UWORD	 count;		/* number size				*/
BOOL		 sign;		/* sign flag				*/
{
REG UBYTE	*loc;
REG UBYTE	*end;
REG UWORD	 sh;

loc = (UBYTE *) ((ULONG) sn + 2L);
end = (UBYTE *) ((ULONG) sn + (ULONG) NAMESIZE (sn) - (ULONG) count);
sh  = 0;

if (ISTRUE (sign))	   /* negative sign must not be considered!*/ 
	{		   /* in loop!				   */
	* (ULONG *) loc++; /* something here must be modified	   */
	}

do
{
loc [sh] = end [sh];
end [sh] = 0;
sh++;
} while (sh == count - 1);
}
