/*****************************************
 *					 *
 *  @@ 1990-92 TDC blocks routines	 *
 *					 *
 *****************************************/

#define	BLOCKS_C	1

#include <blocks.h>
#include <items.h>
#ifndef LOGICS_H	
#include <globals.h>
#endif
#include <ms3fn.h>

/* %%
** newblock
** createblock
** deleteloneblock
** makeroom
** $ ptrtoword
** packblock
** deleteblockchain
** blockwrite
** bwritew
** lastusedbyte
** reallastbyte
** freeblockarea
** wordtoptr
** bwritewat
** 
*/ 

VOID  FreeMem ();


/* # newblock
** 
*/ 

BLOCK *
newblock (x)
UWORD		 x;
{
REG BLOCK	*bl;
REG UWORD	 c;

if (x < 0 || x > 65536)
	{
	return (0);
	}

bl = Alloc ((ULONG) (x + (sizeof (B_))));

if (ISZERO (bl))
	{
	return (0);
	}

bl->B_Size = x;
return (bl);
}


/* # createblock
** 
*/ 

BLOCK *
createblock (x, y)
UWORD		 x;
UBYTE		 y;
{
REG BLOCK	*child = newblock (x);

if (ISZERO (child))
	{
	return ((PTR) 0);
	}

child->B_ItemsType = y;

return (child);
}


/* # deleteloneblock
** 
*/ 

BOOL
deleteloneblock (x)
REG BLOCK	*x;
{
return (FreeMem (x, (ULONG) (x->B_Size + (sizeof (B_)))));
}


/* # makeroom
**
** makes some room in a block (it is very similar to AllocMem of Amiga)
**
** it should be optimized to a very good way since it will be used
** a lot of times
*/

PTR
makeroom (block, rsize)
REG BLOCK	*block;
ULONG		 rsize;
{
REG UWORD	 acc = 0;
REG BLOCK	*de = block; 
	
start1:;

acc = de->B_Size - de->B_LastByte;

if (acc => rsize) 
	{
	de->B_ItemsCount++;
	de->B_LastByte += rsize;
	}
else
	{
	if (ISNOTZERO (de->B_Next)) 
		{
		de = de->B_Next;
		goto start1;
		}

de = createblock (de->B_Size, de->B_ItemsType);
de->B_LastByte = rsize;
de->B_ItemsCount = 1;
}

return ((PTR) ((ULONG)de + (ULONG) (de->B_LastByte) - (ULONG) rsize));
}


/* # ptrtoword
**
** turns a standard pointer to word one (do I need it? I am not so sure!!)
*/

$ ptrtoword (block, ptr)
BLOCK	*block;
VOID	*ptr;
{
VOID	*ptr0 = (PTR) block;
VOID	*ptr1 = (PTR) 0;


}
} /* this routine must be completed the sooner */


/* # packblock
** 
*/ 

BLOCK *
packblock (block)
BLOCK		*block;
{
REG UWORD	 tot;
REG UWORD	 tot0;
REG BLOCK	*de;
REG BLOCK	*de1;
REG VOID	*pl;

de = block;

if (ISZERO (de->B_Next))
	{
	return (0);
	}

while (ISNOTZERO (de))
{
tot  += de->B_LastByte;
tot0 += de->B_ItemsCount;
de    = de->B_Next;
}

de  = block;
de1 = createblock (tot, de->B_ItemsType);

de1->B_ItemsCount = tot0;

tot	= 0;
tot0	= sizeof (BLOCK) ;

while (ISNOTZERO (de))
{
pl  = (PTR) de + (PTR) sizeof (BLOCK);
tot = de->B_LastByte;

CopyMemQuick (pl, (PTR) de1 + (PTR) tot0, tot);

tot0= tot0 + tot;
de  = de->B_Next;
}

return (de1);
}


/* # deleteblockchain
** 
*/ 

VOID
deleteblockchain (block)
BLOCK		*block;
{
REG BLOCK	*cur = block;
REG BLOCK	*next = cur->B_Next;

do
{
deleteloneblock (cur);
cur  = next;
next = cur->B_Next;
} while (ISNOTZERO (next));
}


/* # blockwrite
** 
** it is very time consuming since it is
** a critical routine
** 
*/ 

VOID
blockwrite (block, buf, size)
BLOCK		*block;
UBYTE		*buf;
REG ULONG	 size;
{
REG UBYTE	*h;

h = makeroom (block, size);	/* something to change here!! */
CopyMemQuick (buf, h, size);
}


/* # bwritew
** 
*/ 

VOID
bwritew (block, word)
BLOCK		*block;
REG UWORD	*word;
{
REG UWORD	*h;
REG BLOCK	*b;

b  = block;

h  = (UWORD *) makeroom (block, 2L);
*h = *word;
}


/* # lastusedbyte
** 
** gives back current offset
** 
*/ 

ULONG
lastusedbyte (blk)
REG BLOCK	*blk;
{
REG ULONG	 count;

while (blk->B_Next != 0)
	{
	count += blk->B_LastByte;
	blk = blk->B_Next;
	}

count += blk->B_LastByte;
return (count);
}


/* # reallastbyte
** 
*/ 

PTR
reallastbyte (blk)
REG BLOCK	*blk;
{

while (blk->B_Next)
{
blk = blk->B_Next;
}

return ((PTR) ((ULONG) blk + (ULONG) blk->B_LastByte));
}


/* # freeblockarea
** 
*/ 

BOOL
freeblockarea (block, off, size)
REG BLOCK	*block;
REG WPTR	 off;
REG UWORD	 size;
{
REG BLOCK	*searchblock;
REG WPTR	 last = size + off;
REG VOID	*base = (PTR) ((ULONG) block + BS + (ULONG) off);

packblock (block);

if (block->B_LastByte < off)
	{
	return (FALSE);
	}

if (last == block->B_LastByte)
	{
	block->B_LastByte = off;
	return (TRUE);
	}

CopyMem (((PTR) ((UL) base + (UL) size)), base, block->B_LastByte - size);
block->B_LastBye = off + B_LastBye - size;

return (TRUE);
}

/* # wordtoptr
** 
** CHECK IT IF IT GETS THE RIGHT WORD PTR!!!
** 
*/ 

UWORD *
wordtoptr (block, offset)
BLOCK		*block;
REG UWORD	 offset;
{
REG BLOCK	*b;

b = block;

next:;

if (offset < b->B_LastByte)
	{
	goto write
	}
else
	{
	offset -= b->B_LastByte;
	b	= b->B_Next;
	
	if (b == 0)
		{
		return (0);
		}
	
	goto next;
	}

writeit:;
w = (UWORD *) ((ULONG) b + (ULONG) word);

return (w);
}


/* # bwritewat
** 
** CHECK IT IF IT GETS THE RIGHT WORD PTR!!!
** 
*/ 

BOOL
bwritewat (block, offset, word)
BLOCK		*block;
WPTR		 offset;
REG UWORD	 word;
{
REG UWORD	*w;
REG BLOCK	*b;

b = block;

next:;

if (offset < b->B_LastByte)
	{
	goto write
	}
else
	{
	offset -= b->B_LastByte;
	b	= b->B_Next;
	
	if (b == 0)
		{
		return (FALSE);
		}
	
	goto next;
	}

writeit:;
w = (UWORD *) ((ULONG) b + (ULONG) word);
*w = word;
return (TRUE);
}
