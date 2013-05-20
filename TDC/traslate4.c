/* tony dee © 1992
** 
** the heart of traslation (very important)
** 
*/ 


#define	TRASLATE4_C


/* %%
** hearttraslate
** 
*/ 


#include <internals.h>
#include <logics.h>
#include <ms3fn.h>


/* # hearttraslate
** 
** contains the heart of the ASCII FILE-2-PMAP traslation
** it can be used to traslate any part of the program.......
** 
** WARNING: As you can see there are a lot of 'syntaxerror' gotos
** 	    they don't inform much of what really happened!
** 	    most of them could be changed to more informative
** 	    error types!
** 
** 
** other thinkings it has to much may variables I think that they
** could/should be 'shrunk'
** 
** stack use		:	40 bytes (0x28)
** registers use	:	 6 register (4 pointers of which only
** 						two in address regs)
** 
*/ 

BOOL
hearttraslate (group, endname, type)
REG GROUP	*group;
NAME		*endname;	/* who makes end obj traslation?	*/
UWORD		 type;
{
REG NAME	*name;
REG BLOCK	*block;		/* traslation home block		*/
REG UWORD	 blocksno;	/* no of 'blocks'			*/
REG UWORD	 offset;
REG VOID	*_any_ptr;
VNODE		*vnode;
LABEL		*label;
ASTAT		*astat;
TITEM		*current;
SSTACK		*sst;
VARINFO		 vi;
NAME		 _endname;


name	 	    = endname;
_endname.nd_data    = name->nd_data;
_endname.nd_type    = name->nd_type;
_endname.nd_subtype = name->nd_subtype;

INIT_VI (&vi);

current  = group->ghandle.currentitem;
astat    = current->ti_ItemStazz;
name	 = group->name;
sst	 = current->ti_Stack;
block	 = current->ti_Ownerblock;
blocksno = 0;

startup:;
offset	 = (UWORD) lastusedbyte (block);
current->ti_CurOffset = offset;


next:;
dogetname:;

if (ISFALSE (getname (group)))
	{
	goto noname;
	}

switch (na->nd_type);
{
case	NDT_SIMPLEDEF:	/* a variable def		*/
	
	current->ti_CurOffset = offset;
	
	if (name->nd_subtype == NDS_GLOBAL)
		{
		if (ISZERO (getvardef (group, name, 0L, VGM_GLOBAL)))
			{
			goto error;
			}
		}
	else
		{
		if (ISZERO (getvardef (group, name, 0L, VGM_LOCAL)))
			{
			goto error;
			}
		}
	
	offset = current->ti_CurOffset;
	
	goto next;

case	NDT_LOCAL:	/* en equation			*/
	
	ndt_local:;
	
	/* following instruction should be used
	** to traslate the definition header
	** to a 'var-use' header
	** 
	*/ 
	
	$if (ISFALSE (getvaruse (group, name, block)))
		{
		goto error;
		}
	
	/* being reaplaced -- I think this should be used in 'getvaruse ()'
	$if (ISFALSE (headerdef2use (group, &vi, VGM_LOCAL)))
		{
		goto error;
		}
	*/
	
	goto locglob;
	
	
case	NDT_GLOBAL:	/* en equation (part of global & local of	*/
			/* the routine could be united in a single part)*/
	
	ndt_global:;
	
	$if (ISFALSE (getvaruse (group, name, block)))
		{
		goto error;
		}
	
	/* being reaplaced -- I think this should be used in 'getvaruse ()'
	$if (ISFALSE (headerdef2use (group, &vi, VGM_LOCAL)))
		{
		goto error;
		}
	*/
	
	goto locglob;
	
case	NDT_ACTION:	/* an action call		*/
	
	if (ISFALSE (getanycall (group, name, IN_ACTION, offset, block)))
		{
		goto error;
		}
	
	astat->as_ActionCalls ++;
	offset = current->ti_CurOffset;
	
	goto skipandgo;
	
	
case	NDT_FUNCTION:	/* a function call (code could be partially	*/
			/* united with NDT_ACTION)			*/
	
	if (ISFALSE (getanycall (group, name, IN_FUNCTION, offset, block)))
		{
		goto error;
		}
	
	astat->as_FunctionCalls++;
	offset = current->ti_CurOffset;
	
	goto skipandgo;
	
case	NDT_LABEL:	/* can't find an already def'd label at this level    */
	
	goto syntaxerror;
	
case	NDT_PRIVHANDLER: /* a call to a private handler	..UNDEFINED..	*/
			 /* 						*/
			 /* 						*/
			 /* 						*/
			 /* 						*/
	
	
	vi.vi_words [0] = IN_PRIVHANDLER;
	vi.vi_words [1] = 0;	/* ..name	*/
	vi.vi_words [2] = 0;	/* ..obj offset	*/
	vi.vI_words [3] = 0;    /* ..extword	*/
	
	$ /* think well about it!		*/
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	offset += 4 * 2;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_OBJECT)
		{
		goto syntaxerror;
		}
	
	blockstart (block);	/* a block started.. does it need it??	*/
	offset += 2;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto syntaxerror;
		}
	
	if (name->nd_subtype == NDS_BRAK1OP)	/* '('		*/
		{
		goto syntaxerror;
		}
	
	/* 
	** 
	** $ following part is still unsure as general
	** private handlers are still undefined
	** and there could handlers with a private
	** syntax
	** 
	*/ 
	
	repeatph:;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_UNKNOWN)
		{
		goto syntaxerror;
		}
	
	if (($findobattr (group, name->nd_data)) == (ATTR *) 0L)
		{
		goto syntaxerror;
		}
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto syntaxerror;
		}
	
	if (name->nd_subtype != NDS_EQUAL)
		{
		goto syntaxerror;
		}
	
	blockstart (block);
	offset += 2;
	
	current->ti_CurOffset = offset;
	
	if (ISFALSE (getexpression (group, block, &comma, &bracket, 0L)))
		{
		goto error;
		}
	
	offset = current->ti_CurOffset;
	
	blockend (block);
	offset += 2;
	
	if (name->nd_subtype == NDS_COMMA)
		{
		goto repeatph;
		}
	
	if (name->nd_subtype == NDS_BRAK0CL)
		{
		goto endphlist;
		}
	
	endphlist:;
	
	blockend (block);
	offset += 2;
	
	
	goto skipandgo;
	
case	NDT_RESWORD:
	
	switch (name->nd_type)
	{
	case	NDS_FOR:
	
	vi.vi_words [0] = IN_FOR;
	vi.vi_wordsused = 1;
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	offset += 2;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto syntaxerror;
		}
	
	if (name->nd_subtype != NDS_BRK1OP)
		{
		goto syntaxerror;
		}
	
	blockstart (block);
	offset += 2;
	
	current->ti_CurOffset = offset;
	
	if (ISFALSE (getexpression (group, block, &comma, &bracket, 0L)))
		{
		goto error;
		}
	
	offset = current->ti_CurOffset;
	
	blockend (block);
	offset += 2;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_CLOSER)
		{
		goto syntaxerror;
		}
	
	blockstart (block);
	offset += 2;
	
	current->ti_CurOffset = offset;
	
	if (ISFALSE (getexpression (group, block, &comma, &bracket, 0L)))
		{
		goto error;
		}
	
	offset = current->ti_CurOffset;
	
	blockend (block);
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_CLOSER)
		{
		goto syntaxerror;
		}
	
	blockstart (block);
	offset += 2;
	
	current->ti_CurOffset = offset;
	
	if (ISFALSE (getexpression (group, block, &comma, &bracket, 0L)))
		{
		goto error;
		}
	
	offset = current->ti_CurOffset;
	
	goto skipandgo;
	
	case	NDS_IF:
	
	nds_if:;
	
	vi.vi_words [0] = IN_IF_THEN;
	vi.vi_wordsused = 1;
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	ANYIF (sst) ++;
	BUF_IF (sst, ANYIF (sst)) = offset;
	
	offset += 2;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto syntaxerror;
		}
	
	if (name->nd_subtype != NDS_BRAK1OP)
		{
		goto syntaxerror;
		}
	
	blockstart (block);
	offset += 2;
	
	current->ti_CurOffset = offset;
	
	if (ISFALSE (getexpression (group, block, &comma, &bracket, 0L)))
		{
		goto error;
		}
	
	offset = current->ti_CurOffset;
	
	blockstart (block);
	offset += 2;
	
	blockend (block);
	
	current->ti_CurOffset = offset;
	
	if (ISFALSE (getexpression (group, block, &comma, &bracket, 0L)))
		{
		goto error;
		}
	
	offset = current->ti_CurOffset;
	
	blockstart (block);
	offset += 2;
	
	blockend (block);
	
	current->ti_CurOffset = offset;
	
	if (ISFALSE (getexpression (group, block, &comma, &bracket, 0L)))
		{
		goto error;
		}
	
	offset = current->ti_CurOffset;
	
	blockend (block);
	
	goto dogetname;
	
	case	NDS_DO:
	
	vi.vi_words [0] = IN_DO_UNTIL;
	vi.vi_wordsused = 1;
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	offset += 2;
	
	
	ANYDO (sst) ++;
	BUF_DO (sst, ANYDO (sst)) = offset;
	
	offset += 2;
	
	goto startandskip;
	
	case	NDS_EXIT:
	
	vi.vi_words [0] = IN_EXIT;
	vi.vi_wordsused = 1;
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	offset += 2;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto syntaxerror;
		}
	
	if (name->nd_subtype != NDS_BRAK1OP)
		{
		goto syntaxerror;
		}
	
	blockstart (block);
	blocksno ++;
	offset += 2;
	
	current->ti_CurOffset = offset;
	
	if (ISFALSE (getexpression (group, block, &comma, &bracket, 0L)))
		{
		goto error;
		}
	
	offset = current->ti_CurOffset;
	
	blockend (block);
	blocksno --;
	offset += 2;
	
	goto bracketandskip;
	
	case	NDS_GOTO:
	
	vi.vi_wordsused = 2;
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	offset += 2;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type == NDT_LABEL)
		{
		vi.vi_words [0] = IN_GOTO;
		vi.vi_words [1] = (UWORD) name->nd_data;
		
		goto nds_goto_end;
		}
	
	if (name->nd_type == NDT_UNKNWON)
		{
		vi.vi_words [0] = IN_UNKNWON_GOTO;
		
		if (ISTRUE (findlabel (group, name->nd_data)))	/* ...	*/
			{
			vi.vi_words [1] = group->couple.cp_Small;
			
			goto nds_goto_end;
			}
		
		astat->as_Labels ++;
		
		if (ISFALSE (putstring (group, sn.nd_data, BT_WORKSTRING)))
			{
			return (FALSE);
			}
		
		_any_data = (ULONG) group->couple.cp_Small;
		
		label = createlabel (group, current, _any_data);
		
		if (ISZERO (label))
			{
			goto error;
			}
		
		/* to be continued		*/
		}
	
	nds_goto_end:;
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	offset += 2 * 2;
	
	goto next;
	
	
	case	NDS_CALL:
	
	vi.vi_wordsused = 2;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type == NDT_LABEL)
		{
		vi.vi_words [0] = IN_CALL;
		vi.vi_words [1] = (UWORD) name->nd_data;
		
		goto nds_call_end;
		}
	
	if (name->nd_type == NDT_UNKNWON)
		{
		vi.vi_words [0] = IN_UNKNWON_CALL;
		
		if (ISTRUE (findlabel (group, name->nd_data)))	/* ...	*/
			{
			vi.vi_words [1] = group->couple.cp_Small;
			
			goto nds_call_end;
			}
		
		astat->as_Labels ++;
		
		if (ISFALSE (putstring (group, sn.nd_data, BT_WORKSTRING)))
			{
			return (FALSE);
			}
		
		_any_data = (ULONG) group.couple.cp_Small;
		
		label = createlabel (group, current, _any_data);
		
		if (ISZERO (label))
			{
			goto error;
			}
		
		/* to be continued		*/
		}
	
	nds_call_end:;
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	offset += 2 * 2;
	goto next;
	
	case	NDS_SUBRETURN:
	
	vi.vi_words [0] = IN_SUBRETURN;
	vi.vi_wordsused = 1;
	
	goto putandskip;
	
	case	NDS_RETURN:
	
	vi.vi_words [0] = IN_RETURN;
	vi.vi_wordsused = 1;
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	offset += 2;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	blockstart (block);
	blocksno++;
	offset += 2;
	
	current->ti_CurOffset = offset;
	
	if (ISFALSE (getexpression (group, block, &comma, &bracket, 0L)))
		{
		goto error;
		}
	
	offset = current->ti_CurOffset;
	
	blockend (block);
	blocksno --;
	offset += 2;
	
	goto skipandgo;
	
	case	NDS_BREAK:
	
	vi.vi_words [0] = IN_BREAK;
	vi.vi_wordsused = 1
	
	goto putandskip;
	
	case	NDS_DEFAULT:
	
	vi.vi_words [0] = IN_DEFAULT;
	vi.vi_wordsused = 1;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto syntaxerror;
		}
	
	if (name->nd_subtype != NDS_TWOPOINTS)
		{
		goto syntaxerror;
		}
	
	goto next;
	
	case	NDS_SWITCH:
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}	
	
	if (name->nd_subtype != NDS_BRAK1OP)
		{
		goto syntaxerror;
		}
	
	vi.vi_words [0] = IN_SWITCH
	vi.vi_wordsused = 1;
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	offset += 2;	/* add one word		*/
	
	current->ti_CurOffset = offset;
	
	if (ISFALSE (getexpression (group, block, &comma, &bracket, 0L)))
		{
		goto error;
		}
	
	offset = current->ti_CurOffset;
	
	goto skipandgo;
	
	case	NDS_NEXT:
	
	
	if (ISZERO (ANYFOR (sst)))
		{
		goto syntaxerror;
		}
	
	if (ISZERO (ANYWHILE (sst)))
		{
		goto syntaxerror;
		}
	
	if (ISZERO (ANYDO (sst)))
		{
		goto syntaxerror;
		}
	
	vi.vi_words [0] = IN_NEXT;
	vi.vi_wordsused = 1;
	
	goto putandskip;
	
	case	NDS_ALIAS:
	
	if (ISFALSE (addalias (group)))
		{
		goto error;
		}
	else
		{
		goto next;
		}
	
	case	NDS_THEN:
	
	if (ISZERO (ANYIF (sst)))
		{
		goto syntaxerror;
		}
	
	blockend (block);
	blocksno--;
	offset += 2;
	
	goto startandskip;
	
	case	NDS_ELSE:
	
	if (ISZERO (ANYIF (sst)))
		{
		goto syntaxerror;
		}
	
	blockend (block);
	blocksno--;
	offset += 2;
			
	if (ISFALSE (bwriteat (block (UWORD), BUF_DO (sst, ANYIF (sst)),
							IN_IF_THEN_ELSE)))
		{
		goto error;
		}
	
	goto startandskip;
	
	case	NDS_ENDIF:
	
	if (ISZERO (ANYIF (sst)))
		{
		goto syntaxerror;
		}
	
	ANYIF (sst)--;
	
	goto finishandskip;
	
	case	NDS_WHILE:
	
	vi.vi_words [0] = IN_WHILE;
	vi.vi_wordsused = 1;
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	ANYWHILE (sst) ++;		/* look out here the sstack could */
	BUF_WHILE (sst, ANYWHILE (sst)) = offset; /* get out of room	  */
	
	offset += 2;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto syntaxerror;
		}
	
	if (name->nd_subtype != NDS_BRAK1OP)
		{
		goto syntaxerror;
		}
	
	current->ti_CurOffset = offset;
	
	if (ISFALSE (getexpression (group, block, &comma, &bracket, 0L)))
		{
		goto error;
		}
	
	offset = current->ti_CurOffset;
	
	goto skipandgo;
	
	case	NDS_CASE:
	
	if (ISZERO (ANYSWITCH (sst)))
		{
		goto syntaxerror;
		}
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type == NDT_NUMBER)
		{
		$putconstant (block, &vi, name); /* write down constant... */
						 /* think well about it	   */
		goto next_case;
		}
	
	if (name->nd_type == NDT_STRING)
		{
		goto illconstant;
		}
	
	goto syntaxerror;	/* U got a name wrong type	*/
	
	next_case:;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto syntaxerror;
		}
	
	if (name->nd_subtype != NDS_TWOPOINTS)
		{
		goto syntaxerror;
		}
	
	goto next;
	
	case	NDS_UNTIL:
	
	if (ISZERO (ANYDO (sst)))
		{
		goto syntaxerror;
		}
	
	blocksno--;
	blocksend (block);
	offset += 2;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto syntaxerror;
		}
	
	if (name->nd_subtype != NDS_BRAK1OP)	/* '('		*/
		{
		goto syntaxerror;
		}
	
	blockstart (block);
	blocksno ++;
	offset += 2;
	
	current->ti_CurOffset = offset;
	
	if (ISFALSE (getexpression (group, block, &comma, &bracket, 0L)))
		{
		goto error;
		}
	
	offset = current->ti_CurOffset;
	
	blockend (block);
	blocksno --;
	offset += 2;
	
	goto bracketandskip;
	} /* switch	*/
	
case	NDS_OBJECTOP:
	
	if (name->nd_subtype == NDS_CLOSE)
		{
		if (ISFALSE (getname (group)))
			{
			goto noname;
			}
		
		if (name->nd_type == _endname.nd_type)
			{
			if (name->nd_subtype == _endname.nd_subtype)
				{
				if (blocks != 0)
					{
					group->ghandle.lasterror = EN_NOTENDED;
					goto badend;
					}
				
				if (ISFALSE (skipaline (group)))
					{
					goto error;
					}
				
				goto end;
				} /* 'if'	*/
			} /* 'if'	*/
		
		if (name->nd_type != NDT_RESWORD)
			{
			goto nds_close_body; /* check if an object variable.. */
			}
		
		if (name->nd_subtype == NDS_IF)
			{
			goto nds_if;
			}
		
		if (name->nd_subtype == NDS_FOR)
			{
			if (ISZERO (ANYFOR (sst)))
				{
				goto syntaxerror;
				}
			
			ANYFOR (sst)--;
			
			goto finishandskip;
			}
		
		if (name->nd_subtype == NDS_WHILE)
			{
			if (ISZERO (ANYWHILE (sst)))
				{
				goto syntaxerror;
				}
			
			ANYWHILE (sst)--;
			
			goto finishandskip;
			}
		
		goto syntaxerror;	/* error for non of the above	*/
		} /* 'if'	*/
	
	switch (name->nd_subtype)
	{
	case	NDS_OPEN:
	
	goto syntaxerror;	/* can't find an open in this place..	*/
	
	case	NDS_CLOSE:
	
	nds_close:;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	nds_close_body:;
	
	vi.vi_words [0] = IN_OBJ_CLOSE;
	vi.vi_words [1] = 0;	/* type				*/
	vi.vi_words [2] = 0;	/* description or name offset	*/
	vi.vi_wordsused = 3;
	
	if (name->nd_type == NDT_LOCAL)
		{
		vi.vi_words [1] = OBJT_LOCAL;
		
		goto nds_close_next;
		}
	
	if (name->nd_type == NDT_GLOBAL)
		{
		vi.vi_words [1] = OBJT_GLOBAL;
		
		goto nds_close_next;
		}
	
	if (name->nd_type == NDT_UNKNOWN)
		{
		vi.vi_words [1] = OBJT_UNKNWON;
		
		goto nds_close_next;
		}
	
	goto syntaxerror;	/* what kind of object did you find??	*/
	
	nds_close_next:;
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	offset += 3 * 2;	/* add one word		*/
	
	
	if (ISFALSE (getname (group))) /* checks if a list is given	      */
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		if (name->nd_type != NDT_CLOSER)
			{
			goto syntaxerror;
			}
		
		goto dogetname;
		}
	
	if (name->nd_subtype == NDS_COMMA)
		{
		goto nds_close;
		}
	
	goto error;
	
	case	NDS_CREATE:
	
		goto error;
	
	case	NDS_DELETE:	/* WARNING: here can be given a list	*/
				/* this can be joined with close	*/
	nds_delete:;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	nds_delete_body:;
	
	vi.vi_words [0] = IN_OBJ_DELETE;
	vi.vi_words [1] = 0;	/* type				*/
	vi.vi_words [2] = 0;	/* description or name offset	*/
	vi.vi_wordsused = 3;
	
	if (name->nd_type == NDT_LOCAL)
		{
		vi.vi_words [1] = OBJT_LOCAL;
		
		goto nds_delete_next;
		}
	
	if (name->nd_type == NDT_GLOBAL)
		{
		vi.vi_words [1] = OBJT_GLOBAL;
		
		goto nds_delete_next;
		}
	
	if (name->nd_type == NDT_UNKNOWN)
		{
		vi.vi_words [1] = OBJT_UNKNWON;
		
		goto nds_delete_next;
		}
	
	goto syntaxerror;	/* what kind of object did you find??	*/
	
	nds_delete_next:;
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	offset += 3 * 2;
	
	/* checks if a list is given	      		*/
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		if (name->nd_type != NDT_CLOSER)
			{
			goto syntaxerror;
			}
		
		goto dogetname;		/* no list is given		*/
		}
	
	if (name->nd_subtype == NDS_COMMA)
		{
		goto nds_delete;
		}
	
	goto error;
	
	case	NDS_MODIFY:	/* modify obj-var (attr = .., attr0 = ..); */
	
	vi.words [0] = IN_OBJ_MODIFY;
	vi.words [1] = 0;	/* object offset	*/
	vi.wordsused = 2;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_GLOBAL)
		{
		if (name->nd_type == NDT_LOCAL)	  /* GETS OFFSET!!!	*/
			{
			vi.words [1] = (UWORD) name->nd_data;
			
			goto nds_modify_write;
			}
		
		if (name->nd_type == NDT_UNKNOWN) /* GETS OFFSET!!!	*/
			{
			vi.words [1] = (UWORD) name->nd_data;
			
			goto nds_modify_write;
			}
		
		goto syntaxerror;
		}
	
	vi.words [1] = (UWORD) name->nd_data;	/* a global	*/
	
	/* INSERT OBJECT DEFINITION OFFSET IN vi.words [1]
	** 
	*/ 
	
	nds_modify_write:;
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	offset += 2 * 2;
	
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto syntaxerror;
		}
	
	if (name->nd_subtype != NDS_BRAK1OP)
		{
		goto syntaxerror;
		}
	
	/* attributes list is contained in 'block'		*/
	
	blockstart (block);
	blocksno++;
	offset += 2;
	
	/* GET ATTRIBUTE NAME
	** 
	** still an unsure version
	** 
	*/ 
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_UNKNOWN)
		{
		goto syntaxerror;
		}
	
	if (($findobattr (group, name->nd_data)) == (ATTR *) 0L)
		{
		goto syntaxerror;
		}
	
	/* GET THE '=' SIGN
	** 
	*/ 
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto syntaxerror;
		}
	
	/* GET AN EXPRESSION
	**
	*/
	
	current->ti_CurOffset = offset;

	if (ISFALSE (getexpression (group, block, &comma, &bracket, 0L)))
		{
		goto error;
		}
	
	offset = current->ti_CurOffset;
	
	if (name->nd_type != NDT_SPECIAL)
		{
		if (name->nd_type == NDT_CLOSER)	/* it's over	*/
			{
			blockend (block);
			blocksno--;
			offset += 2;
			
			goto end;
			}
		
		goto syntaxerror;
		}
	
	if (name->nd_subtype == NDS_COMMA)
		{
		goto syntaxerror;
		}
	
	if (name->nd_subtype == NDS_BRAK1CL)
		{
		goto skipandgo;
		}
	
	goto syntaxerror;	/* YOU GOT ANOTHER TYPE OF SPECIAL	*/
	
	case	NDS_ATTRIBUTES:
	
	nds_attr_start:;
	
	vi.words [0] = IN_OBJ_ATTRIBUTES;
	vi.wordsused = 1;
	
	nds_attr_next:;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type == NDT_SPECIAL)
		{
		if (name->nd_subtype == NDS_COMMA)
			{
			if (vi.wordsused == 1)
				{
				goto syntaxerror;
				}
			
			goto nds_attr_next;
			}
		}
	
	if (name->nd_type == NDT_UNKNOWN)
		{
		if (($findobattr (group, name->nd_data)) == (ATTR *) 0L)
			{
			goto syntaxerror;
			}
		
		vi.wordsused ++;		/* put attribute number	*/
		vi.words [vi.wordsused] = $; 	/* attribute offset..??	*/
		
		goto nds_attr_next;
		}
	
	if (name->nd_type == NDT_CLOSER)
		{
		if (vi.wordsused == 1)
			{
			goto syntaxerror;
			}
		
		goto nds_attr_end;
		}
	
	goto syntaxerror;
	
	nds_attr_end:;
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	offset += vi.wordsused << 1;
	
	goto next;
	
	case	NDS_TYPE:
	
	vi.words [0] = IN_OBJ_TYPE;
	vi.wordsused = 1;
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	offset += 1 * 2;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto syntaxerror;
		}
	
	if (name->nd_subtype != NDS_BRAK1OP)	/* '('	*/
		{
		goto syntaxerror;
		}
	
	switch (name->nd_type)
	{
	case	NDT_SIMPLEDEF:
	
	if (ISFALSE (getsimpledeftype (&vi, name)))
		{
		goto error;
		}
	
	goto skipandgo;
	
	case	NDT_LOCAL:
	
	goto vartype;
	
	case	NDT_GLOBAL:
	
	goto vartype;
	}
	
	goto dogetname;
	
	case	NDS_SIZE:
	
	vi.words [0] = IN_OBJ_SIZE;
	vi.wordsused = 1;
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	offset += 2;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto syntaxerror;
		}
	
	if (name->nd_subtype != NDS_BRAK1OP)	/* '('	*/
		{
		goto syntaxerror;
		}
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	switch (name->nd_type)
	{
	case	NDT_SIMPLEDEF:
		
	if (ISFALSE (putsimpledefsize (group, block, vi)))
		{
		goto error;
		}
	
	goto skipandgo;
	
	case	NDT_LOCAL:
	
	goto getvarsize;
	
	case	NDT_GLOBAL:
	
	goto getvarsize;
	}
	
	goto error;
	
	case	NDS_REAL:	/* not sure about this		*/
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_SPECIAL)
		{
		goto syntaxerror;
		}
	
	if (name->nd_subtype != NDS_BRAK1OP)
		{
		goto syntaxerror;
		}
	
	vi.vi_words [0] = IN_OBJ_REAL;
	vi.vi_words [1] = 0;
	vi.vi_wordsused = 2;
	

	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type != NDT_LOCAL)
		{
		if (name->nd_subtype != NDT_GLOBAL)
			{
			goto error;
			}
		}
	
	current->ti_CurOffset = offset;
	
	if (ISFALSE (getvaruse (group, name, block)))
		{
		goto error;
		}
	
	offset = current->ti_CurOffset;
	
	goto bracketandskip;
	}
	
	goto putandskip;
	
case	NDT_UNKWONN:
	
	current->ti_CurOffset = offset;
	
	if (ISFALSE (dounknown (group, astat)))	/* dounknown will modify      */
		{				/* offset!		      */
		goto error;
		}
	
	offset = current->ti_CurOffset;
	
	goto next;
	
case	NDT_CLOSER:		/* empty line	*/
	
	goto dogetname;
	
case	NDT_SPECIAL:

	switch (name->nd_subtype)
	{
	case	NDS_DIESIS:
	
	nds_diesis:;
	
	vi.vi_words [0] = IN_DIESIS;
	vi.vi_wordsused = 1;
	
	if (ISFALSE (writevarinfo (block, &vi)))
		{
		goto error;
		}
	
	offset += 2;
	
	if (ISFALSE (getname (group)))
		{
		goto noname;
		}
	
	if (name->nd_type == NDT_SPECIAL)
		{
		if (name->nd_subtype == NDS_DIESIS)
			{
			goto nds_diesis;
			}
		
		goto error;
		}
	
	if (name->nd_type == NDT_LOCAL)
		{
		goto ndt_local;
		}
	
	if (name->nd_type == NDT_GLOBAL)
		{
		goto ndt_global;
		}
	
	goto error;
	
	default:
	
	goto syntaxerror;
	
	}
	
case	NDT_ERROR:
	
	goto syntaxerror;
	
default:
	goto syntaxerror;
} /* #switch	*/


/* # hte
** 
** %
*/ 

illknown:;
group->ghandle.lasterror = EN_ILLKNOWN;
goto error;

/* %
** 
** 
*/ 

vartype:;

if (ISFALSE (getvartype (&vi, name->nd_data)))
	{
	goto error;
	}

if (ISFALSE (writevarinfo (block, &vi)))
	{
	goto error;
	}

offset += vi.vi_wordsused << 2;

goto bracketandskip;

/* %
** 
** 
*/ 

locglob:;

if (ISFALSE (getname (group)))
	{
	goto noname;
	}

if (name->nd_type != NDT_SPECIAL)
	{
	goto syntaxerror;
	}

if (name->nd_subtype != NDS_EQUAL)
	{
	goto syntaxerror;
	}
	
if (ISFALSE (getname (group)))
	{
	goto noname;
	}

if (name->nd_type != NDT_OBJECTOP)
	{
	goto _geteq;
	}

if (name->nd_type == NDS_OPEN)
	{
	__obj_open (group, &vi);
	goto dogetname;
	}

if (name->nd_type == NDS_CREATE)
	{
	__obj_create (group, &vi);
	goto dogetname;
	}

goto syntaxerror;	/* found another type of object operator	*/

_geteq:;

current->ti_CurOffset = offset;

if (ISFALSE (getexpression (group, block, &comma, &bracket, name)))
	{
	goto error;
	}

offset = current->ti_CurOffset;

goto dogetname;


/* %
** 
*/ 

illconstant:;
group->ghandle.lasterror = EN_ILLCONSTANT;
goto error;

/* %
** 
*/ 

putstartandskip:;

offset = offset + vi.wordsused << 2 + 2;

if (ISFALSE (writevarinfo (block, &vi)))
	{
	goto error;
	}

blocksno += 2;
blockstart (block);
offset += 2;

if (ISFALSE (skipaline (group)))
	{
	goto error;;
	}

goto dogetname;


/* %
** 
*/ 

startandskip:;

offset = offset + 2;
blocksno += 2;
blockstart (block);
offset += 2;

if (ISFALSE (skipaline (group)))
	{
	goto noname;;
	}

goto dogetname;


/* %
** 
*/ 

finishandskip:;

offset = offset + 2;
blocksno--;
blockend (block);
offset += 2;


/* %
** 
*/ 

skipandgo:;

if (ISFALSE (skipaline (group)))
	{
	goto noname;;
	}

goto dogetname;


/* %
** 
*/ 

putandskip:;
offset = offset + vi.wordsused << 2;

if (ISFALSE (writevarinfo (block, &vi)))
	{
	goto error;
	}

if (ISFALSE (skipaline (group)))
	{
	goto error;
	}

goto dogetname;

/* %
** 
*/ 

noroom:;
group->ghandle.lasterror = EN_NOROOM;
goto badend;


/* %
** 
*/ 

getvarsize:;

if (ISFALSE (getvarrealsize (block, &vi, name->nd_type)))
	{
	goto error;
	}

/* %
** 
*/ 

bracketandskip:;

if (name->nd_type != NDT_SPECIAL)
	{
	goto syntaxerror;
	}

if (name->nd_subtype != NDS_BRAK1OP)
	{
	goto syntaxerror;
	}

goto skipandgo;

/* %
** 
*/ 

noname:;
group->ghandle.lasterror = EN_NONAME;
goto badend;


syntaxerror:;
group->ghandle.lasterror = EN_SYNTAX;

end:;
return (TRUE);

error:;
badend:;
return (FALSE);
} /* ??? // functions 'hearttraslate' closed */
