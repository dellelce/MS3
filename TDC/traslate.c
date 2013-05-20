/* 
** 
** 
** FILE TRASLATION HEART
** developing by tony dee
** file 1
** 
** 
*/ 

#define	TRASLATE_C	1

#include <logics.h>
#include <traslate.h>
#include <ms3fn.h>

EXTERN NAME	comma;
EXTERN NAME	bracket;
EXTERN NAME	bracket0;

/* %%
** This file routines:
**
** setcostant
** skipaline
** traslatepmap
**
**
*/

#define VARSETBASE	0x0010000000000000


struct VarTag
{
UBYTE	vt_Val;
USHORT	vt_Size;
};


UWORD ___far___TRUE =
{
0x0000,
0x0000
};

UWORD ___far___FALSE =
{
0x0000,
0x0000
};

#define	VT	VarTag


/*
** objects starting with '$'
** must be replaced or changed!
** 
** hgetname (struct fh *, SNAME *)
** getnametype (GHANDLE *, PMAP *, SNAME *, NAME *)
** 
*/ 



/*
** WARNING: the first level only contains
** 	    names such as with the types: (?? it looks not so correct!!)
**	    NDT_SOURCE		::	source call == link to a pmap library
**	    NDT_DEFINER		::	new object def (action, object, struct.)
**	    NDT_SIMPLEDEF	::	global ver definition
**	    NDT_CLOSER		::	what for if here?? it is just an empty
**				::	line!
**	    NDT_STRUCTURE	::	structure name
**				::	used for a global name
**	    NDT_OBJECT		::	object name
**	    			::	very alike to above
**				::	(not sure it can object can be used as
**				::	a global var!)
*/

EXTERN V2T _buf [11];


/* # traslatepmap
** 
** %steps
** 
** (%Sxx step number)
** (%Lxx current traslateing level)
** 
** 1. create the 'group' structure	** R E M O V E D
** 2. create a 'sname' structure	** R E M O V E D
** 3. create a 'NAME' structure		** R E M O V E D
** 4. open program text file
** 5. make 'varinfo'
** 6. get a name %L0
**  6A. a definer?
**   6A0. an action?
**   6A1. an object?
**   6A2. the starter?
**   6A3. a structure?
**   6AE. none of the above? it should be an error?
**  6B. a simple definer?
**   6B-. geve a glance at it!
**  6C. a structure definition?
**  6D. an user var type? -- still not used
**  6E. an object?
**  6F. a source call?
**  
**  
*/

BOOL
traslatepmap (group, file)
REG GROUP	*group;
UBYTE		*file;
{
REG FH		*fl;
REG ULONG	 type;
REG BOOL	 what;
REG VOID	*_any_ptr;
REG ULONG	 _any_data;
PROENV		*pe	= (PROENV *) ghandle->environment;
PMAP	 	*pm	= pe->WorkPmap; /* let's get our pmap */
GHANDLE		*ghandle;
VARU		 vu;
VARINFO		 vi;


/* %S1 thru %S3 has been removed
** from here and relocated to
** the TDC/ms3.c file! (now: mc.c)
** 
*/ 


/* %S4
** 
*/ 

fl = hopen (file);

if (ISZERO (fl))		/* COULDN'T OPEN FILE */
	{
	ghandle->lasterror = EN_NOMEMORY;
	freesname (group->sna);
	FreeMem (group->name, NASIZE);
	FreeMem (group,	      GRSIZE);
	return (FALSAE);
	}

group->file = fl;

INIT_VI (&vi);

next:;
here:;

/* #S6
** 
*/ 

getname (group);

type = name->nd_type;

/* %L0 (TRASLATION LEVEL 0)
** %6A
** 
*/ 

if (type == NDT_DEFINER) /* first class of object analyzed */
{
item = $createitem (group->pmap);

switch (name->nd_subtype)
	{
	case	NDS_ACTION:	/* %6A0	*/
			   what = makeaction (group);
			   
			   if (ISFALSE (what))
				{
				goto error;
				}
			   break;
	
	case	NDS_OBJECT:	/* %6A1	*/
			   what = makeobject (group);
			   
			   if (ISFALSE (what))
				{
				goto error;
				}
			   break;
	
	case	NDS_STARTER:	/* %6A2	*/
			    what = makestarter (group);
			    
			    if (ISFALSE (what))
				{
				goto error;
				}
			    break;
		
	case	NDS_STRUCTURE:	/* %6A3	*/
			    what = makestructure (group);
			    
			    if (ISFALSE (what)) /* here something must*/
				{	        /* changed	      */
				goto error;
				}
			    break;
			    
	default:		/* %6AE	*/
			    goto error;
	
	} /* end for SWITCH */

goto next;		/* gets next object */
} /* end for IF */

/* %6B
** 
*/ 

if (name->nd_type == NDT_SIMPLEDEF)	/*$$s*/
	{
	if (ISFALSE (getvardef (group, name, 0L, VGM_GLOBAL)))
		{
		goto $error;
		}
	
	}

/* %6C
** 	
*/ 

if (name->nd_type == NDT_STRUCTURE) /* we got a struct var global	*/
	{
	if (ISFALSE (getvardef (group, name, 0L,VGT_GLOBAL)))
		{
		goto $error;
		}
	}


/* %6D
** 
*/ 
	
/*if (name->nd_type == NDT_USERTYPE)	a user type global var definition
	{				yet not usable
	}*/


/* %6E
** 
*/ 
	
if (name->nd_type == NDT_OBJECT)   /* we have an object def		*/
	{
	if (ISFALSE (getvardef (group, name, 0L, VGT_GLOBAL)))
		{
		goto $error;
		}
	}


/* %6F
** 
*/ 
	
if (name->nd_type == NDT_SOURCE)
	{
	if (source (group) != TRUE)
		{
		goto error;
		}
	}

goto next; /* analyzes a next global line */

syntax:;
ghandle->lasterror = EN_SYNTAX;

error:;
if (ISNOTZERO (fl))
	{
	hclose (fl);
	}

/* HERE THERE WAS SOME CODE THAT DELETE THE 'group' STUFF.. */

return (FALSE);

end:;

hclose (fl);
Free (group->name, NASIZE);
freesname (group->sna);
Free (group, GRSIZE);

return (TRUE); /* ?? */
} /* function: 'traslatepmap' close//to be changed */


/*
** BOOL
** # setconstant (group)
**
** Returns FALSE or TRUE depending to if the constant has been
** set or not.
**
** group contains data about the constant.
*/

#define	__HEADER	vi.words [0]
#define	__VAR_0		vi.words [1]
#define	__VAR_1		vi.words [2]
#define	__VAR_2		vi.words [3]
#define	__VAR_3		vi.words [4]

BOOL
setconstant (group, block)
REG GROUP	*group
BLOCK		*block;
{
REG NAME	*name = group->name;
REG UWORD	 words;
UWORD	 	*offset;
TITEM		*current;
VARINFO		 vi;


INIT_VI (&vi);
words	= 2;
current = group->ghandle->currentitem;
offset	= &current->ti_CurOffset;

switch (name->nd_type)
{
case	NDT_STRING:
		   
	__HEADER = VBT_STRING;
	
	goto word;
	
case	NDT_NUMBER:
	
	switch (name->nd_subtype)
	{
	case NDS_FLOAT:
	
	__HEADER = VBT_FLOAT;
	
	goto long;
	
	
	case NDS_DOUBLE:
	
	__HEADER = VBT_DOUBLE;
	
	goto double;
	
	
	case NDS_UBYTE:
	
	__HEADER = VBT_SGN_BYTE;
	
	goto word;
	
	
	case NDS_BYTE:
	
	__HEADER = VBT_BYTE;
	
	goto word;
	
	
	case NDS_UWORD:
	
	__HEADER = VBT_SGN_WORD;
	
	goto word;
	
	
	case NDS_WORD:
		
	__HEADER = VBT_WORD;
	
	goto word;
	
	
	case NDS_ULONG:
		
	__HEADER = VBT_SGN_LONG;
	
	goto long;
	
	
	case NDS_LONG:
			
	__HEADER = VBT_LONG;
	
	goto long;
	}	/* 'switch'	*/

case	NDT_RESCONST:
		     
	switch (name->nd_subtype)
	{
	case NDS_FALSE:
	
	__HEADER = VBT_SGN_LONG;
	__VAR_0  = 0x0000;
	__VAR_1  = __FALSE;
	
	goto doit;
	
	case NDS_TRUE:
	
	__HEADER = VBT_SGN_LONG;
	__VAR_0  = 0x0000;
	__VAR_1  = __FALSE;
	
	goto doit;
	}	/* 'switch'	*/
}

double:;

(DOUBLE) __VAR_0 = * (DOUBLE *) name->nd_data;

words = 5;
goto doit;

long:;

(ULONG) __VAR_0 = name->nd_data;

words = 3;
goto doit;

word:;

__VAR_0 = (UWORD) name->nd_data;

doit:;

vi.wordsused = words;

if (ISFALSE (writevarinfo (block, &vi)))
	{
	goto error;
	}

*offset += words << 1;

end:;
return (TRUE);

error:;
return (FALSE);
} /* function 'setconstant' closed (but not ended at all!) */


/* # skipaline
** 
*/ 

BOOL
skipaline (group)
REG GROUP	*group;
{
REG NAME	*name;
REG SHORT	 type;
REG ULONG	*error;

name	= group->name
error	= &group->ghandle->lasterror;

if (ISFALSE (getname (group)))
	{
	*error = EN_NONAME;
	
	error:;
	return (FALSE);
	}

type = name->nd_type;

if (type != NDT_CLOSER)
	{
	*error = EN_NOCLOSER;
	
	goto error;
	}

return (TRUE);
} /* functions 'skipaline' closed */
