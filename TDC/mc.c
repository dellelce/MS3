** tony dee special creation
** MS3 language compiler main v0.11
** now defining.
**
** 
** a m i g a  r e l e a s e
** 
** 
*/


#include <startup.h>
#include <logics.h>
#include <ms3.h>


#define	 SUCCED		 0L
#define	 FAIL		10L


ULONG	 OpenLibrary ();
VOID	 CloseLibrary ();
VOID	 FreeMem ();

UBYTE	 gfxlib [] = "graphics.library";
UBYTE	 doslib [] = "dos.library";

ULONG	 GfxBase;
ULONG	 DosBase;


/* # initghandle
** 
*/

BOOL
initghandle (ghandle)
REG GHANDLE *gh;
{
REG VLIST   *vl;

vl = (VLIST *) Alloc (VLSIZE);

if (ISZERO (vl))
	{
	Free (gh, OBSIZE (GHANDLE));
	return (FALSE);
	}

gh->locals	= vl;

vl = (VLIST *) Alloc (VLSIZE);

if (ISZERO (vl))
	{
	Free (gh, OBSIZE (GHANDLE));
	return (FALSE);
	}

gh->globals	= vl;

/* $ <- <- something missing		*/

return (TRUE);
}


/* # _main
** 
** 
*/ 

ULONG
_main ()
{
REG GROUP	*group;
_FLAG		*fl;
GHANDLE		*ghandle;

group = (GROUP *) Alloc (GRSIZE);

if (ISZERO (group))
	{
	goto error;	/* it may greatly improved	*/
	}

GfxBase = OpenLibrary (&gfxlib, 0L);

if (ISZERO (GfxBase))
	{
	goto error;
	}

DosBase = OpenLibrary (&doslib, 0L);

if (ISZERO (DosBase))
	{
	goto error;
	}

/* get startup environment
** 
*/ 

fl = (_FLAG *) Alloc (fl);

if (ISFALSE (getstartupenv (fl)))
	{
	goto error;
	}


if (ISFALSE (initghandle ($ghandle)))
	{
	goto error;
	}

/*
if (ISZERO (ghandle))
	{
	goto error;
	}
*/

ghandle->flags = fl;


/* %S1
** 
** removed since useless!
** 
*/ 

/* %S2
** 
*/ 

group->sna	= createsname (SMALLNAME);

if (ISZERO (group->sna))
	{
	$showerror ($memoryerror);
	
	goto error;
	}

/* %S3
** 
*/ 

group->name = (NAME *) Alloc (NASIZE);

if (ISZERO (group->name))
	{
	$showerror ($memoryerror);
	
	goto error;
	}


if (ISFALSE (traslatepmap (group, $filename)))
	{
	goto error;
	}

if (ISFALSE ($reviewpmap (group)))
	{
	goto error;
	}

if (ISFALSE (makecode ($ group)))
	{
	goto error;
	}

end:;

shutdowngroup (group);
CloseLibrary (DosBase);
CloseLibrary (GfxBase);

return (SUCCED);

error:;

if (ISNOTZERO (group))
	{
	shutdowngroup (group);
	}

if (ISNOTZERO (DosBase))
	{
	CloseLibrary (DosBase);
	}

if (ISNOTZERO (GfxBase))
	{
	CloseLibrary (GfxBase);
	}

return (FAIL);
}
