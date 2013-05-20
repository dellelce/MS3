/* tony dee © 1990/91/92
** 
** variables header v2.28 -- file split: structure defs gone to vardefs.h
** see file variables for major update (in the /M directory), but not for all
** 
*/ 

#ifndef	VARIABLES_H
#define	VARIABLES_H 1


#ifndef WSYSTEM_H
#include <wsystem.h>
#endif
#ifndef VARDEFS_H
#include <vardefs.h>
#endif


#define	VT_BYTE		 0
#define	VT_WORD		 1
#define	VT_LONG		 2
#define	VT_NUMBER	 3
#define	VT_STRING	 4
#define	VT_RANGE	 5	/* perhaps removed	*/
#define	VT_BOOL		 6	/*    "	      "		*/
#define	VT_DOUBLE	 7
#define	VT_FLOAT	 8
#define	VT_UNKNOWN	15

/* %%
** general-var handling macros
** 
*/ 

#define	ENSIZE(x)		 (x << 8)

/* TO REDEFINED								      */
#define	SETSIZE(w, s)		 (OR (AND (w, 0xf8ff),	(s-1)<<7 )) 
#define	SETDEF(w,  d)		 (OR (AND (w, 0x7fff),	d<<15	 ))
#define	SETGENTYPE(w, t)	 (OR (AND (w, 0x9fff),  t<<13	 ))

#define	SIZE(w)			 _var_size (w)
#define	DEF(w)			 GetBit (* (UWORD *) w, 15)
#define	GENTYPE(w)		 (AND (w, NOT (0x9fff)>>13))

#define	NEXTVAR(w)		 _next_var (w)


/* %%
** variable alloc/def SETs -- OLDER SET
** 
*/ 

#define	SETATYPE(w, t)		(OR (AND (w, 0xfff0),	t    ))
#define	SETGLOBAL(w, g)		(OR (AND (w, 0xffef),	g<<4 ))
#define	SETSIGN(w, s)		(OR (AND (w, 0xffbf),	s<<6 ))
#define	SETCOMPLEX(w, c)	(OR (AND (w, 0xefff),	c<<12))
#define SETPOINTER(w, p)	(OR (AND (w, 0xffdf),	p<<5 ))
#define SETINIT(w, i)		(OR (AND (w, 0xff70),	i<<7 ))


#define	ATYPE(w)		(AND (w, NOT (0xfff0)))
#define	GLOBAL(w)		(AND (w, NOT (0xffef)))
#define	SIGN(w)			(AND (w, NOT (0xffbf)))
#define	GTMODE(x)		(AND (x, 0xe000))


/* %%
** variable use SETs

#define	SETMODE(w, m)		(OR (AND (w, 0xE7FF), m << 11))
#define	SETUSECMPX (w, x)	(OR (AND (w, 0xFF7F), m << 7))

#define	MODE(w)			(AND (w, NOT (0xE7FF) >> 11))
#define	USECMPX(w)		(AND (w, NOT (0xFF7F) >> 7))

*/ 

/* 
** basical data regarding a variable
** 
** with the term 'variable' is meant
** an word which is used to represent 'a piece
** of program', for example calls, loops, real 
** variables defs, all them can be represented 
** by this 'variable'... I think I gotta change its
** name!!
** 
** 
*/

#define	VBP_DEFUSE	15

#define	VF_DEFINITION	%0
#define	VF_USE		%1

#define	VB_DEFINITION	VF_DEFINITION   <<   VBP_DEFUSE
#define	VB_USE		VF_USE		<<   VBP_DEFUSE


/* %%
** general type
** 
** 			 XXXXYYYYZZZZNNNN
** 			 dtt--SSS--------
*/

#define	VBT_VARDEF	%0010000000000000
#define	VBT_VARUSE	%1010000000000000
#define	VBT_CALL	%1000000000000000
#define	VBT_SPECIAL	%0100000000000000

#define	VBM_GENTYPE	%1110000000000000
#define	_GENTYPE(x)	(x & VBM_GENTYPE)

/* %%
** variable use
** 
** 
** 			 XXXXYYYYZZZZNNNN
** 			 101ddSSS--------
*/ 

#define	VBT_SIMVARUSE	%1010000000000000
#define	VBT_CPXVARUSE	%1010100000000000
#define	VBT_CONSTANT	%1011000000000000

#define	VBT_SIMPLE	%0000000000000000
#define	VBT_COMPLEX	%0000100000000000


/* %%
** simple variable use -- WARNING: changed update m/variables file and doc.
** 
** 				 XXXXYYYYZZZZNNNN
** 				%10100SSS--ig----
** i --> 0 'WPTR'
** i --> 1 'WSTR' that is we don't understand it
** 
*/ 

#define	VDMS_IDENTIFIER		%0000000000100000
#define	VDMS_GLOBALITY		%0000000000010000

#define	S_GLOBAL(w)		(w & VBT_GLOBALITY)
#define	S_INDETIFY(w)		(w & VBT_INDENTIFIER)

#define SIMPLEUNKNOWN		VBT_SIMVARUSE|VDMS_IDENTIFIER

/* %%
** complex variable use
** 
** 				 XXXXYYYYZZZZNNNN
** 				%10101SSShvgi----
** 
*/ 

#define	VDMX_IDENTIFIER		%0000000010000000
#define	VDMX_GLOBALITY		%0000000001000000
#define	VDMX_VECTOR		%0000000000100000
#define	VDMX_DIMENSION		%0000000000010000

#define	X_DIMENSION(w)		(w & VBT_DIMENSION)
#define	X_VECTOR(w)		(w & VBT_VECTOR)
#define	X_GLOBAL(w)		(w & VBT_GLOBALITY)
#define	X_INDETIFY(w)		(w & VBT_INDENTIFIER)


/* %%
** constants definition
** see m/variables for a better understanding
** 
** 
** 				 XXXXYYYYZZZZNNNN
** 				%10110SSS----fstt
** 
*/ 

#define	VBT_STRING		%1011000100001010	/* 0xB10A	*/
#define	VBT_FLOAT		%1011001000001000	/* 0xB208	*/
#define	VBT_DOUBLE		%1011010000001101	/* 0xB40D	*/
#define	VBT_BYTE		%1011000100000000	/* 0xB100	*/
#define	VBT_WORD		%1011000100000001	/* 0xB101	*/ 
#define	VBT_LONG		%1011001000000010	/* 0xB202	*/
#define	VBT_SGN_BYTE		%1011000100000100	/* 0xB104	*/
#define	VBT_SGN_WORD		%1011000100000101	/* 0xB105	*/
#define	VBT_SGN_LONG		%1011001000000110	/* 0xB206	*/


/* %%
** 
** 'EXTENDED' types.
** 
*/ 

#define XT_RESWORD	0xD800
#define XT_OBOPERATOR	0xD810
#define XT_OBEXTENSION	0xD820
#define XT_OBOPUNKNOWN	0xD830
#define XT_PMAPOP	0xD840
#define XT_PHANDLE	0xD850

#define XT_MAGICS	0xD8E0
#define XT_STOPPERS	0xD8F0
/* 
#define XT_
#define XT_
*/ 

#define	IN_PRIVHANDLER	XT_PHANDLE

/* %%
** variable definition
** 
** 
** 				 XXXXYYYYZZZZNNNN
** 
*/ 

#define	VDMD_COMPLEX		%0001000000000000
#define	VDMD_TYPE		%0000100000000000
#define	VDMD_INIT		%0000000010000000
#define	VDMD_SIGN		%0000000001000000
#define	VDMD_POINTER		%0000000000100000
#define	VDMD_STATICITY		%0000000000010000

#define	VDMD_CXANDTYPE		%0001100000000000
#define	_CANTYPE(x)		(x & VDMD_CXANDTYPE)

#define	VDB_COMPLEX		12
#define	VDB_TYPE		11
#define	VDB_INIT		 7
#define	VDB_SIGN		 6
#define	VDB_POINTER		 5
#define	VDB_STATICITY		 4

#define	COMPLEX(w)		(w & VDMD_COMPLEX)
#define	TYPE(w)			(w & VDMD_TYPE)
#define	INIT(w)			(w & VDMD_INIT)
#define	_SIGN(w)		(w & VDMD_SIGN)
#define	POINTER(w)		(w & VDMD_POINTER)
#define	STATICITY(w)		(w & VDMD_STATICITY)

#define	VD_SETTYPE(v,t)		(SETBIZZ (v, t))

#define	VD_SETINIT(x)		(SETBIZZ (x, VDMD_INIT))
#define	VD_SETSIGN(x)		(SETBIZZ (x, VDMD_SIGN))
#define	VD_SETPOINTER(x)	(SETBIZZ (x, VDMD_POINTER))
#define	VD_SETSTATICITY(x)	(SETBIZZ (x, VDMD_STATICITY))


/* %%
** variable definition extension word
** 
** 
** 				 XXXXYYYYZZZZNNNN
*/ 

#define	VDXM_INIT		%0000000000000011
#define	VDXM_MATRIX		%0000000000001100
#define	VDXM_MATRIXEXT		%0000000000110000
#define	VDXM_INITBLOCK		%0000111100000000

#define	VX_INIT(x)		(x & VDXM_INIT)
#define	VX_MATRIX(x)		(x & VDXM_MATRIX)
#define	VX_MATRIXEXT(x)		(x & VDXM_MATRIXEXT)
#define	VX_INITBLOCK(x)		(x & VDXM_INITBLOCK)

/* %%
** 
** stoppers
** 
*/ 

#define	__STOP		0xD8F0

#endif
