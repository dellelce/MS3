/* tony dee © 1992
** 
** MS3 language items management
** 
** %$% ---> (stands for) new feature
** 
**
*/

#ifndef ITEMS_H
#define	ITESM_H 1


#ifndef WSYSTEM_H
#include <wsystem.h>
#endif


/* # DirItem
** # ITEM
** 
** definitions for directory management
** 
*/ 

typedef struct DirItem	/* directory items descriptions			*/
{
USHORT	 di_type;	/* item type					*/
USHORT	 di_subtype;	/* item subtype - new feature, will it be used?	*/
WPTR	 di_str;	/* offset for working string			*/
WPTR	 di_def;	/* definition offset				*/
} ITEM;

#define	ITEMSIZE	OBSIZE (ITEM)
#define ITSIZE		ITEMSIZE

#define	IT_OBJECTDEF	0x0001
#define IT_ACTION	0x0002
#define	IT_FUNCTION	0x0003
#define IT_STRUCTUREDEF	0x0004
#define IT_GLOBALVAR	0x0005
#define	IT_SOURCE	0x0006
#define	IT_PRIVHANDLER	0x0007	/* we need 'di_subtype' for him		*/
#define	IT_ALIAS	0x0008	/* let compiler remember aliases (%$%)	*/
#define	IT_UNKNOWN	0x0009

/* 
** kinds of private handlers...
** 
*/ 

#define	IS_PHNORMAL	0x0000
#define	IS_PHSIMPLELIST	0x0001
#define	IS_PHCMPXLIST	0x0002

#define	ITEMS		8

#endif
