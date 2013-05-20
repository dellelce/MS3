/* tony dee © 1992
** 
** MS3 errors handling
** 
** 
*/ 

#ifndef	ERRORS_H
#define	ERRORS_H  1

#ifndef	 TONYEXTEND_H
#include <tonyextend.h>
#endif


/*
** Specific error kinds
**
*/

#define	EN_NOMEMORY		0x0000	/* run out of memory		*/
#define	EN_NOPMAPFILE		0x0001	/* file has not a processmap	*/
#define	EN_NONAME		0x0002	/* did not get any name		*/
#define	EN_KNOWNNAME		0x0003	/* names found already known	*/
#define	EN_SYNTAX		0x0004  /* simple syntax error		*/
#define	EN_NOOPEN		0x0005	/* can not open file		*/
#define	EN_IOERROR		0x0006	/* disk i/o error		*/
#define	EN_NOTTFFFILE		0x0007	/* file is not Tony Format	*/
#define	EN_UNKNOWNNAME		0x0008	/* name is not known		*/
#define	EN_NAMEUSE		0x0009	/* illegal name use		*/
#define	EN_UNKNOWNFUNCTION	0x000A	/* unknwon function type	*/
#define	EN_INTERNALALLOC	0x000B	/* failing in internal alloc	*/
#define	EN_NOROOM		0x000B	/* failing in internal alloc	*/
#define	EN_NOCLOSER		0x000C	/* couldn't find closer!	*/
#define	EN_INVNAMETYPE		0x000D	/* invalid name type		*/
#define EN_ILLRESWUSE		0x000E	/* $I don't rem. much of it!!	*/
#define	EN_NOSTARTER		0x000F	/* pmap doesn't have the starter*/
#define	EN_STRANGE		0x0010	/* strange; it shouldn't happen!*/
#define	EN_INITERR		0x0011	/* tried to init a structure	*/
#define	EN_PMOPAVAIL		0x0012	/* operators not available	*/
#define	EN_ILLKNOWN		0x0013	/* token already known		*/

#define ERRNO			19

/*
** Error strings
**
*/

#define	ES_NOMEMORY	  "out of memory"
#define	ES_FILEOPEN	  "could not open file"
#define	ES_NONAME	  "did not get name!"
#define	ES_SYNTAX	  "wrong syntax"
#define	ES_IOERROR	  "disk i/o error"
#define	ES_NOTFFFILE	  "file is not a Tony Format File"
#define	ES_NOTPMAPFILE    "file does not contain a Process Map"
#define	ES_KNOWNNAME	  "name already exists"
#define	ES_UNKNOWNNAME	  "name does not exist"
#define	ES_NOSOURCE	  "could not find source file"
#define	ES_NAMEUSE	  "illegal name use"
#define	ES_EXECUTED	  "operation on ProcessMap already executed"
#define	ES_UNKOWNFUNCTION "function type not known"
#define	ES_INTERNALALLOC  "failed allocating object in ready memory"
#define	ES_NOCLOSER	  "could not find line closing character (;)!"
#define	ES_NOSTARTER	  "program doesn't have the starter"
#define	ES_STRANGE	  "a strange error happened"
#define	ES_INITERR	  "structures definitions cannot be initizialed"
#define	ES_PMOPNOTAVAIL	  0 /* it does not have a string....	*/
#define	ES_ILLKNOWN	  "object must not be already known!"


/*
** Warnings
*/

#define	WARN_NUMBERLESS		0x0000
#define	WARN_SHORTMEMORY	0x0001
#define WARN_LASTSTANDARD	WARN_SHORTMEMORY
/*#define	WARN_NOMEMORY		future!!	*/


/*
** warning strings
*/

#define	WS_TOOARGS	"too many arguments passed to the action or function"
#define	WS_INVALIDARG	"argument is not valid for the function/action"
#define	WS_FORGOTTEN	"object has been already forgotten"


EXTERN UBYTE	*__errors [ERRNO];

#endif
