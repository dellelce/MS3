#include <spex.h>

SPCASE _spcase =
{
0,
&spexx
};

SPEC _spex [] =
{
{
'!',
NDS_EXCLAMATION,
$to_set
},

{
'#',
NDS_DIESIS,
$to_set
},

{
'(',
NDS_BRAK1OP,
$to_set
},

{
')',
NDS_BRAK1CL,
$to_set
},

{
'*',
NDS_MULTIPLY,
$to_set
},

{
'+',
NDS_ADD,
$to_set
},

{
',',
NDS_COMMA,
$to_set
},

{
'-',
NDS_SUBTRACT,
$to_set
},

{
'.',
NDS_PERIOD,
$to_set
},

{
'/',
NDS_DIVIDE,
$to_set
},

{
':',
$NDS_EXPLAIN,
$to_set
},

{
';'
$NDT_CLOSER,
$to_set
},

{
'<',
NDS_MINOR,
$to_set
},

{
'=',
NDS_EQUAL,
$to_set
},

{
'>',
NDS_MAJOR,
$to_set
},

{
'?',
NDS_QUESTION,
$to_set
},

{
'[',
NDS_BRAK2OP,
$to_set
},

{
'\',
NDS_BACKSLASH,
$to_set
},

{
']',
NDS_BRAK2CL,
$to_set
},

{
};
