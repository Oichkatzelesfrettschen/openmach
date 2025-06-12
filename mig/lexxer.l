%{%
#include <stdio.h>
#include <string.h>
#ifndef PARAM_DECL
#define PARAM_DECL(type, name, init) type name init
#endif
#include "global.h"
#include "mig_string.h"
#include "type.h"
#include "statement.h"
#include "routine.h"
#include "error.h"
#include "utils.h"
#include "parser.h" /* MODIFIED: Use parser.h as y.tab.h gets renamed */
#include "cpu.h"
extern int yylineno;
extern FILE *yyin;
extern char *yytext;

#define input()		(yyinput())
#define unput(c)	(yyunput(c))
#define output(c)	(yyoutput(c))

static int yylex_KeyWord(int token);
static int yylex_Identifier(char *text);
static int yylex_SymbolicType(char *text, int type_token);
static int yylex_StringConst(char *text);
static int yylex_CharConst(char *text);
static int yylex_Number(char *text);
static int yylex_Boolean(boolean_t val);
static int yylex_Strudel(void);
static void next_char(void);
%}

DIGIT    [0-9]
HEXDIGIT [0-9a-fA-F]
OCTALDIGIT [0-7]
ALPHA    [a-zA-Z_]
ALNUM    [a-zA-Z0-9_]

pathname ({ALPHA}|{DIGIT}|[\.\/+])({ALPHA}|{DIGIT}|[\.\/+]|[-_])*
comment  \/\*([^*]|\*+[^*/])*\*+\/ /* Corrected non-greedy C-style comment */
cppcomment \/\/[^\n]*

rcsident {ALPHA}({ALPHA}|{DIGIT}|_|-)*
ident    {ALPHA}{ALNUM}*
number   {DIGIT}+
hexnumber 0x{HEXDIGIT}+
octalnumber 0{OCTALDIGIT}*
string   "\""([^"\\]|\\.)*"\"" /* Allows escaped quotes */
charconst "'"([^'\\]|\\.)"'" /* Allows escaped quotes */

%s STATE_COMMENT STATE_ENDCOMMENT STATE_SEMANTICS

%%
{comment}		{ /* ignore comments */ }
{cppcomment}    { /* ignore c++ comments */ }

^"/*"			{ BEGIN STATE_COMMENT; next_char(); }
<STATE_COMMENT>"*/"		{ BEGIN STATE_ENDCOMMENT; next_char(); }
<STATE_COMMENT>.			{ next_char(); }
<STATE_COMMENT>\n		{ yylineno++; next_char(); }

^"#ident"		{ BEGIN STATE_SEMANTICS; return yylex_Strudel(); }
<STATE_SEMANTICS>[^\n]*	{ return yylex_Strudel(); }
<STATE_SEMANTICS>\n		{ yylineno++; BEGIN INITIAL; return '\n'; }

"boolean"		{ return yylex_SymbolicType(yytext, sySymbolicType); }
"char"			{ return yylex_SymbolicType(yytext, sySymbolicType); }
"string"		{ return yylex_SymbolicType(yytext, sySymbolicType); }
"integer"		{ return yylex_SymbolicType(yytext, sySymbolicType); }
"real"			{ return yylex_SymbolicType(yytext, sySymbolicType); }
"pointer"		{ return yylex_SymbolicType(yytext, sySymbolicType); }
"array"			{ return yylex_KeyWord(syArray); }
"struct"		{ return yylex_KeyWord(syStruct); }
"union"			{ return yylex_KeyWord(syType); }
"void"			{ return yylex_SymbolicType(yytext, sySymbolicType); }

"in"			{ return yylex_KeyWord(syIn); }
"out"			{ return yylex_KeyWord(syOut); }
"inout"			{ return yylex_KeyWord(syInOut); }
"requestport"	{ return yylex_KeyWord(syRequestPort); }
"replyport"		{ return yylex_KeyWord(syReplyPort); }
"server"		{ return yylex_KeyWord(syServer); }
"subsystem"		{ return yylex_KeyWord(sySubsystem); }
"type"			{ return yylex_KeyWord(syType); }
"skip"			{ return yylex_KeyWord(sySkip); }
"wait"			{ return yylex_KeyWord(syWaitTime); }
"nowait"		{ return yylex_KeyWord(syNoWaitTime); }
"routine"		{ return yylex_KeyWord(syRoutine); }
"simpleroutine"	{ return yylex_KeyWord(sySimpleRoutine); }
"msgtype"		{ return yylex_KeyWord(syMsgType); }
"destructor"	{ return yylex_KeyWord(syDestructor); }
"ipc"			{ return yylex_KeyWord(syIPC); }
"variable"		{ return yylex_KeyWord(syVariable); }
"fixed"			{ return yylex_KeyWord(syFixed); }
"error"			{ return yylex_KeyWord(syErrorProc); }
"abort"			{ return yylex_KeyWord(syAbort); }
"map"			{ return yylex_KeyWord(syMap); }
"noexport"		{ return yylex_KeyWord(syNoExport); }
"kernel"		{ return yylex_KeyWord(syKernelUser); }
"user"			{ return yylex_KeyWord(syUserPrefix); }
"cpp"			{ return yylex_KeyWord(syCPP); }
"c"			{ return yylex_KeyWord(syCType); }
"true"			{ return yylex_Boolean(TRUE); }
"false"			{ return yylex_Boolean(FALSE); }

{ident}			{ return yylex_Identifier(yytext); }
{number}		{ return yylex_Number(yytext); }
{hexnumber}		{ return yylex_Number(yytext); }
{octalnumber}   { return yylex_Number(yytext); }
{string}		{ return yylex_StringConst(yytext); }
{charconst}		{ return yylex_CharConst(yytext); }

":"			{ return syColon; }
";"			{ return sySemi; }
"("			{ return syLParen; }
")"			{ return syRParen; }
"{"			{ return syLBrack; }
"}"			{ return syRBrack; }
"["			{ return syLBrack; }
"]"			{ return syRBrack; }
","			{ return syComma; }
"+"			{ return syPlus; }
"-"			{ return syMinus; }
"*"			{ return syStar; }
"/"			{ return syDiv; }
"="			{ return syEqual; }
"&"			{ return '&'; }
"|"			{ return syBar; }
"^"			{ return syCaret; }
"~"			{ return syTilde; }
"<<"			{ return syLShift; }
">>"			{ return syRShift; }

[ \t]+			/* ignore whitespace */;
\n			{ yylineno++; }
.			{ yyerror("invalid character"); }
%%
PARAM_DECL(int, yylineno, =1);
static int yylex_KeyWord(int token) { return token; }
static int yylex_Identifier(char *text) { yylval.identifier = LookUpIdentifier(text); return syIdentifier; }
static int yylex_SymbolicType(char *text, int type_token) { yylval.identifier = LookUpIdentifier(text); return type_token; }
static int yylex_StringConst(char *text) { yylval.string = DeString(text); return syString; }
static int yylex_CharConst(char *text) { yylval.number = DeChar(text); return syNumber; }
static int yylex_Number(char *text) { char *ptr=NULL; if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X')) yylval.number = strtol(text, &ptr, 16); else if (text[0] == '0') yylval.number = strtol(text, &ptr, 8); else yylval.number = atoi(text); return syNumber; }
static int yylex_Boolean(boolean_t val) { yylval.boolean = val; return syBoolean; }
static int yylex_Strudel(void) { yylval.string = strdup(yytext); return syStrudel; }
static void next_char(void) { /* Stub */ }
/* yyerror is in parser.y */
int yywrap(void) { return 1; }
