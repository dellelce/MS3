/* tony dee © 1992
** 
** routines used for
** the compiler coding part
** 
** 
*/ 

#include <trace.h>
#include <ms3fn.h>

/* %%
** branchat
** createrlist
** dellab
** bcountused
** writegbunch
** makecode
** createhunk
** $ envar
** 
** 
*/ 


/* 
** 
** action structure: (NORMAL)
** 
** | 
** | 
** | LOCAL STATIC DATA
** | 
** | 
**  |
**  |
**  | ACTION CODE
**  |
**  |
** 
** 
** 'STARTER' action structure:
** 
** | 
** | 
** | STARTER CODE
** | 
** | 
**  |
**  |
**  | STARTER LOCAL STATIC DATA
**  |
**  |
** 
** 
** code file structure:
** 
** | 
** | 
** | STARTER
** |
** |
**  |
**  |
**  | GLOBAL STATIC DATA
**  |
**  |
**   |
**   |
**   | PROGRAM ACTIONS
**   |
**   |
** 
** 
** 
** 
** 
*/ 

/* # makeatbc
** 
** 
*/ 

ATBC *
makeatbc (count)
UWORD		 count;
{
REG ATBC	*ab;

ab = (ATBC *) Alloc (ATBCSIZE * (ULONG) count);

if (ISZERO (ab))
	{
	goto error;
	}

/* make body year	*/

end:;
return (TRUE);

error:;
return (FALSE);
}


/* # branchat
** 
*/

VOID
branchat (bunch, type, offs)
REG BUNCH	*bunch;
REG UBYTE	 type;
REG WPTR	 offs;
{
if ((((WORD) offs) > -129) && (((WORD) offs) < 128))
	{
	bunch->b_cnum = 1;
	bunch->b_code [0] = 0x6000 | (type << 8) + (UWORD) ((UBYTE) offs);
	goto end;
	}

bunch->b_cnum	  = 2;
bunch->b_code [0] = 0x6000 | (type << 8);
bunch->b_code [1] = offs;

end:;
}


/* # createrlist
** 
** creates replacement list
** 
*/ 

WRLIST *
createrlist (count)
REG UWORD	 count;
{
REG WRLIST	*rlist;
REG VOID	*list;

rlist = (RLIST *) Alloc (RLSIZE);

if (ISZERO (rlist))
	{
	return (0);
	}

list  = Alloc ((ULONG) count);

if (ISZERO (list))
	{
	Free (rlist, RLSIZE);
	return (0);
	}

rlist->rl_Tags = count;
rlist->rl_List = rlist;

return (rlist);
}


/* # dellab
** 
** 
*/ 

VOID
dellab (lab)
REG LABEL	*lab;
{
if (ISNOTZERO (lab->cl_Hits))
	{
	Free (lab->cl_HitsBuffer, HITSIZE * ((ULONG) lab->cl_Hits));
	}

Free (lab, CLSIZE);
}


/* # bcountused
** 
** I think it is just a time-consuming, space-consuming,
** non-smart routine
** 
*/ 

USHORT
bcountused (gb)
REG GBUNCH	*gb;
{
REG BUNCH	*b;
REG USHORT	 k;
REG USHORT	 n;

k	 = gb->bunches;
n	 = 1;
gb->used = 0;

b = (BUNCH *) NEXT (gb, GBUNCH);

do
{
gb->used += b->b_cnum;
b = (BUNCH *) NEXT (b, BUNCH);
n++;
} while (n > k);

return (n);
}


/* # writegbunch 
** 
** I would turn this routine in assembly
** 
*/ 

UWORD
writegbunch (hx, bh)
HC		*hx;
REG BUNCH	*bh;
{
REG HUNK	*kk;
REG UWORD	 words;
REG UWORD	*write;
REG HC		*hunkc;

hunk  = hx;
words = bh->b_cnum;

kk = (HUNK *) bh->hc_Hunks.tl_Last;

if (ISZERO (kk))
	{
	kk = (HUNK *) bh->hc_Hunks.tl_First;
	
	if (ISZERO (kk))
		{
		kk = createhunk (bh, STDHUNKROOM, 0);
		
		if (ISZERO (kk))
			{
			goto error;
			}
		
		bh->hc_Hunks.tl_First = kk;
		
		$	/* <- <- increase ..hc_TotAlloc		*/
		
		goto writedown;
		}
	
	goto error;
	}
else
	{
	if ((kk->h_AllocatedWords - kk->h_LastUsedWord) < count)
		{				/* create another hunk	*/
		kk = createhunk (bh, $512, 0);
		
		if (ISZERO (kk))
			{
			goto error;
			}
		
		$	/* <- <- increase ..hc_TotAlloc		*/
		
		ENQUEUE (hunkc->hc_Hunks, kk)
		
		goto writedown;
		}
	
	}

writedown:;

hunkc->hc_TotCode += ((ULONG) count) * 2L;

write   = kk + HUNKSIZE + (ULONG) ((kk->h_LastUsedWord * 2) + 2);
count	= 0;

do
{
write [count] = bh->b_code [count];
} while ((count ++) < count);

end:;
return (count);

error:;
return (0);
}


/* 
** # makecode
** 
*/ 

#define	reg0		ap0
#define	reg1		ap1
#define	

BOOL
makecode (group)
GROUP		*group;
{
REG PTR		*ap0; /* A2 register					*/
REG PTR		*ap1; /* A3 reg. the only addr reg available for vars.	*/
REG PMAP	*wpmap;
CALLBOX		*box;
BLOCK		*workblock;
ACTION		*curact;
ULONG		*error;
/* local block data
** 
*/ 
PROGRAM		 prog;
TRACEARGS	 targs;
ATBC		 atbc;


/* initialize data
** 
** 
*/ 

MemClear (&prog, PROGSIZE);
MemClear (&targs, TARGSSIZE);

ap0			=	 group;
ap1			=	 ((GROUP *) ap0)->pmap;
wpmap			=	 ap1;
error			=	&((GROUP *) ap0)->ghandle.lasterror;
prog.prog_Name  	=	 name;	/* that's the name	*/
prog.prog_SaveName	=	 name;
prog.prog_ProgramMap	=	 ap1;

$makeatbc (&atbc);

targs.ta_group = group;
targs.ta_group = &atbc;

ap1 = ((PMAP *) ap1)->PBlocks[_Starter];

if (ISZERO (ap1))
	{
	*error = EN_NOSTARTER;
	goto error;
	}

workblock = ap1;


/* let's trace the starter
** 
*/ 

if (ISFALSE (lifetrace (&targs)))
	{
	goto error;
	}

/* let's code the starter
** 
** docodeit .... it has jumped right now on my mind (~ 21:15, Oct 17, 1992)
** 		 it should make real code of anction
** 
*/ 

if (ISFALSE ($docodeit (&targs, &prog)))
	{
	goto error;
	}

/* let's trace the first action
** 
** 
*/ 

targs.ta_def = wpmap->PBlocks[$_Actions];
targs.ta_wstart = targs.ta_def + ACTSIZE;

if (((ACTION *) targs.ta_def)->ac_Type != AT_NORMAL)	/* not to be traced */
	{
	
	}

if (ISFALSE (lifetrace (&targs)))
	{
	goto error;
	}

/* let's code action
** 
** 
*/ 

if (ISFALSE ($docodeit (&targs, &program)))
	{
	goto error;
	}

targs.ta_wstart += 2;

if (*targs.ta_wstart == $$__STOPLIST)	/* that's should be end of all!	*/
	{
	goto end;
	}

badend:;
error:;
return (FALSE);

end:;
return (TRUE);
}


/* # createhunk
** 
** 
*/ 

HUNK *
createhunk (hx, words, model)
REG HC		*hunkc;
REG UWORD	 words;
REG UWORD	 model;
{
REG HUNK	*hunk;

if (ISZERO (hunkc))
	{
	hunk = (HUNK *) Alloc (HUNKSIZE + (2L * (ULONG) words));
	
	if (ISZERO (hunk))
		{
		goto error;
		}
	
	hunk->h_Model = model;
	
	goto end;
	}
else
	{						 /* hope it to work!! */
	hunk = (HUNK *) Alloc (HUNKSIZE + (2L * ((ULONG) (HUNK *)
		(hunkc->hc_Hunks.tl_First)->AllocteWords)));
	
	if (ISZERO (hunk))
		{
		goto error;
		}
	
	hunk->h_Model = ((HUNK *) (hunkc->hc_Hunks.tl_First))->Model;
	
	ENQUEUE (hunkc->hc_Hunks, hunk);
	goto end;
	}

end:;
return (hunk);

error:;
return ((HUNK *) 0L);
}


/* # envar
** 
*/ 

MAKEVAR *
$ envar (var)		/* THIS envar () gets a the def from the procmap  */
REG VAR		*var;
{
REG MAKEVAR	*mv;

if (ISZERO (mv = MEW_MAKEVAR ()))
	{
	return ((MAKEVAR *) 0);
	}

mv->mv_Header    = * (UWORD *) var;
mv->mv_NameValue = * (UWORD *) NEXT (var, UWORD);

if (ISZERO (DEF (* (UWORD *) var))) /* use of variable		*/
	{
	
	}
else				   /* definition of variable	*/
	{
	
	}

mv->mv_Header = * (UWORD *) var;
mv->mv_Mode   = MODE (* (UWORD *) var);


end:;
return (mv);

error:;
return ((MAKEVAR *) 0L);
}

/* # FindBlockEnd
** 
** very simple routine (for this release -- 0.00)
** it may simply traslated to assembly
** 
*/ 

VAR *
FindBlockEnd (var)
REG VAR		*var;
{
REG COUNT	 count;

FOREVER
{
if (ISBLOCKEND (var))
	{
	if (ISZERO (count))
		{
		goto end;
		}
	else
		{
		count --;
		goto next;
		}
	}

if (ISBLOCKSTART (x))
	{
	count++;
	}

next:;
}

end:;
return (var);
}

/* # CreateRPNBuf
** 
** 
*/ 

POLISH *
CreateRPNBuf ()
{
REG POLISH	*_p;

_p = MK_POLISH();

if (ISZERO (_p))
	{
	goto error;
	}

P_USED (_p) = 0;
P_ROOM (_p) = STDPOLISHROOM;

return (_p);

error:;
return ((POLISH *) _p);
}


/* # Turn2RPN
** 
** now building. v0.00.
** 
** 
*/ 

BOOL
Turn2RPN (group, var)
GROUP		*group;
VAR		*var;
{
POLISH		*polish;

polish = $ &group->ghandle.polish;


}
