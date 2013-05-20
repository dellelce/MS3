/* 
** 
** processmap management v1.2 -- now updating
** by tony dee 1991/92
** 
*/ 

#define	PROCESS_C	1

/* %%
** savepmap
** loadpmap
** deletepmap
** packpmap
** createpmap
** 
*/ 

#include <logics.h>
#include <ms3fn.h>


/* # savepmap
** 
*/

BOOL
savepmap (name, pm)
UBYTE		*name;
REG PMAP	*pm;
{
REG ULONG	 file;
REG BLOCK	*bl;
REG UBYTE	 count;  /* counter				*/
ULONG 		 dat;	 /*					*/
ULONG		 storer; /* rarily used, but fastens things	*/
PMAP		*pmap;
STATIC FHEAD	 fhead =
{
'TONY',
0x0000,
0x0001,
0x00000000,		/* filled next (file size)		*/
0xc0000000 		/* process map type			*/
};

pmap = (PMAP *) Alloc (PMSIZE);

if (ISZERO (pmap))
	{
	return (0);
	}

/* 
** let's shrink the blocks
** 
*/ 

do
{
bl = pm->Pblocks [count];

pm->Pblocks [count]	=	packblock (pm->Pblocks [count]);

deleteblockchain (bl);
} while (count < _LAST);

count	= 0;
dat	= PMAPSIZE;

do
{
dat += pm->Pblocks [count];

count++;
} while (count < _LAST);

FHD_1STSIZE (fhead) = dat;

file = Open (name, MODE_NEWFILE);

if (ISZERO (file))
	{
	goto error;
	}

/*  
** writes the header
** 
*/ 

dat = Write (file, &fhead, FHEADSIZE);

if (dat < FHEADSIZE)
	{
	goto error;
	}

count = 0;

/* 
** let's set pmap structure 
** 
*/ 

pmap.Library	=	pm.Library;
pmap.Version	=	pm.Version;
pmap.FirstComp	=	pm.FirstComp;

do
{
pmap->Pblocks [count]	=	pm->Pblocks [count]->BlockSize;

count++;
} while (x < _LAST);

if (Write (file, &pmap, PMAPSIZE) > PMAPSIZE)
	{
	goto error:;
	}

count = 0;

/* 
** let's save up
** 
*/ 

do
{
storer = pm->Pblocks [count]->BlockSize;	/* makes things faster	*/

if ((Write (file, pm->Pblocks [count], storer)) < storer)
	{
	goto error;
	}

count++;
} while (x < _LAST);

end:;

Close (file);
return (FALSE);


error:;

if (file != 0L)
	{
	Close (file);
	}

return (FALSE);
}


/* # loadpmap
**  
*/

PMAP *
loadpmap (name)
UBYTE		*name;
{
REG PMAP	*pmap;
REG ULONG	 file;
REG ULONG	 siz;
REG ULONG	 ch;
FHEAD		 fhead;

pmap = (PMAP *) Alloc (PMSIZE);

if (ISZERO (pmap))
	{
	goto byebye;
	}

file = Open (name, MODE_OLDFILE);

if (ISZERO (file))
	{
	goto error;
	}

if ((Read (file, &fhead, FHEADSIZE)) < FHEADSIZE)
	{
	goto error;
	}

if (FHD_MAGIC (fhead) != MAGIC) 
	{
	goto error;
	}

if ((Read (file, pmap, PMSIZE)) < PMSIZE)
	{
	goto error;
	}

ch = 0;

do
{
siz = pmap->Pblocks [ch];

if (ISZERO (pmap->Pblocks [ch] = Alloc (siz)))
	{
	goto error;
	}
	
if ((Read (file, pmap->Pblocks [ch], siz)) < siz)
	{
	goto error;
	}

ch++;
} while (ch < 10);


error:;

if (file != 0L)
	{
	Close (file);
	}

byebye:;
return ((PMAP *) 0L);

end:;

Close (file);
return (pmap);
}


/* # deletepmap
** 
*/ 

VOID
deletepmap (pm)
REG PMAP	*pm;
{
REG UWORD	 c = 0;

do
{
deleteblockchain (pm->Pblocks[c]);
c++;
} while (c < _LAST);

FreeMem (pm, PMSIZE);
}


/* # packpmap
** 
** check out this routine
** 
*/ 

VOID
packpmap (pm)
REG PMAP	*pm;
{
REG PMAP	*pp;
REG UWORD	 c = 0;

do
{
pp = pm->Pblocks[c];
packblock (pp);
deleteblockchain (pp);

c++;
}; /* closes 'do'	*/
}  /* closes 'function	*/


/* # createpmap
** 
*/

PMAP *
createpmap (type)	/* must be updated	*/
ULONG		 type;
{
REG PMAP	*cur;
REG UWORD	 h;
REG UWORD	 cnt;

STATIC UBYTE types [_LAST - 1] =
{
BT_DIRECTORY,		/* directory block			*/
BT_USER,		/*					*/
BT_SPECIAL,
BT_WORKSTRING,
BT_PROGSTRING,
BT_STARTER,
BT_ACTION,
BT_OBJECT,
BT_STRUCTURE,
BT_GLOBAL,
BT_INITIALIZED
BT_FUNCTION
};

ULOG sizes [_LAST - 1] =
{
400 * ITEMSIZE,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0
};

cur = Alloc (PMSIZE);

if (ISZERO (cur))
	{
	goto error;
	}

cnt = 0;

/* 
** Blocks item sizes and types allocation
** 
*/ 

for (h = 0; h++; h <( _LAST) - 1)
{
Pblocks [h]->BlockItemsType = sizes [h];
}

for (h = 0; h++; h <( _LAST) - 1)
{
Pblocks [h]->BlockItemsSize = types [h];
}

cur->Library	=   FALSE;
cur->Statues	=   PMS_STARTUP;

end:;
return (cur);

error:;

if (ISNOTZERO (cur))
	{
	Free (cur, $PMAPSIZE);
	}

return ((PMAP *) 0L);
}
