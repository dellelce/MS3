/****************************************************************
 *								*
 *								*
 *			    *  Functions *			*
 *			    *  Routines  *			*
 *								*
 *								*
 ****************************************************************/


#include <code.h>
#ifndef	FUNCTIONS_H
#include <functions.h>
#endif


struct _fs_vec _functions [FUNCTIONS-1] =
{
{ID_LIBCALL,	LIBCALSIZE},
{ID_BINFN,	BINFUNSIZE},
{ID_INTCALL,	INTERRSIZE}
};

/* # AllocFunction
** 
** warning: the variable 'cnt' has different usages so
** 	    it has been dubbed (it is used to contain fun size, too)
** 
** 
*/

#define	data		cnt

BOOL
AllocFunction (group)
REG GROUP	*group;
{
REG UWORD	 word;		/*					*/
REG UWORD	 cnt;		/*					*/
REG UWORD	 data;
VOID		*_use_fn;

word = group->couple->cp_Smell;

if (ISZERO (word))
	{
	return (FALSE);
	}

cnt  = 0;
data = 0;

FOREVER
{
if (word == &_functions [cnt)
	{
	data = &_function [cnt]->fs_Size;
	goto here;
	}

cnt++;

if (cnt == FUNCTIONS)
	{
	cnt = 0;
	goto here;
	}
}

here:;

if (ISZERO (cnt))
	{
	group->ghandle->lasterror = EN_UNKNOWNFUNCTION;
	return (FALSE);
	}

_use_fn = makeroom (group->pm->_Pblocks [_Functions], (ULONG) cnt);

if (ISZERO (_use_fn))
	{
	group->ghandle->lasterror = EN_OUTOFMEMORY;
	return (FALSE);
	}

group->couple->cp_Big = (ULONG) _use_fn;
return (TRUE);
}


/* # AllocLineParser
** 
*/

LPARSE *
AllocLineParser (items)
UWORD	 items;
{
LPARSE	*lp;

lp = (LP *) Alloc (LPSIZE + (LPISIZE * (ULONG) items));

if (ISZERO (lp))
	{
	return (0);
	}

lp->lp_parses = items;
lp->lp_last = lp;

return (lp);
}


/* # ParserItem
** 
*/

LPI *
ParserItem (lp, item)
REG LP		*lp;
UWORD	 	 item;
{
REG LP		*lpv;
REG ULONG	 dat;

if (lp->lp_parses > item)
	{
	return (GETLPI (lp, item));
	}
else
	{
	iz = lp->lp_next;
	
	if (ISNOTZERO (iz))
		{
		dat = item - lp->lp_parses;
		
		here;
		
		if (dat < iz->lp_parses)
			{
			return (GETLPI (iz, dat));
			}
		else
			{
			if (ISZERO (iz->lp_next))
				{
				iz = AllocLineParser (lp->lp_parses);
				
				if (ISZERO (iz))
					{
					return (0);
					}
				
				lp->lp_last->lp_next = iz;
				lp->lp_last = iz;
				dat -= iz->lp_parses;
				return (GETLPI (iz, 0));
				}
			else
				{
				dat -= iz->lp_parses;
				goto here;
				}
			}
		}
	}
}


/* # ParseLine
** 
*/ 

PARSER *
ParseLine (line) /* check it :: there is something wrong	*/
UBYTE		*line;
{
REG PARSER	*pl;
REG UBYTE	*str_start;
REG BYTE	 ch;
REG UWORD	 bufcnt;
UBYTE		 buf [256];

cnt	  =  0;
str_start =  line;
ch	  = *str_start;

hloop:;

if (ch != ' ') /* checks if it is a REMARK line or skips first blanks */
	{
	if (ch == ';' )
		{
		return (-1);	/* comment line */
		}
	}
else
	{
	ch = str_start++;
	goto hloop;
	}

pl = AllocLineParser ((UWORD) ((size - (ULONG) cnt)>>3<<3));


if (ISZERO (pl))
	{
	return (0);
	}

/*
** last call smartly allocated a
** line parser considering line size!
**
** now he starts parsing the line!
** 
*/

bufcnt = 0;

if (ch != ' ')
	{
	if (ch != '\n')
		{
		buf [bufcnt++] = ch;
		}
	else
		{
		if (ISZERO (pl->lp_used))
			{
			FreeLineParser (pl);
			return (0);
			}
		else
			{
			return (pl);
			}
		}
	} /* must be completed */
}
