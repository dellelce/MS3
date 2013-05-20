/* tony dee © 1992
** 
** 
** Defining new archive base
** 
** 
*/ 

#include <names.h>


#define	SIZEONE		10

UWORD names = $NAMES;


NAMEVEC	*internal [25]
{
a_names,	/* HERE IS THE VECTOR!				*/
b_names,
c_names,
d_names,
e_names,
f_names,
g_names,
h_names,
i_names,
j_names,
k_names,
l_names,
m_names,
n_names,
o_names,
p_names,
q_names,
r_names,
s_names,
t_names,
u_names,
v_names,
w_names,
x_names,
y_names,
z_names		/* BUT SOMETHING WRONG IN IT!			*/
};

UBYTE intcounters [25] =
{
5,	/* 'a'	*/
4,	/* 'b'	*/
5,	/* 'c'	*/
5,	/* 'd'	*/
1,	/* 'e'	*/
5,	/* 'f'	*/
3,	/* 'g'	*/
0,	/* 'h'	*/
1,	/* 'i'	*/
0,	/* 'j'	*/
0,	/* 'k'	*/
0,	/* 'l'	*/
1,	/* 'm'	*/
2,	/* 'n'	*/
2,	/* 'o'	*/
1,	/* 'p'	*/
1,	/* 'q'	*/
8,	/* 'r'	*/
7,	/* 's '	*/
2,	/* 't'	*/
2,	/* 'u'	*/
0,	/* 'v'	*/
0,	/* 'w'	*/
0,	/* 'x'	*/
0,	/* 'y'	*/
0,	/* 'z'	*/
};

NAMEVEC	 a_names = 
{
0,	/* to be set */
SIZEONE,
a_vec
};

NAME	 a_vec[SIZEONE] =
{
 {
 "action",
 NDT_DEFINER,
 NDS_ACTION
 },

 {
 "attributes",
 NDT_OBJECTOP,
 NDS_ATTRIBUTES
 },

 {
 "argin",
 NDT_RESLABEL,
 NDS_ARGIN
 },

 {
 "argout"
 NDT_RESLABEL,
 NDS_ARGOUT
 },

 {
 "alias",
 NDT_RESWORD,
 NDS_ALIAS
 }
};


NAMEVEC	 b_names =
{
0,
SIZEONE,
b_vec
};

NAME	 b_vec[SIZEONE] =
{
 {
 "byte",
 NDT_SIMPLEDEF,
 NDS_BYTE
 },

 {
 "break",
 NDT_RESWORD
 NDS_BREAK
 },

 {
 "bool",
 NDT_SIMPLEDEF,
 NDS_BOOL
 },

 {
 "body",
 NDT_RESLABEL,
 NDS_BODY
 }
};


NAMEVEC p_names =
{
0,
SIZEONE,
p_vec
};

NAME	 p_vec[SIZEONE] =
{
 {
 "pointer".
 NDT_SIMPLEDEF,
 NDS_POINTER
 }
};


NAMEVEC n_names = 
{
0,
SIZEONE,
n_vec
};

NAME	 n_vec[SIZEONE] =
{
 {
 "next",
 NDT_RESWORD,
 NDS_NEXT
 },

 {
 "newtype",
 NDT_RESWORD,
 NDS_NEWTYPE
 }
};


NAMEVEC o_names =
{
0,
SIZEONE,
o_vec
};

NAME	 o_vec[SIZEONE] =
{
 {
 "open",
 NDT_OBJECTOP,
 NDS_OPEN
 },

 {
 "object",
 NDT_DEFINER,
 NDS_OBJECT
 }
};


NAMEVEC c_names =
{
0,
SIZEONE,
c_vec
};

NAME	 c_vec[SIZEONE] =
{
 {
 "create",
 NDT_OBJECTOP,
 NDS_CREATE
 },

 {
 "close",
 NDT_OBJECTOP,
 NDS_CLOSE
 },

 {
 "call",
 NDT_RESWORD,
 NDS_CALL
 },

 {
 "case"
 NDT_RESWORD,
 NDS_CASE
 },

 {
 "continue",
 NDT_RESWORD,
 NDS_NEXT,
 }
};


NAMEVEC d_names =
{
0,
SIZEONE,
d_vec
};

NAME	 d_vec[SIZEONE] =
{
 {
 "delete",
 NDT_OBJECTOP,
 0L
 },
 
 {
 "double",
 NDT_SIMPLEDEF,
 NDS_DOUBLE
 },
 
 {
 "do",
 NDT_RESWORD,
 NDS_DO
 },

 {
 "define",
 NDT_RESWORD,
 NDS_DEFINE
 },

 {
 "default",
 NDT_RESWORD,
 NDS_DEFAULT
 }
};


NAMEVEC s_names =
{
0,
SIZEONE,
s_vec
};

NAME	 s_vec[SIZEONE] =
{
 {
 "structure",
 NDT_DEFINER,
 NDS_STRUCTURE
 },

 {
 "struct",
 NDT_DEFINER,
 NDS_STRUCTURE
 },

 {
 "subreturn",
 NDT_RESWORD,
 NDS_SUBRETURN
 },

 {
 "size",
 NDT_OBJECTOP,
 NDS_SIZE
 },

 {
 "starter",
 NDT_DEFINER,
 NDS_STARTER
 },

 {
 "switch",
 NDT_RESWORD,
 NDS_SWITCH
 },

 {
 "switch",
 NDT_RESWORD,
 NDS_SWITCH
 }
};


NAMEVEC f_names =
{
0,
SIZEONE,
f_vec
};

NAME	 f_vec[SIZEONE] =
{
 {
 "fetched",
 NDT_DEFINER,
 NDS_FETCHED
 },

 {
 "find",
 NDT_PMAPOPERATOR,
 NDS_FIND
 },

 {
 "float",
 NDT_SIMPLEDEF,
 NDS_FLOAT
 },

 {
 "false"
 NDT_RESCONST,
 NDS_FALSE
 },

 {
 "forget"
 NDT_RESWORD,
 NDS_FORGET
 }
};


NAMEVEC r_names =
{
0,
SIZEONE,
r_vec
};

NAME	 r_vec[SIZEONE] =
{
 {
 "range",
 NDT_SIMPLEDEF,
 NDS_RANGE
 },
 
 {
 "remove",
 NDT_PMAPOPERATOR,
 NDS_REMOVE
 },
 
 {
 "return",
 NDT_RESWORD,
 NDS_RETURN
 },
 
 {
 "real",
 NDT_OPBJECTOP,
 NDS_REAL
 },
 
 {
 "replace",
 NDT_PMAPOPERATOR,
 NDS_REPLACE
 },
 
 {
 "restring",
 NDT_PMAPOPERATOR,
 NDS_RESTRING
 },
 
 {
 "removeline",
 NDT_PMAPOPERATOR,
 NDS_REMOVELINE
 },
 
 {
 "removezone",
 NDT_PMAPOPERATOR,
 NDS_REMOVEZONE
 }
};


NAMEVEC e_names =
{
0,
SIZEONE,
e_vec
};

NAME	 e_vec[SIZEONE] =
{
 {
 "exit",
 NDT_RESWORD,
 NDS_EXIT
 }
};


NAMEVEC g_names =
{
0,
SIZEONE,
g_vec,
};

NAME	 g_vec[SIZEONE] =
{
 {
 "ghost",	/* for pre-executed actions */
 NDT_DEFINER,
 NDS_GHOST,
 },

 {
 "goto",
 NDT_RESWORD,
 NDS_GOTO
 },

 {
 "global",
 NDT_DEFINER,
 NDS_GLOBAL
 }
};


NAMEVEC t_names =
{
0,
SIZEONE,
t_vec
};

NAME	 t_vec[SIZEONE] =
{
 {
 "type",
 NDT_OBJECTOP,
 NDS_TYPE
 },

 {
 "true",
 NDT_RESCONST,
 NDS_TRUE
 }
};


NAMEVEC u_names =
{
0,
SIZEONE,
u_vec
};

NAME	 u_vec[SIZEONE] =
{
 {
 "undefined",
 0,
 0L
 },
 {
 "until",
 NDT_RESWORD,
 NDS_UNTIL
 }
};

NAMEVEC i_names =
{
0,
SIZEONE,
i_vec
};

NAME	 i_vec[SIZEONE] =
{
 {
 "if",
 NDT_RESWORD,
 NDS_IF
 }
};

NAMEVEC m_names =
{
0,
SIZEONE,
m_vec
};

NAME	 m_vec[SIZEONE] =
{
 {
 "modify",
 NDT_OBJECT,
 NDS_MODIFY
 }
};


NAMEVEC q_names =
{
0,
SIZEONE,
q_vec
};

NAME	 q_vec[SIZEONE] =
{
 {
 "quit",	/* stands for exit */
 NDT_RESWORD,
 NDS_EXIT
 }
};

/* 
** to be improved
** 
*/ 
