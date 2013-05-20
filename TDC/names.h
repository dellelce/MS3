/* 
** 
** NAMES MANAGEMENT DEFINITIONS
** tony dee © 1992
** version 0.05 -- updated because file had too many errors
** version 0.06 -- new features: 'name-def size' (adding), PLUS: TOKEN as NAME
** 
** %$% stands for new feature (now introducing)
** 
*/ 


#ifndef NAMES_H
#define	NAMES_H 1

#ifndef	WSYSTEM_H
#include <wsystem.h>
#endif
#ifndef LOGICS_H
#include <logics.h>
#endif


/* # NameDes
** # NAME
** 
** size: 12 bytes
** 
*/ 

typedef struct NameDes	/* a name description	*/
{
VOID	*nd_data;	/* definition		*/
USHORT	 nd_size;	/* 'def size' %$%	*/
SHORT	 nd_type;	/* type			*/
ULONG	 nd_subtype;	/* secondary type	*/
} NAME;

#define	NASIZE		OBSIZE (NAME)
#define	SUBTYPENULL	((ULONG) -1L)
#define	TOKEN		NAME

#define	TK_DATA(x)	(x->nd_data)	/* %$% new feature		*/
#define	TK_SIZE(x)	(x->nd_size)
#define	TK_TYPE(x)	(x->nd_type)
#define	TK_SUBTYPE(x)	(x->nd_subtype)


/* DOGETNAME
** macro per 'prendere'
** velocemente un 'NAME' -- sarà rimossa il piu presto possibile...
** 
** if (ISFALSE (getname (group)))
** 	{
**	group->ghandle->lasterror = EN_NONAME;
**	return (0);
**	}
** 
*/ 

#define	DGN0		if (ISFALSE (getname (group)))
#define	DGN1		group->ghandle->lasterror = EN_NONAME
#define	DGN2		return (0)
#define	DOGETNAME	DGN0 { DGN1; DGN2; }


/* # StrName
** # SNAME
** 
*/ 

typedef struct StrName	/* name header	(something like BCPL strings) */
{
UWORD		sn_Size;
} SNAME;

#define	LITTLENAME	 128
#define	SMALLNAME	 512
#define	BIGNAME		1024

#define	STDNAME		 512

#define	SNSIZE	    	OBSIZE (SNAME)
#define	SNZERO(x)   	(UBYTE *) (OBSIZE (UWORD) + (ULONG) x)
#define	NAMESTR(x)  	(UBYTE *) ((VOID *) x + (VOID *) SNSIZE)
#define NAMESIZE(x) 	(x->sn_Size)
#define	NSIZE(x)    	(ULONG) (x->sn_Size)


/* 
** name types
** 
*/ 

#define	NDT_NUMBER	  0  /* numbers					*/
#define NDT_LOCAL	  1  /* a local variable			*/
#define NDT_GLOBAL	  2  /* a global static variable		*/
#define NDT_FUNCTION	  3  /* a system or an external routine		*/
#define NDT_ACTION	  4  /* a program or a library routine		*/
#define NDT_DEFINER	  5  /* such as 'object', 'structure' etc	*/
#define NDT_SIMPLEDEF	  6  /* such as 'byte', 'string', 'long'	*/
#define NDT_RESWORD	  7  /* such as 'if', 'do', 'while', etc	*/
#define NDT_CLOSER	  8  /* ";" close a line, also a 'special'	*/
#define NDT_SPECIAL	  9  /* such as ':', '[', '(', ']', etc		*/
#define	NDT_OBJECTOP	 10  /* such as 'create', 'modify', etc		*/
#define NDT_STRING	 11  /* a string!				*/
#define NDT_PMAPOPERATOR 12  /* such as 'find', 'add', 'remove'		*/
#define	NDT_OBJECT	 13  /* an object (...)				*/
#define	NDT_STRUCTURE	 14  /* a structure definition ptr		*/
#define	NDT_LABEL	 15  /* a label					*/
#define	NDT_RESLABEL	 16  /* for reserved labels (body:, argin:)	*/
#define	NDT_RESCONST	 17  /* reserved constants			*/
#define	NDT_SOURCE	 18  /* data about a library name...??		*/
#define	NDT_USERTYPE	 19  /* user private type -- not sure if used	*/
#define	NDT_PRIVHANDLER	 20  /* user def handler			*/
#define	NDT_STRUCTITEM	 21  /*	name of structure item			*/
#define	NDT_OBJATTR	 22  /* an object attribute			*/
#define	NDT_ERROR	 -1  /* error					*/
#define NDT_UNKNOWN	 -2  /* unknown object				*/
#define NDT_EMPTY	 -3  /* names is empty -- not sure if used	*/
#define	NDT_ENDOFFILE	 -4  /* file is over.... I forgot about it!!!!	*/


/* 
** names subtypes
** 
*/ 


/* %
** 
** numbers
** 
*/ 

#define	NDS_NUMFLOAT	0x0001L
#define	NDS_NUMDOUBLE	0x0002L
#define	NDS_NUMUBYTE	0x0003L
#define	NDS_NUMBYTE	0x0004L
#define	NDS_NUMUWORD	0x0005L
#define	NDS_NUMWORD	0x0006L
#define	NDS_NUMULONG	0x0007L
#define	NDS_NUMLONG	0x0008L


/* %
** 
** functions
** 
*/ 

#define	NDS_LIBCALL	0x1000L	/* library function			*/
#define	NDS_BINFUN	0x1001L	/* binary function			*/
#define	NDS_INTCALL	0x2000L	/* 8086 family interrupt		*/


/* %
** 
** definers
** 
*/ 

#define	NDS_ACTION	0x0000L	/* defining a new action		*/
#define	NDS_OBJECT	0x0001L	/* defining a new object		*/
#define	NDS_STRUCTURE	0x0002L	/* defining a new structure		*/
#define	NDS_GHOST	0x0003L	/* a 'pre-exeuted' action		*/
#define	NDS_FETCHED	0x0004L	/* a 'fetched' action			*/
#define	NDS_STARTER	0x0005L	/* similar to the 'C' main		*/


/* %
** 
** simple defs
** 
*/ 

#define	NDS_BYTE	0x0000L
#define	NDS_WORD	0x0001L
#define	NDS_LONG	0x0002L
#define	NDS_NUMBER	0x0003L
#define	NDS_STRING	0x0004L
#define	NDS_RANGE	0x0005L
#define	NDS_BOOL	0x0006L
#define	NDS_DOUBLE	0x0007L
#define	NDS_FLOAT	0x0008L
#define	NDS_SIGNED	0x0010L
#define	NDS_UNSIGNED	0x0011L
#define	NDS_POINTER	0x0012L
#define	NDS_STATIC	0x0013L
#define	NDS_GLOBAL	0x0014L

#define NDS_LSIMPLE	NDS_GLOBAL
#define	NDS_LASTSIMPLE	NDS_GLOBAL


/* %
** 
** Reserved words
** 
*/ 

#define	NDS_SHIFTR	0x0000L	/* '>>'	shift right			*/
#define	NDS_SHIFTL	0x0001L	/* '<<' shift left			*/
#define	NDS_LOGICOR	0x0002L	/* '||'	logic 'OR'			*/
#define	NDS_LOGICAND	0x0003L	/* '&&'	logic 'AND'			*/
#define	NDS_IF		0x0004L	/* 'if', selection			*/
#define	NDS_CASE	0x0005L	/* 'case', case selection		*/
#define	NDS_DO		0x0006L	/* 'do'					*/
#define	NDS_EXIT	0x0007L /* exits from the program		*/
#define	NDS_ISEQUAL	0x0008L	/* '==' checks if equal			*/
#define	NDS_GOTO	0x0009L	/* goes to a certain place		*/
#define	NDS_CALL	0x000AL	/* calls an action "subroutine"		*/
#define	NDS_SUBRETURN	0x000BL	/* returns fron a "subroutine"		*/
#define	NDS_RETURN	0x0009L /* returns from an action		*/
#define	NDS_BREAK	0x000AL /* breaks a loop			*/
#define	NDS_DEFINE	0x000BL	/* not goodly defined!			*/
#define	NDS_DEFAULT	0x000CL	/* default place			*/
#define	NDS_SWITCH	0x000EL	/* switcher				*/
#define	NDS_NEXT	0x000FL	/* do next loop cycle			*/
#define	NDS_ALIAS	0x0010L	/* alias operator			*/
#define	NDS_FORGET	0x0011L	/* when to forget a variable		*/
#define	NDS_SOURCE	0x0012L /* library access res word		*/
#define	NDS_NEWTYPE	0x0013L	/* creates an user 'simple' type	*/
#define NDS_THEN	0x0020L /* 'IF' programming structure		*/
#define NDS_ELSE	0x0021L	/* 'IF' programming structure		*/
#define NDS_ENDIF	0x0022L	/* 'IF' programming structure		*/
#define NDS_WHILE	0x0023L	/* 'while' you needed this!!!		*/
#define NDS_FOR		0x0024L	/* needed too!!!			*/
#define NDS_EQMAJOR	0x0025L	/* major or equal			*/
#define NDS_EQMINOR	0x0026L	/* minor or equal			*/
#define NDS_NOTEQUAL	0x0027L	/* not equal				*/
#define NDS_UNTIL	0x0028L	/* for the 'do-until' cycle		*/
#define NDS_
#define NDS_


/* %
** 
** specials
** 
*/

#define	NDS_EXCLAMATION	0x0000L	/* '!'  exclamation mark		*/
#define	NDS_DIESIS	0x0001L	/* '#'	diesis				*/
#define	NDS_AND		0x0002L	/* '&'	boolean 'AND'			*/
#define	NDS_BRAK1OP	0x0003L	/* '('	open 1st type of brack.		*/
#define NDS_BRAK1CL	0x0004L	/* ')'	close 1st type of brack.	*/
#define	NDS_MULTIPLY	0x0005L	/* '*'  multiply symbol			*/
#define	NDS_ADD		0x0006L	/* '+'	add symbol			*/
#define	NDS_COMMA	0x0007L	/* ','  comma, used in lists		*/
#define	NDS_SUBTRACT	0x0008L	/* '-'	subtract symbol			*/
#define	NDS_PERIOD	0x0009L	/* '.'	period, how to use it?		*/
#define	NDS_DIVIDE	0x000AL	/* '/'  divide symbol			*/
#define	NDS_TWOPOINTS	0x000BL	/* ':'	label identifier		*/
#define	NDS_MINOR	0x000CL	/* '<'	minor symbol			*/
#define NDS_EQUAL	0x000DL	/* '='	equal symbol			*/
#define	NDS_MAJOR	0x000EL	/* '>'	major symbol			*/
#define	NDS_QUESTION	0x000FL	/* '?'	question mark r			*/
#define NDS_BRAK2OP	0x0010L	/* '['	opens 2nd type of brack.	*/
#define NDS_BACKSLASH	0x0011L	/* '\'	backslash			*/
#define	NDS_BRAK2CL	0x0012L	/* ']'	closes 2nd type of brak.	*/
#define	NDS_EXOR	0x0013L	/* '^'	exclusive 'OR'			*/
#define	NDS_UNDERLINE	0x0014L	/* '_'	underline			*/
#define	NDS_OR		0x0015L	/* '|'  an 'OR'!			*/
#define	NDS_WAVE	0x0016L	/* '~' what's for?			*/


/* %
** 
** object operators
** 
*/ 

#define	NDS_OPEN	0x0000L
#define	NDS_CLOSE	0x0001L
#define	NDS_CREATE	0x0002L
#define	NDS_DELETE	0x0003L
#define	NDS_MODIFY	0x0004L
#define	NDS_ATTRIBUTES	0x0005L
#define	NDS_TYPE	0x0006L	/* gets an object type			*/
#define	NDS_SIZE	0x0007L /* gets an object size			*/
#define	NDS_REAL	0x0008L	/* real attribute for calling		*/


/* %
** 
** processmap operators
** used only in GHOST routines
** 
** 
*/ 

#define	NDS_REPLACE	0x0000L
#define	NDS_MREPLACE	0x0001L
#define	NDS_RESTRING	0x0002L
#define	NDS_INIT	0x0003L
#define	NDS_INSERT	0x0004L
#define	NDS_REMOVE	0x0005L
#define	NDS_INSERTLINE	0x0006L
#define	NDS_REMOVELINE	0x0007L
#define	MDS_REMOVEZONE	0x0008L
#define	NDS_FIND	0x0009L


/* %
** 
** reserved labels
** 
*/ 

#define	NDS_BODY	0x0000L
#define	NDS_ARGIN	0x0001L
#define	NDS_ARGOUT	0x0002L


/* %
** 
** Reserved constants
** 
*/ 

#define	NDS_TRUE	0x0000L
#define	NDS_FALSE	0x0001L


/* # NameVecArchive
** # NAMEVEC
** 
** STRUCTURES USED FOR
** NAMES FILING
** They've been changed, look at their routines if they have any...
** 
*/

typedef struct NameVecArchive
{
UWORD		  nb_Used;
UWORD		  nb_Available;
NAME		 *nb_NamesVec;
} NAMEVEC;


/* # ExtName
** # XNAME
** 
** 
*/ 

typedef struct ExtName
{
UBYTE	*xn_NameStr;	/* only 'built-in' have strings ptr in		*/
NAME	 xn_Name;	/* the nd_def field.				*/
} XNAME;


/* # NameNode
** # NNODE
** 
** 
*/ 

typedef struct NameNode
{
TNODE	 nn_ArcNode;
XNAME	 nn_Name;
} NNODE;

#define	NNSIZE		OBSIZE (NNODE)


/* # NameListHeader
** # NLIST
** 
*/ 

typedef	struct NameListHeader
{
TLIST		nlh_Archiver;
UWORD		nlh_Count;
} NLIST;


/* # Library
** # LIB
** 
** library name access def (will it be used??)
** 
** now updating
** 
*/ 

#define	LIB		struct Library
#define	LIBRARY		LIB
#define	SOURCE		LIB

struct Library
{
TNODE		 sc_ArcNode;
UBYTE		*sc_Name;
BLOCK		*sc_SourceDir;	/*					*/
BLOCK		*sc_Strings;	/* initially used			*/
VOID		*sc_ProcessMap;	/* CAST to pmap				*/
UBYTE		*sc_DirName;	/* what is it?				*/
ULONG		 sc_Strings;	/* counter for strings			*/
ULONG		 sc_DirLock;	/* under amiga environment, to change!	*/
};

#define	lib_		sc_


/* # NameBase
** # NBASE
** 
** names archive basic header
** 
*/ 

typedef struct NameBase
{
UWORD		  nb_GlobCount;
UWORD		  nb_NamesInList;
NLIST		 *nb_NameList;
UWORD		  nb_NamesInVec;
NAMEVEC		**nb_NameVec [25];		/* vector per chars 	*/
LIB		 *nd_NamesLibrary;
} NBASE;


#define	NAMEBASE	NBASE
#define	NBSIZE		OBSIZE (NBASE)


/* # NameBox
** # NBOX
** 
** $ NAME BOX
** will it be used?
** 
*/ 

#define	NBOX		struct NameBox
#define	NBXSIZE		OBSIZE (NBOX)

struct NameBox
{
NBOX	*next;
UWORD	 used;
NAME	 name [7];
};


/* # NameBoxHeader
** # NBH
** 
*/ 

struct MameBoxHeader
{
UWORD	 subboxes;
UWORD	 names;
NBOX	*first;
};

#define	NBH		struct NameBoxHeader
#define	NBHSIZE		OBSIZE (NBH)


#endif
