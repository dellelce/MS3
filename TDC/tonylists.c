/****************************************************************
 *								*
 *								*
 *			This file will be used			*
 *		     together with tonylists.h in		*
 *		 the next release of The MS3 Compiler		*
 *								*
 *								*
 ****************************************************************/

#include <tonylists.h>

BOOL
freenode (l, n)
REG TLIST	*l;
REG TNODE	*n;
{
/*REG TNODE	*no; where has it gone??*/

if (ISZERO (l) && ISZERO (n))
	{
	return (FALSE);
	}

if (n == l->tl_First)
	{ 
	l->tl_First->tn_Prev = 0;
	l->tl_First = l->tl_First->tn_Next;
	return (TRUE);
	}

if (n == l->tl_Last)
	{
	l->tl_Last->tn_Next = 0;
	l->tl_Last = l->tl_Last->tn_Prev;
	return (TRUE);
	}

n->tn_Prev->tn_Next = n->tn_Next;
n->tn_Next->tn_Prev = n->tn_Prev;

return (TRUE);
}
