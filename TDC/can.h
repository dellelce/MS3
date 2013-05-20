/* tony dee © 1992
** 
** MS3 characters analyzing data
** 
*/ 


#ifndef CAN_H
#define CAN_H 1

#ifndef WSYSTEM_H
#include <wsystem.h>
#endif


#define	CT_NULL		33
#define	CT_UNKNOWN	 0
#define CT_CHUP		37
#define	CT_CHDOWN	38	
#define	CT_BLANK	32
#define	CT_NUMBER	39


EXTERN UBYTE	 _cts[255];

#define	ctype(x)	_cts[x]
#define	ispecial(x)	(ctype (x) < CT_BLANK || (x == 40))
#define	isnumber(x)	(ctype (x)  == CT_NUMBER)
#define	ischar(x)	((ctype (x) == 37) || (ctype (x) = 38))
#define	isblank(x)	(ctype (x)  == 32)
#define	ischarup(x)	(ctype (x)  == 37)
#define	ischardown(x)	(ctype (x)  == 38)
#define	isnull(x)	(ctype (x)  == 33)
#define	isinvalid(x)	(ctype (x)  == 33 || ctype (x) == 32 || ctype (x) == 0)

#endif
