/* tony dee © 1992
** 
** 
** error handling routines
** 
** 
*/ 

#ifndef WSYSTEM_H
#include <wsystem.h>
#endif
#ifndef GLOBALHANDLE_H
#include <globalhandle.h>
#endif
#ifndef ERRORS_H
#include <errors.h>
#endif
#ifndef	 TONYEXTEND_H
#include <tonyextend.h>
#endif



/* # typeerror
** 
** 
** should just type an error given its number
** 
** 
*/ 

UBYTE	 ret [] = "\n";

BOOL
typeerror (group)
REG GROUP	*group;
{
REG ULONG	 output;
REG UBYTE	*str;

if (group->ghandle.lasterror == 0)
	{
	goto error;
	}

output = group->ghandle.output;

if (ISZERO (output))
	{
	goto error;
	}

/* not so sophisticated..... I had some thoughts about it...	*/

str = __errors [group->ghandle.lasterror];

Write (output, "ERROR: (at line ", 17L);
__rawdumpnum (output, ((FH *) group->ghandle.fl->tl_Last)->lines);
Write (output, ") ", 3L);
Write (output, str, STRLEN (str));
Write (output, &ret, 2L);

return (TRUE);

error:;
return (FALSE);
}
