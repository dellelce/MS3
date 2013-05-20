/* 
** special chars definitions
** definition will be used 'getname' function!
** 
** =  <- expression equal
** == <- 'if'-fy equal
** 
*/ 

#ifndef  WSYSTEM_H
#include <wsystem.h>
#endif

/* # subspecial
** # SUBSPEC
** 
*/ 

struct subspecial
{
UBYTE	id;
WORD	type;
ULONG	subtype;
};

#define	SUBSPEC		struct subspecial


/* # special
** # SPEC
** 
*/ 

struct special
{
UBYTE	 id;		/* identifies the special char		*/
ULONG	 subtype;	/* 'type' here will not be used!	*/
SUBSPEC	*subs;		/* sub-special types			*/
UWORD	 no;
};

#define	SPEC		struct special


/* # speccase
** # SPCASE
** 
*/ 

struct speccase
{
UWORD	 specs;
SPEC	*spex;
};

#define	SPCASE		struct speccase
