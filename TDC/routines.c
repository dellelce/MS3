/***********************************************
 **					      **
 ** @@ 1990-92 TDC basical compiler routines  **
 ** This routines will be used by	      **
 ** By The MS3 Compiler			      **
 ** (Now on release 0.10)		      **
 **					      **
 ***********************************************/


#include <logics.h>
#include <globalhandle.h>
#ifndef	 TONYEXTEND_H
#include <tonyextend.h>
#endif
#include <ms3fn.h>

/* %%
** hopen
** hclose
** hclosedown
** hnextblock
** hget
** goback
** hskipblank
** getrawstr
** hgetname
** getanumber
** getalphaname
** getspecial
** createsname
** delsname
** 
** 
*/ 

/************************************************
*						*
* @@ TDC MS3 basical filing routines		*
*						*
************************************************/


#define	ROUTINES.C	1


/* # hopen
** 
*/ 

FH *
hopen (ghandle, name)			/* simply, it opens a file	*/
GHANDLE		*ghandle;
UBYTE		*name;
{
REG FH		*this;
REG TLIST	*fl;
REG FHANDLE	 file;

file = Open (name, MODE_OLDFILE);

if (ISZERO (file))
	{
	goto error;
	}

fl = ghandle->fl;

this = (FH *) Alloc (sizefh);

if (ISZERO (this))
	{
	Close (file);
	goto error;
	}

this->fm  = file;
this->buf = (UBYTE *) Alloc (BUFSIZE);

if (ISZERO (this->buf))
	{
	Close (file);
	Free (this, sizefh);
	goto error;
	}

this->size = BUFSIZE;

if (ISZERO (fl->tl_Last == fl->tl_First))
	{
	fl->tl_Last = fl->tl_First = this;
	goto end;
	}

fl->tl_Last.tn_Next	= this;
fl->tl_Last		= this;

end:;
return (this);

error:;
return ((FH *) 0L);
}


/* # hclose
** 
*/ 

VOID
hclose (ghandle, fh)		/** chiude il file **/
GHANDLE		*ghandle;
REG FH		*fh;
{
REG TLIST	*filelist;

filelist = &ghandle->filelist;

FREE (filelist, fh);
Close (fh->fm);

Free (fh->buf, BUFSIZE);
Free (fh,	sizefh);
}


/* # hclosedown
** 
*/ 

BOOL
hclosedown (tl)
REG TLIST	*tl;
{
REG TNODE	*tnode0;
REG TNODE	*tnode;

tnode = tl->tl_First;

if (ISZERO (tnode))
	{
	return (FALSE);
	}

FOREVER
{
tnode0 = tnode->tn_Next;

if (ISZERO (tnode0))
	{
	return (FALSE);
	}

Close (tnode0);
tnode = tnode0;
}
} /* closes 'hclosedown' */


/* # hnextblock
** 
*/ 

VOID
hnextblock (fh)		/* gets next block	*/
REG FH		*fh;
{
REG FHANDLE	*th = fh->fm;
REG ULONG	 v;

v = Read (th, fh->buf, BUFSIZE);

if (v == (ULONG) -1L)
	{
	fh->error = FE_ENDOFFILE;
	}

fh->size  = v;
fh->count = 0L;
fh->error = IoErr ();	/* for fool people	*/

end:;
}


/* # hget
** 
*/ 

UBYTE
hget (fh)		/* prende prossimo carattere	*/
REG FH	*fh;
{
if (fh->count != fh->size)
	{
	init:;
	
	count++;
	return (fh->buf [fh->count]);
	}
else
	{
	hnextblock (fh);
	
	if (ISNOTZERO (fh->error))
		{
		goto error;
		}
	
	goto init;
	}

error:;
return (0);
}


#define _GOBACK(x) x->count--

/* # goback
** 
*/ 

VOID
goback (fh)		/* goes back of a char		*/
REG FH	*fh;		/* this is just an example	*/
{
fh->count--;
}


/* # hskipblank
** 
*/ 

BOOL
hskipblank (fh)
REG FH		*fh;
{
REG USHORT	 cnt = 0;
REG UBYTE	 ch;

here:;

ch = hget (fh);
	
if (ch == 0x00)
	{
	if (ISNOTZERO (fh->error))
		{
		goto here;
		}
	
	goto error;
	}

if (ch == 0x09)
	{
	goto here;
	}

if (ch == 0x0a)
	{
	fh->lines++;
	goto here;
	}

if (ch == 0x20)
	{
	goto here;
	}

fh->count--;
return (TRUE);

error:;
return (FALSE);
}


/* # getrawstr
** 
*/ 

BOOL
getrawstr (fh, name, bk)
REG FH		*fh;
REG UBYTE	*name;
REG UBYTE	 bk;
{
REG USHORT	 cn;
REG UBYTE	 ch;

cn = 0;

do
{
ch = hget (fh);

if (ISZERO (ch))
	{
	if (ISNOTZERO (fh->error))
		{
		return (FALSE);
		}
	}
	
if (ch == '\\')
	{
	switch (g)
	{
	case	'\\n':
			ch = '\n';
			break;
	case	'\\i':
			ch = '\t';
			break;
	};
	}

name [cn] = ch;
cn++;
} while (ch != bk);

return (TRUE);
}


typedef UBYTE	STAT;

#define	HS_NUMBER	0x01
#define	HS_CHAR		0x02

/* # hgetname
** 
*/ 

VOID
hgetname (fh, na, nsize)		/* gotta be fixed!	*/
REG FH		*fh;
REG SNAME	*na;
REG ULONG	 nsize;
{
REG SHORT	 cnt = 0;
REG STAT	 st;
REG UBYTE	*name = (UBYTE *) ((ULONG) na + (ULONG) sizeof (UWORD))
UWORD		 nsize = na->sn_Size;	/* ??			*/
UBYTE		 ch;

if (ISFALSE (hskipblank (fh)))
	{
	na->sn_Size = 0;
	goto end;
	}

ch = hget (fh);

if (ISZERO (ch))
	{
	if (ISNOTZERO (fh->error))
		{
		error:;
		na->sn_Size = 0;
		goto end;
		}
	}

nsize = na->sn_Size;

if (ch == '\;')
	{
	name [0] = '\;';	/* met a 'line closer'..		*/
	name [1] = 0x00;
	goto end;
	}

if (ch == '\'' || ch == '\"')
	{
	if (ISFALSE (getrawstr (fh, name, ch)))
		{
		goto error;
		}
	
	goto end;
	}

if (isnumber (ch) || (ch == '-')) 
	{
	getanumber (fh, name);	/* prende un numero			*/
	goto end;
	}

if (ischar (ch)) 
	{
	if (ISFALSE (getalphaname (fh, name)))
		{
		goto error;
		}
	
	goto end;
	}

if (ispecial (ch))
	{
	if (ISFALSE (getaspecial (fh, name)))
		{
		goto error;
		}
	
	goto end;
	}

speclose:;			/* who's to jump here??			*/
	_GOBACK (fh);

end:;
}


/* # getanumber
** 
*/ 

BYTE *
getanumber (fh, sname)
REG FH		*fh;
SNAME		*sname;
{
$ /* WARNING: this routine has to be improved and completed		*/
REG UBYTE	*name;
REG UCOUNT	 cnt = 0;
REG UBYTE	 ch
REG UBYTE	 stat;

name = NAMESTR (sname);

_GOBACK (fh);

FOREVER
{
ch = hget (fh);

if ((ISZERO (cnt)) && (ch == '-'))
	{				/* $la prima lettera é un meno	*/
	ch = hget (fh);
	
	if (isnumber (ch))
		{			/* $la seconda un numero	*/
		name [0] = '-';
		name [1] = ch ;
		name [2] = 0x00;	/* $dovrebbe essere sbagliato	*/
		}
	else				/* $non un numero		*/
		{
		fh->count -= 2;		/* you shouldn't do it this way	*/
		name [0] = '-';
		name [1] = 0x00;
		goto end;
		}
	}

if (isnumber (ch))
	{
	cnt++;
	name [cnt] = ch;
	}
else
	{
	switch (ch)
	{
	case	'e':
	case	'E':

		if (stat == 'E')
			{
			goto end;
			}
		
		stat = 'E';
		cnt++;
		name [cnt] = 'E';
		break;
	
	case	'+':
	case	'-':

		if (stat != 'E')
			{
			_GOBACK (fh);
			goto end;
			}
		
		name[cnt] = ch;

	case	'.':
		
		if (stat == '.')
			{
			goto end;	/* to improve	*/
			}
		
		stat = '.';
		cnt++;
		name [cnt] = '.';
		break;
	default:
		goto end;		/* to improve	*/
		break;

		} /* 'switch' end	*/
	} /* 'if' end	*/
} /* 'for'	*/

end:;
return (1);	/* WARNING: shouldn't it give back a BYTE * ???	*/
} /* routine end	*/


/* # getalphaname
** 
** gets an alphanumerical 'name' or 'token'
** 
*/ 

BOOL
getalphaname (ghandle, fh, name)
REG GHANDLE	*ghandle;
REG FH		*fh;
REG UBYTE	*name;
{
REG BYTE	 ch;
REG UWORD	 cnt;
REG BOOL	 st;

cnt = 0;
st  = 0;

_GOBACK (fh);

do
{
ch = hget (fh);

if (ISZERO (ch))
	{
	if (ISZERO (fh->error))
		{
		name [0] = 0x00;
		return;
		}
	else
		{
		goto error;
		}
	}

if (ischar (ch))
	{
	name [cnt] = ch;
	cnt++;
	}
else
	{
	st = FALSE;
	}
} while (ISTRUE (st));

end:;
name [cnt] = 0x00;
return (TRUE);

error:;
return (FALSE);
}


/* # getspecial
** 
*/ 

BOOL
getspecial (fh, name)
REG FH		*fh;
REG UBYTE	*name;
{
REG UWORD	 cnt;
REG UBYTE	 ch;

cnt = 0;
ch  = 0;

_GOBACK (fh);

do
{
ch = hget (fh);

if (ISZERO (ch))
	{
	if (ISZERO (fh->error))
		{
		name [0] = 0x00;
		goto end;
		}
	else
		{
		goto error;
		}
	}

switch (ctype (ch))
{
	case	2:
		fh->FE_ENDOFFILE;	/* strange error happened	*/
		goto error;
		
	case	4:
		goto getahex;

	case	5:
		goto getabinary;

	case	6:
		goto checkand;

	case   14:	
		goto checkperiod;

	case   18:	/* '>'	*/
		
		name[0] = '>';
		
		if (ISZERO (ch->error))
			{
			goto shutdown;
			}
		else
			{
			goto error;
			}
		
		if (ch == '>')
			{
			name[1] = '>';
			goto shutdown2;
			}
		
		goto shutdown;
	
	case   19:	/* '='	*/
		name[0] = '=';
		
		if (ISZERO (ch->error))
			{
			goto shutdown;
			}
		else
			{
			goto error;
			}
		
		if (ch == '=')
			{
			name[1] = '=';
			goto shutdown2;
			}
		
		goto shutdown;
	
	case   20:	/* '<'	*/
		
		goto checkminor;
		
		name[0] = '>';
		
		ch = hget (fh);
		
		if (ISZERO (ch->error))
			{
			goto shutdown;
			}
		else
			{
			goto error;
			}
		
		if (ch == '<')
			{
			name [1] = '<';
			goto shutdown2;
			}
		
		goto shutdown;
	
	case   29:
		goto checkor;
	
	default:
		name[0] = ch;
		name[1] = 0x00;
		goto end;
}	/* gotta fix it!	*/

}

shutdown:;
	name [1] = 0x00;
	goto end;

shutdown3:;
	name [cnt++] = 0x00;
	goto end;

shutdown2:;
	name [2] = 0x00;
	goto end;

getabinary:;
	ch = hget (fh);
	
	if (ch == 0x00)
		{
		if (ISNOTZERO (fh->error))
			{
			goto error;
			}
		
		goto gab_next;
		}
		
	while (ch == '0' || ch == '1')
	{
	cnt++;
	name [cnt] = ch;
	};
	
	gab_next:;
	
	_GOBACK (fh);
	goto shutdown3;

end:;
return (TRUE);

error:;
return (FALSE);
}


/* # createsname
** 
** may be changed in a macro
** 
*/ 

SNAME *
createsname (bytes)
REG UWORD	 bytes;
{
return (Alloc ((ULONG) sizeof (SNAME) + (ULONG) bytes));
}


/* # delsname
** 
** may be changed in a macro
** 
*/ 

VOID
delsname (sn)
REG SNAME	*sn;
{
Free (sn, (ULONG) sn->sn_Size + (ULONG) sizeof (UWORD) );
}


