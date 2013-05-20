/* tony dee © 1992
** 
** variables handling routines (formerly on routines.c)
** 
*/ 

#include <wsystem.h>
#include <blocks.h>
#include <variables.h>
#include <tonylists.h>
#include <logics.h>


/* %%
** addvarl
** resetvlist
** findindir
** findinvlist
** 
** 
*/ 


/* # addvarl
** 
** give yet another look at it...
** 
*/ 

VNODE *
addvarl (group, type, var, offset)
GROUP		*group;
ULONG		 type;
REG VAR		*var;
WPTR		 offset;
{
REG VLIST	*list;
REG VNODE	*no;
REG COUNT	 count;
GHANDLE		*ghandle;

ghandle = &group->ghandle;	/* ...		*/

if (type == VLT_GLOBAL)
	{
	list = ghandle->globals;
	VLN_TYPE (no) = TRUE;
	}
else
	{
	if (type == VLT_LOCAL)
		{
		list = ghandle->locals;
		VLN_TYPE (no) = FALSE;
		}
	else
		{
		goto error;
		}
	}

if (VL_USED (list) < VL_ROOM (list))
	{
	count = 0;
	no = VL_FIRST (list);
	
	loop:;
	
	count += 1;
	
	if (count == (VL_USED (list) + 1))
		{
		goto here;	/* got a free seat!!		*/
		}
	else
		{
		count++;
		
		no = VLN_NEXT (no);
		goto loop;
		}
	}
else
	{
	VL_ROOM (list) ++;
	VL_USED (list) ++;
	
	no = (VNODE *) Alloc (VNODESIZE);
	
	if (ISZERO (no))
		{
		goto here;
		}
	
	ENQUEUE (type, no);
	}

here:;

if (ISZERO (no))
	{
	goto error;
	}

no->vln_Variable = var;
no->vln_Id	 = 0;	/* from where do we get this		*/

return (no);
}


/* # resetvlist
** 
** too much time-consuming, to update
** 
*/ 

UWORD
resetvlist (ghandle, li)	/* Frees a variable list	*/
REG GHANDLE	*ghandle;
ULONG		 li;
{
REG VLIST	*vl;
REG VNODE	*vcur;
REG VNODE	*vnext;

if (li == VLT_LOCAL)
	{
	vl = ghandle->globals;
	}
else
	{
	if (li == VLT_GLOBAL)
		{
		vl = ghandle->locals;
		}
	}

vcur = ghandle->vlh_First;

FOREVER
{
vnext = vcur->vln_ArcNode.tn_Next;

if (ISZERO (vcur))
	{
	break;
	}

Free (vcur, VNODESIZE);

vcur = vnext;
};	/* don't know if ok, check it well!	*/
}


/* # findindir
** 
*/ 

ITEM *
findindir (pmap, itna)
REG PMAP	*pmap;
UBYTE		*itna;
{
BLOCK		*bdir = pmap->Pblocks[_Directory];
BLOCK		*block= pmap->Pblocks[_WorkStrings];

if (ISZERO (AND (bdir, block))
	{
	goto error;
	}

return (findinblock (bdir, block, itna));

error:;
return ((ITEM *) 0L);
}


/* # findinvlist
** 
** 
*/ 

VAR *
findinvlist (pm, vl, name)	/* searchs in variable list	*/
PMAP		*pm;
VLIST		*vl;
REG UBYTE	*name;
{
REG BLOCK 	*strb	= pm->Pblocks[_WorkStrings];
REH VNODE	*vn	= vl->vl_List.tl_First;

do
{
if ($ISZERO (strcmp (WORKSTRING (pm, (UWORD) (vn->Variable + 2)), name)))
	{
	return (vn->vln_Variable);
	}

vn = vn->vln_ArcNode;
} while (ISNOTZERO (vn));

return ((VAR *) 0L);
}

/* 
** 
** blocks routine (extended)
** 
** 
*/ 


/* # writevarinfo
** 
** 
*/ 

BOOL
writevarinfo (block, vi)
BLOCK		*block;
REG VARINFO	*vi;
{
REG UWORD	*dt;
REG ULONG	 cnt;
UWORD		*makeroom ();

cnt = (ULONG) vi->vi_wordsused;

if (ISZERO (cnt))
	{
	return (FALSE);
	}

dt  = makeroom (block, cnt);

if (ISZERO (dt))
	{
	return (FALSE);
	}


for (cnt = 0; cnt ++; cnt < vi->vi_wordsused)
{
dt [cnt] = _WORDS (vi, cnt);
}

return (TRUE);
}
