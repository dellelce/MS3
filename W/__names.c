/* names search  ** NEW VERSION **
** by tony dee
** 
** under MS3 language -- developing 
** 
** should be new version...
** 
** 
*/ 


#include <wsystem.h>
#include <tonylists.h>


byte $getbyte (file);


#define	BYT_EMPTYCHAR	0x00
#define	BYT_ERROR	0x01
#define	BYT_SPECIAL	0x02
#define	BYT_ASC		0x03
#define	BYT_NUMBER	0x04
#define	BYT_ENDOFLINE	0x05
#define	BYT_ENDOFFILE	0x06
#define	BYT_UNUSED	0xff

/* amiga io support
** 
*/ 

#define	PRIER_ENDOFFILE		1000
#define	FILE			struct fi
#define	SYS_ENDOFFILE		(ULONG) -1L	/* returned by Read ()	*/

typedef struct smartbyte
{
UBYTE	 sb_byte;
UBYTE	 sb_type;
} B;

typedef struct fi
{
TNODE	 f_filenode;		/* <-- do we need this??	*/
ULONG	 f_sysh;
UBYTE	*f_name;
UBYTE	*f_buffer;
UWORD	 f_bufsize;
UWORD	 f_bufcurrent;
UWORD	 f_bufmarker;
ULONG	 f_bufused;
UWORD	 f_lines;
ULONG	 f_error;
B	 f_bbuf;
} FI;


/* # hget
** 
** 
*/ 

BOOL
hget (fi)
REG FI		*fi;
{

hget_start:;

if (fi->f_bufsize == fi->f_bufcurrent)
	{
	fi->f_bufused = Read (fi->f_sysh, fi->f_buffer, (ULONG) fi->f_bufsize);
	
	if (fi->f_bufused == SYS_ENDOFFILE)
		{
		$
		}
	
	if (fi->f_bufused < fi->f_bufsize)
		{
		fi->f_error = IoErr ();
		goto error;
		}
	
	}

readchar:;

fi->f_bbuf.sb_byte = fi->f_buffer [fi->f_bufcurrent];
fi->f_bufcurrent ++;

$getchtype (&fi->f_bbuf);

if (fi->f_bbuf.sb_byte == BYT_ENDOFLINE)
	{
	fi->f_line ++;
	
	goto hget_start;
	}

end:;
return (TRUE);

error:;
return (FALSE);
}


#define	SNAME		UWORD			/* simulated under this ver. */
#define	SNSIZE (x)	* (UWORD *) x
#define	SNSTR (x)	(UBYTE *) (((ULONG) (UWORD *) x) + 2L)

/* # getname

getname (group)
GROUP		*group;
{
$file		*fi;
SNAME		*ns;
ULONG		 nacount;
UBYTE		 bastype;

here:;

$getbyte (fi, &by);

if (byte->type != BYT_ERROR)
	{
	if (byte->type == BYT_EMPTYCHAR)
		{
		if (nacount == 0)
			{
			goto here;
			}
		else
			{
			$save_word:;
			}
		}
	else
		{
		if (byte->type == BYT_ASC)
			{
			bastype = BYT_ASC; /* sorry! but this should shorten */
			nacount++;	   /* things!			     */
			}
		
		if (byte->type == BYT_NUMBER)
			{
			}
		
		if (byte->type == BYT_SPECIAL)
			{
			if (bastype != BYT_UNUSED)
				{
				}
			}
		}
	}
}
