/* 
** 
** 
** tony dee lists definition
** 
** 
*/ 

#ifndef	TONYLISTS_H
#define	TONYLISTS_H 1

#ifndef WSYSTEM_H
#include <wsystem.h>
#endif
#ifndef TONYEXTEND_H
#include <tonyextend.h>
#endif


/* # TonyNode
** # TNODE
** 
*/ 

#define	TNODE		struct TonyNode

struct TonyNode
{
TNODE		*tn_Next;
TNODE		*tn_Prev;
};


/* # TonyList
** # TLIST
** 
** 
*/ 

typedef struct TonyList
{
TNODE		*tl_First;
TNODE		*tl_Last;
} TLIST;

#define	TNSIZE		OBSIZE (TNODE)
#define	TLSIZE		OBSIZE (TLIST)
#define	MAKETL ()	Alloc (TLSIZE)
#define	MAKETN ()	Alloc (TNSIZE)

#define	NZ (x,y)		if (ISNOTZERO(x)) x = y

#define	ADDNEXT (n, x)	n->tn_Next = x
#define	ADDPREV (n, x)	n->tn_Prev = x
#define	ADDHEAD (l, x)	ADDPREV (l->tl_First, x); NZ (tl->First, x)
#define	ADDTAIL (l, x)	ADDNEXT (l->tl_Last, x); NZ (tl->Last, x)
#define	ENQUEUE		ADDTAIL
#define	FREE (l, n)	freenode (l, n)

/* 
** Warning: the FREE macro is corresponding to freenode,
** 	     a routine located in tonylists.c
** 
*/ 


/* # maphead
** # MAPH
** 
** about maps
** 
*/ 

	
typedef struct maphead
{
TLIST	mh_Maps;		/* map list chain			*/
UWORD	mh_ItemSize;		/* each map item size			*/
UWORD	mh_GlobalItems;		/* no of items available		*/
UWORD	mh_UsedItems;		/* no of used items			*/
UWORD	mh_EachMapItems;	/* items no contained by a single map	*/
} MAPH;


/* # listhead
** # LISTH
** 
*/ 

typedef struct listhead
{
TLIST	lh_List;
UWORD	lh_UsedItems;
} LISTH;


/* # strnode
** # STRNODE
** 
*/ 

typedef struct strnode
{
TNODE	 sn_Node;
UBYTE	*sn_String;
} STRNODE;


#endif
