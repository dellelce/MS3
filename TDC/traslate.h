/* tony dee © 1992
** 
** traslate definitions
** (traslate.h, project TDL1) // should be joined with vardefs.h
** 
*/ 

#ifndef TRASLATE_H
#define	TRASLATE_H		1

#ifndef WSYSTEM_H
#include <wsystem.h>
#endif


#define	DEF_OK(x)	(AND (x, %1001) == %1001)


/* # varbuild
** # VARBUILD
** 
** used WHEN DEFINING A VARIABLE (not when traslating var use....)
** 
** all items names should be changed! (for standing to the METAFORM concept)
** 
** size = 30 + VARU size
** 
** 
*/ 

struct varbuild
{
UWORD	 build;		/* needed to build the HEAD [temporarily used]	*/
UWORD	 buildspc;	/* extension to 'build'				*/
BOOL	 name;		/* did you get the variable name		*/
UWORD	 gentype;	/* (three) general types			*/
UBYTE	*nameval;	/* name C pointer				*/
WPTR	 np;		/* name WORD pointer				*/
UWORD	 type;		/* 0 = static 1 = non static			*/
BLOCK	*ownerblock;	/* this is where the var must be placed		*/
VOID	*definition;	/* used if an object or structure		*/
VARU	 vu;		/* this words are used to store the definition	*/
UWORD	 usedwords;	/* counts the number of used words		*/
PTR	 structdef;	/* $if a structure				*/
UWORD	 semphore;	/* semaphore inclusion -- NEW IDEA --		*/
} VARBUILD;

#define	METAFORM	VARBUILD	/* pre-MetaForm definition	*/
#define	MFORM		VARBUILD

/* standardize arguments
** 
*/ 

#define	MFARG_0(x)		(x->build)
#define	MFARG_1(x)		(x->buildspc)
#define	MFARG_2(x)		(x->name)
#define	MFARG_3(x)		(x->gentype)
#define	MFARG_4(x)		(x->nameval)
#define	MFARG_5(x)		(x->np)
#define	MFARG_6(x)		(x->type)
#define	MFARG_7(x)		(x->ownerblock)
#define	MFARG_8(x)		(x->definition)
#define	MFARG_9(x)		(x->vu)
#define	MFARG_10(x)		(x->usedwords)
#define	MFARG_11(x)		(x->structdef)

#define	MF_ISSTATIC(x)		(MFARG_6 (x) == 0)
#define	MF_ISNONSTATIC(x)	(MFARG_6 (x) == 0)
#define	MF_XDEFINITION(x)	(MFARG_11 (x))
#define	MF_VARINFO(x)		(MFARG_9 (x))


#define	VBSIZE		(ULONG) sizeof (VARBUILD)


#define	VGT_SIMPLEDEF	0x0001
#define	VGT_STRUCT	0x0002
#define	VGT_OBJECT	0x0003

#define	NIB_LOWEST	%0000000011111111
#define	NIB_MID		%0000111100000000
#define	NIB_HIGH	%1111000000000000

#define	NLOWEST(x)	(x & NIB_LOWEST)
#define	NMID(x)		(x & NIB_MID)
#define	NHIGH(x)	(x & NIB_HIGH)

/*			 VVVVHHHHLLLLLLLL very high = V; high = H; low = L    */
#define	VBB_BYTE	%0000000000000000
#define	VBB_WORD	%0000000000000010
#define	VBB_LONG	%0000000000000011
#define	VBB_NUMBER	%0000000000000100
#define	VBB_STRING	%0000000000000101
#define	VBB_RANGE	%0000000000000110
#define	VBB_BOOL	%0000000000000111
#define	VBB_DOUBLE	%0000000000001000
#define	VBB_FLOAT	%0000000000001001

/*			 VVVVHHHHLLLLLLLL very high = V; high = H; low = L    */
#define	VBB_SIGNED	%000000010000000
#define	VBB_UNSIGNED	%000000000000000
#define	VBB_POINTED	%000000100000000
#define	VBB_UNPOINTED	%000000000000000
#define	VBB_INIT	%000001000000000	
#define	VBB_UNINIT	%000000000000000	
#define	VBB_GLOBAL	%000010000000000	
#define	VBB_LOCAL	%000000000000000	

#define	VBM_SIGN	  8
#define	VBM_POINTER	  9
#define	VBM_INIT	 10
#define	VBM_GLOBAL	 11

/*			 VVVVHHHHLLLLLLLL very high = V; high = H; low = L    */
#define	VBB_COMPLEX	%0001000000000000
#define	VBB_SIMPLE	%0000000000000000
#define	VBB_TPSTD	%0010000000000000
#define	VBB_TPDEF	%0000000000000000
#define	VBB_MATRIX	%0100000000000000
#define	VBB_VECTOR	%????????????????

#define	VDM_COMPLEXITY	 12
#define	VDM_TYPE	 13
#define	VDM_CMPXMODE	 14


/* for 'buildspc'
** 
*/ 

#define	VBS_STARTUP	0x0000
#define	VBS_NORMAL	0x0001	/* not a structure		*/
#define	VBS_STRUCTURE	0x0002	/* a known structure		*/


/* # VBB2TOKEN
** 
** correlate a varbuild bit (vbb) to a token type (name->nd_subtype)
**  
*/ 

typedef struct VBB2TOKEN
{
UWORD	 v2t_vbb;
UWORD	 v2t_tokentype;
} V2T;

#define	VTVBB(x)	(x->v2t_vbb)
#define	VTTYPE(x)	(x->v2t_tokentype)


/* # init
** # INIT
** 
** struttura usata per fornire i dati
** alla funzione di inizializzazione
** 
*/ 

typedef struct init
{
UWORD	 in_mode;
UWORD	 in_place;
PMAP	*in_pmap;
BLOCK	*in_block;
STRUCT	*in_obj;		/* to know how to init it rightly	*/
} INIT;

#define	INITSIZE		(ULONG) sizeof (INIT)

#define	IM_NUMBERS		0x0001
#define	IM_STRUCTMODE		0x0002
#define	IM_ANYWAY		0x0003

#define	IP_LOCAL		0x0001
#define	IP_GLOBAL		0x0002
#define	IP_STRUCTURE		0x0003


/* general mode (mode to 'get' a variable)
** 
** 
*/ 

#define	VGM_LOCAL		0x0001
#define	VGM_GLOBAL		0x0002
#define	VGM_STRUCTURE		0x0003


/* type for the 'hearttraslate' functions
** 
** re-check it!
** 
*/ 

#define	HTT_ACTION		0x0001
#define	HTT_FETCHED		0x0002
#define	HTT_STARTER		0x0003

#define	HTT_NORMAL		0x000F	/* end of normal actions	*/
#define	HTT_GHOST		0x0010
#define	HTT_ACTION		0x001F	/* ACTION bound			*/
#define	HTT_OBJECT		0x0020
#define	HTT_SPECIAL		0x002F	/* SPECIAL bound		*/

#define	_NORMALTYPE(x)		(x <= HTT_NORMAL)
#define	_ACTIONTYPE(x)		(x <= HTT_ACTION)
#define	_SPECIALTYPE(x)		(x <= HTT_SPECIAL)


/* 'how' for getexpression (save quickly or save later, data regarding
** vars)
** 
*/ 

#define	GH_QUICKLY	0x0001	/* vars are saved as completely def	*/
#define	GH_SAVELATER	0x0002	/* vars are cached			*/


/* 
** kind of object for 'delete' or 'close'
** 
*/

#define	OBJT_LOCAL	0x0001
#define	OBJT_GLOBAL	0x0002
#define	OBJT_UNKNOWN	0x0003

#endif
