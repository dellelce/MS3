/* tony dee © 1992
** 
** used to leave a trace of the givem object
** it will used to have a faster working program
** 
*/ 


#include <trace.h>

/* %% 
** lifetrace
** MakeATBox
** FindTracedVar
** 
** 
*/ 


/* # lifetrace
** 
** creates a full list of all actions, functions & vars 'called'
** in the processmap
** 
** 1- chiamata
** 	1a- può essere un 'azione'
** 	1b- può essere una 'funzione'
** 	1c- può essere una azione 'sconosciuta'
** 
** 2- variabile
** 	2a- una definizione: ULTIME NOTIZIE': non ci importa!!
** 	2b- una variabile senza che ne venga trovata la definizione
** 	2c- una variabile, della quale viene trovata la definizione
** 
** 3- speciale
** 	3a- una etichetta o 'label'
** 
** 
*/ 

#define	_GROUP		((GROUP *) ptr0)
#define	_BLOCK		((BLOCK *) ptr1)
#define	_CURVAR		((UWORD *) ptr0)

#define	_REFRESH_BLOCK	(_BLOCK = block_STORE)
#define	_REFRESH_CURVAR (_CURVAR = curvar_STORE)
#define	_STORE_BLOCK	(block_STORE = _BLOCK)
#define	_STORE_CURVAR	(curvar_STORE = _CURVAR)
#define	_STORE_GROUP	(group = _GROUP)

BOOL
lifetrace (traceargs)
TRCARGS		*traceargs;
{
REG VOID	*ptr0;		/* multi-purpose pointers, the only	*/
REG VOID	*ptr1;		/* ones that will be put in addr regs	*/
REG GROUP	*group;		/* it goes in a DATA reg.		*/
TITEM		*titem;
CALL		*call;		/* what is it for?			*/
BLOCK		*block_STORE;	/* 'storing' variables			*/
UWORD		*curvar_STORE;

ptr0	= traceargs->ta_group;
_STORE_GROUP;
titem	= ((_GROUP)->current->ti_Item;
_BLOCK	= ((_GROUP)->pmap->Pblocks [_Starter];

if ((_BLOCK)->B_ItemsCount == 0)
	{
	goto error;
	}

ptr0	= B_FIRST (_BLOCK);

block_STORE	= ptr1;	/* let's put them away	*/
curvar_STORE	= ptr0;

goto here:;

start:;
nextvar:;

_CURVAR = NEXTVAR (_CURVAR);

here:;

if (_CURVAR == wlast)
	{
	goto end;
	}

if (*_CURVAR == __STOP)	/* met end of item??		*/
	{
	goto end;
	}

switch (_GENTYPE (_CURVAR))
{
case	VBT_CALL:	/* met a call		*/

	if ($_CANTYPE (*_CURVAR)) < %0000100000000000)	/* otherwise a	      */
		{					/* function or undef  */
		if (ISFALSE (addtracefunct (traceargs, _CURVAR)))
			{
			goto error;
			}
		else
			{
			goto nextvar;
			}
		}
	
	
	/* 
	** WARNING: 'findcall'
	** 	    and to 'newcall' just do not exist...
	** 	    think at them
	** 	    
	** 	    next routine is made chiefly to show
	** 	    the way it should be..
	** 
	** 
	*/ 
	
	
	_CURVAR += 2;	/* let's skip header			*/
	
	_STORE_CURVAR;	/* we can do anything we like with ptr0	*/
	
	ptr0 = WORKSTRING (wpmap, * (UWORD *) ptr0);
	
	if (ISFALSE (findcall (group, ptr0)))
		{
		if (ISFALSE (newcall (group, ptr0)))
			{
			goto error;
			}
		
		call = (CALL *) ((GROUP *) group)->couple.cp_Big;
		
		
		$
		}
	
	
	$	/* <- <- something is missing		*/
	
	
	goto nextvar;
	
case	VBT_VARDEF:
	
	traceargs->ta_vardefs ++;
	goto nextvar;
	
case	VBT_VARUSE:
	
	
	goto nextvar;
	

case	VBT_SPECIAL:
	
	if ($ISALABEL(*_CURVAR))
		{
		$		/* that's a label			*/
		}
	else
		{
		$		/* it must be an unknown object:	*/
		}		/* alas an object 'not already defined'	*/

	goto nextvar;

} /* 'switch'	*/


end:;
return (TRUE);

error:;
return (FALSE);
}


/* # MakeATBox
** 
** 
*/ 


ATBOX *
MakeATBox (chain, boxno)
REG TLIST	*chain;
REG UWORD	 boxno;
{
REG ATBOX	*abox;

abox = (ATBOX *) FastAlloc (ATBOXSIZE + ATSIZE * boxno);

if (ISZERO (abox))
	{
	return ((ATBOX *) 0L);
	}

ENQUEUE (chain, (TNODE *) abox);

abox->atb_used = 0;
abox->atb_acts = boxno;

return (atbox);
}


/* # FindTraceVar
** 
** what is left in couple.cp_Big: (if function returning FALSE)
** 
** 0xFFFFFFFFL	no variable in list...
** 0x00000000L	var not found
** 
*/ 

BOOL
FindTraceVar (targs, var)
TRCARGS		*targs;
UWORD		*var;
{
REG TVV		*tracevar;
REG WPTR	 varname;
REG GROUP	*group;
TVH		*tvh;

varname = var [1];
group	= targs->ta_group;
tvh	= targs->ta_tvh;

if (ISTHEREANYVAR (tvh))
	{
	tracevar = TVH_FIRST (tvh);
	
	do
	{
	if (TV_NAME (tracevar) == varname)	/* variable met		*/
		{
		group->couple.cp_Big = (ULONG) tracevar;
		
		goto end;
		}
	
	tracevar = TVV_NEXT (tracevar);
	} while (tracevar != 0);
	
	group->couple.cp_Big = (ULONG) 0L;
	goto error;
	}
else
	{
	group->couple.cp_Big = (ULONG) -1L
	
	goto error;
	}

end:;
return (TRUE);

novar:;
notfound:;
error:;
return (FALSE);
}
