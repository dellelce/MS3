/* tony dee © 1992
** 
** a very quick (and effective) string comparer
** 
*/ 

#define REG		register
#define VOID		void
#define	UN		unsigned
#define	LONG		long
#define	ULONG		UN LONG
#define	BYTE		char
#define	UBYTE		UN BYTE
#define	SHORT		short
#define	USHORT		UN SHORT
#define	WORD		SHORT
#define	UWORD		UN WORD
#define	BOOL		USHORT
#define	FALSE		0
#define	TRUE		1
#define	ISZERO(x)	(x == 0)
#define	ISNOTZERO(x)	(x != 0)


BOOL
_far_strcmp (str0, str1)
REG UBYTE	*str0;
REG UBYTE	*str1;
{
REG ULONG	 cnt;

cnt = 0;

if ((* (ULONG *) str0) == (* (ULONG *) str1))
	{
	goto checkforzeroes;
	}
else
	{
	if ((* (UWORD *) str0) == (* (UWORD *) str1))
		{
		goto end;
		}
	else
		{
		goto error;
		}
	}

checkforzeroes:;

str1 += 4;

next0:;

if (ISZERO (* (++cnt, ++str0)))
	{
	goto end;
	}
else
	{
	if (cnt == 3)
		{
		++str0;
		goto checkfullstr;
		}
	
	goto next0;
	}

checkfullstr:;
next:;

if ((*str0) == (*str1))
	{
	if (ISZERO (*str0))
		{
		goto end;
		}
	else
		{
		str0 ++;
		str1 ++;
		
		goto next;
		}
	}
else
	{
	goto error;
	}

	
end:;
return (TRUE);

error:;
return (FALSE);
}
