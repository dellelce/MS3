/* 
** 
** MS3 files traslation heart code file
** creating by tony dee
** file 2
** 
*/ 

#define	TRASLATE2_C	1

#include <logics.h>
#include <ms3fn.h>
#include <traslate.h>


/* 
** %%
** This are the file's routines:
** dounknown
** getginit
** makeobject
** getexpression
** makeaction
** makestarter
** 
** 
*/


/* # dounknown (% LEVEL 1)
** 
** this routine will be called anytime
** an object will result to be unknown
** 
** 
*/ 

BOOL
dounknown (group, astat)
REG GROUP	*group;
REG ASTAT	*astat;
{
REG NAME	*name;
REG TITEM	*tit;
REG LABEL	*label;
REG UWORD	 _any_data;
REG UWORD	 offset;
BLOCK		*obblock;
NAME		 sn;
VARINFO		 vari;

INIT_VI (&vi);

tit		= group->ghandle->currentitem;
obblock		= tit->ti_OwnerBlock;	/* might it be different?	*/
offset		= tit->ti_CurOffset;
name		= group->name;

sn.nd_data	= name->nd_data;
sn.nd_type	= name->nd_type;
sn.nd_subtype	= name->nd_subtype;

next:;
dogetname:;

if (ISFALSE (getname (group)))
	{
	goto noname;
	}

if (name->nd_type != NDT_SPECIAL)
	{
	/*	simple variables use		*/
	
	
	}

switch (name->nd_subtype)/* check for different types of special*/
{
case	NDS_BRAK1OP:	/* '(' we got a call */
	
	if (ISFALSE (putstring (group, sn.nd_data, BT_WORKSTRING)))
		{
		goto error;
		}
	
	vi.vi_words [0] = $IN_UNKNOWN_ACTION;
	vi.vi_words [1] = (UWORD) group->couple.cp_Small;
	vi.vi_words [2] = 0; /* number of arguments		*/
	
	if (ISFALSE (setitem (group->pmap, IT_UNKNOWN, 
					(UWORD) group->couple.cp_Small, 0)))
		{
		goto noroom;
		}
	
	if (ISFALSE (writevarinfo (block, &vari)))
		{
		goto error;
		}
	
	offset += 3 * 2;
	
	blockstart (block);
	offset += 2;
	
	tit->ti_Offset = offset;
	
	if (ISFALSE (getexpression (group, obblock, &comma, &bracket, 0L)))
		{
		goto error;
		}
	
	offset = tit->ti_Offset;	/* do we need to get it back??	*/
	
	blockend (block);
	offset += 2;
	
	if (name->nd_subtype == NDS_COMMA)
		{
		goto repeat;		/* $ check it out		*/
		}
	
	if (name->nd_subtype == NDS_BRAK1CL)
		{
		goto end;
		}
	
case	NDS_TWOPOINTS:	/* ':' we got a new label	*/
	
	/* checks if the label already
	** exists
	** 
	*/ 
	
	if (ISTRUE (findlabel (group, (UBYTE *) sn.nd_data)))
		{
		goto error;
		}
	
	astat->as_Labels ++;
	
	if (ISFALSE (putstring (group, sn.nd_data, BT_WORKSTRING)))
		{
		return (FALSE);
		}
	
	_any_data = (ULONG) group->couple.cp_Small;
	
	if (ISZERO (label = createlabel (group, tit, sn.nd_data)))
		{
		goto error;
		}
	
	break;
		
case	NDS_BRAK2OP:	/* '[' a vector or matrix		*/
	
	$		/* must set complex var use data	*/
	
	getdim:;
	
	blockstart (block);
	offset += 2;
	
	tit->ti_Offset = offset;
	
	if (ISFALSE (getexpression (group, obblock, &comma, &bracket, 0L)))
		{
		goto error;
		}
	
	offset = tit->ti_Offset;
	
	blockend (block);
	offset += 2;
	
	/* 
	** it may be a matrix
	** 
	*/ 
	
	if (ISFALSE (getname (group)))
		{
		goto error;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto $end;	/* it is just a one-dimension var	*/
		}
	
	if (name->nd_subtype == NDS_BRAK2OP)
		{
		$	/* <- <- increase dimensions counter		*/
		
		
		
		goto $getdim;
		}
	
	if (name->nd_subtype == NDS_PERIOD)
		{
		
		
		goto $getdim;
		}
	
	goto $end;	/* <- <- it is just simply a one dim var	*/
	
case	NDS_PERIOD:	/* '.' a structure or a $object			*/
	
	
	
	
	
} /* switch		  */

skipaline:;

if (ISFALSE (dounknown (group, astat)))
	{
	goto error;
	}

if (name->nd_type != NDT_CLOSER)
	{
	goto syntaxerror;
	}

/* $ check this area			*/

end:;
return (TRUE);

noroom:;
group->ghandle->lasterror = EN_NOROOM;
goto error;

invalid:;
group->ghandle->lasterror = EN_INVNAMETYPE;
goto error;

noname:;
group->ghandle->lasterror = EN_NONAME;

error:;
badend:;
return (FALSE);
} /* 'dounknown SHUTDOWN' */


/* # makeobject
** 
*/

BOOL
makeobject (group)
GROUP		*group;
{
NAME		*name = group->name;
ITEM		 item;
TITEM		*tit;
SNAME		*sn;
USHORT		 type;
OBJECT		*ob;
BLOCK		*block;


if (ISFALSE (getname (group))) /* must get object name */
	{
	goto noname;
	}

if (name->type != NDT_UNKNOWN)
	{
	goto nameknown;
	}


sn = createsname (SNSIZE (group->sna));

if (ISZERO (sn))
	{
	group->ghandle->error = EN_NONAME;
	return (FALSE);
	}

if (ISFALSE (putstring (group, name->nd_type, BT_WORKSTRINGS)))
	{
	goto error;
	}

$copy name string to 'sn';

block = group->pmap->Pblocks [BT_OBJECT];



tit   = group->ghandle->currentitem;

BltClear (tit, TITSIZE);

/* 
** INIT TRASLATE ITEM
*/ 



noname:;
group->ghandle->lasterror = EN_NONAME;

error:;
return (FALSE);

end:;
return (TRUE);
}


/* # getexpression
** 
** 
** the C way. (... the assembly way, is long to come...)
** 
** 
** 
*/ 
	
BOOL
getexpression (group, block, varend0, varend1, prename)
REG GROUP	*group;
REG BLOCK	*block;
NAME		*varend0;
NAME		*varend1;
BOOL		 prename;
{
UWORD		 blocksno;
UWORD		 words;
UWORD		 _items;/* no of vars/calls/operators (+, -, *) met	*/
ULONG		*error;
NAME		*na = &group->name;
VARINFO		 vi;

error = &group->ghandle.lasterror;

INIT_VI (&vi);

_items	= 0;

if (prename == FALSE)
	{
	goto getfirstname;	/* there is no 'pre-name'	*/
	}
else
	{
	goto begin;		/* there is a 'pre-name'	*/
	}

next:;
getfirstname:;

if (ISFALSE (getname (group)))
	{
	goto noname;
	}

begin:;

if (varend0->nd_subtype == na->nd_subtype)
	{
	if (varend0->nd_type == na->nd_type)
		{
		group->ghandle->expdata.ed_names = 0;
		goto end;
		}
	}

if (varend1->nd_subtype == na->nd_subtype)
	{
	if (varend1->nd_type == na->nd_type)
		{
		$group->ghandle->expdata.ed_names = 0;
		goto end;
		}
	}

switch (na->nd_type)
{
case	NDT_SPECIAL:
	
	switch (na->nd_subtype)
	{
	case NDS_EXCLAMATION:	/* '!'		*/
	
	
	case NDS_DIESIS:	/* '#'		*/
	
	
	case NDS_AND:		/* '&' ?	*/
	
	
	
	case NDS_BRAK1OP:	/* '('		*/
	
	blockstart (block);
	blocksno++;
	offset += 2;
	goto next;
	
	case NDS_BRAK2OP:	/* '['		*/
	
	goto $error;
	
	
	case NDS_MULTIPLY:	/* '*'		*/
	
	if (ISZERO (_items))
		{
		goto $error;
		}
	
	
	case NDS_ADD:		/* '+'		*/
	
	if (ISZERO (_items))
		{
		goto $error;
		}
	
	
	
	case NDS_COMMA:		/* ','		*/
	
	
	case NDS_SUBTRACT:	/* '-'		*/
	
	if (ISZERO (_items))
		{
		goto $error;
		}
	
	
	case NDS_PERIOD:	/* '.'		*/
	
	
	case NDS_DIVIDE:	/* '/'		*/
	
	
	case NDS_TWOPOINTS:	/* ':'		*/
	
	
	case NDS_MINOR:		/* '<'		*/
	
	
	case NDS_EQUAL:		/* '='		*/
	
	
	case NDS_MAJOR:		/* '>'		*/
	
	
	case NDS_QUESTION:	/* '?'		*/
	
	
	case NDS_BRAK2OP:	/* '['		*/
	
	
	case NDS_BACKSLASH:	/* '\'		*/
	
	
	case NDS_BRAK2CL:	/* ']'		*/
	
	
	case NDS_EXOR:		/* '' ??	*/
	
	
	case NDS_UNDERLINE:	/* '_' ??	*/
	
	
	case NDS_OR:		/* '|' ??	*/
	
	
	case NDS_WAVE:		/* '~' ??	*/
	
	default:
	
	goto invalidchartype;
}

writevar:;

if (ISFALSE (writevarinfo (group, &vi)))
	{
	goto error;
	}

offset += vi.wordsused << 2;
goto getfirstname;

invalidchartype:;
*error = $$;
goto error;

noname;;
*error = EN_NONAME;
goto error;

end:;
return (TRUE);

error:;
return (FALSE);
}


/*
** # makeaction (fh, group)
**
** group :: GROUP *
**
*/

EXTERN NAME	stopname;

BOOL
makeaction (group)
REG GROUP	*group;
{
REG GHANDLE	*gh	=	group->ghandle;
REG PROENV	*pe	=	(PROENV *) gh->environment;
REG TITEM	*tit;
REG WPTR	 offset;
REG ULONG	 type;
ACTION		*act;
BLOCK		*block	=	pm->Pblocks[_Actions];

tit = group->ghandle->currentitem;

MemClear (tit, TITSIZE);

tit->ti_Type = TIT_ACTION;


offset = lastusedbyte (block);

act = (ACTION *) makeroom (block, ACTSIZE);

if (ISZERO (act))
	{
	goto noroom;
	}

tit->ti_InitialOffset = offset;
$tit->ti_CurOffset    = offset;
act->ac_Offset	      = offset;
act->ac_ArgOut	      = FALSE;


if (ISZERO (getname (group)))
	{
	goto noname;
	}

type = name->nd_type;

if (type == NDT_ERROR)	/* erron in name */
	{
	goto syntaxerror;
	}

if ((type != NDT_DEFINER) && (type != NDT_UNKWON))
	{
	goto illegalres;
	}

if (type == NDT_DEFINER)
	{
	switch (subtype) /* HERE THINGS WILL BE CHANGED */
	{
	case NDS_GHOST:
		
		act->ac_Type = AT_GHOST;
		goto here;
		
	case NDS_FETCHED:
		
		act->ac_Type = AT_FETCHED;
		goto here;
		
	default:
		goto illegalres;
		
	} /* end 'switch' */
	
	act->ac_Type = AT_NORMAL;
	goto putactname:;
	} /* end 'if'	  */

here:;

if (ISFALSE (getname (group)))
	{
	goto error;
	}

putactname:;

if (ISFALSE (putstring (group, (ULONG) (group->sna) + 2L, BT_PROGSTRINGS)))
	{
	goto error;
	}

act->ac_Name = group->couple.cp_Small;
tit->ti_Name = group->couple.cp_Big;

if (ISFALSE (getname (group)))
	{
	goto error;
	}

if (name->nd_type != NDT_RESLABEL)
	{
	goto $syntaxerror;
	}

switch (name->nd_subtype)
{
case	NDS_BODY:
	
	$
	
	
	hearttraslate ($group);
	
	goto $shutdown;
	
case	NDS_ARGIN:
	
	
	
case	NDS_ARGOUT:
	
	act->ac_ArgOut = TRUE;
	
}

/* 
** supposed function body
** 
*/ 


goto end; /* here things will be changed */


illegalres:;
group->ghandle->lasterror = EN_ILLRESWUSE;
goto error;

group->ghandle->lasterror = EN_SYNTAXERROR;
goto error;

noroom:;
group->ghandle->lasterror = EN_NOROOM;

error:;
return (FALSE);

end:;
return (TRUE);
} /* function 'makeaction' closed */


/* # makestarter
** 
** 
*/ 

BOOL
makestarter (group)
REG GROUP	*group;
{
REG TITEM	*tit;
ACTION		*act;
NAME		*name;
PMAP		*pmap;
BLOCK		*block;

pmap = group->pmap;
name = group->name;

block  = pmap->Pblocks [BT_STARTER];

if (ISNOTZERO (blk))			/* starter can not be duplicated!     */
	{
	group->ghandle->lasterror = EN_STARTERDUP;
	goto error;
	}

tit = group->ghandle->currentitem;

MemClear (tit, TITSIZE); /* $ perhaps it will changed someway	*/

tit->ti_Type = TIT_STARTER;

act = (ACTION *) makeroom (block, ACTSIZE);

if (ISZERO (act))
	{
	goto noroom;
	}

$	/* <- <- something still to do, isn't it?	*/

if (ISFALSE (getname (group)))
	{
	goto noname;
	}

if (name->nd_type != NDT_RESLABEL)	/* you can't start an action	*/ 
	{				/* without placing a reslabel	*/
	goto syntaxerror;
	}

if (name->nd_subtype == NDS_BDDY)
	{
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto syntaxerror;
		}
	
	if (name->nd_subtype != NDS_TWOPOINTS)	/* we need a ':' to	*/
		{				/* finish the label	*/
		goto syntaxerror;
		}
	
	$ /* is needed any check for other reserved labels?	*/
	
	if (ISFALSE (hearttraslate (group, $__endname__, 0))
		{
		goto error;
		}
	
	}

if (name->nd_subtype == NDS_ARGIN)
	{
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto syntaxerror;
		}
	
	if (name->nd_subtype != NDS_TWOPOINTS)	/* we need a ':' to	*/
		{				/* finish the label	*/
		goto syntaxerror;
		}
	
	$	/* is needed any check for other reserved labels?	*/
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type == NDT_RESLABEL)
		{
		$
		}
	
	if (ISFALSE (getvardef (group, name, block, $0)))
		{
		goto error;
		}
	
	}

if (name->nd_subtype == NDS_ARGOUT)
	{
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto syntaxerror;
		}
	
	if (name->nd_subtype != NDS_TWOPOINTS)	/* we need a ':' to	*/
		{				/* finish the label	*/
		goto syntaxerror;
		}
	
	$	/* is needed any check for other reserved labels?	*/
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type == NDT_RESLABEL)
		{
		$
		}
	
	if (ISFALSE (getvardef (group, name, block, $0)))
		{
		goto error;
		}
	}



syntaxerror:;
group->ghandle->lasterror = EN_SYNTAX;

error;
badend:;
return (FALSE);

end:;
return (TRUE);
}


/* 
** # getginit
** 
** 
** gets a global var initialization data
** --- (THIS WAS PART OF THE INITIAL COMMENT 
** 	I DON'T KNOW WHAT'S FOR PRECISELY!!)
** 
** I think it must be removed
** 
*/ 

BOOL
getginit (group, flag, vec)
REG GROUP	*group;
REG BOOL	 flag;
REG BOOL	 vec;
{
REG SHORT	 *type    = &group->name->nd_type; /* not sure if it'll work! */
ULONG		 *subtype = &group->name->nd_subtype;

if (ISFALSE (getname (group)))
	{
	goto noname;
	}

if (*type != NDT_SPECIAL)
	{
	goto syntax; /* will it work? who knows!? we'll try next!! */
	}

if (*subtype != NDS_BRAK1OP)
	{
	goto syntax;
	}

$	/* <- <- here there should be the routine body!!	*/

syntax:;
group->ghandle->lasterror = EN_SYNTAXERROR;
goto badend;

noname:;
group->ghandle->lasterror = EN_NONAME;

badend:;
error:;
return (FALSE);

end:;
return (TRUE);
} /* function 'getginit' closed but not ended */
