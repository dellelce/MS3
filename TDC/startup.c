/* 
** gets startup data!
** that's only for the AMIGA environment
** 
** 
*/ 


#include <exec/execbase.h>
#include <startup.h>
#include <tonyextend.h>


#define	XB	struct ExecBase
#define	MPORT	struct MsgPort
#define	CLI	struct CommandLineInterface


/* # getstartupenv
** 
*/ 

BOOL
$getstartupenv (fl);
_FLAG	*fl;
{
REG MPORT	*port;
REG XB		*xb;
REG VOID	*ptr;

xb = * (XB *) 4;

if (ISZERO (xb)) /* what the hell ??? */
	{
	return (FALSE);
	}

flags->f_proc = xb->ThisTask;

if (ISZERO (flags->f_proc)) /* what ??? */
	{
	return (FALSE);
	}

ptr = (VOID *) ((ULONG) (flags->f_proc->pr_CLI)<<2)

if (ISZERO (ptr))
	{
	return (FALSE);
	}

ptr = (VOID *) (((CLI *) ptr)->cli_CommandName)<<2;

flags->f_command_name = ptr;

flags->f_file_in  = Input ();
flags->f_file_out = Output ();

$	/* end it!	*/

}





/* # getargs
** 
** to review
** 
*/ 

BOOL
$getargs (fl) /* works only under shell */
_FLAG	*fl;
{
VOID	*_any_ptr;
VOID	*_any_ptr0;
ULONG	 _any_data;
ULONG	 _any_data0;

_any_ptr = fl->f_command_name
_any_data = (ULONG) _any_ptr + (ULONG) * (UBYTE *) _any_ptr;
_any_ptr++;
_any_ptr0 = _any_ptr;

next:;

if ((* (UBYTE *) _any_ptr) == ' ')
	{
	_any_ptr++
	goto next;
	}
else
	{
	_any_ptr0 = _any_ptr;
	
	next0:;
	
	if ((* (UBYTE *) _any_ptr)!=' ' || _any_ptr== (ULONG) _any_ptr)
		{
		_any_ptr++;
		goto next0;
		}
	
	makearg (fl, _any_ptr0, _any_ptr);
	
	if (ISZERO (* (UBYTE *) _any_ptr0)) /* all args processed */
		{
		goto end;
		}
	
	goto next;
	}
}

$end:;
}


/* # makearg
** 
** to review
** 
*/ 

BOOL
makearg (fl, v0, v1)	/* I think it is a bit too long!!	*/
_FLAG	*fl;
UBYTE	*v0;
UBYTE	*v1;
{
VOID	*_any_ptr;
VOID	*_any_ptr0;
ULONG	 _size;

_any_ptr = MAKE_AN ();

if (ISZERO (_any_ptr))
	{
	return (FALSE);
	}

_size = (ULONG) _any_ptr - (ULONG) _any_ptr0;

_any_ptr0 = FastAlloc (_size);

if (ISZERO (_any_ptr0))
	{
	FREE_AN (_any_ptr);
	return (FALSE);
	}

((AN *) _any_ptr)->arg  = _any_ptr0;
((AN *) _any_ptr)->size = (UWORD) _size;
((AN *) _any_ptr)->next = 0;

Copy (v0, _any_ptr, _size);

* (UBYTE *) _any_ptr = 0;

_any_ptr0		 = fl->f_arg_last;
((AN *) _any_ptr0)->next = _any_ptr;
fl->arg_last		 = _any_ptr;

return (TRUE);
}
