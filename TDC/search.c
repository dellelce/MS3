/* tony dee © 1992
** 
** global searchers...
** 
** 1st. they must be reviewed...
** 2nd. I think they will be used just in future...
** 
** 
*/ 


#include <tonylists.h>


/* 
** 
** 
** 
** 
** the first 'long' of a map item (not considering the tnode)
** gotta be always used
** as string pointer
** (if u want to use this 'mapfind' routine)
** 
*/ 


/* # mapfind
** 
** it is (or should be, since it used nearly by none....)
** an any-map finder, alas, you give him a map with a
** standard header and a string and it will
** search your wished object....
** 
*/ 

VOID *
mapfind (map, object)
REG VOID	*map;
REG UBYTE	*object;
{
TNODE		*current;
VOID		*view;
ULONG		 mapblockcnt;
ULONG		 viewedcnt;


if (ISZERO (((MAPH *) map)->mh_GlobalItems))
	{
	return (0);
	}

mapblockcnt	= 0;
viewedcnt	= (ULONG) ((MAPH *) map)->mh_UsedItems;
current		= map->mh_Maps->tl_First;
view		= NEXT (current, TNODE);

next:;

if (ISZERO (strcmp (* (UBYTE **) view, str)))	/* we found it,	      */
	{					/* at last!	      */
	return (view);
	}

mapblockcnt++;

if (mapblockcnt == ((MAPH *)map)->mh_EachMapItems)
	{
	view = current->tn_Next;
	} 

if (ISZERO (view))
	{
	return (0);		/* not found! */
	}
view = NEXT (view, TNODE);
goto next;

/* here is to check!! */

viewedcnt--;

f (ISZERO (viewedcnt))
	{
	return (0);
	}
else
	{
	goto next;
	}
}


/* # listfind
** 
*/ 

STRNODE *
listfind (list, str)
LISTH		*list;
UBYTE		*str;
{
REG STRNODE	*strnode;

if (ISZERO (list->lh_UsedItems))
	{
	return (0);
	}

strnode = list->lh_List.tl_First;

next:;

if (ISZERO (strcmp (strnode->sn_String, str))) /* got it!!!... */
	{
	return (strnode);
	}

strnode = strnode->sn_Node.tn_Node;

if (ISZERO (strnode))
	{
	return (0);
	}
else
	{
	goto next;
	}
}
