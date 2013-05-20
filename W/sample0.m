{
 esample of an MS3 program
 from Antonio Dell'Elce
 
 
 WARNING: my language has no preprocessor
 the 'alias' works this way: it adds to current list of symbols
 another one with data taken from the already existing object.
 Its syntax:
 
}

source "anylists" {routines for lists-and-nodes handling (add/enqueue,remove..)}

alias	LONG	long;
alias	PTR	pointer;
alias	STR	string;

action strlen
args:			{this is a 'reserved label', unsure about itsname}
STR	string;


action copystring
args:
STR	source;
STR	destination;

body:


object doanything

real	LONG		objaddress;
	PTR LONG	anyreply0;
	LONG		anyreply1;
	STR		anyreply2;
	STR		anyname;

variables: {global static variables reserved for the object}

LONG	DAsemi;
LONG	DAseqno;
LONG	DAobjecttillnow;
ANYLIST	DAobjlist;	{from anylists 'source of code'}

handlers:

handler create

	attributes anyname; {attributes that are needed to 'create the
				object'}
	
	
	{do whatever you thing right to create the object}
	
