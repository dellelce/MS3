/* tony dee © 1992
**  
** temporary file.
** used to understand 68K code.....
** this will be finally deleted!
** now for (shift, roll, pea and next others..)
** 
** 
** 	 HHHH*---D*SSZ-*----
** 		 
** 		 D -> direction (LEFT = 1 // RIGHT = 0)
** 		 Z -> if Z = 1 then DATA REG to DATA REG
** 		         Z = 0 then 
** 			 	    if SS = 11 then 'one operator mode'
** 				    else
** 				    number No to register
** 
*/ 

/*
#define	RS_ONEARG	%0000000011000000


#define	RSZ_ON		%0000000000100000
#define	RSZ_OFF		%0000000000000000
*/

#define	RSS_BYTE	%0000000000000000
#define	RSS_WORD	%0000000001000000
#define	RSS_LONG	%0000000010000000

#define	RLS_LEFT	%0000000100000000
#define	RLS_RIGHT	%0000000000000000

#define	RLS_L		RLS_LEFT
#define	RLS_R		RLS_RIGHT

#define	LGSH1		%11100000000001000	/* value 2 data		*/
#define	ROXI		%11100000000010000
#define	ROLI		%11100000000011000
#define	ASHF		%11100000000100000
#define	LGSH2		%11100000000101000	/* data 2 data		*/
#define	ROLX		%11100000000110000
#define	ROLL		%11100000000111000


#define	RARGS(x,y)	(RSARG1 (x) | y)


#define	ROLLR_BR(b,x,y)		W0 (b, ROLL_B | RSS_BYTE | RLS_R | RARGS (x, y))
#define	ROLLR_WR(b,x,y)		W0 (b, ROLL_B | RSS_WORD | RLS_R | RARGS (x, y))
#define	ROLLR_LR(b,x,y)		W0 (b, ROLL_B | RSS_LONG | RLS_R | RARGS (x, y))

#define	ROLLR_BL(b,x,y)		W0 (b, ROLL_B | RSS_BYTE | RLS_L | RARGS (x, y))
#define	ROLLR_WL(b,x,y)		W0 (b, ROLL_B | RSS_WORD | RLS_L | RARGS (x, y))
#define	ROLLR_LL(b,x,y)		W0 (b, ROLL_B | RSS_LONG | RLS_L | RARGS (x, y))


#define	ROLXR_BR(b,x,y)		W0 (b, ROLX_B | RSS_BYTE | RLS_R | RARGS (x, y))
#define	ROLXR_WR(b,x,y)		W0 (b, ROLX_B | RSS_WORD | RLS_R | RARGS (x, y))
#define	ROLXR_LR(b,x,y)		W0 (b, ROLX_B | RSS_LONG | RLS_R | RARGS (x, y))

#define	ROLLR_BL(b,x,y)		W0 (b, ROLX_B | RSS_BYTE | RLS_L | RARGS (x, y))
#define	ROLLR_WL(b,x,y)		W0 (b, ROLX_B | RSS_WORD | RLS_L | RARGS (x, y))
#define	ROLLR_LL(b,x,y)		W0 (b, ROLX_B | RSS_LONG | RLS_L | RARGS (x, y))

/* 
** arithmetic shift reg 2 reg, left and right
** 
*/ 

#define	ASHIFTR_BR(b,x,y)	W0 (b, ASHF_B | RSS_BYTE | RLS_R | RARGS (x, y))
#define	ASHIFTR_WR(b,x,y)	W0 (b, ASHF_B | RSS_WORD | RLS_R | RARGS (x, y))
#define	ASHIFTR_LR(b,x,y)	W0 (b, ASHF_B | RSS_LONG | RLS_R | RARGS (x, y))

#define	ASHIFTR_BL(b,x,y)	W0 (b, ASHF_B | RSS_BYTE | RLS_L | RARGS (x, y))
#define	ASHIFTR_WL(b,x,y)	W0 (b, ASHF_B | RSS_WORD | RLS_L | RARGS (x, y))
#define	ASHIFTR_LL(b,x,y)	W0 (b, ASHF_B | RSS_LONG | RLS_L | RARGS (x, y))

 

#define	BITA_TEST	%0000000100000000
#define	BITA_CHANGE	%0000000101000000
#define	BITA_CLEAR	%0000000110000000
#define	BITA_SET	%0000000111000000


