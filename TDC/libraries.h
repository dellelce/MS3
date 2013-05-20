/* tony dee © 1992
** 
** file release v0.01
** 
** 
*/ 

#ifndef	LIBRARIES_H
#define	LIBRARIES_H	1


#ifndef WSYSTEM_H
#include <wsystem.h>
#endif
#ifndef TONYEXTEND_H
#include <tonyextend.h>
#endif


typedef struct library
{
PMAP		*lib_ProcMap;
UBYTE		*lib_Name;
UWORD		*lib_Hits;
} LIB;

#define	LIBSIZE		OBSIZE (LIB)

#define	LIB_PROCMAP(x)	(x->lib_ProcMap)
#define	LIB_NAME(x)	(x->lib_Name)
#define	LIB_HITS(x)	(x->lib_Hits)
#define	LIB_
#define	LIB_


typedef struct libraryvec
{
TNODE		 lv_ArcNode;	/* optional use		*/
PTR		*lv_Head;	/* optional use		*/
LIB		*lv_Vector;
UWORD		 lv_Used;
UWORD		 lv_Total;
} LIBVEC;

#define	LVECSIZE		OBSIZE (LIBVEC)

#define	LV_NEXT(x)	(LIBVEC *) (x->lv_ArcNode.tn_Next)
#define	LV_PREV(x)	(LIBVEC *) (x->lv_ArcNode.tn_Prev)
#define	LV_HEAD(x)	(x->lv_Head)
#define	LV_USED(x)	(x->lv_Used)
#define	LV_TOTROOM(x)	(x->lv_Total)
#define	LV_FIRSTUSED(x)	(x->lv_Vector)
#define	LV_LASTUSED(x)	(LV_FIRSTUSED (x) + (LIB *) ((LV_USED (x)--) * LIBSIZE))
#define	LV_ROOM(x)	(LV_TOTROOM (x) - LV_USED (x))
#define	LV_
#define	LV_
#define	LV_


typedef struct _sourcedirs
{
UBYTE		*sd_dir;
ULONG		 sd_lock;
ULONG		 sd_count;
} SD;

#define	SD_DIR(x)	(x.sd_dir)
#define	SD_LOCK(x)	(x.sd_lock)
#define	SD_COUNT(x)	(x.sd_count)


#endif
