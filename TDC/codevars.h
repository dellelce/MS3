/* tony dee © 1992
** 
** 
*/ 

#ifndef CODEVARS_H
#define CODEVARS_H
#ifndef WSYSTEM_H
#include <wsystem.h>
#endif


/*
** variable locations
**
*/

#define	VPD_STACKAREA	0x01	/* stack area variable		*/
#define	VPD_REGISTER	0x02	/* register located variable	*/
#define	VPD_LOCALSTAT	0x03	/* end of action loc'd vars	*/
#define VPD_GLOBALSTAT	0x04	/* end of hunk loc'd vars	*/


/* # CodeVariable
** # CODEVAR
** 
** size: 8
** 
*/ 

typedef struct CodeVariable
{
VAR	*cv_Variable;
WORD	 cv_VarOffset;
UBYTE	 cv_VarPlaceType;
UBYTE	 cv_Pad;
} CODEVAR;

#endif
