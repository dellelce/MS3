/* tony dee © 1992
** 
** should be the lowest touch-point with the OS
** (not with the coding part, since as you could see the pmap
** need direct traslation)
** 
** info:
** 	
** 	(by tony dee) since I am developing this
** 	program on the Aztec 3.6a compiler for the
** 	Amiga computer, the use of the register
** 	variables has been planned thinking that this
** 	compiler permits the use of only 2 address
** 	registers as REG vars (a2/a3) meanwhile the
** 	other available are used one (a4) as global
** 	data pointer another as local data pointer (a5),
** 	one NEVER used in anycase (A6, that is used
** 	only in hubs..), this compiler, finally, 
** 	does not trace the real usage of registers so...
**	you'll have always a bad program... (not so quick, etc...)
** 	
*/ 

#ifndef WSYSTEM_H
#define	WSYSTEM_H		1

/* 
** environment name
** 
*/ 

#define	AMIGA			1

/* 
** we need so that other header will not load exec/types.h
** 
*/ 

#define	EXEC_TYPES_H		1


#define	UN			unsigned
#define	BYTE			char
#define	UBYTE			UN char
#define	WORD			int
#define	UWORD			UN int
#define	SHORT			WORD
#define	USHORT			UWORD
#define	LONG			long
#define	ULONG			UN long
#define	BOOL			short
#define	FLOAT			float
#define	DOUBLE			double
#define	VOID			void
#define	COUNT			USHORT	/* standard counter type	*/
#define	LCOUNT			ULONG	/* big counter mode		*/
#define	LBOOL			ULONG
#define	CPIECE			USHORT	/* that's it, here		*/
#define OFFSET			SHORT
#define	BSS			ULONG
#define	STR			UBYTE *
#define	PTR			VOID *

#define	FALSE			0
#define	TRUE			1
#define	LFALSE			0L
#define	LTRUE			1L

#define	NULL			0L	/* a pointer is formed by 1 long*/

/* amiga flags for memory allocation
** I don't think them will be used
** 
*/

#define MEMF_PUBLIC		(1L <<  0)
#define MEMF_CHIP		(1L <<  1)
#define MEMF_FAST		(1L <<  2)
#define MEMF_CLEAR		(1L << 16)
#define MEMF_LARGEST		(1L << 17)

#define	_BLANCHE	MEMF_CLEAR | MEMF_PUBLIC

VOID	 FreeMem ();
ULONG	 _tot_memory ();
ULONG	 _memory ();
VOID	*_alloc ();
VOID	*_fast_alloc ();
BOOL	 _amigarawinit ();


#define	Copy(x, y, z)		CopyMemQuick (x, y, (ULONG) sizeof (z))
#define	CopyAS(x, y, z)		CopyMemQuick (x, y, z)
#define	Free(x, y)		FreeMem (x, y)


#define	Memory()		_tot_memory ()
#define	Avail()			_tot_memory ()
#define	MaxAvail()		_memory ()
#define	FastAlloc(x)		_fast_alloc (x)
#define	Alloc(x)		_alloc (x)
#define	MEMORY()		_tot_memory ()
#define	MEM()			_tot_memory ()
#define	Mem()			_tot_memory ()
#define	SysRawInit()		_amigarawinit ()

/* 
** amigaDOS interfacing data.. may be easily changed 
** to standard C programs..
** 
*/ 

#define	FHANDLE			ULONG

FHANDLE		 Open ();
VOID		 Close ();
LONG		 Read ();
LONG		 IoErr ();
ULONG		 Input ();
ULONG		 Output ();

#define	MODE_OLDFILE		1005L
#define	MODE_NEWFILE		1006L

#define OFFSET_BEGINNING	-1L
#define OFFSET_CURRENT		 0L
#define OFFSET_END		 1L
#define OFFSET_BEGINING		OFFSET_BEGINNING

/* 
** extended features
** 
*/ 

#define	MemClear(x, y)		_clearmem (x, y)
#define	QuickMemClear(x, y)	_quickclearmem (x, y)
#define	TurboMemClear(x, y)	_turboclearmem (x, y)

#define	OBSIZE(x)		(ULONG) sizeof (x)

#endif
