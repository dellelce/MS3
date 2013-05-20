/* tony dee © 1992
** 
** 
*/ 

#ifndef	 WSYSTEM_H
#include <system.h>
#endif
#ifndef  TONYLISTS_H
#include <tonylists.h>
#endif

#define MEMPAGESIZE		8L
#define MEMPAGEMASK		0xfffffff8L
#define	RIGHTSIZE(x)		(x + (x - (x & MEMPAGEMASK)))



typedef struct memblock
{
TNODE	 mb_ArcNode;
PTR	 mb_Bottom;
PTR	 mb_Top;
ULONG	 mb_Size;
} MEMBLOCK;

#define MBLOCKSIZE		OBSIZE (MEMBLOCK)


typedef struct memchain
{
PTR	 mc_Next;
SHORT	 mc_Size;
} MCHAIN;
