/* tony dee © 1992
** 
** here there will be all definitions
** regarding 'items' handling
** 
** VERSION  1.00 (this is the first time a version is given to this file)
** 
*/ 

/* %%
** setitem
** newitem	<simulated>
** createitem
** loaditem
** 
*/ 


#include <items.h>


/* # setitem
** 
** creation of processmap item 
** it should be translated in assembly as soon as possible!!
** 
** 
*/ 

BOOL
setitem (pm, type, subtype, str, def)
REG PMAP	*pm;
USHORT		 type;
USHORT		 subtype;
WPTR		 str;
WPTR		 def;
{
REG BLOCK	*block;
ITEM		 item;

item.di_type	=	type;
item.di_subtype	=	subtype;
item.di_str	=	str;
item.di_def	=	def;

block = pm->Pblocks [_Directory];

if (ISFALSE (blockwrite (block, (UBYTE *) &item, ITEMSIZE)))
	{
	return (FALSE);
	}

block->BlockItemsCount++;

return (TRUE);
}


/* 
** ITEM * (pointer to the new item structure )
** # createitem (pm) (pmap where to be created the new item)
** 
** 
** creates an item structure to a pmap directory
** block.
** (used for archiving general data)
** 
*/ 

#asm
	public	_newitem
_newitem:
#endasm

ITEM *
createitem (pm)
REG PMAP	*_pm;
{
REG ITEM	*item;

return (makeroom (_pm->Pblocks[_Items], ITSIZE));
}


/* # loaditem
** 
** given a processmap and string it should get the
** item it represents
** 
** 
*/ 


BOOL
loaditem (li_group, li_pmap, li_name)
GROUP		*li_group;
PMAP		*li_pmap;
UBYTE		*li_name;
{
ITEM		*li_item;

li_item = findindir (li_pmap, li_name);

if (ISZERO (li_item))
	{
	goto error;
	}

switch (li_item->it_type)
{
case	IT_OBJECTDEF:

case	IT_ACTION:

case	IT_FUNCTION:

case	IT_

case	IT_

case	IT_

case	IT_

case	IT_

case	IT_

case	IT_

case	IT_
};

end:;
return (TRUE);

error:;
return (FALSE);
}
