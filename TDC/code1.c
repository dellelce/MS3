/* tony dee © 1992
** 
** secondary coding file
** 
*/ 

#define CODE1_C

#include <code.h>
#ifndef WSYSTEM_H
#include <wsystem.h>
#endif
#ifndef TONYEXTEND_H
#include <tonyextend.h>
#endif
#include <ms3fn.h>


/* %%
** createcoden
** createmove
** initregs
** findcall
** newcall
** 
** 
** 
*/ 


/* # createcoden 
** 
*/ 

CODEN *
createcoden (pmap, wfile)
PMAP		*pmap;
UBYTE		*wfile;
{
REG CODEN	*coden;
REG RLIST	*rlist;

coden = (CODEN *) Alloc (CESIZE);

if (ISZERO (coden))
	{
	return (0);
	}

coden->ProgramFile	=	wfile;
coden->TraslatePmap	=	pmap;

/* 
** now creates replacement list
** 
*/ 

rlist = (RLIST *) Alloc (RLSIZE);

if (ISZERO (rlist))
	{
	return (0);
	}

rlist->rl_Tags = RLITEMS;
rlist->rl_List = Alloc (RTSIZE * RLITEMS);

if (ISZERO (rlist->rl_List))
	{
	FreeMem (rlist, RLSIZE);
	return (0);
	}

return (rlist);
}


/* # createmove 
** 
*/ 

createmove (gbunch, var1, var2, coden)
GBUNCH		*gbunch;
VAR		*var1;
VAR		*var2;
CODEN		*code;
{
$
}


/* # initregs 
** 
*/ 

VOID
$ initregs (ce)
CODEN		*ce;
{
REG UWORD	 regcount;
REG UWORD	 view;

regcount = ce->regcount;
view	 = 0;

do
{
regs [view] = $RS_FREE;
view++;
} (view != regcount-1);
}


/* # makecode
** 
** 
*/ 

/* makecode-reserved macros
** 
*/ 

#define	MC_SWAP(x,y)	(store = x; x = y; y = store)
#define	MC_READY_PMAP	_any_ptr = (VOID *) pmap_store;

#define	_pmap		((PMAP *) _any_ptr)

BOOL
makecode (group)
GROUP		*group;
{
REG VOID	 _any_ptr;	/* all registers used		*/
REG VOID	 _any_ptr0;
REG ULONG	 _any_data;
REG ULONG	 _any_data0;
REG ULONG	 _any_data1;
REG ULONG	 _any_data3;
REG ULONG	 _any_data4;
REG ULONG	 _any_data5;
REG ULONG	 _any_data6;
ULONG		 store;
PMAP		*pmap_store;
ACTION		*action_store;
ULONG		*errptr;

errptr = &group->ghandle.lasterror;

_pmap = group->pmap;

pmap_store = _pmap;

if (ISZERO (_pmap->Pblocks [BT_STARTER]))
	{
	*errptr = EN_NOSTARTER;
	goto error;
	}


/* yet can't see the body!!
** 
** 
*/ 


error:;
badreturn:;
return (FALSE);

goodret:;
end:;
return (TRUE);
}


/* # findcall
** 
** I did a great job with this....but will it be used????
** 
*/ 

BOOL
findcall (group, cname)
REG GROUP	*group;
UBYTE		*cname;
{
REG VOID	*ptr0;
REG UBYTE	*q_cname;	/* it'll go to a DATA reg, but we don't care! */
REG UWORD	 bxk0;
REG UWORD	 bxk1;
CBOX		*cbox;		/* cbox store -- think about it	*/

q_cname = cname;
ptr0	= (VOID *) ($group->current->ti_Item);

if (ISZERO (((CACTION *) ptr0)->ca_Calls))
	{
	goto error;
	}

ptr0 = ((CACTION *) ptr0)->ca_CallsData;

extendedloop:;

cbox = ptr0;			/* let's put ptr0 (the real CBOX	*/
				/* pointer) to a safe place		*/
bxk1 = 1;
bxk0 = ((CBOX *) ptr0)->cb_BoxCalls;
ptr0 = FIRSTCALL (ptr0);

loop:;

if (ISTRUE (strcmp (q_cname, (((CALL *) ptr0)->call_Name))))
	{
	goto end;
	}
else
	{
	if (bxk1 == bxk0)	/* let's to the next CBOX...		*/
		{
		ptr0 = cbox;
		ptr0 = ((CBOX *) ptr0)->cb_Next;
		
		if (ISZERO (ptr0))
			{
			goto error;
			}
		
		goto extendedloop;
		}
	
	bxk1++;
	
	ptr0 = NEXTCALL (ptr0);
	goto loop;
	}

end:;
return (TRUE);

error:;
return (FALSE);
}


/* # newcall
** 
** 
** 
*/ 


BOOL
newcall (group, titem, cname)
GROUP		*group;
TITEM		*titem;
UBYTE		*cname;
{
REG VOID	*ptr0;
VOID		*item;

ptr0	= titem
item	= ptr0;

if (ISZERO (((CACTION *) ptr0->ca_CallsData)))
	{
	if (ISZERO (((CACTION *) ptr0->ca_CallsData)) = Alloc (STDBOXSIZE))
		{
		goto error;
		}
	
	ptr0	= ((CACTION *) ptr0->ca_CallsData);
	
	putdown:;
	
	((CBOX *) ptr0)->cb_BoxCalls	= STDCALLSNO;
	((CBOX *) ptr0)->cb_UsedCalls	= 1;
	
	ptr0	= FIRSTCALL (ptr0);
	
	goto end;
	}

if ((((CBOX *) ptr0)->cb_UsedCalls) == (((CBOX *) ptr0)->cb_BoxCalls))
	{
	ptr0 = Alloc (STDBOXSIZE);
	
	if (ISZERO (ptr0))
		{
		goto error;
		}
	
	item->cb_Next = ptr0;
	
	goto putdown;
	}

((CBOX *) ptr0)->cb_UsedCalls ++;

ptr0 = (FIRSTCALL (ptr0) + (ptr0 + (((CBOX *) ptr0)->cb_UsedCalls --) 
								* CALLSIZE));

end:;

group->couple.cp_Big = (ULONG) ptr0;

return (TRUE);

error:;
return (FALSE);
}
