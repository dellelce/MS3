; tony dee © 1992
; 
; non-complete assembly traslation of logics.h v3.39
; 
	
	include "exec/types.h"
	
	
WPTR	EQU	WPTR
	
	
	STRUCTURE ASTAT,0
	USHORT	as_StringCalls
	USHORT	as_ObjectCalls
	USHORT	as_StructureCalls
	USHORT	as_FunctionCalls
	USHORT	as_ActionCalls
	USHORT	as_Labels
	USHORT	as_LocalVariables
	USHORT	as_StreamCalls
	LABEL	AS_SIZE
	
	
	STRUCTURE ACTION,0
	SHORT	ac_Type
	ULONG	ac_ActionSize
	WPTR	ac_Name
	USHORT	ac_Args
	WPTR	ac_Offset
	STRUCT	ac_Data,ASTAT
	UWORD	ac_Locals
	UWORD	ac_Globals
	UWORD	ac_LocalStatics
	UWORD	ac_Code
	BOOL	ac_ArgOut
;	UWORD	ac_ArgDes
	LABEL	ACT_SIZE
	
AT_GHOST	EQU	-2
AT_FETCHED	EQU	-1
AT_NORMAL	EQU	 0
	
	STRUCTURE PMAP,0
	BOOL	pm_Library
	UWORD	pm_Status
	UWORD	pm_Version
	UWORD	pm_FirstComp
	UWORD	pm_BlocksNum
	UWORD	pm_TotCalledObj
	UWORD	pm_PMHeaderSize
	APTR	pm_Pblocks*11
	LABEL	PM_SIZE
	
PMBLOCKS	EQU	11

PMS_STARTUP	EQU	#$0000
PMS_WRITE	EQU	#$0001
PMS_READ	EQU	#$0002
PMS_LINK	EQU	#$0003
PMS_REVIEW	EQU	#$0004
PMS_PACK	EQU	#$0005
PMS_UPDATE	EQU	#$0006

PMT_SMALL	EQU	#$0001
PMT_MIDSIZE	EQU	#$0002
PMT_BIG		EQU	#$0003
PMT_VERYBIG	EQU	#$0004
PMT_LAST	EQU	#$0004


; handlers

HANDLER		EQU	USHORT

AN_OPEN		EQU	0
AN_CLOSE	EQU	1
AN_CREATE	EQU	2
AN_DELETE	EQU	3
AN_MODIFY	EQU	4
AN_ASK		EQU	5

BV	MACRO
/1	EQU	1<</2
	ENDM	


	BV	AB_OPEN,0
	BV	AB_CLOSE,1
	BV	AB_CREATE,2
	BV	AB_DELETE,3
	BV	AB_MODIFY,4
	BV	AB_ASK,5
	
	
	STRUCTURE OBJECT,0
	WPTR	ob_Name
	WORD	ob_ObjectSize
	WPTR	ob_Offset
	USHORT	ob_Type
	USHORT	ob_Attributes
	USHORT	ob_RealAttr
	USHORT	ob_AttrWords
	USHORT	ob_Handlers
	USHORT	ob_StaticData
	USHORT	ob_LocalData
	USHORT	ob_Globals
	STRUCT	ob_Statistics,ASTAT
	LABEL	OBJ_SIZE
	
	
OT_REAL		EQU	#$0001
OT_UNREAL	EQU	#$0002
	
; status stack
	
ST_FOR		EQU	#$0000
ST_DO		EQU	#$0001
ST_WHILE	EQU	#$0002
ST_IF		EQU	#$0003
ST_SWITCH	EQU	#$0004
	
STYPES		EQU	ST_CASE + 1
	
	
	STRUCTURE SSTACK,0
	APTR	ss_Next
	UWORD	ss_Each
	LABEL	SS_SIZE
	
	
	STRUCTURE TITEM,0
	APTR	ti_Name
	UWORD	ti_Type
	APTR	ti_Item
	APTR	ti_ItemStazz
	WPTR	ti_InitialOffset
	WPTR	ti_CurOffset
	APTR	ti_OwnerBlock
	APTR	ti_FathGroup
	APTR	ti_Status
	UWORD	ti_LastNameIDUsed
	UWORD	ti_LastLabIDUsed
	STRUCT	ti_MakeVars,TLIST
	LABEL	TITSIZE
	
	
	STRUCTURE COUPLE,0
	WPTR	cp_Small
	ULONG	cp_Big
	LABEL	CP_SIZE
	
	
	STRUCTURE GROUP,0
	STRUCT	gr_ghandle,GHANDLESIZE
	APTR	gr_pmap
	APTR	gr_sna
	APTR	gr_name
	APTR	gr_file
	APTR	gr_curitem
	STRUCT	gr_couple,CP_SIZE
	LABEL	GR_SIZE
	
	
	STRUCTURE CALLINFO,0
	APTR	ci_Next
	BOOL	ci_Type
	APTR	ci_Object
	ULONG	ci_Revs
	APTR	ci_Name
	ULONG	ci_Size
	LABEL	CI_SIZE
	
; what do they mean?
	
	STRUCTURE _STR,0
	APTR	next
	APTR	str
	LONG	size
	LABEL	STRSIZE
	
	
	STRUCTURE _STRINGBOX,0
	UWORD	count
	STRUCT	_strings,TLISTSIZE*25
	LABEL	STRBOXSIZE
	
	STRUCTURE _DATAFLAG,0
	WPTR	df_Name
	WPTR	df_Id
	FLAG	df_Status
	LABEL	DFSIZE
		
