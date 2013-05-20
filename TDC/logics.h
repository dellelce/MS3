/* @@ 1990-92 TDC logics header v3.44
** 
** developing by tony dee
** all rights reserved
** 
** OTHERS UPDATES...
** done a lot of work over it!
** 
** Thu Dec 24 1992	** UPDATE **
** simple restyle.
** 
** (logics.h, project TDL1)
** 
*/ 

#ifndef LOGICS_H
#define	LOGICS_H 1

#ifndef	 WSYSTEM_H
#include <wsystem.h>
#endif
#ifndef	 TONYEXTEND_H
#include <tonyextend.h>
#endif
#ifndef	 ITEMS_H
#include <items.h>
#endif
#ifndef	 BLOCKS_H
#include <blocks.h>
#endif
#ifndef  VARIABLES_H
#include <variables.h>
#endif
#ifndef	 INTERNALS_H
#include <internals.h>
#endif
#ifndef	 TONYF_H
#include <tonyf.h>
#endif
#ifndef	 MAGICS_H
#include <magics.h>
#endif
#ifndef	 CALLS_H
#include <calls.h>
#endif

#define	USE_IN_MS3	TRUE

/* %%
** ASTAT
** ACTION
** OBJECT
** SSTACK
** TITEM
** PROENV
** CALLINFO
** COUPLE
** GROUP
** 
** 
*/ 


/* # ActionStatistics
** # ASTAT
** 
** aXrefs		-->		access references
** 
*/ 

#define	aXrefs			Calls

typedef struct ActionStatistics
{
USHORT	 as_StringCalls;
USHORT	 as_ObjectCalls;
USHORT	 as_StructureCalls;
USHORT	 as_FunctionCalls;
USHORT	 as_ActionCalls;
USHORT	 as_Labels;
USHORT	 as_LocalVariables;
USHORT	 as_StreamCalls; 	/* yet unused!!			*/
UWORD	 as_UnkownVars;		/* unknown variables		*/
UWORD	 as_UnkownCalls;	/* unknown calls		*/
} ASTAT;

/* access by macros for ASTAT
** 
** 
*/ 

#define	ASI_STRINGSNO(x)	(x->as_StringaXrefs)
#define	ASI_OBJECTSNO(x)	(x->as_ObjectaXrefs)
#define	ASI_STRUCTURESNO(x)	(x->as_StructureaXrefs)
#define	ASI_FUNCTIONSNO(x)	(x->as_FunctionaXrefs)
#define	ASI_ACTIONSNO(x)	(x->as_ActionsaXrefs)
#define	ASI_LABELS(x)		(x->as_Labels)
#define	ASI_LOCVARSNO(x)	(x->as_LocalVariables)
#define	ASI_STREAMSNO(x)	(x->as_StreamaXrefs)
#define	ASI_UNKNOWNVARS(x)	(x->as_UnkownVars)
#define	ASI_UNKNOWNCALLS(x)	(x->as_UnknownCalls)


/* # Action
** # ACTION
** 
** check well from item ac_Locals to ac_Code
** 
*/ 

typedef	struct Action
{
MAGICW	 ac_Magic;		/* identifier			*/
SHORT	 ac_Type;		/* ghost, fetched or normal	*/
ULONG	 ac_ActionSize;		/* room used in block		*/
WPTR	 ac_Name;		/* action name			*/
USHORT	 ac_Args;		/* number of args		*/
ASTAT	 ac_Data;		/* statistics			*/
WPTR	 ac_Offset;		/* what's its offset in block?	*/
UWORD	 ac_Locals;		/* $size of locals ..		*/
UWORD	 ac_Globals;		/* $size of globals ..		*/
UWORD	 ac_LocalStatics;	/* $size of static locals ..	*/
UWORD	 ac_Code;		/* process data offset end	*/
BOOL	 ac_ArgOut;		/* is there the arg out?	*/
VARU	 ac_ArgDes;		/* arg out description		*/
} ACTION;

#define	NEXTACTION(x)		(x->ac_Offset + x->ac_ActionSize)
#define	ISANACTION(x)		((* (UWORD *) x) == MAGIC_ACTION)

#define	AT_GHOST		-2
#define AT_FETCHED		-1
#define AT_NORMAL		 0

#define	ACTSIZE			OBSIZE (ACTION)


#ifndef	PROCMAP_H		/* why here?	*/
#include <procmap.h>
#endif


/*
** Basic object definitions (??)
**
*/

#define	HANDLER		USHORT


/* 
** Handlers numbers offsets
** (there are 26 slots free for private handlers!)
** 
*/

#define	AN_OPEN		0
#define	AN_CLOSE	1
#define	AN_CREATE	2
#define	AN_DELETE	3
#define	AN_MODIFY	4
#define	AN_ASK		5


/*
** Bit definition
**
*/

#define	AB_OPEN		(1 << AN_OPEN)
#define	AB_CLOSE	(1 << AN_CLOSE)
#define	AB_CREATE	(1 << AN_CREATE)
#define	AB_DELETE	(1 << AN_DELETE)
#define	AB_MODIFY	(1 << AN_MODIFY)
#define	AB_ASK		(1 << AN_ASK)


/* # Object
** # OBJECT
** 
*/ 

typedef struct Object
{
MAGICW		ob_Magic;	/* structure identifier		*/
WPTR		ob_Name;	/* object def name		*/
UWORD		ob_ObjectSize;	/* room used in block		*/
WPTR		ob_Offset;	/* offset in block -- NEEDED!!	*/
USHORT		ob_Type;	/* object type			*/
USHORT		ob_Attributes;	/* attributes no.		*/
USHORT		ob_RealAttr;	/* points 'real attribute'	*/
USHORT		ob_AttrWords;	/* attributes size in words	*/
ULONG		ob_Handlers;	/* handlers			*/
USHORT		ob_StaticData;	/* size of statics		*/
USHORT		ob_LocalData;	/* size of locals		*/
USHORT		ob_Globals;	/* size of global vars		*/
ASTAT		ob_Statistics;	/* action statistics		*/
} OBJECT;

#define	OBJSIZE			OBSIZE (OBJECT)
#define	NEXTOBJECT(p,x)		_OBJECT (p, (x->ob_Offset + x->ob_ObjectSize))


/*
** object types
*/

#define	OT_REAL		0x0001
#define	OT_UNREAL	0x0002


/* # StatusStack
** # SSTACK
** 
*/

#define	ST_FOR		0x0000
#define	ST_DO		0x0001
#define	ST_WHILE	0x0002
#define	ST_IF		0x0003
#define	ST_SWITCH	0x0004

#define	STYPES		ST_SWITCH + 1

#define	SSTACK		struct StatusStack

struct StatusStack
{
SSTACK		*ss_Next;
UWORD		 ss_Each;
WPTR		*ss_Buffers [STYPES];
UWORD		 ss_Used [STYPES];
UWORD		 ss_LastOffset [STYPES];
};

#define	STATUS			USHORT
#define	SSTSIZE			OBSIZE (SSTACK)
#define	LASTOFFSET(x,y)		x->ss_LastOffset [y]
#define	ANYFOR(x)		x->ss_Used [ST_FOR]
#define	ANYDO(x)		x->ss_Used [ST_DO]
#define	ANYWHILE(x)		x->ss_Used [ST_WHILE]
#define	ANYIF(x)		x->ss_Used [ST_IF]
#define	ANYSWITCH(x)		x->ss_Used [ST_SWITCH]
#define	LASTFOR(x)		x->ss_LastOffset [ANYFOR (x)]
#define	LASTDO(x)		x->ss_LastOffset [ANYDO (x)]
#define	LASTWHILE(x)		x->ss_LastOffset [ANYWHILE (x)]
#define	LASTIF(x)		x->ss_LastOffset [ANYIF (x)]
#define	LASTSWITCH(x)		x->ss_LastOffset [ANYSWITCH (x)]
#define	ONELESS(x, y)		x->ss_Used [y] --
#define	BUF_FOR(x, y)		(x->ss_Buffers [ST_FOR]) [y]
#define	BUF_DO(x, y)		(x->ss_Buffers [ST_DO]) [y]
#define	BUF_WHILE(x, y)		(x->ss_Buffers [ST_WHILE]) [y]
#define	BUF_IF(x, y)		(x->ss_Buffers [ST_IF]) [y]
#define	BUF_SWITCH(x, y)	(x->ss_Buffers [ST_SWITCH]) [y]
#define	freelaststatus()	ONELESS ()


/* # TraslateItem
** # TITEM
** 
*/ 

typedef struct TraslateItem	/* traslating file to pmap		      */
{
STR		 ti_Name;
UWORD		 ti_Type;
PTR		 ti_Item;
ASTAT		*ti_ItemStazz;	/* statistics				      */
WPTR		 ti_InitialOffset;
WPTR		 ti_CurOffset;	/* optionally used			      */
BLOCK		*ti_Ownerblock;	/* owner (where the action or object is)      */
GROUP		*ti_FathGroup;	/* father group				      */
SSTACK		*ti_Status;	/* status stack (will it be moved??)	      */
UWORD		 ti_LastNameIDUsed;
UWORD		 ti_LastLabIDUsed;
TLIST		 ti_MakeVars;
} TITEM;

#define	TITFEEDCUR(x, y)	x->ti_CurOffset += y

#define	TIT_OBJECT		0x0001
#define	TIT_ACTION		0x0002
#define	TIT_STARTER		0x0003	/* needed for the kind treatment      */

#define	TITSIZE			OBSIZE (TITEM)


/* # ProcessEnvironment
** # PROENV
** 
** file traslation environment
** could it be removed?
** 
*/ 

typedef struct ProcessEnvironment
{
ULONG		 pe_Type;
PMAP		*pe_UsedPMap;
STR		 pe_ProcFileName;
STR		 pe_TraceFileName;
PTR		 pe_TraceFile;
TITEM		*pe_Object;
FH		*pe_CurrentFile;
NBASE		*pe_NameBase;
} PROENV;

#define	PESIZE			OBSIZE (PROENV)


/* 
** traslation possible types (used in pe_Type)
** 
*/ 

#define	PET_ACTION		0x0001L
#define	PET_OBJECT		0x0002L
#define PET_STRUCTURE		0x0003L
#define PET_GLOBAL		0x0004L	/* something here must be changed */


/* # CallInfo
** # CALLINFO
** 
** CallInfo and alike structures will be
** used only when coding file!
** so this definitions have to be moved
** to 'code.h' file!
** 
*/ 

#define	CALLINFO		struct CallInfo

struct CallInfo
{
CALLINFO	*ci_Next;	/* next object in chain!	*/
BOOL		 ci_Type;	/* function (FALSE) or action	*/
PTR		 ci_Object;	/* description			*/
ULONG		 ci_Revs;	/* times object is called	*/
STR		 ci_Name;	/* function name		*/
LONG		 ci_Size;	/* -1 if size unknown		*/
};

#define	cisize			sizeof (CALLINFO)
#define	CISIZE			(ULONG) cisize
#define	CopyCIB(x,y)		CopyMemQuick (x, y, CIBSIZE)


typedef struct CallInfoBox	/* to check/nodify!		*/
{
MAPH		cib_Head;	/* defines the header		*/
} CIBOX;

/*
#define	CIBSIZE			OBSIZE (CIBOX)
#define	CIB(x)			(ULONG) (x) * CISIZE + CIBSIZE
#define	AllocCIBOX(x)		Alloc (CIBSIZE + CISIZE * x)
#define	FreeCIBOX(x)		FreeMem (x, x->cib_totsize)
*/


#ifndef	 GHANDLE_H
#include <ghandle.h>
#endif


/* # Couple
** # COUPLE
** 
** A Couple: a word pointer and a 'C' pointer
** 
*/ 

typedef struct Couple
{
WPTR		 cp_Small;
ULONG		 cp_Big;
} COUPLE;


/* # group
** # GROUP
** 
** structure bunch -- very important facilty
** 
*/ 

typedef struct group
{
GHANDLE		 ghandle;	/* update for version 3.39 (pointer removed) */
PMAP		*pm;
SNAME		*sna;
NAME		*name;
FH		*file;
COUPLE		 couple;
BLOCK		*strashblock;
} GROUP;

#define GRSIZE				OBSIZE (GROUP)


/* patch for newer version of 'group'...
** ACTUAL patches needed, either for this item
** or others!
** 
*/ 

#define	group->ghandle->lasterror	group->ghandle.lasterror

/*
** gets an object -- you gotta give a processmap ptr and an offset
**
*/

#define	BOBJECT(x, y)		(OBJECT *)	GET (x, y)
#define	BACTION(x, y)		(ACTION *)	GET (x, y)
#define	BSTRUCTURE(x, y)	(STRUCTURE *)	GET (x, y)
#define	BFUNCTION(x, y)		(VOID *)	GET (x, y)
#define	BGLOBAL(x, y)		(VAR *)		GET (x, y)
#define	STRING(x, y)		(UBYTE *)	GET (x, y)

#define	_OBJECT(x, y)	 	BOBJECT		(x->Pblocks[_Objects], y)
#define	_ACTION(x, y)	 	BACTION		(x->Pblocks[_Actions], y)
#define	STRUCTURE(x, y)		BSTRUCTURE	(x->Pblocks[_Structures], y)

/* There are different kinds of functions, so there is just a general	*/
/* cast									*/
#define	FUNCTION(x, y)		BFUNCTION	(x->Pblocks[_Functions], y)
#define	GETGLOBAL(x, y)		BGLOBAL		(x->Pblocks[_Globals], y)
#define	WORKSTRING(x, y)	STRING		(x->Pblocks[_WorkStrings], y)
#define	PROGSTRING(x, y)	STRING		(x->Pblocks[_ProgramStrings], y)

#ifndef  CODE_H
#include <code.h>
#endif
#ifndef	 STRUCTURES_H
#include <structures.h>
#endif

#endif
