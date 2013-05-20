/* 
** general flags definition
** for the AMIGA environment
** 
*/ 

#ifndef STARTUP_H
#define	STARTUP_H 1

#ifndef WSYSTEM_H
#include <wsystem.h>
#endif


#define	FLAG_NO_STD_IO			0
#define	FLAG_NO_STD_WARNING		1
#define	FLAG_NO_STD_ERROR_SHOW		2
#define	FLAG_SECONDARY_WARNING		3
#define	FLAG_SECONDARY_ERROR_SHOW	4
#define	FLAG_SAVE_PMAP			5
#define	FLAG_NO_CODE_FILE		6
#define	FLAG_QUIT_ON_WARNING		7
#define	FLAG_MAKE_ALTERNATIVE_FILES	8
#define	FLAG_WORDS_TO_LONGS		9

#define	PROC	struct Process *

/* # flag
** # FLAG
** # _FLAG
** 
*/ 

struct _flag
{
ULONG	 f_flag_short;
BOOL	 f_shell;
ULONG	 f_file_in;
ULONG	 f_file_out;
VOID	*f_command_name;
PROC	*f_proc;
USHORT	 f_args_no;
UBYTE	*f_argv [100];
};

#define	_FLAG		struct _flag
#define	FLAG		struct _flag *

/* # _arg_node
** # AN
** 
** -- unused
** 
*/ 

#define	AN		struct _arg_node
#define	ANSIZE		OBSIZE (AN)
#define	MAKE_AN ()	FastAlloc (ANSIZE)
#define	FREE_AN (x)	Free (x, ANSIZE)
#define	NEXT_AN (x)	x->next

struct _arg_node
{
AN	*next;
UBYTE	*arg;
UWORD	 size;
};


/* # messie
** # MESSIE
** 
*/ 

#define	MESSAGE		ULONG	/* $....		*/

typedef struct messie
{
MESSAGE	 head;
UWORD	 type;
AN	*first;
AN	*last;
UWORD	 args;
ULONG	 text_info;
UBYTE	*text;
VOID	*special_args;
} MESSIE;

#define	MSIZE		OBSIZE (MESSIE)

#endif
