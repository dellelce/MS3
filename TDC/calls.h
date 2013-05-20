/* tony dee © 1992
** 
** I put definitions about 'CALLs'
** and 'CALLBOXes' because I don't remember
** well what are theirs purpose, so they 
** can be killed very easily
** 
** 
*/ 

#ifndef CALLS_H
#define CALLS_H		1
#ifndef WSYSTEM_H
#include <wsystem.h>
#endif
#ifndef TONYEXTEND_H
#include <tonyextend.h>
#endif


/* # Call
** # CALL
** 
** please help me about understand it...
** 
*/ 

typedef struct Call
{
UWORD	 call_Type;		/* act/fun/unknown		*/
UBYTE	*call_Name;		/* to look around for it!	*/
WPTR	 call_Offset;		/* offset in action		*/
WPTR	 call_CalledObject;
} CALL;

#define	CALLSIZE		OBSIZE (CALL)
#define	NEXTCALL(x)		(CALL *) NEXT (x, CALL)


/* # CallBox
** # CBOX
** 
*/ 

#define CBOX			struct CallBox

struct CallBox
{
UWORD	 cb_BoxCalls;
UWORD	 cb_UsedCalls;
CBOX	*cb_Next;
};

#define	CBOXSIZE		OBSIZE (CBOX)
#define	FIRSTCALL(x)		(CALL *) ((ULONG) x + CBOXSIZE)

#define	STDCALLSNO		20L
#define	STDBOXSIZE		(CBOX + STDCALLSNO * CALLSIZE)


#endif
