/* FILE TRASLATION HEART
** creating by tony dee
** file 3
** 
** 
*/ 


#define	TRASLATE2_C

#include <logics.h>
#include <ms3fn.h>
#include <traslate.h>


/* %%
** makestructure
** getmatrix
** getinit
** closetitem
** 
** 
*/ 

/*
** Example of structure:
**
** struct List (1)
** pointer List Next;
** pointer List Prev;
** string  ListName;
** unsigned long Flags;
** List Son;
** close struct;
**
** (1) It is the name of the structure
**     It must an 'UNKNOWN' type name
**	A new item is created containing the name of the
**	Structure.
**
**
*/

/*
** # makestructure (group)
** 
** It will surely changed completly!
** 
** group:: GROUP *
**
*/

BOOL
makestructure (group)
REG GROUP	*group;
{
REG PMAP	*pm = group->pm;
REG GHANDLE	*group->ghandle;
REG UWORD	 type;
REG ULONG	 subtype;
REG NAME	*name = group->name;

STRUCTURE	*stru;
BLOCK		*blk;
WPTR		 structitemoff;
WPTR		 off1;
ITEM		*item;
UWORD		 un;
UWORD		 stats;
UBYTE		*structname;
UWORD		 autocalls;
STRUCTURE	 secstruct;

STATIC VT	vt[] =
{
{VT_BYTE,	 1},
{VT_WORD,	 2},
{VT_LONG,	 4},
{VT_NUMBER,	 4},
{VT_STRING,	 4},
{VT_RANGE,	 2}, /* or 4 bytes */
{VT_BOOL,	 2},
{VT_DOUBLE,	 4},
{VT_FLOAT,	 4}
}

stru = makeroom (blk, SHSIZE);

if (ISZERO (stru))	/* couldn't alloc STRUCTURE header */
	{
	group->ghandle->lasterror = EM_NOMEMORY;
	goto error;
	}

blk	  = pm->Pblocks[_Structure]
un	  = VARSETBASE;
autocalls = 0; 

off1 = lastusebyte (blk);

group->couple->cp_Small = off1;
group->couple->cp_Big   = stru;

if (ISFALSE (getname (group)))
	{
	goto noname;
	}

subtype = name->nd_subtype;
type	= name->nd_type;

if (type != NDT_UNKNOWN) /* needs it not to be a known name!! */
	{
	group->ghandle->lasterror = EM_KNOWNNAME;
	goto error;
	}

item = newitem (group->item);

item->di_type	=  IT_STRUCTUREDEF;
item->di_def	=  off1;	/* here must be completed */


/* gets structure name
** 
*/ 
structname	= NAMESTR (group->sna);


/* sets it in the directory
** 
*/ 
if (ISFALSE (putstring (group, structname, BT_WORKSTRINGS)))
	{
	goto error;
	}

/* sets its offset cp_Smalll
** 
*/ 
item->di_str	=  group->couple->cp_Small;


/* Here on things will surely change
** 
*/ 

FOREVER		/* for all items		*/
{
FOREVER		/* analyzes a single item	*/
{

DOGETNAME

subtype = name->nd_subtype;
type	= name->nd_type;

switch (type)
{
case	NDT_SIMPLEDEF:

if (subtype <= NDS_LSIMPLE) /* SOMETHING HERE SHOULD BE MODIFIED */
	{
	if (GETBIT (stats, STF_SIMPLEDEF) != 1)
		{
		SETBIT (stats, STF_SIMPLEDEF);
		}
	else
		{
		goto syntaxerror;
		}
	
	SETTYPE (un, vt [subtype]->vt_Val1);
	
	goto next;
	}
		
	SETTYPE (un, vt [subtype]->vt_Val);	/* set new item */
	
	stru->st_Items++;
	stru->st_Bytes += vt [subtype]->vt_Size;
	
	break;

case	NDT_CLOSER:

	if (DEF_OK (stats))
		{
		goto end;
		}
	else
		{
		goto syntaxerror;
		}

case	NDT_STRUCTURE:

	structitemoff = name->nd_data;
	
	if (GETBIT (stats, STF_STRUCTURE) == 1)
		{
		goto syntaxerror;
		}
	
	if (ISZERO (strcmp (NAMESTR (group->sna), structname)))
		{
		if (ISZERO (GETBIT (stats, STF_POINTER))
			{
			autocalls++;
			}
		else
			{
			stru->st_SelfCall = TRUE;
			}
		}
	else
		{
		secstruct = STRUCTURE (pm, structitemoff);
		stru->st_Bytes += secstruct->st_Bytes;
		}
	
	stru->st_Items++;
	break;
	
case	NDT_ERROR:
	
	
	goto syntaxerror;

default:
	
} /* close SWITCH */

/* 
** 
*/ 

next:;
} /* end of 'FOREVER' */

syntaxerror:;
syntax:;
couple->ghandle->lasterror = EN_SYNTAX;

error:;
freeblockarea (blk, off1, lastusedbyte (blk) - off1);
return (FALSE);

end:;
struct->st_Bytes += ;
return (TRUE);

} /* end of forever: exits if found 'close struct;'	*/
} /* closes 'makestructure' function			*/


/* # getmatrix
** 
** 
** 
*/ 

BOOL
getmatrix (group, vb, mode)
REG GROUP	*group;
REG VARBUILD	*vb;
UWORD		 mode;
{
REG UWORD	*var;
BLOCK		*block;

block 	= vb->ownerblock;
var	= vb->nameval;

if (ISZERO (var))
	{
	return (FALSE);
	}

switch (mode)
{
case	IM_NUMBERS:
	
	numbers:;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_NUMBER)
		{
		goto syntaxerror;
		}
	
	$	/* <- <- PUT CONSTANT		*/
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto syntaxerror;
		}
	
	if (name->nd_subtype == NDS_COMMA)
		{
		/* $ DO SOMETHING ELSE		*/
		
		goto numbers;
		}
	
	if (name->nd_subtype == NDS_BRAK0CL)
		{
		$	
		}
	
case	IM_ANYWAY:
	
	
	blockstart (block);
	
	if (ISFALSE (getexpression (group, block, &bracket0, 0L, 0)))
		{
		goto error;
		}
	
	blockend (block);
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type = NDT_CLOSER)
		{
		goto end;
		}
	
	if (name->nd_type == NDT_SPECIAL)
		{
		if (name->nd_subtype != NDS_BRAK2CL)
			{
			goto syntaxerror;
			}
		
		}
	
	goto syntaxerror;
	
case	$IM_STRUCTMODE:
	
	
	
}


end:;
return (TRUE);

syntaxerror;
group->ghandle->lasterror = EN_SYNTAX;
goto error;

noname:;
group->ghandle->lasterror = EN_NONAME;

badend:;
error:;
return (FALSE);
}


/* # getinit
** 
** gets initialization data
** 
*/ 

BOOL
getinit (group, init)
REG GROUP	*group;
REG INIT	*init;
{
BLOCK		*block;

block = init->block;

switch (init->mode)
{
case	IM_NUMBERS:
	
	
	goto end;
	
case	IM_STRUCTMODE:
	
	
	goto end;
	
case	IM_ANYWAY:
	
	blockstart (block);
	
	if (ISFALSE (getexpression (group, block, &closer, 0L, $0L)))
		{
		goto error;
		}
	
	blockend (block);
	
	goto end;
}

end:;
return (TRUE);

error:;
return (FALSE);
}


/* # closetitem
** 
** 
*/

BOOL
closetitem (group)
REG GROUP	*group;
{
REG GHANDLE	*ghandle;
REG TITEM	*tit;
REG VOID	*now;

ghandle = group->ghandle;
tit	= ghandle->currentitem;


}
