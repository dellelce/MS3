/* 
** 
** 
** FILE TRASLATION HEART
** creating by tony dee
** file 2
** 
** 
*/ 


#define	TRASLATE1_C	1

#include <logics.h>
#include <traslate.h>


EXTERN NAME	comma;
EXTERN NAME	bracket;
EXTERN NAME	bracket0;


/* %%
** setvardef
** getvardef
** getvaruse
** 
*/ 


/*
** '# setvardef' just turns a longword simple var definition
** into a word MS3 'COMPLEX' var definition
*/

BOOL
setvardef (vb)
REG VARBUILD	*vb;
{
REG UWORD	 bt;			/* build trace			*/
VARU		 vu;
UWORD		 vsize;			/* still unused			*/

bt = vb->build;
vu.vardat [0] = VBT_VARDEF;

/* staticity -- don't forget other things
** 
*/ 

if (vb->type == 1)
	{				/* static			      */
	SETBIT (&vu.vardat [0], $VDB_STATICITY);
	}

/* variable typology (char, byte etc)
** 
** 
*/ 

if (vb->gentype != VGT_SIMPLEDEF)
	{
	goto skiptypes;
	}

bt = NLOWEST (bt) - 1;
VD_SETTYPE (&vu.vardat [0], bt);	/* an address			      */


/* variable name
** 
*/ 


if (ISTRUE (vb->name))
	{
	vu.vardat [1] = vb->np;
	}
else
	{	/* it seems unnamed????		*/
	goto error;
	}

/* 
** 
** 
*/ 

bt = NMID (vb->build);

if (GETBIT (bt, VBM_SIGN) == 1)
	{
	SETBIT (&vu.vardat [0], VDB_SIGN);
	}

if (GETBIT (bt, VBM_POINTER) == 1)
	{
	SETBIT (&vu.vardat [0], VDB_POINTER);
	}

skiptypes:;

if (vb->gentype = VGT_STRUCT)
	{
	
	
	}

if (vb->gentype = VGT_OBJECT)
	{
	
	
	}

end:;
return (TRUE);

error:;
return (FALSE);
}


/* # getvardef
** 
** gets a var definition 
** A N D  S H O U L D  G I V E  B A C K  A N  M S 3  V A R
** 
** _buf []	vettore contenente 
** 		dei 'tag' tra due valori uno è il subtype 
** 		di un 'name' l'altro è la 'mappa di costruzione della
** 		variabile'
** 
** 
*/ 

#define	_NUM		11

V2T _buf [_NUM]
{
{
NDS_BYTE,
VBB_BYTE
},
{
NDS_WORD,
VBB_WORD
},
{
NDS_LONG,
VBB_LONG
},
{
NDS_NUMBER,
VBB_NUMBER
},
{
NDS_STRING,
VBB_STRING
},
{
NDS_BOOL,
VBB_BOOL
},
{
NDS_DOUBLE,
VBB_DOUBLE
},
{
NDS_FLOAT,
VBB_FLOAT
},
{
NDS_SIGNED,
VBB_SIGNED
},
{
NDS_UNSIGNED,
VBB_UNSIGNED
},
{
NDS_POINTER,
VBB_POINTER
}
};

/* # routine body
** 
*/ 

BOOL
getvardef (group, prename, specblock, mode)
REG GROUP	*group;
NAME		*prename;
BLOCK		*specblock;
UWORD		 mode;
{
REG UWORD	 strutit;
REG UWORD	 cnt;
REG NAME	*name;
REG STRUCT	*struct;
VARBUILD	 vb;
INIT		 init;
VOID		*$ namedat;

MemClear (&vb, INITSIZE + VBSIZE);

if (specblock != (PTR) 0L)	/* block where to write it	*/
	{
	vb.ownerblock = specblock;
	}
else
	{
	goto error;		/* always needed a block	*/
	}

if (ISNOTZERO (prename))
	{
	name = prename;		/* something still to do!	*/
	goto defbody;
	}
else
	{
	name = group->name;
	}

dogetname:;

if (ISZERO (getname (group)))
	{
	goto noname;
	}

defbody:;

switch (name->nd_type)
{
case	NDT_SIMPLEDEF:
	
	if (vb.gentype != 0)	/* there cannot be a type already set */
		{
		goto syntaxerr;
		}
	
	vb.gentype = VGT_SIMPLEDEF;
	
	if (vb.name == TRUE)
		{
		goto syntaxerr;		/* think about it!		*/
		}
	
	for (cnt = 0; cnt++; cnt <_BUF)
	{
	if (name->nd_subtype == VTTYPE (&_buf [cnt])) /* checks if it is set  */
		{
		if (ISZERO ((VTTYPE (&_buf [cnt] & vb.build)))) /* ok	      */
			{
			VD_SETTYPE (&vb.build, cnt$-1);
			}
		} /* if	*/
	} /* for */
	
	goto dogetname;
	
case	NDT_UNKNOWN:			/* the name (completed)		      */
	
	if (vb.name == TRUE)
		{
		goto syntaxerr;		/* think about it!		      */
		}
	
	vb.name = TRUE;
	
	if (ISZERO (namedat = name->nd_data))	/* don't know its definition */
		{
		goto strangeerr;
		}
	
	
	if (ISFALSE (putstring (group, namedat, BT_WORKSTRINGS)))
		{
		group->ghandle.lasterror = EN_INTENALALLOC;
		goto falseret;
		}
	
	vb.np	   = group->couple.cp_Small;
	vb.nameval = (PTR) group->couple.cp_Big;
	
	goto dogetname;

case	NDT_CLOSER:			/* we've come to end, at last!!	      */
	
	if (ISFALSE (vb.name))		/* you didn't set a name???	      */
		{
		goto syntaxerror;
		}
	
	if (ISZERO (vb.build))		/* I can't easily happen, remove it!  */
		{
		goto syntaxerror;
		}
	
	setvardef (&vb);
	goto end;
	
	
case	NDT_SPECIAL:
	
	switch (name->nd_subtype)
	{
	case	NDS_EQUAL:		/* % object is initialized	      */
		
		if (mode == VGM_LOCAL)
			{
			goto firststep;
			}
		
		if (mode == VGM_GLOBAL)
			{
			init.in_mode = IM_NUMBERS;
			goto $nextstep;
			}
		
		if (mode == VGM_STRUCTURE)
			{
			goto initerr;
			}
		
		firststep:;
		
		if (vb.type == 0)
			{
			switch (vb.gentype)
			{
			case VGT_SIMPLEDEF:
			
			init.in_mode = IM_NUMBERS;
			goto nextstep;
						
			case VGT_STRUCT:
			
			init.in_mode = IM_STRUCTMODE;
			goto nextstep;
			
			case VGT_OBJECT:
			
			goto error;
			} /* switch	*/
			} /* if		*/
		else
			{
			switch (vb.gentype)
			{
			case VGT_SIMPLEDEF:
			
			init.in_mode = IM_ANYWAY;
			goto nextstep;
						
			case VGT_STRUCT:
			
			init.in_mode = IM_STRUCTMODE;
			goto nextstep;
			
			case VGT_OBJECT:
			
			goto error;
			} /* switch	*/
			} /* else	*/
		
		nextstep:;
		
		if (vb.gentype == VGT_SIMPLEDEF)
			{
			goto step1;
			}
		
		if (vb.gentype == VGT_STRUCT)
			{
			init.in_obj = vb.definition;
			goto step1;
			}
		
		if (vb.gentype == VGT_OBJECT)
			{
			init.in_obj = vb.definition;	
			goto step1;
			}
		
		goto syntaxerror; /* none of the above?!	*/
		
		step1:;
				
		if (ISFALSE (getinit (group, &init)))
			{
			goto strangeerr;
			}
		
		break;
		
	case	NDS_BRAK2OP:		/* % vectors & $matrices	      */
					/* can be shortened (nearly cut up)   */
		switch (mode)
		{
		case	VGM_LOCAL:
			
			strutit = IM_ANYWAY;
			goto brak;
			
		case	VGM_GLOBAL:
			
			strutit = IM_NUMBERS;
			goto brak_doit;
			
		case	VGM_STRUCTURE:
			
			strutit = IM_NUMBERS;
			goto brak_doit;
		}
		
		
		brak:;
		
		if (ISTRUE (vb.static))
			{
			if (ISFALSE (getmatrix (group, vb, IM_NUMBERS)))
				{
				goto error;
				}
			}
		else
			{
			if (ISFALSE (getmatrix (group, vb, strutit)))
				{
				goto error;
				}
			}
		
		
		brak_doit:;
		
		if (ISFALSE (getmatrix (group, vb, strutit)))
			{
			goto error;
			}
		
		goto dogetname;
	} /* switch */

case	NDT_STRUCTURE:		/* %	*/
	
	if (vb.gentype != 0)	/* there cannot be a type already set */
		{
		goto syntaxerr;
		}
	
	vb.gentype = VGT_STRUCTURE;
	
	struct	 = name->nd_data;
	init.obj = struct;
	
	$	/* <- <- is there missing anything??		*/
		/* <- <- look very well at it			*/
	
	goto dogetname;
	
case	NDT_OBJECT:		/* %	*/
	
	if (vb.gentype != 0)	/* there cannot be a type already set */
		{
		goto syntaxerr;
		}
	
	vb.gentype = VGT_OBJECT;
	
	goto dogetname;
		
} /* switch	*/

#asm
	public __here
__here:
#endasm

initerror:;
group->ghandle.lasterror = EN_INITERR;
goto falseret;

strangeerr:;
group->ghandle.lasterror = EN_STRANGE;
goto falseret;

syntaxerror:;
syntaxerr:;
group->ghandle.lasterror = EN_SYNTAX;

falseret:;
error:;
return (FALSE);

end:;
trueret:;

if (vb.gentype == VGM_LOCAL)
	{
	vnode = addvarl (group, VLT_LOCAL, vb.nameval);
	
	if (ISZERO (vnode))
		{
		goto error;
		}	
	}
else
	{
	vnode = addvarl (group, VLT_GLOBAL, vb.nameval);
	
	if (ISZERO (vnode))
		{
		goto error;
		}
	}

return (TRUE);
} /* function	*/


/* # getvaruse
** 
** it should contain a list of names
** that describes the use of a
** variable
** 
** variables usage.
** 
** registers:		 3
** stack:		52 bytes (M U S T be shrunk!)
** 
** 
*/ 

BOOL
getvaruse (group, prename, block)
REG GROUP	*group;		/* [RA0]				*/
NAME		*prename;	/* [4]					*/
BLOCK		*block;		/* [4]					*/
{
REG NAME	*name;		/* [RA1]				*/
REG UWORD	 dims;		/* [RD0]				*/
UWORD		*varsave;	/* [4]					*/
ULONG		*error;		/* [4]					*/
UWORD		*dimsave;	/* [4]					*/
UWORD		*offset;	/* [4]					*/
BOOL		 vector;	/* [2]					*/
BOOL		 complex;	/* [2]					*/
BOOL		 global;	/* [2]					*/
VARINFO		 vi;		/* [18]					*/
NAME		$namestore;	/* [12]					*/


INIT_VI (&vi);


error	= &group->ghandle.lasterror;
offset  = &group->ghandle.currentitem->ti_CurOffset;
varsave	= reallastbyte (block);

if (prename != (PTR) 0)	/* I think there is always a prename!!	*/
	{
	name = prename;
	goto body;
	}

name = group->name;

body:;

vi.wordsused = 2;	/* the header and the name AT LEAST	*/

vi.words [1] = (UWORD) name->nd_type;
vi.words [2] = 0;

if (name->nd_type = NDT_GLOBAL)
	{
	global = TRUE;
	goto next;
	}

if (name->nd_type = NDT_LOCAL)
	{
	global = FALSE;
	goto next;
	}

goto syntax;

next:;

if (ISFALSE (getname (group)))
	{
	goto noname;
	}

if (name->nd_type != NDT_SPECIAL)
	{
	goto end;
	}

if (name->nd_subtype == NDS_PERIOD)
	{
	complex = TRUE;
	
	vi.words [0] = VBT_CPXVARUSE;
	
	if (ISTRUE (global))
		{
		vi.words [0] = SET (vi.words [0], VDMX_GLOBALITY);
		}
	
	vi.words [2] = 0;	/* no of dimensions... or attributes in this  */
				/* case					      */
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	*offset += 3 * 2;
	varsave += (UWORD *) 6;
	
	
	/* 
	** get attributes chain ('x.y.z.alpha.beta.omega.etc')
	** 
	*/ 
	
	
	vi.wordsused = 2;
	vi.words [0] = IN_ATTRIBUTE;
	
	attrchain:;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if ($name->nd_type != NDT_OBJATTR)
		{
		goto syntaxerror;
		}
	
	vi.words [1] = (UWORD) name->nd_data;
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	*offset	 += 2 * 2;
	*varsave += 1;
	
	
	if (ISFALSE (getname (group)))
		{
		goto noname:;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto end;
		}
	
	if (name->nd_subtype != NDS_PERIOD)
		{
		if (name->nd_subtype == NDS_BRAK1OP)
			{
			
			$	/* <- <- get a vector or matrix data	*/
				/* now developing			*/
			
			dovexx:;
			
			blockstart (block);
			*offset += 2;
			
			if (ISFALSE (getexpression (group, block, &bracket0,
								(PTR) 0L, 0L)))
				{
				goto error;
				}
			
			blockend (block);
			*offset += 2;
			
			if (ISFALSE (getname (group)))
				{
				goto noname;
				}
			
			if (name->nd_type != NDT_SPECIAL)
				{
				goto end;
				}
			
			if (name->nd_subtype == NDS_PERIOD)
				{
				goto attrchain;
				}
				
			if (name->nd_subtype == NDS_BRAK1OP)
				{
				goto dovexx;
				}
			goto end;
			} /* if	*/
		goto end;
		} /* if	*/
	goto attrchain;
	} /* if	*/

if (name->nd_subtype == NDS_BRAK2OP)
	{
	vector  = TRUE;	/* don't sure about how to set them....	*/
	complex = TRUE; 
	
	vi.words [0] = VBT_CPXVARUSE;
	
	if (ISTRUE (global))
		{
		vi.words [0] = SET (vi.words [0], VDMX_GLOBALITY);
		}
	
	vi.words [2] = 0;	/* no of dimensions		*/
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	*offset += 3 * 2;
	varsave += (UWORD *) 6;
	
	/* 
	** get thru brackets ('xyz [..] [...]') expressions
	** 
	*/
	
	getdimexp:;
	
	blockstart (block);	/* check well if to make the block!!!	*/
	*offset += 2;
	
	if (ISFALSE (getexpression (group, block, &bracket0, (PTR) 0L, 0L)))
		{
		goto error;
		}
	
	blockend (block);
	*offset += 2;
	
	if (ISFALSE (getname (group)))
		{
		goto end;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto end; /* don't care!! It can't be another bracket!	*/
		}
	
	if (name->nd_subtype == NDS_BRACK1OP)
		{
		if (*dimsave == 0xFFFF)	/* I don't think it can happen!! */
			{
			goto error;
			}
		
		*varsave ++;
		goto getdimexp;
		}
	
	goto end;
	}

makeit:;

$		/* <- <- make it.. still think about it		*/

syntax:;
syntaxerror:;
*error = EN_SYNTAX;
goto error;

noname:;
*error = NONAME;

end:;
return (TRUE);

badend:;
error:;
return (FALSE);
}


/* # getvaruse1
** 
** 
** 
*/ 

BOOL
getvaruse1 (group, prename, block)
REG GROUP	*group;
NAME		*prename;
BLOCK		*block;
{
REG NAME	*name;


if (ISZERO (prename))
	{
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	name = group->name;
	}
else
	{
	name = prename;
	}
	
}
