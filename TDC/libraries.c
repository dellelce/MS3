/* tony dee © 1992
** 
** file release v0.00
** 
** 
*/ 

#include <libraries.h>


/* # source
** 
** 
*/ 

BOOL
source (group)
REG GROUP	*group;
{
ITEM		*item;
NAME		*name;
ULONG		*error;

error = &group->ghandle.lasterror;

if (ISFALSE (getname (group)))
	{
	*error = EN_NONAME;
	goto error;
	}

if (name->nd_type != NDT_STRING)
	{
	*error = EN_INVALIDARG;
	goto error;
	}

item = createitem (group->pmap);

if (ISZERO (item))
	{
	goto intalloc;
	}

item->di_type = IT_SOURCE;

if (ISFALSE (putstring (group, name->nd_data, BT_WORKSTRINGS)))
	{
	goto intalloc;
	}

item->it_str = group->couple->cp_Small;

if (ISFALSE (__addsourcef (group, name->nd_data)))
	{
	goto error;
	}

if (ISFALSE (skipaline (group))) /* skips a line */
	{
	goto error;
	}

intalloc:;
*error = EN_INTERNALALLOC;
goto error;

end:;
return (TRUE);

error:;
return (FALSE);
}


/* # __addsourcef
** 
** gestione delle librerie
** 
** in ritorno da: un no. + se name è stata trovata
** 		  un no. - se non è stata trovata
** 
** esempio: +7 indica di aver cercato in 7 directory trovandala
** 	    -4   "     "  "      "    in 4 directory non trovandolo
** 
** 
*/ 

LONG
__addsourcef (group, name)
REG GROUP	*group;
UBYTE		*name;
{
UBYTE		 namebuf [100];
UWORD		 nasz;
SD		 _sd;
LONG		 ll;
LOCK		 lk;

if (name == (PTR) 0L)
	{
	return (0);
	}

nasz = strlen (name);

if (nasz == 0)
	{
	return (0);
	}

if (nasz > 100)
	{
	return (0);
	}

/* set data
** 
** 
*/ 

ll		=	0L;

SD_DIR (_sd)	=	(STR) 0;
SD_LOCK (_sd)	=	      0L;
SD_COUNT (_sd)	=	      0L;

/* put extension
** 
*/ 

name [nasz++] = '.';
name [nasz++] = 'p';
name [nasz++] = 'm';
name [nasz++] = 'l';
name [nasz++] = (UBYTE) 0;
nasz --;

here:;

$getdirs (group, &_sd);

if (_sd.dir == (PTR) 0L)	/* nome directory vuota		*/
	{
	if (_sd.lock == 0L)	/* 'lock' directory  vuota	*/
		{
		return (ll);
		}
	
	ll++;
	
	if ($rawgetlf (group, lock, &name) == FALSE)	/* prende la lib.     */
		{					/* nella dir settata  */
		goto here;				/* col nome &name     */
		}
	else
		{
		return (ll);
		}
	}
else
	{
	lk = Lock (_sd.dir, ACCESS_READ);
	
	if (lk == 0L)
		{
		group->ghandle.lasterror = $EN_DOSERROR;
		$return (0);
		}
	
	}
}
