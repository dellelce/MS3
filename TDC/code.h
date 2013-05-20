/* tony dee © 1991/1992
**
** MS3 Coding
**
*/

#ifndef	CODE_H
#define	CODE_H	1


#ifndef WSYSTEM_H
#include <wsystem.h>
#endif
#ifndef LOGICS_H
#include <logics.h>
#endif
#ifndef TONYEXTEND_H
#include <tonyextend.h>
#endif
#ifndef LABELS_H
#include <labels.h>
#endif
#ifndef CODEVARS_H
#include <codevars.h>
#endif


#define	MEMF_FREE	MEMF_CLEAR|MEMF_PUBLIC
#define	chunk(x)	(CHUNK *) Alloc (x << 1 + OBSIZE (CHUNK));
#define	BADDR(x)	(x >> 2)
#define CADDR(x)	(x << 2)


/* # hunk
** # HUNK
** 
** contiene il codice del programmma
** praticamente è costituito di tabella
** di WORDS
** 
*/ 

typedef struct	hunk
{
TNODE	 h_HunkChain;
UWORD	 h_Model;
UWORD	 h_AllocatedWords;
UWORD	 h_LastUsedWord;
UWORD	 h_FirstEmpty;
UWORD	 h_LastEmpty;
CPIECE	*h_CurrentWord;
UWORD	 h_References;
} HUNK;

#define	HUNKSIZE	OBSIZE (HUNK)
#define	STDHUNKROOM	512L


/* # HunkC
** # HC
** 
*/ 

typedef	struct HunkC
{
TLIST	 hc_Hunks;
ULONG	 hc_TotCode;
ULONG	 hc_TotAlloc;
} HC;

#define	MPUSH		0x48e0 /* pushes data to the A7-stack	*/
#define MPOP		0x4cd8 /* pops data from A7-stack	*/
#define SHIFTER		0xe000 /* shift/roll header		*/
#define RETURN		0x4e75 /* RTS instruction		*/
#define TEST		0x4a00 /* tests with zero		*/
#define	COMPARE		0xb000 /* compares two values		*/

#define	WRITERET(x)	x->code [0] = RETURN; x->cnum = 1

#define	REGNUM(x)	(1<<x)
#define SH8(x)		(x<<4)


/* # bunch
** # BUNCH
** 
** 
** basical code container
** it can contain a whole
** m68000 instruction (alias 5 words)
** 
** 
*/ 

typedef struct	bunch
{
UBYTE	b_cnum;
CPIECE	b_code [5];
} BUNCH;


/* # groupofbunches
** # GBUNCH
** 
*/ 

typedef struct groupofbunches
{
USHORT	bunches;
USHORT	used;
} GBUNCH;

#define	GBSIZE		OBSIZE (GBUNCH)
#define	BSIZE		OBSIZE (BUNCH)
#define	WORDS(x)	(ULONG) (x * sizeof (UWORD))

#define	ALGBSIZE(x)	(GBSIZE + BSIZE * (ULONG) x)
#define	ALGBUNCH(x)	(GBUNCH *) Alloc (ALGBSIZE (x))


/* 
** Segment kinds... maybe replaced to codefast.h file...
** 
*/ 

#define	HID_HEADER	0x03F3L
#define	HID_DATA	0x03EAL
#define	HID_CODE	0x03EBL
#define	HID_RELOC	0x03ECL
#define	HID_CLOSEFILE	0x03F2L
#define	HID_CLOSEHUNK	0x03F2L


/* # Register
** # _REG
** 
*/ 

typedef struct Register
{
UBYTE	reg_Status;
VOID   *reg_VarDescrition;
} _REG;

#define	RS_FREE			0x00 /* reg can be used freely		*/
#define	RS_VAR			0x01 /* a variable itself		*/
#define	RS_POINTERTOVAR		0x02 /* pointer to a variable		*/
#define	RS_LIBRARY		0x03 /* pointer to a library		*/
#define	RS_STACK		0x04 /* stack pointer			*/
#define	RS_LOCALSAREA		0x05 /* offset for local vars		*/
#define	RS_ACTION		0x06 /* pointer to an action		*/
#define	RS_OBJECT		0x07 /* object identifier		*/
#define	RS_STARTUPSTACK		0x08 /* contains program initial A7	*/
#define	RS_INITIALSTACK		0x09 /* contains routine initial A7..	*/
#define	RS_LIBNAME		0x0A /* reg contains a lib name		*/
#define	RS_UNUSED		0xff /* reg is currently unused		*/


/* # RegMap
** # RMAP
** 
*/ 

typedef struct RegMap
{
UWORD	 regcount;
_REG	 regs [14];	/* FROM D0 TO A6! A7 IS THE STACK POINTER!! */
VAR	*vars [14];
} RMAP;


/*
** program models
*/

#define	PM_SMALL	0x0001	/* program size < 64k	*/
#define	PM_LARGE	0x0002	/* program size > 64k	*/


/* # References
** # HREF
** 
** contenitore delle 'REFERENZE'
** una referenza
** 
*/ 

#define	HREF		struct References

struct References
{
ULONG		 rs_RefNo;	/* number of references		*/
UWORD		 rs_HunkNo;	/* number of hks. refered to	*/
UWORD		 rs_RefBlockRefs;
HREF		*rs_Next;
};


/* # Ref
** 
*/ 

struct	Ref
{
UWORD		rf_Refs;
UWORD		rf_Hunk;
};

#define	RFH_ITSELF	0x0000
#define	RFH_DATAHUNK	0x0001


/*	|								      */
/*	|								      */
/*	| BSS header							      */
/*	|								      */
/*	|								      */
/*	  |								      */
/*	  |								      */
/*	  | Ref header 							      */
/*	  |								      */
/*	  |								      */
/*	     |								      */
/*	     |								      */
/*	     | references list ( by longs )				      */
/*	     |								      */
/*	     |								      */
/*	       |							      */
/*	       |							      */
/*	       | * restart work *					      */
/*	       |							      */
/*	       |							      */


/* # ReplacementTag
** # RTAG
** 
*/ 

typedef struct ReplacementTag
{
UWORD		rt_Type;
UWORD		rt_ZeroOffset;
} RTAG;


/* # ReplacementList
** # RLIST
** 
*/ 

#define	RLIST		struct ReplacementList

struct ReplacementList			/* thru hunks		*/
{
UWORD		rl_Tags;		/* no of tags		*/
VOID	       *rl_List;		/* list data		*/
RLIST	       *rl_Next;		/* ?			*/
UWORD		rl_ListCount;		/* used count		*/
UWORD		rl_UsedCountInList;	/* ?			*/
};

#define	RTT_BYTE	0xcd01
#define	RTT_WORD	0xcd02
#define	RTT_LONG	0xcd03

#define	RTSIZE		OBSIZE (WRTAG)
#define RLSIZE		OBSIZE (WRLIST)

#define	RLITEMS		1000


/* # datahunk
** # DHUNK
** 
** used for static data
**
*/

typedef struct datahunk
{
UWORD		*dh_Data;
UWORD		 dh_WordSize;
UWORD		 dh_LastUsedWord;
} DHUNK;


/* # Program
** # PROGRAM
** 
** perhaps this structure will
** be removed and $incorporated to the CodeEnvironment structure or
** viceversa...
** 
*/ 

typedef struct Program			/* really shitty		 */
{
UBYTE		*prog_Name;
UBYTE		*prog_SaveName;
UWORD		 prog_Model;
VOID		*prog_ProgramMap;	/* a CAST needed	*/
ULONG		 prog_TotSize;
HC		*prog_Code;
DHUNK		*prog_GlobalData;
RLIST		*prog_ReplacementData;
} PROGRAM;

#define	PROGSIZE	OBSIZE (PROGRAM)

/*
** LAST STRUCTURE GOTTA BE REVIEWED!
**
** the 'Program structure' is able to write up to 2
** hunks (code, data and a bss one. As needed! Of course!)
** in the next future ms3 assembling program will surely create
** more hunks!
** 
*/



/* # CLabelsList
** # CLL
** 
*/ 

typedef struct CLabelsList
{
TLIST	 cll_Labels;
UWORD	 cll_Count;
} CLL;


/* # CodeAction
** # CACTION
** 
*/ 

typedef struct CodeAction
{
STR	 ca_Name;
HUNK	*ca_ActionCode;
DHUNK	*ca_LocalStaticData;
CLL	 ca_Labels;
ULONG	 ca_CalAls;
VOID	*ca_CallsData;		/* points to a semimatrix of CALLs	*/
} CACTION;			/* here is missing a lot of stuff	*/


/* # MakeVariable
** # MAKEVAR
** 
** this structure is used for archiving all data regarding a variable life
** 
** size: 42 -- something too big
** 
*/

typedef struct MakeVariable
{
TNODE		 mv_ArcNode;	/* archiving node - maybe removed	*/
VAR		*mv_Definition;	/* its definition			*/
CODEVAR		 mv_CodeLoc;	/* used only when coding		*/
UWORD		 mv_Header;	/* basical definition			*/
WORD		 mv_Mode;	/* object use				*/
WORD		 mv_Dims;	/* used if a vector or a matrix		*/
BOOL		 mv_Name;	/* FALSE = a number TRUE = a string	*/
WPTR		 mv_NameValue;	/* Name ID or Name string offset	*/
WPTR		 mv_Lives;	/* first time used			*/
WPTR		 mv_Dies;	/* last time used			*/
UWORD		 mv_Times;	/* no of times variable is used		*/
} MAKEVAR;

#define	MVC_SIMPLEVAR		 1 /* using */
#define	MVC_GENCOMPLEX		 2
#define	MVC_VECTOR		 3
#define	MVC_MATRIX		 4

#define	MV_DEFINING		-1

#define	MVARSIZE		OBSIZE (MAKEVAR)
#define	NEW_MAKEVAR ()		(MVARSIZE *) Alloc (MVARSIZE)
#define	KILL_MAKEVAR (x)	Free (x, MVARSIZE)


/* 
** the # CodeEnvironment structure is thought to contain data available
** also in other structures, but I added there since I think they will be
** helpful to make the final structure
** 
** # CODEN
** 
*/ 

typedef struct CodeEnvironment
{
UBYTE	       *ce_CodeFile;
UBYTE	       *ce_ProgFile;
UBYTE	       *ce_TraceFile;
VOID	       *ce_TraceSave;
ULONG		ce_TotAlloc;
TLIST	       *ce_ReplacementList;	/* thru hunks			*/
ITEM	       *ce_CurrentItem;		/* current traslation item	*/
RMAP		ce_Registers;		/* regs status and value	*/
CACTION		ce_CurAction;		/*				*/
} CODEN;

#define	CESIZE	OBSIZE (CODEN)


/* # polish
** # POLISH
** 
** A simple structure used to convert
** an expression to the 'Reverse Polish
** Notation'
** 
** WARNING: it should be located in the 'ghandle'...
** 
** 
*/ 

#define	STDPOLISHROOM		512*2

typedef struct polish
{
UWORD		p_Room;
UWORD		p_Used;
UWORD		p_ConvertionBuf [STDPOLISHROOM];
} POLISH;

#define	POLISHSIZE		OBSIZE (POLISH)
#define	MK_POLISH()		FastAlloc (POLISHSIZE)

#define	P_ROOM(x)		(x->p_Room)
#define	P_USED(x)		(x->p_Used)
#define	P_BUF(x)		(&x->p_ConvertionBuf [0])
#define	P_PTRENDBUF(x)		(&x->p_ConvertionBuf [STDPOLISHROOM])
#define	P_PTRLASTUSED(x)	(&x->p_ConvertionBuf [P_USED (x)])
#define	P_USEDMORE(x)		(P_USED (x) ++)


#endif
