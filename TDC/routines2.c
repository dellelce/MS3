/********************************************************
 *							*
 *							*
 *		    MS3 Routines File 3			*
 *							*
 *							*
 ********************************************************/


#include <logics.h>
#include <ms3fn.h>

#define	ROUTINES2_C	1


#define	PORT	struct MsgPort

/* # boxfind
*/

BOOL
boxfind (box, name)
STRBOX	*box;
UBYTE	*name;
{
STATIC BYTE	_kas[255] =
{
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
 -1, -1, -1, -1,  0,  1,  2,  3,  4,  5,
  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
 -1, -1, -1, -1, -1, -1,  0,  1,  2,  3,
  4,  5,  6,  7,  8,  9, 10, 11, 12, 13,
 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
 24, 25, -1, -1
};
BYTE		check = _kas[str[0]];
REG STR		str;

if (check == -1)
	{
	return (FALSE);
	}

if (ISZERO (box->count))
	{
	return (FALSE);
	}

str = box->_strings[check];

next:;

if (ISZERO (str))
	{
	return (FALSE);
	}

if (ISZERO (strcmp (str->str, name)))
	{
	return (TRUE);
	}

str = str->next;
goto next;
}

/* # wbound
*/

UWORD
wbound (x, boundhigh, boundlow)
REG UWORD x, boundhigh, boundlow;
{
if (x < boundlow)
	{
	return (boundlow);
	}

if (x > boundhigh)
	{
	return (boundhigh);
	}

return (x);
}


/* # realp
*/

VOID *
realp (block, wp)	/* gets real pointer by wp */
REG BLOCK	*block;
REG WPTR	 wp;
{
REG BLOCK	*bk = block;
REG WPTR	 remaining = 0;

here:;

remaining += bk->B_LastByte - bk->B_OverHead;

if ((bk->B_LastByte - bk->B_OverHead) < wp)
	{
	if (ISZERO (bk->B_Next))
		{
		return (0L);
		}
	bk = bk->B_Next;
	goto here:;
	}
else
	{
	return ((ULONG) (bk + BS + wp - bk->B_OverHead));
	}
}


/* # findinblock
*/

ITEM *
findinblock (bdir, block, itna)
REG BLOCK *bdir;
REG PMAP  *pmap;
REG UBYTE *itna;
{
REG ITEM  *item;
REG UWORD  count;
REG UWORD  count0;

if ( bdir->BlockItemsType != BT_DIRECTORY )
	{
	return (0);
	}

item  = (ITEM *) ((ULONG) bdir + (ULONG) bdir->BlockOverHead + BS);
count = bdir->BlockItemsCount;

FOREVER
{
if (ISZERO (strcmp (itna, BSTR (block, item->di_str))))
	{
	return (item);	/* FOUND	*/
	}

count0++;

if (count0 == count)	/* NOT FOUND	*/
	{
	return (0);
	}

item = (ITEM *) NEXT (item, ITEM);
}
}


/* # joincibox
*/

CIBOX *
joincibox (cb1, cb2, condense)
REG CIBOX	  *cb1;	  /* joins two CIBOXes making a condensed one */
REG CIBOX	  *cb2;
REG BOOL	   condense;
{
REG UWORD	   cnt;
REG ULONG	   siz;
REG CIBOX	  *cib;
REG CALLINFO	  *info0, *info2;


if (ISTRUE (condense))
	{
	cnt = cb1->used + cb2->used;
	}
else
	{
	cnt = cb1->cib;
	}

siz = CIB (cnt);

if (MaxAvail () < siz)
	{
	return (0);
	}

cib = Alloc (siz);

if (ISTRUE (condense))
	{
	cib->callsinfo = cib->used = cnt;
	}
else
	{
	cib->callsinfo = cnt;
	cib->used = cb1->used + cb2->used;
	}

cnt = 1;

info0 = (CALLINFO *) NEXT (cb1, CIBOX);
info1 = (CALLINFO *) NEXT (cib, CIBOX);

hloop:;

if (ISZERO (info0->ci_ObjectType))
	{
	goto next;
	}

CopyCIB (info0, info1);
goto hloop;

next:;

info0 = (CALLINFO *) NEXT (cb2, CIBOX);

hloop1:;

if (ISZERO (info0->ci_ObjectType))
	{
	goto end;
	}

CopyCIB (info0, info1);
goto hloop1;

return (cib);
}


/* # countcalls
** 
** being removed..... 
** 
*/ 

CIBOX *
$countcalls (group, cbx, block, start, end, totcalls)
GROUP		*group;
CIBOX		*cbx;
BLOCK		*block;
UWORD		*start;
UWORD		*end;
REG UWORD	 totcalls;
{
/* 
** 
** A some bureaucratic action
** 
** 
*/ 
}


/* # writevarinfo
** 
** turn it in assembly!
** 
*/ 

BOOL
writevarinfo (block, vi)
BLOCK		*block;
VARINFO		*vi;
{
REG ULONG	size = ((ULONG) vi->vi_wordsused) << 1;

return (blockwrite (block, &vi->_in_vi.vi_word[0], size));
}


/* # getdefinition
** 
** this simple routine traslate the di_def offset pointer of
** the 'DirItem' structure into a real pointer, which really points
** to the declared object.
** 
*/ 

VOID *
getdefinition (pmap, item)	/* will be surely enhanced!!	*/
REG PMAP	*pmap;
REG ITEM	*item;
{
REG USHORT	 wd = item->di_type;
REG BLOCK	*block;

switch (wd)
{
case	IT_OBJECTDEF:
	
	block = pmap->Pblocks[_Objects];
	break;
	
case	IT_ACTION:

	block = pmap->Pblocks[_Actions];
	break;

case	IT_FUNCTION:
	
	block = pmap->Pblocks[_Functions];
	break;

case	IT_STRUCTUREDEF:
	
	block = pmap->Pblocks[_Structures];
	break;
	
case	IT_GLOBALVAR:
	
	block = pmap->Pblocks[_Globals];
	break;
	
case	IT_SOURCE:
	
	return (WORKSTRING (pmap, item->di_str));
	
default:
	
	return (0);
}

return (GET (block, item->di_def));
}
