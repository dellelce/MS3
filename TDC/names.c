/* tony dee © 1992
** 
** name type access
** 
** 
*/ 


#ifndef	 NAMES_H
#include <names.h>
#endif
#ifndef	 CAN_H
#include <can.h>
#endif
#define	NAMES_C		1
#include <ms3fn.h>

/* %%
** getnametype
** delname
** createnb
** addname
** 
** 
*/ 


/* # getnametype
** 
** 7 pointers in REGs...
** 2 'non-pointing' variables in REGs... (give another look at this
** variable-placing, you 6 data REGs and 2 data REGs free...)
** 
** 
*/ 

VOID
getnametype (ghandle, pm, sn, na)
GHANDLE	 	*ghandle;
PMAP	 	*pm;
REG SNAME	*sn;
REG NAME	*na;
{
REG NAMEBASE	*nb;
REG BLOCK	*block;
REG NAME	*name;
REG VOID	*data;
REG UBYTE 	*filename;
REG UBYTE 	 byte;
REG UWORD	 count;		/* loops counter	*/
ITEM		*item;
PMAP		*pmap;
UWORD		 size;		/* name size		*/
UBYTE 		*str;		/* name string		*/

pmap = (PMAP *) Alloc (PMSIZE);

if (ISZERO (pmap))
	{
	goto end;
	}

size	=  sn->sn_Size;
str 	=  NAMESTR (str);
byte	=  ctype (str [0]);
count	=  0;
nb	=  ghandle->namebase;

/* %
** 
** initial control
** 
*/ 

if (ispecial (byte))				/* is it a special ?	*/
	{
	goto seespecial;
	}

if (ischar (byte))				/* is it a char	?	*/
	{
	goto seechar;
	}

if (byte == 33 || byte == 32 || byte == 0)	/* is it invalid ?	*/
	{
	return;
	}

/* %
** 
** checks the number kind
** 
*/ 

/* let's see what kind of number	*/

na->nd_type = NDT_NUMBER;

do	/* contiene il ciclo d'analisi del tipo di numero */
{
count++;
byte = str [count];

if (byte == '.')				/* a number met		*/
	{
	na->nd_subtype = NDS_FLOATING;		/* to improve		*/
	byte = str [count++];
	
	if (ctype (byte) != CT_NUMBER)
		{
		na->nd_type = NDT_ERROR;
		return;
		}
	return;
	}

if (byte == 'e' || byte == 'E')
	{
	na->nd_subtype = NDS_FLOATING;
	return;
	}

if (count == size)	/* WARNING: something wrong here!	*/
	{
	return;
	}

if (byte == 0x00)	/* qui c'e' qualcosa di sbagliato	*/
	{
	return;
	}
} while ();		/* $ TO MODIFY (HOW??)			*/

/* %
** 
** checks the kind of special it is
** 
*/ 

seespecial:;

na->nd_type	=	NDT_SPECIAL;	/* sets NDT_SPECIAL	*/
					/* to speed up things	*/

if (byte > 9)
	{
	goto switch1;
	}

switch (byte)	/* HERE THINGS WILL BE SURELY MODIFIED	*/
{
case    1:	/* '!'	*/
	
	na->nd_subtype  =  NDT_EXCLAMATION;
	
	if (str [1] == '=')
		{
		na->nd_type	=  NDT_RESWORD;
		na->nd_subtype	=  NDS_NOTEQUAL;
		return;
		}
	
	return;
	
case	3:	/* '#'	*/
	
	na->nd_subtype  =  NDS_DIESIS;
	return;
	
case    4:	/* '$' = hexdecimal */
	
	na->nd_type	 = NDT_NUMBER;
	na->nd_subtype = NDS_HEX;
	return;
	
case    5:	/* '%' = binary     */
	
	na->nd_type	 = NDT_NUMBER;
	na->nd_subtype = NDS_BINARY;
	return;
	
case    7:	/* '/'' */
	
	break;	/* WHAT'S UP HERE? */
	
case    8:	/* '('	*/
	
	na->nd_subtype = NDS_BRAK1OP;
	return;
	
case	9:	/* ')'	*/
	
	na->nd_subtype = NDS_BRAK1CL;
	return;
}

switch1:;

if (switch < 19)
	{
	goto switch2;
	}

switch (byte)
{
case   10:	/* '*'	*/
	
	na->nd_subtype  =  NDS_MULTIPLY;
	return;
	
case   11:	/* '+'	*/
	
	na->nd_subtype  =  NDS_ADD;
	return;
	
case   12:	/* ','	*/
	
	na->nd_subtype  =  NDS_COMMA;
	return;
	
case   13:	/* '-'	*/
	
	na->nd_subtype  =  NDS_SUBTRACT;
	return;
	
case   14:	/* '.'					*/
		/* checks if a floating (such as .77)	*/
	
	byte = ctype (str [1]);
	
	if (byte != CT_NUMBER)
		{
		if (isnull (str [1]))
			{
			na->nd_subtype = NDS_PERIOD;
			return;
			}
	else
		{
		na->nd_type    = NDT_ERROR;
		return;
		}
	}
  else
	{
	na->nd_type	=  NDT_NUMBER;
	na->nd_subtype  =  NDS_FLOATING;
	return;
	}

case   15:	/* '/'	*/

	na->nd_subtype  =  NDS_DIVIDE;
	return;

case   16:	/* ':'	*/

	na->nd_subtype  =  NDS_SUBTRACT;
	return;

case   17:	/* ';' = closer     */

	na->nd_type	 = NDT_CLOSER;
	return;

case   18:	/* '<'	*/

	if (str [1] == '<')
		{
		na->nd_type	=  NDT_RESWORD;
		na->nd_subtype	=  NDS_SHIFTR;
		return;
		}
	
	if (str [1] == '=')
		{
		na->nd_type	=  NDT_RESWORD;
		na->nd_subtype	=  NDS_EQMINOR;
		return;
		}
	
	na->nd_subtype = NDS_MINOR;
	return;

case   19:	/* '=' */

	if (str[1] == '=')	/* '==' */
		{
		na->nd_type	=  NDT_RESWORD;
		na->nd_subtype	=  NDS_ISEQUAL;
		return;
		}
	
	if (str [1] == '>')
		{
		na->nd_type	=  NDT_RESWORD;
		na->nd_subtype	=  NDS_EQMAJOR;
		return;
		}
	
	if (str [1] == '<')
		{
		na->nd_type	=  NDT_RESWORD;
		na->nd_subtype	=  NDS_EQMINOR;
		return;
		}
	 
	na->nd_subtype = NDS_EQUAL;
	return;
}

switch2:;

switch (byte)
{
case   20:	/* '>'	*/

	if (str [1] == '>')	/* '>>' */
		{
		na->nd_type	=  NDT_RESWORD;
		na->nd_subtype	=  NDS_SHIFTL;
		return;
		}
	
	if (str [1] == '=')	/* '>='	*/
		{
		na->nd_type	=  NDT_RESWORD;
		na->nd_subtype	=  NDS_EQMAJOR;
		return;
		}
	
	na->nd_subtype = NDS_MAJOR;
	return;

case   21:	/* '?'	*/

	na->nd_subtype  =  NDS_QUESTION;
	return;
	
case   22:	/* '['	*/
	
	na->nd_subtype  =  NDS_BRAK2OP;
	return;
	
case   23:	/* '\'	*/
	
	na->nd_subtype  =  NDS_BACKSLASH;
	return;
	
case   24:	/* ']'	*/
	
	na->nd_subtype  =  NDS_BRAK2CL;
	return;
	
case   25:	/* '^'	*/
	
	na->nd_subtype  =  NDS_EXOR;
	return;
	
case   26:	/* '_'	*/
	
	na->nd_subtype  =  NDS_UNDERLINE;
	return;
	
case   29:	/* '|'	*/
	
	if (str[1] == '|')	/* '||' */
		{
		na->nd_type	=  NDT_RESWORD;
		na->nd_subtype	=  NDS_LOGICOR;
		return;
		}
	
	na->nd_subtype = NDS_OR;
	return;
	
case   31:	/* '~'	*/
	
	na->nd_subtype = NDS_WAVE;
	return;
	
default:

	na->nd_type	 = NDT_ERROR;
	return;

} /* TO COMPLETE AND FIX! **/


/* %
** 
** checks if an internal
** 
*/ 

seechar:;	/* first is character */

/* let's check if it is an internal */

name = findname (&gb, str);

if (ISZERO (name))
	{
	goto next1; /* not an internal */
	}

na->nd_data	=	name->nd_data;
na->nd_type	=	name->nd_type;
na->nd_subtype	=	name->nd_subtype;

goto end;

/* %
** 
**  CHECKS IF A GLOBAL, A FUNCTION OR AN ACTION
** 
*/ 

next1:;	/* let's check if a global or a function or else	*/

item = findindir (pm, str);

if (ISZERO (item))
	{
	goto next2;	/* last chance! */
	}

if (item->di_type == IT_OBJECTDEF)
	{
	na->nd_data  =	OBJECT (pm, item->di_def);
	na->nd_type  =  NDT_OBJECT;
	goto end;
	}

if (item->di_type == IT_ACTION)
	{
	na->nd_data  =  ACTION (pm, item->di_def);
	na->nd_type  =	NDT_ACTION;
	goto end;
	}

if (item->di_type == IT_FUNCTION)
	{
	na->nd_data  =	STRUCTURE (pm, item->di_def);
	na->nd_type  =  NDT_STRUCTURE;
	goto end;
	}

if (item->di_type == IT_GLOBALVAR)	/* TO BE CHECKED */
	{
	na->nd_data  =	GETGLOBAL (pm, item->di_def);
	na->nd_type  =  NDT_GLOBAL;
	goto end;
	}

/* %
** 
** LOOKS IN LIBRARIES (called by 'source' keyword)
** ...this still just an example piece of code.....
** 
** 
*/ 

next2:;

lib = ((PROENV *) ghandle->environment)->pe_NameBase->nd_NamesLibrary;

filename = lib->lib_FileName;	/* <- <- 'filename' var may be removed	*/

item = findinlib (filename, str);

if (ISZERO (item))
	{
	goto next3;
	}

switch (item->di_type)
	{
	case	IT_OBJECTDEF:
		
		if (ISZERO (pmap->Pblocks[_Objects]))
			{	
			block = loadblock (filename, BT_OBJECT);
			pmap->Pblocks[_Objects] = block;
			}
		else
			{
			block = pmap->Pblocks[_Objects];
			}
		
		na->nd_data = POBJECT (block, item->di_def);
		na->nd_type = NDT_OBJECT;
		goto end;

	case IT_ACTION:

		if (ISZERO (pmap->Pblocks[_Actions]))
			{
			block = loadblock (filename, BT_ACTION);
			pmap->Pblocks[_Actions] = block;
			{
		else
			{
			block = pmap->Pblocks[_Actions];
			}
		
		na->nd_data = PACTION (block, item->di_def);
		na->nd_type = NDT_ACTION;
		goto end;

	case IT_FUNCTION:

		if (ISZERO (pmap->Pblocks[_Functions]))
			{
			block = loadblock (filename, BT_FUNCTION);
			pmap->Pblocks[_Functions] = block;
			}
		else
			{
			block = pmap->Pblocks[_Functions];
			}
		
		na->nd_data = PFUNCTION (block, item->di_def);
		na->nd_type = NDT_FUNCTION;
		goto end;

	case IT_GLOBALVAR:

		if (ISZERO (pmap->Pblocks[_Globals]))
			{
			block = loadblock (filename, BT_GLOBAL);
			pmap->Pblocks[_Globals] = block;
		else
			{
			block = pmap->Pblocks[_Globals];
			}
		
		na->nd_data = PGLOBAL (block, item->di_def);
		nd->nd_type = NDT_GLOBAL;
		goto end;

	case IT_STRUCTUREDEF:
	
		if (ISZERO (pmap->Pblocks[_Structures]))
			{
			block = loadblock (filename, BT_STRUCTURE);
			pmap->Pblocks[_Structure] = block
			}
		else
			{
			block = pmap->Pblocks[_Structures];
			}
		na->nd_data = PSTRUCTURE (block, item->di_def);
		nd->nd_type = NDT_STRUCTURE;
		
		goto end;	
	} /* closes SWITCH.... */


/* %
** 
** CHECKS IF A LOCAL
** 
*/ 

next3:;

data = (VOID *) ((PROENV *) ghandle->environment)->pe_Object->ti_Locals;

data = findinvlist (pm, lox, name); /* STILL TO BE DEFINED */

if (ISZERO (data))
	{
	goto unknown;
	}

na->nd_type	=  NDT_LOCAL;
na->nd_data	=  var;
return;

/* %
** 
** it is an unknown kind of name!
** 
*/ 

unkown:;

na->nd_type	=  NDT_UNKNOWN;
na->nd_data	=  str;
end:;

if (ISNOTZERO (pmap))
	{
	deletepmap (pmap);
	}
}	/* IT IS OVER ! **/


/* # delname
** 
*/ 

VOID
delname (name)
REG NAME *name;
{
FreeMem (name, NASIZE));
} /* THIS ROUTINE GOTTA BE FIXED AND/OR CHANGED TO A MACRO */


/* # createnb
** 
** thats a too big name for a less worthy function
** 
*/ 

EXTERN NAMEVEC  *internals [25];
EXTERN UWORD	 names;

BOOL
createnb (ghandle)
GHANDLE		*ghandle;	/* don't need to go to a register since	*/
{				/* only once used			*/
REG NAMEBASE	*nb;

nb = Alloc (NBSIZE);

if (ISZERO (nb))
	{
	return (FALSE);
	}

nb->nb_NameVec	  = &internals [0];
nb->nb_NamesInVec = names;

ghandle->namebase = nb;

return (TRUE);
}


/* # addname
** 
** add information about a 'name' (alias a 'token') to the database.
** needed to remember for example a variable definition or other......
** 
** it may be turned easily in assembly, I think....
** 
** 
*/ 

VOID
addname (group, na)
GROUP		*group;
REG NNAME	*na;
{
REG NLIST	*nlist;

na->xn_NSSize = (UWORD) strlen (na->xn_NameStr); /* now introducing..	*/

nb = group->ghandle.namebase->nb_NameList;

nlist = nb->nb_NameList;

ENQUEUE (nlist->nlh_Archiver, na);
nlist->nlh_Count ++;
}
