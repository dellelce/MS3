/* tony dee © 1992
** 
** object attributes archiving
** 
*/ 

#ifndef OBJATTRS_H
#define OBJATTRS_H 1

#ifndef WSYSTEM_H
#include <wsystem.h>
#endif
#ifndef TONYLISTS_H
#include <tonylists.h>
#endif

/* # obattrlist
** # ATTRLIST
** 
*/ 

typedef struct obattrlist
{
LISTH	 al_list;
ULONG	 al_attributes;
ULONG	 al_attrused;	/* update routines...				*/
$			/* what would be useful here?? FIND OUT SOON!!	*/
} ATTRLIST;


/* # attrarc
** # ATTR
** 
*/ 

#define	ATTRSIZE		OBSIZE (ATTR)
#define	NEW_ATTR ()		Alloc (ATTRSIZE)
#define	KILL_ATTR (x)		Free (x, ATTRSIZE)

typedef struct attrarc
{
STRNODE		 aa_ArcNode;
WPTR		 aa_AttrOffset;
WPTR		 aa_ObjOffset;
UBYTE		*aa_AttrName;
UBYTE		*aa_ObjName;		/* will it change to a word-ptr??     */
} ATTR;

/* 
** do you find them really useful?
** 
*/ 

#define	A_OFFSET (x)		(x->aa_AttrOffset)
#define	A_ATTRIBUTE (x)		(x->aa_AttrOffset)
#define	A_OBJECT (x)		(x->aa_ObjOffset)
#define	A_OBJNAME (x)		(x->aa_ObjName)
#define	A_ATTRNAME (x)		(x->aa_ArcNode.sn_String)
#define	A_NEXT (x)		(ATTR *) (x->aa_ArcNode.sn_Node.tn_Next)
#define	A_PREV (x)		(ATTR *) (x->aa_ArcNode.sn_Node.tn_Prev)

#endif
