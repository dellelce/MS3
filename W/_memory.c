/* tony dee © 1992
** 
** used in the long future
** 
*/ 

#include <wsystem.h>



/* # iAddSysMemBlock
** 
** MUST be used when program is started for its first time!
** or when all blocks are 
** my remark: the less you use the better it is.
** 
** 
** version 1
** 
** 
*/ 

BOOL
iAddSysMemBlock (group, bsize)
REG GROUP	*group;
REG ULONG	 bsize;
{
REG MEMBLOCK	*balloc;

bsize = RIGHTSIZE (bsize);

balloc = (MEMBLOCK *) FastAlloc (bsize + MBLOCKSIZE);

if (ISZERO (balloc))
	{
	goto error;
	}

balloc->mb_Bottom = (PTR) balloc + (PTR) MBLOCKSIZE;
balloc->mb_Size	  = bsize;
balloc->mb_Top	  = balloc + (PTR) bsize;

ENQUEUE (group->ghandle.$imemblocks, balloc);

group->ghandle.$imemblocksno++;

end:;
return (TRUE);

error:;
return (FALSE);
}


/* # iAlloc
** 
** 
*/ 

BOOL
iAlloc (group, size)
GROUP		*group;
ULONG		 size;
{
MBLOCK		*_mb;

_mb = (MBLOCK *) group->ghandle.$imemblocks.tl_Last;

if (ISZERO (_mb))
	{
	goto error;
	}


}
