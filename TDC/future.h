/* tony dee © 1991
** 
** 
** F U T U R E  U S E
** 
** 
*/ 

#ifndef FUTURE_H
#define	FUTURE_H

#ifndef WSYSTEM_H
#include <wsystem.h>
#endif
#ifndef BLOCKS_H
#ifndef <blocks.h>
#endif


typedef struct _place
{
BLOCK	 p_Block;
WPTR	 p_Offset;
WPTR	 p_Data;		/* free use				*/
} PLACE;

#ifndef VAR
/* # varu FROM VARDEFS.H
** # VARU
** 
** taken from vardefs.h
** and extended!
** 
** 
*/ 

typedef	UWORD	VAR;

typedef struct varu
{
VAR	 vardat [7];
} VARU;

#define	VUSIZE		OBSIZE (VARU)

#define	VUM(x,u)	(x->vardut [u])

#define	HEAD(x)		(VUM (x, 0))
#define	V_FIRST(x)	(VUM (x, 1))
#define	V_SECOND(x)	(VUM (x, 2))
#define	V_THIRD(x)	(VUM (x, 3))
#define	V_FOURTH(x)	(VUM (x, 4))
#define	V_FIFTH(x)	(VUM (x, 5))
#define	V_PRELAST(x)	(VUM (x, 6))
#define	V_LAST(x)	(VUM (x, 7))
#endif

typedef struct logicalvar
{
PLACE		 lv_PmapPlace;
UWORD		 lv_RealPlace;
HUNK		*lv_HomeHunk;
ULONG		 lv_BigOffset;
VAR		*lv_Definition;
} LVAR;


/* real places
** 
** 
** 
*/ 

#define	LVRP_STACK		0x0001
#define	LVRP_REGISTER		0x0002
#define	LVRP_LOCALSTATIC	0x0003
#define	LVRP_GLOBALSTATIC	0x0004

typedef enum 
{
REG0,
REG1,
REG2,
REG3,
REG4,
REG5,
REG6,
REG7
} REGTYPE;

#define	R_ADDRESS	0x1000
#define	R_DATA		0x2000

#define	RA0	R_ADDRESS | REG0
#define	RA1	R_ADDRESS | REG1
#define	RA2	R_ADDRESS | REG2
#define	RA3	R_ADDRESS | REG3
#define	RA4	R_ADDRESS | REG4
#define	RA5	R_ADDRESS | REG5
#define	RA6	R_ADDRESS | REG6
#define	RA7	R_ADDRESS | REG7

#define	RD0	R_DATA | REG0
#define	RD1	R_DATA | REG1
#define	RD2	R_DATA | REG2
#define	RD3	R_DATA | REG3
#define	RD4	R_DATA | REG4
#define	RD5	R_DATA | REG5
#define	RD6	R_DATA | REG6
#define	RD7	R_DATA | REG7

#endif
