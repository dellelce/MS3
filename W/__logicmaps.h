/* tony dee © 1992
** 
** logicmaps definition 
** 
** They in the short future will be used
** to replace code such as the one contained
** in the 'traslate4.c', I think it will surely
** shrink code and maybe will evem fasten it!
** 
** 
*/ 

#ifndef LOGICMAPS_H
#define	LOGICMAPS_H

#ifndef WSYSTEM_H
#include <wsystem.h>
#endif
#ifndef LOGICS_H
#include <logics.h>
#endif

#define	LMAP		UWORD
#define	NEXTLMAP (x)	x += 2
#define	LOGICNULL	0xFFFF


typedef struct logicmaster
{
LMAP	*m_current;
LMAP	*m_previous;
LMAP	*m_container;
GROUP	*m_group;
} MASTER;

#define	MASTERSIZE		(ULONG) sizeof (MASTER)


/* 
** kind of action
** 
** << HUGE WAY	>>
** 
*/ 

#define	_NEWLMAP		0x0001
#define	_SKIPLINE		0x0002
#define	_
#define	_
#define	_

#define	_WAITBRACKET0		0x8001	/* '('		*/
#define	_WAITBRACKET1		0x8002	/* '['		*/
#define	_
#define	_
#define	_

#define	BOUNDARY		0x8000


/* 
** kind of action
** 
** << SMALL WAY	>>
** 
*/ 

#define	_NLM			_NEWLMAP
#define	_SKL			_SKIPLINE
#define	_WB0			_WAITBRACKET0
#define	_WB1			_WAITBRACKET1
#define	_
#define	_
#define	_

#endif
