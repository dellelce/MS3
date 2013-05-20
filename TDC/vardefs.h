/* tony dee © 1992
** 
** definitions of structures regarding 'vars'
** handling
** 
** (vardefs.h, project TDL1) // should be joined with traslate.h
** 
** 
*/ 

#ifndef VARDEFS_H
#define VARDEFS_H		1


#ifndef WSYSTEM_H
#include <wsystem.h>
#endif
#ifndef	TONYEXTEND_H
#include <tonyextend.h>
#endif
#ifndef TONYLISTS_H
#include <tonylists.h>
#endif


/* # varu
** # VARU
** 
** the definition heart
** 
*/ 

typedef	UWORD	VAR;

typedef struct varu
{
VAR	 vardat [7];
} VARU;


/* # VLIST
** # VarList
** 
** variables data archiving
** 
*/ 

typedef struct VarList
{
TLIST	 vl_List;
PTR	 vl_LastFreed;
UWORD	 vl_Used;
UWORD	 vl_Room;
} VLIST;

#define	VLSIZE		OBSIZE (VLIST)

#define	VL_ROOM(x)	(x->vl_Room)
#define	VL_USED(x)	(x->vl_Used)
#define	VL_LASTFREED(x)	(x->vl_LastFreed)
#define	VL_FIRST(x)	(VNODE *) (x->vl_List.tl_First)
#define	VL_LAST(x)	(VNODE *) (x->vl_List.tl_Last)


/* # VNODE
** # VarListNode
** 
** 
*/ 

#define	VNODE		struct VarListNode

#define	vlh_First	tl_First
#define	vlh_Last	tl_Last

struct VarListNode
{
TNODE	 vln_ArcNode;
VAR	*vln_Variable;
BOOL	 vln_Type;		/* global or local		*/
UWORD	 vln_Id;		/* offset			*/
};


#define	VLN_NEXT(x)		(VNODE *) (x->vln_ArcNode.tn_Next)
#define	VLN_PREV(x)		(VNODE *) (x->vln_ArcNode.tn_Prev)
#define	VLN_TYPE(x)		(x->vln_Type)

#define	VNODESIZE		OBSIZE (VNODE)


/* # _work_var
** # WVAR
** 
** maybe replaced by TVAR structure (see it in trace.h>
** 
*/ 

#define	WVAR		struct _work_var
#define	WVSIZE		OBSIZE (WVAR)
#define	MAKE_WV()	Alloc (MVSIZE)
#define	KILL_WV(x)	Free (x, MVSIZE)

struct _work_var
{
VOID	*wv_def;	/* variable definition				*/
UBYTE	*wv_name;	/* its name					*/
BOOL	 wv_global;	/* TRUE if it is a global			*/
BOOL	 wv_static;	/* TRUE if it is static				*/
WPTR	 wv_lives;	/* first time used in the action		*/
WPTR	 wv_dies;	/* last time variable is used			*/
VOID	*wv_location;	/* ?? its location				*/
};


/* # VARINFO
** # _var_info
** 
** size: 18 bytes
** 
*/ 

#define	VARINFO			struct _var_info
#define	_VISIZE			sizeof (VARINFO)
#define	VISIZE			(ULONG) _VISIZE
#define	MAKE_VI()		FastAlloc (VISIZE)
#define	INIT_VI(x)		(x->vi_wordsused = 0)
#define	FREE_VI(x)		Free (x, VISIZE)
#define	AllocVIBlock(x)		Alloc (x * VISIZE)

struct _var_info
{
UWORD	 vi_wordsused;
union
{
struct _wordtable
{
UWORD	 vi_wtab0;
UWORD	 vi_wtab1;
UWORD	 vi_wtab2;
UWORD	 vi_wtab3;
UWORD	 vi_wtab4;
UWORD	 vi_wtab5;
UWORD	 vi_wtab6;
UWORD	 vi_wtab7;
};
UWORD	 vi_words[7];
} _in_vi;
};

#define _WORDS(x,y)	(x->_in_vi.vi_words [y])


/* # EXPRDATA
** # ExpressionData:	!!!!    I THINK IT IS USELESS	 !!!!
** 
** (it was thought to be) used to archive data about an expression...
** not removed since there could be some routine around 
** uses it....(what can be?)
** 
** 
*/

#define	EXPRDATA	 struct ExpressionData
#define	MAKE_EXPDAT()	 Alloc (OBSIZE (EXPRDATA))

struct ExpressionData
{
UWORD	 ed_names;
VOID	*ed_lastendname;	/* CAST would be needed...	*/
UWORD	 ed_vardefs;
UWORD	 ed_vdtotroom;
VARINFO	*ed_vardefdata;
};


/* needed for getexpression
** what is it for?
** 
** 
** 
*/ 

#define	VLT_GLOBAL		0x0001L
#define	VLT_LOCAL		0x0002L


#endif
