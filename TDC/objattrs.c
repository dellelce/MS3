/* tony dee © 1992
** 
** object attributes handling code
** 
** 
** 
*/ 


#define	OBJATTRS_C	1


#include <objattrs.h>
#include <ms3fn.h>


/* # findobattr
** 
** should be used to find an object attribute
** 'object attributes names' (or TOKENs) are given back
** as UNKNOWNs (at least up to now), so you must use this
** routine to find out if it really an object attribute
** 
** TD REMARK: IT AIN'T A VERY GREAT THING... I SHOULD CHANGE IT SOMEWAY!
** 
*/ 

ATTR *
findobattr (group, attribute)
REG GROUP	*group;
UBYTE		*attribute;
{
REG ATTR	*attr;
REG ATTRLIST	*atlist;
REG UBYTE	*atname;

atname	= attribute;
atlist	= &group->ghandle.atlist;
attr	= (ATTR *) atlist->al_list.tl_First;

if (attr = (ATTR *) 0L)
	{
	goto error;
	}

next:;

if (ISTRUE (strcmp (attr->aa_AttrName, atname)))
	{
	goto end;
	}
else
	{
	attr = attr->aa_ArcNode.tn_Next;
	
	if (ISNOTZERO (attr))
		{
		goto next;
		}
	else
		{
		goto error;
		}
	}

end:;
return (attr);

error:;
return ((ATTR *) 0L);
}


/* # addobattr
** 
** function purpose is to add an object attribute 
** to object attributes list
** 
*/ 

BOOL
addobattr (group, _attr)
GROUP		*group;
ATTR		*_attr;
{
REG ATTRLIST	*atlist;
REG ATTR	*newattr;

atlist = &group->ghandle.atlist;
atlist->al_attributes++;

if (ISZERO (newattr = NEW_ATTR ()))
	{
	goto error;
	}

$Copy (_attr, newattr, ATTRSIZE);

ENQUEUE (atlist, _attr);
return (TRUE);

error:;
return (FALSE);
}
