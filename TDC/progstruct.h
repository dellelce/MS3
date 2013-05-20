/* tony dee © 1992
** 
** experimental file
** 
** 
*/ 

#ifndef PROGSTRUCT_H
#define	PROGSTRUCT_H	1

#ifndef WSYSTEM_H
#include <wsystem.h>
#endif
#ifndef BSS
#define	BSS		ULONG
#endif


/* # __hunk_data
** # H_DATA
** 
** 
*/ 

typedef struct __hunk_data
{
ULONG	 hc_seqno;
ULONG	 hd_data;
BSS	 hd_bss;
ULONG	 hd_refs;
} H_DATA;

#define	H_DSIZE			OBSIZE (H_DATA)
#define	MAKEH_D()		Alloc (H_DSIZE)


/* # __hunk_code
** # H_CODE
** 
** 
*/ 

typedef struct __hunk_code
{
ULONG	 hc_seqno;
ULONG	 hc_code;
ULONG	 hc_refs;
} H_CODE;

#define	H_CSIZE			OBSIZE (H_CODE)
#define	MAKEH_C()		Alloc (H_CODE)


/* # __hunk_bss
** # H_BSS
** 
** 
*/ 

typedef struct __hunk_bss
{
ULONG	 hb_seqno;
ULONG	 hb_bss;
ULONG	 hb_refs;
} H_BSS;

#define	H_BSIZE			OBSIZE (H_BSS)
#define	MAKEH_B()		Alloc (H_BSIZE)

#endif
