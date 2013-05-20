/********************************************************
 *							*
 *							*
 *		    MS3 Routines File 3			*
 *							*
 *							*
 ********************************************************/

#define	ROUTINES3_C	1

#include <names.h>
#include <ms3fn.h>
#include <structures.h>


/* %%
** getline
** newtitem
** findstructitem
** openworkstruct
** wstrgetitems
** 
** 
*/ 


/* # getline 
** 
** this functions will get traslated
** a complete line from ascii to a
** name box structure
** 
** tony dee latest remark:
** irt is useless and unused
** 
** 
*/ 

NBH *
getline (group, nbh)
GROUP		*group;
NBH		*nbh;
{
REG NBH		*hbn;
REG NAME	*name = group->name;

if (ISZERO (nbh))
	{
	nbh = $createnbh ();
	}
else
	{
	hbn = nbh;
	}

if (ISFALSE (getname (group))
	{
	$error;
	}

}


/* # newtitem
** 
** to update!!
** 
*/

TITEM *
newtitem (group, size, type, block)
GROUP		*group;
ULONG		 size;
UWORD		 type;
BLOCK		*block;
{
REG TITEM	*tit;
REG VOID	*obt;

/* perhaps allocation will be not necessary!!
** 
** 
*/ 

tit = (TITEM *) Alloc (TITSIZE);

if (ISZERO (tit))
	{
	goto nomemory;
	}

tit->ti_Status = $createsstack (STACKSIZE);

if (ISZERO (tit->ti_Status))
	{
	Free (tit, TITSIZE);
	goto nomemory;
	}

obt = makeroom (block, size);

if (ISZERO (obt))
	{
	Free (tit, TITSIZE);
	freesstack (tit->ti_Status);
	goto noroom;
	}

tit->ti_Type		= type;
tit->ti_OwnerBlock	= block;

tit->ti_InitialOffset	= tit->ti_CurOffset = lastusedbyte (blk);
tit->ti_Item		= obt;


tit->ti_Locals = $createvlist (); /* it looks nearly finished	*/


noroom:;
group->ghandle.lasterror = EN_NOROOM;
return (0);

nomemory:;
group->ghandle.lasterror = EN_OUTOFMEMORY;
return (0);

noerror:;
}


/* # findstructitem
** 
*/ 

UBYTE *
findstructitem (wstruct, name)
$ WSTRUCT	*wstruct;
REG UBYTE	*name;
{
REG WSINAME	*ws;
REG WORD	 cnt;

cnt = wstruct->items;

if (ISZERO (cnt))
	{
	return (0);
	}

ws = wstruct->firstitem;

FOREVER
{
if (ISZERO (strcmp (ws->name, name)))
	{
	return (ws->name);
	}

cnt--;

if (ISZERO (cnt))
	{
	return (0);
	}

ws = ws->next;
}
}


/* # openworkstruct
** 
** next 2 functions
** can be joined togheter!
** 
*/

WSTRUCT *
openworkstruct (pmap, name)
PMAP		*pmap;
UBYTE		*name;
{
REG VOID	*_any_ptr;
REG VOID	*_any_ptr0;
REG VOID	*_any_ptr1;
VOID		*finditem ();

/* get structure pmap directory item
*/ 
_any_ptr = finditem (pmap, name);

if (ISZERO (_any_ptr))
	{
	return (0);
	}

/* get structure name
*/ 
_any_ptr1 = WORKSTRING (pmap, ((ITEM *)_any_ptr)->di_str);

if (ISZERO (_any_ptr1))
	{
	return (0);
	}

/* makes room for 'WSTRUCT'
*/ 
_any_ptr0 = (VOID *) Alloc (WSTRUCTSIZE);

if (ISZERO (_any_ptr0))
	{
	return (0);
	}

/* set structure name in 'WSTRUCT'
*/
((WSTRUCT *)_any_ptr0)->structname = _any_ptr1;


/* get structure definition in pmap
*/
_any_ptr1 = BSTRUCTURE (pmap, _any_ptr);

if (ISZERO (_any_ptr1))
	{
	FREEWSTRUCT (_any_ptr0);
	return (0);
	}

/* set structure definition in 'WSTRUCT'
*/
((WSTRUCT *)_any_ptr0)->definition = (STRUCT *) _any_ptr1;

/* set structure items number in 'WSTRUCT'
*/
((WSTRUCT *)_any_ptr0)->items = ((WSTRUCT *)_any_ptr1)->st_Items;


$if (ISNOTZERO (wstrgetitems (_any_ptr0)))
	{
	return (_any_ptr0);
	}
else
	{
	return (0);
	}
}


/* # wstrgetitems
** 
** crea una lista contenente tutti
** gli 'items' della struttura
** 
*/

USHORT
wstrgetitems (wstruct)
REG WSTRUCT	*_wstruct;
{
REG VAR		*vartable;
REG UBYTE	*strwrite;
WSINAME		*_wsi;
UWORD		 items;
UWORD		 count;

items = (ULONG) _wstruct->items;

if (ISZERO (_wsi = MAKEWSI (items)))
	{
	return (0);
	}

INITWSI (_wsi, items);

_wstruct->firstitem = _wsi;

strwrite = (VAR *) NEXT (_wsi, WSINAME); /* DIEs 'wsi' */
vartable = (VOID *) _wstruct + (VOID *) WSTRUCTSIZE;
vartable = (VOID *) (SIZE (* (UWORD *) vartable) + vartable);

makeroom (_wstruct->pmapfather->PBlocks [WorkStrings], (ULONG) _wstruct->items);

count = 1;

repeat:;

*strwrite = VARNAME (vartable);

if (count == items)
	{
	return (count);
	}
else
	{
	count++;
	strwrite = (UBYTE *) NEXT (strwrite, UBYTE *);
	vartable = NEXTVAR (vartable);
	goto repeat;
	}
}
