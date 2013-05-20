/* tony dee © 1992
** 
** traslation extension
** 
*/ 

#define	TRASLATE5_C

/* %%
** __obj_open
** __obj_create
** getanycall
** 
** 
*/ 

#include <logics.h>
#include <ms3fn.h>

/* # __obj_open
** 
** 
*/ 

BOOL
 __obj_open (group, block, vi)
REG GROUP	*group;
BLOCK		*block;
REH VARINFO	*vi;
{
REG UWORD	*w;

vi->words [0] = IN_OBJ_OPEN;
vi->words [1] = 0;		/* no of attributes		*/
vi->wordsused = 2;

if (ISFALSE (writevarinfo (block , &vi)))
	{
	goto error;
	}

offset += 2 * 2;

w  = (UWORD *) reallastbyte (block);
w += 2;

/* %
** 
** open [object-description-name] ....;
** 
*/ 
	
if (ISFALSE (getname (group)))
	{
	goto noname;
	}


if (name->nd_type != NDT_OBJECT)
	{
	goto syntaxerror;
	}

$	/* why did I put a 'dollar' here??	*/

/* %
** 
** check for parenthesis
** 
*/

if (ISFALSE (getname (group)))
	{
	goto noname;
	}

if (name->nd_type != NDT_SPECIAL)
	{
	goto syntaxerror;
	}

if (name->nd_subtype != NDS_BRAK1OP)
	{
	goto syntaxerror;
	}

$	/* why did I put a 'dollar' here??	*/


/* %
** 
** get lists of attributes definition
** 
*/ 

nds_open:;

if (ISFALSE (getname (group)))
	{
	goto noname;
	}

if (name->nd_type != $NDT_OBJATTR)
	{
	if (name->nd_type != $NDT_UNKNONW)
		{
		goto syntaxerror;
		}
	}

$


/* %
** 
** gets the equal sign
** 
*/ 

if (ISFALSE (getname (group)))
	{
	goto noname;
	}

if (name->nd_type != NDT_SPECIAL)
	{
	goto syntaxerror;
	}	

if (name->nd_subtype != NDS_EQUAL)
	{
	goto syntaxerror;
	}


/* %
** 
** gets the equation that can follow
** 
*/ 

blockstart (block);

if (ISFALSE (getexpression (group, block, &comma, &bracket1, 0L)))
	{
	goto syntaxerror;
	}

blockend (block);


/* %
** 
** checks how does expression ends
** 
*/ 

if (name->nd_subtype == comma.nd_subtype)
	{
	goto nds_open;
	}

$ /* I think here there is something missing	*/

error:;
badend:;
return (FALSE);

end:;
return (TRUE);
}


/* # __obj_create
** 
** 
*/ 

__obj_create (group, vi)
REG GROUP		*group;
REG VARINFO		*vi;
{
REG ULONG		*error;

error = &group->ghandle->lasterror;

vi->words [0] = IN_OBJ_CREATE;
vi->words [1] = 0;
vi->wordsused = 2;

if (ISFALSE (writevarinfo (block , &vi)))
	{
	goto error;
	}

offset += 2 * 2;

/* %
** 
** open [object-description-name] ....;
*/ 

if (ISFALSE (getname (group)))
	{
	goto noname;
	}

if (name->nd_type != NDT_OBJECT)
	{
	goto error;
	}

$

/* %
** 
** check for parenthesis
*/

if (ISFALSE (getname (group)))
	{
	goto noname;
	}

if (name->nd_type != NDT_SPECIAL)
	{
	goto syntaxerror;
	}

if (name->nd_subtype != NDS_BRAK1OP)
	{
	goto syntaxerror;
	}

$

/* %
** 
** get lists of attributes definition
*/

nds_create:;

if (ISFALSE (getname (group)))
	{
	goto noname;
	}

if (name->nd_type != $NDT_OBJATTR) /* here there can be an attribute  */
	{			   /* name or an unknown one	      */
	if (name->nd_type != $NDT_UNKNOWN)
		{
		goto syntaxerror;
		}
	
	}

$

/* %
** 
** gets the equal sign
*/

if (ISFALSE (getname (group)))
	{
	goto noname;
	}

if (name->nd_type != NDT_SPECIAL)
	{
	goto syntaxerror;
	}

if (name->nd_subtype != NDS_EQUAL)
	{
	goto syntaxerror;
	}


/* %
** 
** gets the equation that can follow
** 
*/ 

blockstart (block);

if (ISFALSE (getexpression (group, &comma, &brak1cl,$)))
	{
	goto syntaxerror;
	}

blockend (block);

/* %
** 
** checks how does expression ends
** 
*/ 

if (name->nd_subtype == comma.nd_subtype)
	{
	goto nds_create;
	}


syntaxerror:;
*error = EN_SYNTAX;
goto error;

noname:;
*error = EN_NONAME;

error:;
badend:;
return (FALSE);

end:;
return (TRUE);
}


/* # getanycall
** 
** 
*/ 

BOOL
getanycall (group, callname, type, curoffset, wblock) 
REG GROUP	*group;
REG NAME	*callname;
UWORD		 type;
WPTR		 curoffset;
BLOCK		*wblock;
{
REG WPTR	 offset;
VARINFO		 vi;

INIT_VI (&vi);

vi.vi_words [0] = type;
vi.vi_words [2] = 0;
vi.vi_wordsused = 3;

if (ISFALSE (writevarinfo (block, &vi)))
	{
	goto error;
	}

offset = curoffset;
offset += 3 * 2;
group->couple.cp_Small = offset;
offset -= 3 * 2;

var = (VAR *) wordtoptr (block, offset);

if (type == IN_ACTION) /* get action offset in block	*/
	{
	offset = ((ACTION *) (callname->nd_data))->ac_Offset;
	
	*var = offset;
	goto do_next;
	}

if (type == IN_FUNCTION)
	{
	offset = ((FUNCTION *) (callname->nd_data))->fun_offset;
	
	*var = offset;
	goto do_next;
	}

goto error;

do_next:;
var += 2;

if (name->nd_type != NDT_SPECIAL)
	{
	goto syntaxerror;
	}

if (name->nd_subtype != NDS_BRAK1OP)
	{
	goto syntaxerror;
	}

anyk:;

blockstart (block);

current->ti_CurOffset = offset;

if (ISFALSE (getexpression (group, block, &comma, &bracket, 0L)))
	{
	goto error;
	}

offset = current->ti_CurOffset;

if (name->nd_subtype = NDS_BRAK1CL)
	{
	blockend (block);
	goto end;
	}	

if (name->nd_subtype == NDS_COMMA)
	{
	* ((UWORD *) var) ++;
	
	goto anyk;
	}

syntaxerror:;
group->ghandle->lasterror = EN_SYNTAX;

error:;
badend:;
return (FALSE);

end:;
return (TRUE);
}
