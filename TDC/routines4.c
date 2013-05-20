/* tony dee © 1992
** 
** 
*/ 

#define	ROUTINES4_C		1

#include <logics.h>
#include <ms3.h>

/* %%
** source
** __addsourcef
** shutdowngroup
** addname
** pmopnotavail
** headerdef2use
** putsimpledeftype
** getvartype
** 
** 
*/ 


/* # shutdowngroup
** 
** 
*/ 

VOID
shutdowngroup (group)
REG GROUP	*group;
{
REG VOID	*any;

any = group->pm;

if (ISNOTZERO (any))
	{
	deletepmap (any);
	}

any = group->ghandle;

if (ISNOTZERO (any))
	{
	removeghandle (any);
	}

any = group->sna;

if (ISNOTZERO (any))
	{
	freesname (any);
	}

any = group->name;

if (ISNOTZERO (any))
	{
	Free (any, NASIZE);
	}

any = group->titem;

if (ISNOTZERO (any))
	{
	Free (any, TITSIZE);
	}

any = group->file;

if (ISNOTZERO (any))
	{
	hclose (any);
	}
}


/* # addname
** 
** 
*/ 

VOID
addname (group, nn)
GROUP		*group;
REG NNODE	*nn;
{
REG NLIST	*nl = group->ghandle.namebase->nb_NameList;

ENQUEUE (nl, nn);
}


/* # pmopnotavail
** 
** this is for the very first release
** 
*/ 

BOOL
pmopnotavail (group)
REG GROUP	*group;
{
REG FB		*fn

fb = CreateSingleBuf (FBM_VERYSMALL);

if (ISZERO (fb))
	{
	goto badend;
	}

BufPrint (fb, "I am very sorry, the very first realese\n", FBM_STRING);
BufPrint (fb, "of the MS3 compiler has not available the\n", FBM_STRING);
BufPrint (fb, "processmap handling operators.\n", FBM_STRING);

BufSave (0, fb);
BufDelete (fb);

return (TRUE);

badend:;
return (FALSE);
}


/* # headerdef2use
** 
** 
*/ 

BOOL
headerdef2use (group, vi, how);
GROUP		*group;
VARINFO		*vi;
$ ULONG		 how;
{
UWORD		 def;

/* gets definition header
** 
*/ 

def = * (UWORD *) group->name->nd_type;

end:;
return (TRUE);

badend:;
error:;
return (FALSE);
}


/* # putsimpledeftype
** 
** gets a list of 'simpledefs' and gives back a 
** number depending on the object type
** 
*/ 


$ ULONG
putsimpledeftype (group, block, vi)
REG GROUP	*group;
BLOCK		*block;
REG VARINFO	*vi;
{
REG ULONG	 value;

if (ISFALSE (getname (group)))
	{
	goto noname:;
	}

$ /* function body	*/

end:;
return (value);

noname:;
group->ghandle.lasterror = EN_NONAME;


badend:;
error:;
return (0L);
}


/* # getvartype
** 
** what does it do precisely?? look around for it!!
** $
** 
*/ 

BOOL
getvartype (vi, var)
VARINFO		*vi;
VAR		*var;
{

end:;
return (TRUE);

error:;
bademd:;
return (FALSE);
}


/* # getvarrealsize
** 
** 
*/ 

BOOL
getvarrealsize (block, vi, var)
BLOCK		*block;
VARINFO		*vi;
UWORD		*var;
{

end:;
return (TRUE);

error:;
bademd:;
return (FALSE);
}


/* # putsimpledefsize
** 
** 
*/ 

BOOL
putsimpledefsize (group, block, vi)
GROUP		*group;
BLOCK		*block;
VARINFO 	*vi;
{

if (ISFALSE (getname (group)))
	{
	goto noname;
	}


$ /* function body	*/

end:;
return (TRUE);

noname:;
group->ghandle.lasterror = EN_NONAME:;

error:;
return (FALSE);
}
