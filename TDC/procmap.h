/* tony dee © 1992
** 
** 
** 
*/ 

#ifndef PROCMAP_H
#define	PROCMAP_H	1
#ifndef	 WSYSTEM_H
#include <wsystem.h>
#endif
#ifndef	 BLOCKS_H
#include <blocks.h>
#endif


/* # ProcessMap
** # PMAP
** 
** Process map basic definition
** 
*/ 

#define	PMBLOCKS		11

typedef struct ProcessMap
{
BOOL	 Library;		/* is it a 'linked' library?		*/
UWORD	 Status;		/* current pmap status			*/
UWORD	 Version;		/* file compiler version		*/
UWORD	 FirstComp;		/* first compatible			*/
UWORD	 BlocksNum;		/* number of blocks			*/
UWORD	 PMHeaderSize;		/* pmap header size			*/
UWORD	 TotCalledObj;		/* total no of called object - to check */
BLOCK	*Pblocks[PMBLOCKS];	/* process map blocks			*/
} PMAP;

#define	PROCMAP		 PMAP	/* newer definition			*/

#define	_Directory	 BT_DIRECTORY
#define	_UserBlock	 BT_USER	/* private block??		*/
#define	_Specialties	 BT_SPECIAL	/* amiga stuff and others...??	*/
#define	_WorkStrings	 BT_WORKSTRINGS
#define	_ProgramStrings	 BT_PROGSTRINGS
#define	_Starter	 BT_STARTER
#define	_Actions	 BT_ACTION
#define	_Objects	 BT_OBJECT
#define	_Structures	 BT_STRUCTURE
#define	_Globals	 BT_GLOBALS
#define	_Initialized	 BT_INIT
#define	_Functions	 BT_FUNCTION
#define	_DebugData	 BT_DEBUG
#define _LAST		 _DebugData

#define	PMSIZE		OBSIZE (PMAP)


/* PMAP possible statuses
** 
*/ 

#define	PMS_STARTUP	0x0000	/* initial process map status		  */
#define	PMS_WRITE	0x0001	/* data are being inserted in the pmap	  */
#define	PMS_READ	0x0002	/* reading contents of pmap		  */
#define	PMS_LINK	0x0003	/* processmap is being linked with a lib! */
#define	PMS_REVIEW	0x0004	/* processmap is being reviewed		  */
#define	PMS_PACK	0x0005	/* processmap is being packed		  */
#define	PMS_UPDATE	0x0006	/* processmap is being turned to new rel. */

#define	PM_STATUS(x,y)	(x->Status = y)
#define	PM_READING(x)	(PM_STATUS (x, PMS_READ))
#define	PM_WRITING(x)	(PM_STATUS (x, PMS_WRITE))

/*
** aliases for block types
**
*/

#define	BT_WORKSTRINGS	BT_WORKSTRING
#define	BT_DATA		BT_INITIALIZED


/*
** sizes of process sizes (how to use these flags?!)
**
*/

#define	PMT_SMALL	 0x00000001L
#define	PMT_MIDSIZE	 0x00000002L
#define	PMT_BIG		 0x00000003L
#define	PMT_VERYBIG	 0x00000004L
#define	PMT_LAST	 PMT_VERYBIG

#endif
