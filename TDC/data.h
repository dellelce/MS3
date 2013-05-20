/* tony dee © 1992
** 
** 
*/ 

#ifndef DATA_H
#define	DATA_H 1


#ifndef	 TONYLISTS_H
#include <tonylists.h>
#endif
#ifndef	 WSYSTEM_H
#include <wsystem.h>
#endif

/* # BufName
** # BNAME
** 
*/ 

typedef struct BufName
{
UBYTE	*bf_Name;
ULONG	 bf_Size;
} BNAME;

#define	BNSIZE		OBSIZE (BNAME)


/* # FileBuf
** # FB
** 
*/ 

typedef struct FileBuf
{
TNODE	 fb_Node;	/* ownership list			*/
TLIST	*fb_ArcHead;	/* 					*/
TLIST	*fb_BufPieces;	/* other buffers pieces list		*/
BNAME	*fb_Name;	/* FileBuf name				*/
UBYTE	*fb_Buffer;	/* this one buffer			*/
ULONG	 fb_Size;	/* its size				*/
ULONG	 fb_TotSize;	/* total size: included bufpieces	*/
ULONG	 fb_LastUsed;	/* last byte used			*/
ULONG	 fb_CurrentLoc;	/* the current location			*/
} FB;

#define	FBSIZE			OBSIZE (FB)

#define	FBM_VERYSMALL		0x0001
#define	FBM_SMALL		0x0002
#define	FBM_ITERMEDIATE		0x0004
#define	FBM_BIG			0x0008
#define	FBM_VERYBIG		0x0016


/*
** Print modes
**
*/

#define	FBM_STRING		0x0000
#define	FBM_SHORT		0x0001
#define	FBM_USHORT		0x0002
#define	FBM_LONG		0x0003
#define	FBM_ULONG		0x0004


/* # CL
** 
*/ 

typedef union
{
UWORD	wd[1];		/* two words				*/
ULONG	lonn;		/* one long				*/
} CL;

#endif
