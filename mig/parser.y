%{%
#include <stdio.h>
#include "global.h"
#include "mig_string.h"
#include "type.h"
#include "routine.h"
#include "statement.h"
#include "error.h"
extern int yylex(void);
void yyerror(const char *s);
extern int yylineno;
extern char *yytext;
%}
%union {
    identifier_t identifier;
    const_string_t string;
    int number;
    boolean_t boolean;
    statement_kind_t statement_kind;
    ipc_type_t ipc_type; /* Assuming these are pointers in practice, as per fixed YYSTYPE */
    routine_t routine;   /* For YYSTYPE, complex types are often pointers */
    arg_kind_t arg_kind; /* arg_kind_t itself, not a pointer */
    argument_t argument; /* Assuming pointer */
    ipc_flags_t ipc_flags; /* ipc_flags_t itself */
    struct {
        u_int innumber;
        const_string_t instr;
        u_int outnumber;
        const_string_t outstr;
        u_int size;
    } symtype;
}
%token <identifier> syIdentifier
%token <string> syString syCString syStrudel
%token <number> syNumber
%token <boolean> syBoolean
%token <ipc_flags> syIPCFlags
%token <symtype> sySymbolicType

%type <identifier> SubsystemName TypeName RoutineName ArgumentName /* MsgTypeName KernelName UserName ServerName */
%type <routine> Routine RoutineDecl RoutineHeader RoutineBody RoutineHeaderName RoutineHeaderBody OptionalSemiColon
%type <argument> Argument ArgumentType ArgumentList OptionalArgumentList /* ArgumentBody ArgumentVariable ArgumentTypeSpecial */
%type <ipc_type> Type TypeSpec ActualType /* TypeSimple TypeUser TypeKernel TypeServer TypePointer TypeArray TypeStructOrUnion TypeNameOrType */
%type <statement_kind> Specification

%token sySkip syRoutine sySimpleRoutine syProcedure sySimpleProcedure syFunction
%token sySubsystem syKernelUser syKernelServer
%token syMsgOption syMsgSeqno syWaitTime syNoWaitTime syErrorProc
%token syServerPrefix syUserPrefix syServerDemux syRCSId
%token syImport syUImport sySImport
%token syIn syOut syInOut syRequestPort syReplyPort sySReplyPort syUReplyPort
%token syType syArray syStruct syOf
%token syInTran syOutTran syDestructor syCType syCUserType syCServerType
%token syColon sySemi syComma syPlus syMinus syStar syDiv
%token syLParen syRParen syEqual syCaret syTilde syLAngle syRAngle
%token syLBrack syRBrack syBar
%token syError
%token syServer syFixed syIPC syVariable syMap syNoExport syKernel syUser syCPP syC
%token syLShift syRShift
%%
MigInput: SpecificationList ;
SpecificationList: | SpecificationList Specification ;
Specification: Subsystem OptionalSemiColon | TypeStatement OptionalSemiColon | Routine OptionalSemiColon | RCSIdent OptionalSemiColon ;
Subsystem: sySubsystem SubsystemName syNumber ;
SubsystemName: syIdentifier { /* CurrentSubsystem = $1; */ } ;
TypeStatement: syType TypeName OptionalEquals Type ;
TypeName: syIdentifier ;
OptionalEquals: | '=' ;
Type: ActualType | TypeName ;
ActualType: sySymbolicType { /* $$ = LookUpType(LookUpIdentifier(yytext)); */ } | syStruct syIdentifier "{" "}" { /* $$ = DefineStructType($2, NULL); */ } | syArray "[" syNumber "]" syOf Type { /* $$ = DefineArrayType($3, $6); */ } | syIdentifier ; /* Added syIdentifier here as a form of ActualType */
RCSIdent: syRCSId syString ;
Routine: RoutineHeaderName "(" OptionalArgumentList ")" /* RoutineFlags */  ;
RoutineHeaderName: syRoutine RoutineName { /* NewRoutine($2); */ } ;
RoutineName: syIdentifier ;
OptionalArgumentList: | ArgumentList ;
ArgumentList: Argument | ArgumentList "," Argument ;
Argument: ArgumentName ":" ArgumentType ;
ArgumentName: syIdentifier ;
ArgumentType: Type ; /* Type can now resolve to syIdentifier (TypeName) or ActualType */
/* RoutineFlags: | syMsgType syNumber { CurrentRoutine->MsgType = $2; } ; */
/* RoutineBody: ; */
/* ErrorRoutine: syErrorProc Routine ; */
OptionalSemiColon: | ';' ;
%%
#include <stdlib.h>
/* #include "utils.h" -- Removed as actions using LookUpType etc. are commented out */
void yyerror(const char *s) { fprintf(stderr, "mig: PARSER ERROR: %s at line %d near token \"%s\"\n", s, yylineno, yytext); }
