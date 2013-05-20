/* tony dee © 1992
** 
** Tony Files Format (TFF) handling definition
** 
** currently updating to v2
** 
*/ 

#ifndef TONYF_H
#define TONYF_H		1

#ifndef  WSYSTEM_H
#include <wsystem.h>
#endif
#ifndef	 TONYLISTS_H
#include <tonylists.h>
#endif


/* # FileHead
** # FHEAD
** 
** TFF files regarding MS3 programs
** currently contain just one segment
** 
*/ 

struct FileHead
{
LONG	 Magic;		/* TFF file identifier ('TONY')	*/
UWORD	 Type;		/* 'global type' of file	*/
UWORD	 Segs;		/* no of segmets		*/
ULONG	 SizeFirst;	/* size of first segment	*/
ULONG	 TypeFirst;	/* type of first segment	*/
};

#define	FHEAD		struct FileHead
#define	FHEADSIZE	(ULONG) struct (FHEAD)

#define	FHD_MAGIC(x)	(x->Magic)
#define	FHD_TYPE(x)	(x->Type)
#define	FHD_SEGSNO(x)	(x->Segs)
#define	FHD_1STSIZE(x)	(x->SizeFirst)
#define	FHD_1STTYPE(x)	(x->TypeFirst)

#define	MAGIC		'TONY'
#define	FT_PROCMAP	0xc0000000L
#define	FT_NORMASC	0x10000000L
#define	FT_DIRECTORY	0xddddddddL


/* # FileSegHead
** # FSHEAD
** 
*/ 

struct FileSegHead
{
ULONG	SegSize;
LONG	SegType;
};

#define	FSHEAD		struct FileSegHead



/* # fh
** # FH
** 
** read-only file structure
** used for reading an MS3 text file
** 
*/ 

#define	FH		struct fh

struct fh 				/* struttura gestione file	*/
{
TNODE			 fhnode;	/* chain			*/
VOID			*head;
UBYTE			*buf;		/* buffer			*/
LONG			 size;		/* buffer size	 		*/
ULONG			 count;		/* current character in buffer	*/
FHANDLE			 fm;		/* dos handler			*/
LONG			 error;		/* last error			*/
ULONG			 lines;		/* no o'lines			*/
VOID		       (*fhandle) ();	/* will it ever be used?	*/
};

#define	FHSIZE		(ULONG) sizeof (FH)
#define	sizefh		FHSIZE
#define BUFSIZE		1024

/* FH structure remodeling idea:
** 
** 
** typedef struct BasMS3File
** {
** TNODE	 bmf_ArcNode;
** FHANDLE	 bmf_Handle;
** LONG		 bmf_LastDOSError;
** } BASFH;
** 
** 
** typedef struct BufferedFileH
** {
** BASFH	 bfh_Handle;
** UBYTE	*bfh_Buffer;
** ULONG	 bfh_Size;
** ULONG	 bfh_Current;
** } BFH;
** 
** 
** typedef struct MS3FileHandle
** {
** BFH		 mfh_XHandle;
** UBYTE	*mfh_FileName;
** FHEAD	 mfh_FileHead;
** FSEGMENT	 mfh_CurrentSeg;	/* optional/advanced usage	*/
** ULONG	 mfh_Lines;
** ULONG	 mfh_Flags;
** } FH;				/* or MFH			*/
** 
*/ 

/* 
** private error types (from 500 to 599)
** only 599 (end of file) is really used!
** 
*/ 

#define	FE_TYPEREAD		500 /* ???	*/
#define	FE_NONASCII		501
#define	FE_ENDOFFILE		599


/* # Directory
** # DIR
** 
** ...added prefix 'dir_'; look around if needed to
** update code
** 
*/ 

typedef struct Directory
{
UWORD	dir_EachDirItems;
UWORD	dir_GlobalDirItem;
UWORD	dir_NextDir;
} DIR;

#endif
