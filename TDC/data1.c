/* tony dee © 1992
** 
** 
** this file has the same
** purpose of the data.c file,
** but, instead of the data.c file,
** I don't know what are the several
** functions purpose...
** 
** 
*/ 


#include <data.h>
#define	DATA1_C		1
#include <ms3fn.h>

/* %
** WriteBufArea
** LoadUpBuf
** 
** 
*/ 


/* # WriteBufArea
** 
** write down just a part of the
** filebuf
** 
*/ 

ULONG
WriteBufArea (file, buf, offsetstart, length)
UBYTE		*file;
REG FB		*buf;
REG ULONG	 offsetstart;
REG ULONG	 length;
{
ULONG		 lock;
ULONG		 woffset;

woffset = 0L;

if (file == (PTR) 0L)
	{
	lock = Output ();
	
	if (lock == 0L)
		{
		goto error;
		}
	}
else
	{
	lock = Open (file, MODE_NEWFILE);
	
	if (lock == 0L)
		{
		goto error;
		}
	}

writebuf:;

if (buf->fb_Size < offsetstart)
	{
	if (buf->fb_Size < length)	/* operation accomplished	*/
		{			/* partially			*/
		Write (lock, buf->fb_Buffer, buf->fb_Size);
		length -= buf->fb_Size;
		$	/* repeat operation	*/
		}
	else
		{
		Write (lock, buf->fb_Buffer, length);
		goto end;
		}
	
	}
else
	{
	
	
	}

end:;
return (TRUE);

badend:;
error:;
return (FALSE);
}


/* # LoadUpBuf
** 
** well, I gotta say it, It ain't well defined...
** try remind something about it!!
** 
** -- NOW DEFINING (I HAD A LOT OF TIME SPARE) --
** 
*/ 

FB *
LoadUpBuf (workfile, file)
ULONG		 workfile;
UBYTE		*file;
{
REG ULONG	 wlock;
REG FB		*filebuf;


if (lock == 0L)
	{
	wlock = Open (file, MODE_OLDFILE);
	
	if (ISZERO (wlock))
		{
		goto error;
		}
	}
else
	{
	wlock = lock;
	}


filebuf = CreateSingleBuf (FBM_SMALL);

if (ISZERO (filebuf))
	{
	goto error;
	}

badend:;
error:;

if (ISNOTZERO (filebuf))
	{
	BufDelete (filebuf);
	}

if (ISNOTZERO (wlock))
	{
	Close (wlock);
	}

return ((FB *) 0L);

end:;

Close (wlock);
return (filebuf);
}
