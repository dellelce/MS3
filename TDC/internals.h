/* tony dee © 1992
** newest release (v0.04)
**  
*/ 


#ifndef	INTERNALS_H
#define INTERNALS_H 1


/* 
** 
** internals headers
** divided by class
** 
** 
*/ 


#define	IN_MINOR		0xC881
#define	IN_MAJOR		0xC882
#define	IN_ISEQUAL		0xC883
#define	IN_ISNOTEQUAL		0xC884
#define	IN_EQMAJOR		0xC885
#define	IN_EQMINOR		0xC886
#define	IN_MULTIPLY		0xC887
#define	IN_SUBTRACT		0xC888
#define	IN_ADD			0xC889
#define	IN_DIVIDE		0xC88A
#define	IN_BRAK2OP		0xC88B
#define	IN_BRAK2CL		0xC88C
#define	IN_BRAK1OP		0xC88D
#define	IN_BRAK1CL		0xC88E
#define	IN_OR			0xC891
#define	IN_AND			0xC892
#define	IN_EXCLAMATION		0xC893
#define	IN_EXOR			0xC894
#define	IN_COMMA		0xC895
#define	IN_TWOPOINTS		0xC896
#define	IN_DIESIS		0xC897
#define	IN_QUESTION		0xC898
#define	IN_PERIOD		0xC899
#define	IN_WAVE			0xC89A
#define	IN_UNDERLINE		0xC89B
#define	IN_BACKSLASH		0xC89C
#define	IN_SHIFTR		0xC8A1
#define	IN_SHIFTL		0xC8A2
#define	IN_LOGICAND		0xC8A3
#define	IN_LOGICOR		0xC8A4
#define	IN_EQUAL		0xC8A5


/* 
** res words
** 
*/ 

#define	IN_IF_THEN		0xD800
#define	IN_IF_THEN_ELSE		0xD801
#define	IN_SWITCH		0xD802
#define	IN_CASE			0xD803
#define	IN_DEFAULT		0xD804
#define	IN_WHILE		0xD805
#define	IN_FOR			0xD806
#define	IN_SOURCE		0xD807
#define	IN_MEXT			0xD808
#define	IN_ALIAS		0xD809
#define	IN_DO			0xD80A
#define	IN_BREAK		0xD80B
#define	IN_FORGET		0xD80C
#define	IN_DEFINE		0xD80D
#define	IN_NEWTYPE		0xD80E

#define	blockstart (b)		bwritew (b, IN_BLOCKSTART)
#define	blockend (b)		bwritew (b, IN_BLOCKEND)

#define	ISBLOCKEND(x)		(*x == IN_BLOCKEND)
#define	ISBLOCKSTART(x)		(*x == IN_BLOCKSTART)

/* 
** object operators
** 
*/ 

#define	IN_OBJ_OPEN		0xD810
#define	IN_OBJ_CLOSE		0xD811
#define	IN_OBJ_CREATE		0xD812
#define	IN_OBJ_DELETE		0xD813
#define	IN_OBJ_MODIFY		0xD814
#define	IN_OBJ_ATTRIBUTES	0xD815
#define	IN_OBJ_TYPE		0xD816
#define	IN_OBJ_SIZE		0xD817
#define	IN_OBJ_REAL		0xD818


/* 
** object operators with unknown object
** 
*/ 

#define	IN_UNKN_OPEN		0xD830
#define	IN_UNKN_CLOSE		0xD831
#define	IN_UNKN_CREATE		0xD832
#define	IN_UNKN_DELETE		0xD833
#define	IN_UNKN_MODIFY		0xD834
#define	IN_UNKN_ATTRIBUTES	0xD835
#define	IN_UNKN_TYPE		0xD836
#define	IN_UNKN_SIZE		0xD837
#define	IN_UNKN_REAL		0xD838

#define	OBJ_UNKNOWN_BIT		%0000000000100000

#define	SET_OUB(x)		x | OBJ_UNKNOWN_BIT
#define	FAR_SET_OUB(x)		*x = (*x) | OBJ_UNKNOWN_BIT

#define	ASK_OUB(x)		x & OBJ_UNKNOWN_BIT
#define	FAR_ASK_OUB(x)		(*x) & OBJ_UNKNOWN_BIT

/* 
** 'calls and jumps'
** 
*/ 

#define	IN_GOTO			0xC103
#define	IN_CALL			0xC104
#define	IN_SUBRETURN		0xC005
#define	IN_EXIT			0xC006	/* needed a block after them	*/
#define	IN_RETURN		0xC007

/* 
** 'calls and jumps' to not-well-known places
** 
*/ 

#define	IN_UNKNOWN_GOTO		0xC10B
#define	IN_UNKNOWN_CALL		0xC10C

#endif
