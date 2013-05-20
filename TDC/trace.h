/* tony dee © 1992
** 
** file release V0.07
** 
** code header extension
** 
*/ 

#ifndef	TRACE_H
#define	TRACE_H		1


#ifndef CODE_H
#include <code.h>
#endif
#ifndef LIBRARIES_H
#include <libraries.h>
#endif


/* %%	list of object contained in this file
** VTB
** ACTRC
** ATBOX
** ATBC
** TVAR
** TVV
** TVH
** TRCARGS
** 
** 
*/ 


/* types of objects traced...
** 
** 
*/ 

#define	LTT_ACTION	0x0000
#define	LTT_HANDLER	0x0001
#define	LTT_VARIABLE	0x0002


/* mode of traceing object %$% -- new feature!
** 
** 
*/ 

#define	LTM_NORMAL	0x0000
#define	LTM_ADDING	0x0001 /* add information to existing ones	*/


/* # vartracebuff
** # VTB
** 
** I think I will remove it
** 
*/ 

#define	VTB_STDSIZE		64

struct vartracebuff
{
PTR	*vbt_Next;
UWORD	 vbt_Used;
VT	 vbt_Buffer [VTB_STDSIZE];
} VTB;

#define	VBTSIZE		OBSIZE (VTB)
#define	MAKE_VBT()	FastAlloc (VTBSIZE)


/* # ActionTrace
** # ACTRC
** 
** action trace structure
** 
*/ 

typedef struct ActionTrace
{
UBYTE		*ac_Name;
VOID		*ac_Definition;
WPTR		 ac_Def;
WORD		 ac_StdArgs;
COUNT		 ac_CallsHit;
UWORD		 ac_Type;
LIB		*ac_Source;
} ACTRC;

#define	ATRACE			ACTRC
#define	ATSIZE			OBSIZE (ACTRC)

#define	ACTT_RAW		0x0000	/* not initialized	*/
#define	ACTT_ACTION		0x0001
#define	ACTT_FUNCTION		0x0002
#define	ACTT_UNKNOWN		0x0003

#define	ACTM_TYPE(x)		(x->ac_Type)
#define	ACTM_SETTYPE(x,y)	(x->ac_Type = y)
#define	ACTM_ARGS(x,y)		(x->ac_StdArgs = y)
#define	ACTM_NAME(x)		(x->ac_Name)
#define	ACTM_INCHIT(x)		(x->CallsHit ++)
#define	ACTM_HIT(x)		(x->CallsHit)
#define	ACTM_SMALLDEF(x)	(x->ac_Def)
#define	ACTM_BIGDEF(x)		(x->ac_Definition)


/* # ATBox
** # ATBOX
** 
** a single vector(-node) of 'traced actions(functions)'
** 
*/ 

typedef struct ATBox
{
TNODE		 atb_arcnode;
UWORD		 atb_acts;
UWORD		 atb_used;
} ATBOX;

#define	ATBOXSIZE		OBSIZE (ATBOX)


/* # ATBContainer
** # ATBC
** 
** 'action trace box container'
** 
** 
** 
*/ 

typedef struct ATBContainer
{
TLIST		atbc_list;
UWORD		atbc_total;
UWORD		atbc_known;
UWORD		atbc_unknown;
} ATBC;

#define	ATBCSIZE		OBSIZE (ATBC)


/* # trace_var
** # TVAR
** 
** to trace a variable, any variable.
** real, working definition
** 
** 
*/ 

typedef struct trace_var
{
VOID	*tv_Definition;	/* v:1 pointer to its definition	*/
WPTR	 tv_Place;	/* v:2 ?				*/
WPTR	 tv_Name;	/* v:3 var name				*/
WPTR	 tv_First;	/* v:4 first time met			*/
WPTR	 tv_Last;	/* v:5 last time met			*/
UWORD	 tv_Info;	/* v:6 what kind of var is it?		*/
COUNT	 tv_HitTimes;	/* v:7 no of times met			*/
LIB	*tv_Source;	/* v:8 if taken from a library		*/
} TVAR;

#define	TV_NAME(x)	(x->tv_Name)
#define	TV_INFO(x)	(x->tv_Info)
#define	TV_
#define	TV_
#define	TV_
#define	TV_

/*			 ****++++****++++				*/
#define	TVI_PLACEBIT	%0000000000000010	/* if LOCAL bit is ON	*/
#define	TVI_KNOWN	%0000000000000001	/* if KNOWN bit is ON	*/

#define	TV_ISLOCAL(x)	((x->tv_Info & TVI_PLACEBIT) == 0)
#define	TV_ISGLOBAL(x)	((x->tv_Info & TVI_PLACEBIT) != 0)
#define	TV_ISKNOWN(x)	((x->tv_Info & TVI_KNOWN) != 0)
#define	TV_ISUNKNOWN(x)	((x->tv_Info & TVI_KNOWN) == 0)



/* # tracevarvector
** # TVV
** 
** similar to ATBox, but this one
** archives variables
** 
*/ 

typedef struct tracevarvector
{
TNODE	 tvv_ArcNode;
UWORD	 tvv_Room;
UWORD	 tvv_Used;
} TVV;

#define	TVVSIZE		OBSIZE (TVV)

#define	TVV_NEXT(x)	(TVV *) (x->tvv_ArcNode.tn_Next)
#define	TVV_PREV(x)	(TVV *) (x->tvv_ArcNode.tn_Prev)
#define	TVV_ROOM(x)	(x->tvv_Room)
#define	TVV_USED(x)	(x->tvv_Used)


/* # tracevarheader
** # TVH
** 
** 
*/ 

typedef struct tracevarheader
{
TLIST	 tvh_List;
UWORD	 tvh_VecNum;
UWORD	 tvh_VarNum;
} TVH;

#define	TVH_FIRST(x)		(TVV *) (x->tvh_List.tl_First)
#define	TVH_LAST(x)		(TVV *) (x->tvh_List.tl_Last)
#define	TVH_VECNO(x)		(x->tvh_VecNum)
#define	TVH_VARNUM(x)		(x->tvh_VarNum)

#define	ISTHERANYVAR(x)		(x->ta_tvh->tvh_VarNum != 0)



/* # trace_args
** # TRCARGS
** 
** 
** 
*/ 

typedef struct trace_args
{
GROUP	*ta_group;
VOID	*ta_def;	/* object traced		*/
VAR	*ta_wstart;
VAR	*ta_wend;	/* mwy be removed!		*/
ATBC	*ta_atbc;	/* for action and handlers (..)	*/
TVH	*ta_tvh;	/* for variables		*/
UWORD	 ta_vardefs;
UWORD	 ta_type;
UWORD	 ta_mode;
} TRCARGS;

#define	TRACEARGS	TRCARGS
#define	TARGSSIZE	OBSIZE (TRACEARGS)

#endif
