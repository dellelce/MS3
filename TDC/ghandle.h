/* tony dee © 1992
** 
** global handler definition v1.23
** 
*/ 

#ifndef		GHANDLE_H
#define		GHANDLE_H 1

#ifndef	LOGICS_H
#include <logics.h>
#endif
#ifndef	CODE_H
#include <code.h>
#endif
#ifndef	STARTUP_H
#include <startup.h>
#endif
#ifndef	NAMES_H
#include <names.h>
#endif


/* # GlobalHandle
** # GHANDLE
** 
*/ 

typedef struct GlobalHandle
{
TLIST			 fl;			/* MS3 read files	      */
TLIST			 filebufs;		/* 'virtual' files	      */
VLIST			 locals;
VLIST			 globals;
VOID			*traslatefile;		/* CAST to FH...	      */
ULONG			 lasterror;
UBYTE			*lasterrorstring;	/* optional		      */
FLAG			 flags;			/* to update		      */
ULONG			 envtype;
VOID			*environment;
/*TITEM			*currentitem;		 an error here...	      */
NAMEBASE		*namebase;
/*ATTRLIST		 atlist;		  list of attributes...	      */
UWORD			 trlevel;		/* I think it is unused	      */
ULONG			 output;
ULONG			 input;
} GHANDLE;

#define	files		 filebufs
#define	filelist	 fl
#define	depth		 trlevel


/*
** Environments
**
*/
#define	ET_CODING	0x0L
#define ET_PROCESSING	0x1L

/* 
** Macros
** 
*/

#define	delghandle (x)		Free (x, (ULONG) sizeof (GHANDLE))

#endif
