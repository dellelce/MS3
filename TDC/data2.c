/* tony dee © 1992
** 
** this file was part of the data.c file
** since it was some too big I moved some routines
** to this file
** 
*/ 

#define	DATA2_C		1

#include <tonyexend.h>
#include <data.h>
#include <names.h>
#include <ms3fn.h>

#ifdef	 USE_IN_MS3
#include <logics.h>
#endif


/* %%
** BufDelete
** BufSave
** 
** 
** 
*/ 


/* # BufDelete
** 
*/

VOID
BufDelete (buf)
REG FB		*buf;
{
REG VOID	*place;
REG VOID	*place1;

if (ISNOTZERO (buf->fb_Name))
	{
	place = buf->fb_Name;
	FreeMem (((BNAME *) place)->bf_Name, ((BNAME *) place)->bf_Size);
	FreeMem (place, BNSIZE);
	}

if (ISNOTZERO (buf->fb_ArcHead))
	{
	FREENODE (buf->fb_ArcHead, buf);
	}

if (ISNOTZERO (buf->fb_BufPieces))
	{
	place1 = place = (VOID *) buf->fb_BufPieces.tl_First;
	
	FOREVER
	{
	place1 = ((TNODE *) place1)->tn_Next;
	
	if (ISZERO (place1))
		{
		break;
		}
	
	place = place1;
	FREE (buf->fb_BufPieces, place);
	
	BufDelete (place);
	}
	
	FreeMem (buf->fb_BufPieces, TLSIZE);
	}

FreeMem (buf, FBSIZE);
}


/* # BufSave
** 
*/ 

BOOL
BufSave (file, filebuf)
REG ULONG	 file;
FB		*filebuf;
{
REG FB		*fb0;
REG FB		*fb1;
REG BOOL	 type;

if (ISZERO (file))
	{
	file = Output ();
	
	if (ISZERO (file))
		{
		return (FALSE);
		}
	
	type = FALSE;	/* does not close file at end of work	*/
	}
else
	{
	file = Open (file, MODE_NEWFILE);
	
	if (ISZERO (file))
		{
		return (FALSE);
		}
	
	type = TRUE; 	/* closes file at end of work	*/
	}

if (ISZERO (filebuf->fb_BufPieces))
	{
	if ((Write (file, filebuf->fb_Buffer, filebuf->fb_LastUsed)) <
							filebuf->fb_LastUsed)
		{
		goto error;
		}
	
	goto end;
	}
else
	{
	fb0 = (FB *) filebuf->fb_BufPieces.tl_First;
	
	FOREVER	/* here things must be modified	*/
	{
	if ((Write (file, fb0->fb_Buffer, fb->fb_LastUsed)) < fb->fb_LastUsed)
		{
		goto error;
		}
	
	fb1 = (FB *) fb0.tn_Next;
	
	if (ISZERO (fb1))
		{
		goto end;
		}
	
	fb0 = fb1;
	}
	}

end:;

if (ISTRUE (type))
	{
	Close (file);
	}

return (TRUE);

error:;

if (ISTRUE (type))
	{
	Close (file);
	}

return (FALSE);
}
