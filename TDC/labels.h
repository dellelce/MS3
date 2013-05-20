/* tony dee © 1992
** 
** labels manangement
** 
*/ 

#ifndef	LABELS_H
#define	LABELS_H		1

#ifndef	WSYSTEM_H
#include <wsystem.h>
#endif
#ifndef TONYLISTS_H
#include <tonylists.h>
#endif

/* # Hit
** # HIT
** 
*/ 

typedef struct Hit
{
BOOL	 hit_Size;	/* FALSE = byte TRUE = word (to change)	*/
UWORD	 hit_Offset;	/* label caller offset in code		*/
} HIT;

#define	HITSIZE		OBSIZE (HIT)


/* # CodeLabel
** # LABEL
** 
*/ 

typedef struct CodeLabel
{
TNODE	 cl_Node;		/* label list node			*/
STR	 cl_Name;		/* label name				*/
UWORD	 cl_LabelID;		/* label identifier			*/
WPTR	 cl_LabelOffset;	/* offset in code hunk or in block	*/
UWORD	 cl_Hits;		/* no of times obj is called..		*/
HIT	*cl_HitsBuffer;		/* previously and their locations	*/
} LABEL;

#define	CLSIZE		OBSIZE (LABEL)
#define	alloclab	(LABEL *) Alloc (CLSIZE)


#endif
