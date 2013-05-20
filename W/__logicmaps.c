/* tony dee © 1992
** 
** logicmaps code
** 
** see file '_fut_logicmaps.h' header for more information
** 
** 
*/ 

#include <logicmaps.h>


BOOL
performlmap (master)
MASTER		*master;
{
REG GROUP	*group;
REG LMAP	*lmw;
REG LMAP	*lmap;
NAME		*name;

lmap	= master->m_current;
group	= master->m_group;
lmw	= lmap;
name	= group->name;


next:;

do
{
if (*lmw > BOUNDARY)
	{
	goto overbound;
	}

switch (*lmw)		/* I think in the final release will not	*/
{			/* be used a 'switch'				*/
case	_NEWLMAP:




case	_SKIPLINE:

if (ISFALSE (getname (group)))
	{
	goto noname;
	}

if (name->nd_type != NDT_CLOSER)
	{
	goto syntaxerror;
	}

goto next;

default:
	
	goto $error;
	
}

overbound:;

$

NEXTLMAP (lmw);
} while (*lmw != LOGICNULL);

end:;
return (TRUE);

syntax:;
group->ghandle->lasterror = EN_SYNTAX;
goto error;

noname:;
group->ghandle->lasterror = EN_NONAME;

error:;
return (FALSE);
}
