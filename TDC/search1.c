/* tony dee © 1992-1993
** 
** file version 0.02
** 
** this file is formed by routines taken
** from other file. All these routines
** purpose is to look for something.. (they must be completed)
** 
** 
** 
*/ 


/* %%
** findinlib
** findlabel
** 
** 
*/ 

#include <labels.h>
#include <logics.h>


/* # findinlib
** 
** 
** 
*/ 

ITEM *
findinlib (lib, name)
REG LIBRARY	*lib;
UBYTE		*name;
{
REG ITEM	*item = 0;

if (ISZERO (lib->lib_Directory))
	{
	lib->lib_Directory = loadblock (lib->lib_FileName, BT_LIBRARY);
	
	if (ISZERO (lib->lib_Directory))
		{
		return (0);
		}
	}

if (ISZERO (lib->lib_Str))
	{
	lib->lib_Str = loadblock (lib->lib_FileName, BT_WORKSTRINGS);
	
	if (ISZERO (lib->lib_Str))
		{
		return (0);
		}
	}
do
{
item = findinblock (lib->lib_Directory, lib->lib_Str, name);

if (ISNOTZERO (item))
	{
	goto end;
	}

lib = lib->lib_Next;
} while (ISNOTZERO (lib));

end:;
return (item);
}


/* # findlabel
** 
** td: ??-??-?? something is missing over here!
** td: 01-04-93 may be there is something wrong in args?
** 
*/ 

BOOL
findlabel (group, actname)
REG GROUP	 group;		
UBYTE		*actname;	/* may be it wrong? (labname)		*/
{
ULONG		 data;
LABEL		*label;


data = (ULONG) findindir (group->pm, actname);

if (ISZERO (data)))
	{
	goto error;
	}

if (((ITEM *) data)->di_type != IT_ACTION)
	{
	goto error;
	}
else			/* got the 'action' what do with it?	*/
	{
	}

group->couple.cp_Big	= (ULONG) label;
group->couple.cp_Small	= label->cl_LabelOffset;

end:;
return (TRUE);

error:;
badend:;
return (FALSE);
}
