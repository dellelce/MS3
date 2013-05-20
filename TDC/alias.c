/* tony dee © 1992
** 
** 
** 
*/ 


#include <logics.h>


/* # addalias
** 
** function must be completed...
** 
** 
*/ 

BOOL
addalias (group)
REG GROUP	*group;
{
REG NNODE	*nnode;

if (ISFALSE (getname (group)))
	{
	goto noname;
	}

if (name->nd_type != NDT_UNKNOWN)
	{
	goto $error;
	}

nnode = (NNODE *) FastAlloc (NNSIZE);

if (ISZERO (nnode))
	{
	$
	goto error;
	}

nnode->nn_Name.xn_Name.nd_data    = name->nd_data;
nnode->nn_Name.xn_Name.nd_type    = name->nd_type;
nnode->nn_Name.xn_Name.nd_subtype = name->nd_subtype;

if (ISFALSE (getname (group)))
	{
	goto error;;
	}

if (name->nd_type == NDT_CLOSER)
	{
	(NNODE *) (nnode))->nn_Name.xn_Name.nd_type = NDT_EMPTY;
	}

nnode->nn_Name.xn_Str = $; /* string to find obj.... */

if (ISFALSE (setitem (group->pmap, IT_ALIAS, 0, $$)))
	{
	goto nomemory;
	}
	
if (ISTRUE ($addname (group, nnode)))
	{
	end:;
	return (TRUE);
	}
else
	{
	error:;
	return (FALSE);
	}

}
