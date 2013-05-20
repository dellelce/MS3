/* tony dee © 1992
** 
** Routinnes helping
** the  management
** of process maps.
** 
** it shouldn't be used in the
** compiler, but in helping
** utilities!!
** 
*/ 

#include <logics.h>


UBYTE		 noitem [] = "Directory does have any item\m";
UBYTE		 dirhas [] = "\nDirectory does have ";
UBYTE		 items  [] = "%d items.\n";
UBYTE		 noaitm [] = "Directory has no item!\n";
UBYTE		 brakop [] = " (";
UBYTE		 brakcl [] = " )\n";


/* # showdir
** 
*/ 

BOOL
showdir (file, pmap)
UBYTE		*file;
PMAP		*pmap;
{
REG VOID	*addr;
REG ITEM	*addr1;
REG FH		*fax;
REG UWORD	 items;
REG UWORD	 count;
UBYTE		*string;
UBYTE		*bufstring;
UWORD		 count_STORE;
FB		*fib;
STATIC UBYTE	*its [] =
{
"IT_OBJECTDEF",
"IT_ACTION",
"IT_FUNCTION",
"IT_STRUCTUREDEF",
"IT_GLOBALVAR",
"IT_SOURCE",
(UBYTE *) 0L
};

if (ISZERO (file))	/* get io stream		*/
	{
	fax = Output ();
	
	if (ISZERO (fax))
		{
		goto error;
		}
	}
else
	{
	fax = Open (file, MODE_OLDFILE);
	
	if (ISZERO (fax))
		{
		goto error;
		}
	}

/* gets directory block
** 
*/ 

addr = (VOID *) pmap->Pblocks [_Directory];

if (ISZERO (addr))
	{
	Close (fax);
	goto error;
	}

items = B_ITEMS ((BLOCK *) addr);	/* no of items		*/
addr1 = (ITEM *) (addr + BS);		/* first item address	*/
count = 0;				/* init counter		*/

fib = CreateSingleBuf (FBM_VERYSMALL);	/* simulated file	*/

if (ISZERO (fib))
	{
	Close (fax);
	goto error;
	}

while (count != items)
{
string = WORKSTRING (pmap, addr1 [count]);

BufPrint (fib, string,   FBM_STRING);
BufPrint (fib, &brackop, FBM_STRING);
BufPrint (fib, its [((ITEM *) addr1[count])->di_type-1], FBM_UWORD);
BufPrint (fib, &brackcl, FBM_STRING);
} /* closes 'while' */


if (ISNOTZERO (count))
	{
	BufPrint (fib, &dirhas, FBM_STRING);
	count_STORE = count;
	BufPrint (fib, &count_STORE, FBM_ULONG);
	BufPrint (fib, &items, FBM_STRING);
	goto showdir_close;
	}
else
	{
	BufPrint (fib, &noaitm, FBM_STRING);
	}

showdir_close:;

BufSave (fax, fib);
BufDelete (fib);

end:;
return (TRUE);

error:;

if (ISNOTZERO (fib))
	{
	BufDelete (fib);
	}

return (FALSE);
} /* closes function	*/


/* # showfile
** 
*/ 

BOOL
showfile (filename)
REG UBYTE	*filename;
{
REG UBYTE	*buf;
REG CL		 file;
REG ULONG	 in;
REG ULONG	 size;

in = OutPut ();

if (ISZERO (in))
	{
	goto false;
	}

file.lonn = Open (filename, MODE_OLDFILE);

if (ISZERO (file.lonn))
	{
	goto false;
	}

buf = (UBYTE *) Alloc (512);

if (ISZERO (buf))
	{
	Close (file.lonn);
	goto false;
	}

FOREVER
{
size = (ULONG) Read (file.lonn, buf, 512L);

if (size < 512L)
	{
	Write (out, buf, size);
	goto true;
	}

Write (out, buf, 512L);
}


false:;
c.wd[0] = FALSE;
goto end;

true:;
c.wd[0] = TRUE;

end:;
return ((BOOL) file.wd[0]);
}
