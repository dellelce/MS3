/* tony dee © 1992
** 
** 
*/ 

#ifndef	 NAMES_H
#include <names.h>
#endif
#ifndef	 CAN_H
#include <can.h>
#endif

/* %%
** findname
** 
*/ 

#define	NAMES1_C		1
#include <ms3fn.h>



/* # findname
** 
** Finds for an ascii 
** name in NameBase
** 
** 5 pointers in registers
** 2 'non-pointing' variables in registers
** 
** 
*/ 

EXTERN UBYTE	intcounters [25];

NAME *				/* to be fixed			*/
findname (nb, name)
REG NAMEBASE	*nb;
UBYTE		*name;
{
REG NAME	*dname;
REG NNODE	*curnode;
REG UBYTE	*_name;
REG NAMEVEC	*nvec;
REG UWORD	 count;
REG UWORD	 reach;

_name = name;

if (ISZERO (nb->nb_GlobCount))
	{
	goto error;
	}

if (ISZERO (nb->nb_NamesInVec))	/* it can't be true!!!		*/
	{
	goto findinlist;
	}

count = (UWORD) (toup (* _name) - 65);
nvec = (* nb->nb_NameVec) [count];	/* may be patched	*/
					/* in the future	*/
if (ISZERO (intcounters [count]))
	{
	goto notfound;
	}

reach = 0;
dname = nvec->nb_NamesVec;

loop:;

if (ISTRUE (strcmp (dname->nd_data, _name)))
	{
	goto foundit;
	}
else
	{
	reach ++;
	
	if (reach = count)
		{
		goto notfound;
		}
	
	dname = (NAME *) NEXT (dname, NAME);
	
	goto loop;
	}

findinlist:;

curnode = (NNODE *) nb->nb_NameList->nlh_Archiver.tl_First;
dname	= curnode->nn_Name;

if ((ISZERO (curnode)) || (ISZERO (dname)))
	{
	goto notfound;
	}

FOREVER /* do it for ever, or at least while you haven't find it!	*/
{
if (TK_SIZE (dname->xn_Name) != strlen (_name))
	{
	goto fn_next;
	}

if (ISFALSE (strcmp ((UBYTE *) curnode->xn_NameStr, _name)))
	{
	goto foundit;
	}

fn_next:;

curnode = curnode->nn_ArcNode.tn_Next;

if (ISZERO (curnode))
	{
	goto notfound;
	}

dname	= curnode->nn_Name;
}

error:;
notfound:;
return (0L);

foundit:;
return (dname);
}
