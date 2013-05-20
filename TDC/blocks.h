/* 
** 
** 
** Blocks Management Header
** By Tony Dee
** 
** 
*/

#ifndef BLOCKS_H
#define	BLOCKS_H 1


#ifndef	WSYSTEM_H
#include <wsystem.h>
#endif


/* # Block
** 
*/ 

typedef struct Block
{
struct Block	*BlockNext;
struct Block	*BlockLast;
ULONG		 BlockSize;
UBYTE		 BlockItemsType;
UWORD		 BlockItemsCount;
UWORD		 BlockItemsSize;
UWORD		 BlockLastByte;
} BLOCK;

#define	B_		Block

#define	REAL(x)		(VOID *) ((ULONG) x->B_LastByte)
#define	BS		OBSIZE (BLOCK)
#define BLOCKSIZE 	OBSIZE (BLOCK)
#define	BSPTR		(PTR) BS
#define	BP		BLOCK *
#define	GET(y, x)	((ULONG) x + (ULONG) y + BS)
#define	BSTR(y, x)	(UBYTE *) GET (y, x)
#define BLOCKUSED(x)	(x->B_LastByte)
#define	B_FIRST(x)	(UWORD *) (x + BSPTR)
#define	B_LAST(x)	(UWORD *) (x + BSPTR + x->B_LastByte)
#define	B_INIT(x)	((x->B_Next = (BP) 0L); (x->B_Last =  (BP) 0L))
#define	B_ITEMS(x)	(x->B_ItemsCount)


#define	BT_PRIVATE	0xff /* privato dati non di linguaggio	*/
#define BT_REFERENCES	0xfe /* referenze (per l'assembler !)	*/
#define	BT_DIRECTORY	0x00 /* directory list			*/
#define	BT_USER		0x01 /* user private data		*/
#define	BT_SPECIAL	0x02 /* specialties (??)		*/
#define	BT_WORKSTRINGS	0x03 /* non-program strings		*/
#define BT_PROGSTRINGS	0x04 /* program strings			*/
#define BT_STARTER	0x05 /* starter code			*/
#define	BT_ACTION	0x06 /* actions definitions		*/
#define	BT_OBJECT	0x07 /* object definitions		*/
#define	BT_STRUCTURE	0x08 /* structures definitions		*/
#define	BT_GLOBALS	0x09 /* globals big data		*/
#define	BT_INIT		0x0a /* initialized big data (??)	*/
#define	BT_FUNCTIONS	0x0b /* functions definitions		*/
#define	BT_DEBUGDATA	0x0c /* debugger data			*/

#endif
