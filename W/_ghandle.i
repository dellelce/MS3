; tony dee © 1992
; 
; global handler definition v1.23 (assembly traslation)
; 

	include	'logics.i'
	
	
	STRUCTURE GHANDLE
	STRUCT	gh_fl,TLISTSIZE
	STRUCT	gh_filebufs,TLISTSIZE
	STRUCT	gh_locals,VLISTSIZE
	STRUCT	gh_globals,VLISTSIZE
	APTR	gh_traslatefile
	ULONG	gh_lasterror
	APTR	gh_lasterrorstring
	FLAG	gh_flags		; to change...
	ULONG	gh_envtype
	APTR	gh_emvironment
	APTR	gh_currentitem
	APTR	gh_namebase
	STRUCT	gh_atlist,ATTRLISTSIZE
	UWORD	gh_trlevel		; unused....
	LABEL	GHANDLESIZE
	
	
gh_file		EQU		gh_filebufs
gh_filelist	EQU		gh_fl
gh_depth	EQU		gh_trlevel
