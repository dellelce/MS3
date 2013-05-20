/* 
** 
** 
** MS3 Routines File 2
** by tony dee
** 
** 
*/ 


#include <logics.h>
#include <ms3fn.h>

/* %%
** createsstack
** delsstack
** addstatus
** getstatus
** loadblock
** findinlib
** getname
** freesname
** putstring
** warn
** countactionvardefs
** findlabel
** toup
** createlabel
** 
** 
*/ 


/* # createsstack
** 
*/ 

SSTACK *
createsstack (cnt) /* TO BE REMADE! (CHECK 'STATUS' DEFINITION) */
USHORT		 cnt;
{
REG ULONG 	 val = (ULONG) cnt * (ULONG) sizeof (WPTR);
REG SSTACK	*stk; 
REG UWORD	 cnt0;

stk = Alloc (SSTSIZE);

if (ISZERO (stk))
	{
	return (0);
	}

if (MaxAvail () < val * (STYPES+1))
	{
	Free (stk, SSTSIZE);
	return (0);
	}

for (cnt0 = 0; cnt0++; cnt0 < STYPES++)
{
stk->ss_Buffers[cnt] = (SSTACK *) Alloc (val);
}

stk->ss_Each = cnt;
return (stk);
}


/* # delsstack
** 
** to complete!
** 
** 
*/ 

BOOL
delsstack (sst)
REG SSTACK	*sst;
{
REG ULONG	 size;
SSTACK		*oldsst;

if (ISZERO (sst))
	{
	goto error;
	}

oldsst = sst;

if (ISZERO (sst->ss_Next))
	{
	size = (ULONG) ((sizeof (UWORD)) * (sst->ss_Size--));
	Free (sst->ss_Stack, size);
	Free (sst, SSTSIZE);
	}
else
	{
	$
	}

end:;
return (TRUE);

error:;
return (FALSE);
}


/* # addstatus
** 
** I think it may be change in a macro
** 
*/ 

BOOL
addstatus (ss, val, offset)
SSTACK		*ss;		/* TO BE REMADE! (CHECK 'STATUS' DEFINITION) */
REG STATUS	 val;
WPTR		 offset;
{
REG SSTACK	*sk = ss;

here:;
if (sk->ss_Used[val] == sk->ss_Each)
	{
	if (ISNOTZERO (sk->ss_Next))
		{
		sk = sk->ss_Next;
		goto here;
		}
	
	sk->ss_Next = createsstack (sk->ss_Each);
	
	if (ISZERO (sk->ss_Next))
		{
		return (FALSE);
		}
	}

sk->ss_Used [val]++;
sk->ss_Buffers [val][sk->ss_Used[val]] = offset;
sk->ss_LastOffset [val] = offset;

return (TRUE);
}


/* # getstatus
*/

UWORD
getstatus (sst, type)
REG SSTACK	*sst;
REG UWORD	 type;
{
return ((sst->ss_Buffers [type])[sst->ss_LastOffset[type]);
}


/* # loadblock
** 
*/ 

BLOCK *
loadblock (fname, bn)
REG UBYTE	*fname;
REG UWORD	 dn;
{
REG PMAP	*pmap;
REG ULONG	 start;
REG ULONG	 size;
REG FH		*file;
REG BLOCK	*block;
REG UWORD	 count;

if ((bn > _LAST) _OR_ (ISZERO (fname)))
	{
	return (0);
	}

file = Open (fname, MODE_OLDFILE);

if (ISZERO (file))
	{
	Free (pmap, PMAPSIZE);
	return (0);
	}

pmap = (PMAP *) Alloc (PMSIZE);

if (ISZERO (pmap))
	{
	return (0);
	}

count = 0;

if ((Read (file, pmap, PMSIZE)) < PMSIZE)
	{
	goto error;
	}

start = PMSIZE + pm->PBlocks[dn];

do
{
size += pm->Pblocks [count];
count++;
} while (count == (bn++));

Seek (file, start, OFFSET_BEGINNING);

block = (BLOCK *) Alloc (size);

if (ISZERO (block))
	{
	goto error;
	}

Read (file, block, size);

Free (pmap, PNSIZE);
Close (file);
return (block);

error:;

if (ISNOTZERO (pmap)) 
	{
	Free (pmap, PMSIZE);
	}

if (ISNOTZERO (file))
	{
	Close (file);
	}

return (0);
}


/* # getname
** 
** built as overhead to
** 'getnametype'
** 
*/ 

BOOL
getname (group)
REG GROUP	*group;
{
hgetname (group->fh, group->sna);

if (ISZERO (SNZERO (group->sna)))
	{
	return (FALSE);
	}

getnametype (group->ghandle, group->pm, group->sna, group->name);

return (TRUE);
}


/* # freesname
** 
** think well about it...
** 
*/ 

VOID
$ freesname (sna)
REG SNAME	*sna;
{
Free (sna, SNAME + (ULONG) sna->sn_Size);
}


/* # putstring
** 
*/ 

BOOL
putstring (group, str, type)
REG GROUP	*group;
UBYTE		*str;
UBYTE		 type;
{
REG UBYTE	 *room;
REG ULONG	  size = (UL)_BUILTIN_strlen (str)+1;
REG BLOCK	 *block = group->pm->Pblocks[(UWORD) type];

group->couple->cp_Small = lastusedbyte (block);
room = makeroom (block, size));

if (ISZERO (room))
	{
	ghandle->lasterror = EN_NOMEMORY;
	return (FALSE);
	}

CopyMemQuick (str, room, size);
return (TRUE);
}


/* # warn
** 
*/ 

VOID
warn (ghandle, wn, str)		/* to be modified	*/
REG GHANDLE	*ghandle;
REG ULONG	 wn;
REG UBYTE	*str;
{
REG FB		*fb;

fb = CreateSingleBuf (FBM_VERYSMALL);

if (ISZERO (fb))
	{
	return;
	}

if (wn < WARN_LASTSTANDARD+1)
	{
	switch (wn)
	{
	case	WARN_NUMBERLESS:
		
		BufPrint (fb, str, FBS_STRING);
		goto end;

	case	WARN_SHORTMEMPORY:
		
		BufPrint (fb, "WARNING: there are only ", FBM_STRING);
		BufPrint (fb, (ULONG) MaxAvail () >> 10, FBM_ULONG);
		BufPrint (fb, " kilobytes.\n", FBM_STRING);
		goto end;
	}
	}

BufPrint (fb, "WARNING:: ", FBM_STRING);
BufPrint (fb, wn, FBM_ULONG);
BufPrint (fb, "::", FBM_STRING);
BufPrint (fb, str, FBM_STRING);
BufPrint (fb, "\n", FBM_STRING);

BufSave (0L, fb);	/* 0 stands for 'let's save it to stdio		*/
BufDelete (fb);

return;
}


/* # countactionvardefs
** 
** BEING REMOVED (a some bureaucratic action....)
** 
** 
*/ 

BOOL
countactionvardefs (group, actname, atype)
REG GROUP	*group;
UBYTE		*actname;
UWORD		 atype;
{
/* 
** 
** started removal operation....
** 
** 
*/ 
}


/* # toup
** 
** 
*/ 

VOID
toup (str)
REG UBYTE	*str;
{
REG UWORD	 cnt = 0;
STATIC UBYTE	_kars [255] =
{
  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
 10, 11, 12, 13, 14, 15, 16, 17, 19, 20,
 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
 51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
 61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
 81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
 91, 92, 93, 94, 95, 96, 65, 66, 67, 68,
 69, 70, 71, 72, 73, 74, 75, 76, 77, 78,
 79, 80, 81, 82, 83, 84, 85, 86, 87, 88,
 89, 90,126, 127
};

while (str[cnt])
{
if (str [cnt] < 128)
	{
	str [cnt] = kars [str [cnt]];
	}
};
}


/* # createlabel
**  
** 
*/ 

LABEL	*
$ createlabel (group, item, name)
GROUP		*group;	/*						*/
TITEM		*item;	/*						*/
UBYTE		*name;	/* the label name				*/
{
LABEL		*lab;	/*						*/
TLIST		*tl;	/* this arg will be surely removed		*/
REG VOID	*p0;	/*						*/
REG VOID	*p1;	/*						*/

tl = &item->ghandle->locals;

p0 = (LABEL *) Alloc (CLSIZE);

if (ISZERO (p0))
	{
	group->ghandle->lasterror = EN_NOMEMORY;
	return ((PTR) 0L);
	}

p1 = item;

((LABEL *) p0)->cl_Name		= name;
((LABEL *) p0)->cl_LabelID	= ((TITEM *) p1)->ti_LastLabIDUsed;

((TITEM *) p1)->ti_LastLabIDUsed++;

((LABEL *) p0)->cl_LabelOffset = ((TITEM *) p1)->ti_CurOffset;

p1 = tl;

ENQUEUE (((TLIST *) p1), lab);

return (lab);
}
