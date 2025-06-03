/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 117 "parser.y"


#include <stdio.h>

#include "error.h"
#include "lexxer.h"
#include "global.h"
#include "mig_string.h"
#include "type.h"
#include "routine.h"
#include "statement.h"

static const char *import_name(statement_kind_t sk);

void
yyerror(const char *s)
{
    error(s);
}

#line 92 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    sySkip = 258,                  /* sySkip  */
    syRoutine = 259,               /* syRoutine  */
    sySimpleRoutine = 260,         /* sySimpleRoutine  */
    sySimpleProcedure = 261,       /* sySimpleProcedure  */
    syProcedure = 262,             /* syProcedure  */
    syFunction = 263,              /* syFunction  */
    sySubsystem = 264,             /* sySubsystem  */
    syKernelUser = 265,            /* syKernelUser  */
    syKernelServer = 266,          /* syKernelServer  */
    syMsgOption = 267,             /* syMsgOption  */
    syMsgSeqno = 268,              /* syMsgSeqno  */
    syWaitTime = 269,              /* syWaitTime  */
    syNoWaitTime = 270,            /* syNoWaitTime  */
    syErrorProc = 271,             /* syErrorProc  */
    syServerPrefix = 272,          /* syServerPrefix  */
    syUserPrefix = 273,            /* syUserPrefix  */
    syServerDemux = 274,           /* syServerDemux  */
    syRCSId = 275,                 /* syRCSId  */
    syImport = 276,                /* syImport  */
    syUImport = 277,               /* syUImport  */
    sySImport = 278,               /* sySImport  */
    syIn = 279,                    /* syIn  */
    syOut = 280,                   /* syOut  */
    syInOut = 281,                 /* syInOut  */
    syRequestPort = 282,           /* syRequestPort  */
    syReplyPort = 283,             /* syReplyPort  */
    sySReplyPort = 284,            /* sySReplyPort  */
    syUReplyPort = 285,            /* syUReplyPort  */
    syType = 286,                  /* syType  */
    syArray = 287,                 /* syArray  */
    syStruct = 288,                /* syStruct  */
    syOf = 289,                    /* syOf  */
    syInTran = 290,                /* syInTran  */
    syOutTran = 291,               /* syOutTran  */
    syDestructor = 292,            /* syDestructor  */
    syCType = 293,                 /* syCType  */
    syCUserType = 294,             /* syCUserType  */
    syCServerType = 295,           /* syCServerType  */
    syCString = 296,               /* syCString  */
    syColon = 297,                 /* syColon  */
    sySemi = 298,                  /* sySemi  */
    syComma = 299,                 /* syComma  */
    syPlus = 300,                  /* syPlus  */
    syMinus = 301,                 /* syMinus  */
    syStar = 302,                  /* syStar  */
    syDiv = 303,                   /* syDiv  */
    syLParen = 304,                /* syLParen  */
    syRParen = 305,                /* syRParen  */
    syEqual = 306,                 /* syEqual  */
    syCaret = 307,                 /* syCaret  */
    syTilde = 308,                 /* syTilde  */
    syLAngle = 309,                /* syLAngle  */
    syRAngle = 310,                /* syRAngle  */
    syLBrack = 311,                /* syLBrack  */
    syRBrack = 312,                /* syRBrack  */
    syBar = 313,                   /* syBar  */
    syError = 314,                 /* syError  */
    syNumber = 315,                /* syNumber  */
    sySymbolicType = 316,          /* sySymbolicType  */
    syIdentifier = 317,            /* syIdentifier  */
    syString = 318,                /* syString  */
    syQString = 319,               /* syQString  */
    syFileName = 320,              /* syFileName  */
    syIPCFlag = 321                /* syIPCFlag  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define sySkip 258
#define syRoutine 259
#define sySimpleRoutine 260
#define sySimpleProcedure 261
#define syProcedure 262
#define syFunction 263
#define sySubsystem 264
#define syKernelUser 265
#define syKernelServer 266
#define syMsgOption 267
#define syMsgSeqno 268
#define syWaitTime 269
#define syNoWaitTime 270
#define syErrorProc 271
#define syServerPrefix 272
#define syUserPrefix 273
#define syServerDemux 274
#define syRCSId 275
#define syImport 276
#define syUImport 277
#define sySImport 278
#define syIn 279
#define syOut 280
#define syInOut 281
#define syRequestPort 282
#define syReplyPort 283
#define sySReplyPort 284
#define syUReplyPort 285
#define syType 286
#define syArray 287
#define syStruct 288
#define syOf 289
#define syInTran 290
#define syOutTran 291
#define syDestructor 292
#define syCType 293
#define syCUserType 294
#define syCServerType 295
#define syCString 296
#define syColon 297
#define sySemi 298
#define syComma 299
#define syPlus 300
#define syMinus 301
#define syStar 302
#define syDiv 303
#define syLParen 304
#define syRParen 305
#define syEqual 306
#define syCaret 307
#define syTilde 308
#define syLAngle 309
#define syRAngle 310
#define syLBrack 311
#define syRBrack 312
#define syBar 313
#define syError 314
#define syNumber 315
#define sySymbolicType 316
#define syIdentifier 317
#define syString 318
#define syQString 319
#define syFileName 320
#define syIPCFlag 321

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 139 "parser.y"

    u_int number;
    identifier_t identifier;
    const_string_t string;
    statement_kind_t statement_kind;
    ipc_type_t *type;
    struct
    {
	u_int innumber;		/* msgt_name value, when sending */
	const_string_t instr;
	u_int outnumber;	/* msgt_name value, when receiving */
	const_string_t outstr;
	u_int size;		/* 0 means there is no default size */
    } symtype;
    routine_t *routine;
    arg_kind_t direction;
    argument_t *argument;
    ipc_flags_t flag;

#line 297 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_sySkip = 3,                     /* sySkip  */
  YYSYMBOL_syRoutine = 4,                  /* syRoutine  */
  YYSYMBOL_sySimpleRoutine = 5,            /* sySimpleRoutine  */
  YYSYMBOL_sySimpleProcedure = 6,          /* sySimpleProcedure  */
  YYSYMBOL_syProcedure = 7,                /* syProcedure  */
  YYSYMBOL_syFunction = 8,                 /* syFunction  */
  YYSYMBOL_sySubsystem = 9,                /* sySubsystem  */
  YYSYMBOL_syKernelUser = 10,              /* syKernelUser  */
  YYSYMBOL_syKernelServer = 11,            /* syKernelServer  */
  YYSYMBOL_syMsgOption = 12,               /* syMsgOption  */
  YYSYMBOL_syMsgSeqno = 13,                /* syMsgSeqno  */
  YYSYMBOL_syWaitTime = 14,                /* syWaitTime  */
  YYSYMBOL_syNoWaitTime = 15,              /* syNoWaitTime  */
  YYSYMBOL_syErrorProc = 16,               /* syErrorProc  */
  YYSYMBOL_syServerPrefix = 17,            /* syServerPrefix  */
  YYSYMBOL_syUserPrefix = 18,              /* syUserPrefix  */
  YYSYMBOL_syServerDemux = 19,             /* syServerDemux  */
  YYSYMBOL_syRCSId = 20,                   /* syRCSId  */
  YYSYMBOL_syImport = 21,                  /* syImport  */
  YYSYMBOL_syUImport = 22,                 /* syUImport  */
  YYSYMBOL_sySImport = 23,                 /* sySImport  */
  YYSYMBOL_syIn = 24,                      /* syIn  */
  YYSYMBOL_syOut = 25,                     /* syOut  */
  YYSYMBOL_syInOut = 26,                   /* syInOut  */
  YYSYMBOL_syRequestPort = 27,             /* syRequestPort  */
  YYSYMBOL_syReplyPort = 28,               /* syReplyPort  */
  YYSYMBOL_sySReplyPort = 29,              /* sySReplyPort  */
  YYSYMBOL_syUReplyPort = 30,              /* syUReplyPort  */
  YYSYMBOL_syType = 31,                    /* syType  */
  YYSYMBOL_syArray = 32,                   /* syArray  */
  YYSYMBOL_syStruct = 33,                  /* syStruct  */
  YYSYMBOL_syOf = 34,                      /* syOf  */
  YYSYMBOL_syInTran = 35,                  /* syInTran  */
  YYSYMBOL_syOutTran = 36,                 /* syOutTran  */
  YYSYMBOL_syDestructor = 37,              /* syDestructor  */
  YYSYMBOL_syCType = 38,                   /* syCType  */
  YYSYMBOL_syCUserType = 39,               /* syCUserType  */
  YYSYMBOL_syCServerType = 40,             /* syCServerType  */
  YYSYMBOL_syCString = 41,                 /* syCString  */
  YYSYMBOL_syColon = 42,                   /* syColon  */
  YYSYMBOL_sySemi = 43,                    /* sySemi  */
  YYSYMBOL_syComma = 44,                   /* syComma  */
  YYSYMBOL_syPlus = 45,                    /* syPlus  */
  YYSYMBOL_syMinus = 46,                   /* syMinus  */
  YYSYMBOL_syStar = 47,                    /* syStar  */
  YYSYMBOL_syDiv = 48,                     /* syDiv  */
  YYSYMBOL_syLParen = 49,                  /* syLParen  */
  YYSYMBOL_syRParen = 50,                  /* syRParen  */
  YYSYMBOL_syEqual = 51,                   /* syEqual  */
  YYSYMBOL_syCaret = 52,                   /* syCaret  */
  YYSYMBOL_syTilde = 53,                   /* syTilde  */
  YYSYMBOL_syLAngle = 54,                  /* syLAngle  */
  YYSYMBOL_syRAngle = 55,                  /* syRAngle  */
  YYSYMBOL_syLBrack = 56,                  /* syLBrack  */
  YYSYMBOL_syRBrack = 57,                  /* syRBrack  */
  YYSYMBOL_syBar = 58,                     /* syBar  */
  YYSYMBOL_syError = 59,                   /* syError  */
  YYSYMBOL_syNumber = 60,                  /* syNumber  */
  YYSYMBOL_sySymbolicType = 61,            /* sySymbolicType  */
  YYSYMBOL_syIdentifier = 62,              /* syIdentifier  */
  YYSYMBOL_syString = 63,                  /* syString  */
  YYSYMBOL_syQString = 64,                 /* syQString  */
  YYSYMBOL_syFileName = 65,                /* syFileName  */
  YYSYMBOL_syIPCFlag = 66,                 /* syIPCFlag  */
  YYSYMBOL_YYACCEPT = 67,                  /* $accept  */
  YYSYMBOL_Statements = 68,                /* Statements  */
  YYSYMBOL_Statement = 69,                 /* Statement  */
  YYSYMBOL_Subsystem = 70,                 /* Subsystem  */
  YYSYMBOL_SubsystemStart = 71,            /* SubsystemStart  */
  YYSYMBOL_SubsystemMods = 72,             /* SubsystemMods  */
  YYSYMBOL_SubsystemMod = 73,              /* SubsystemMod  */
  YYSYMBOL_SubsystemName = 74,             /* SubsystemName  */
  YYSYMBOL_SubsystemBase = 75,             /* SubsystemBase  */
  YYSYMBOL_MsgOption = 76,                 /* MsgOption  */
  YYSYMBOL_WaitTime = 77,                  /* WaitTime  */
  YYSYMBOL_Error = 78,                     /* Error  */
  YYSYMBOL_ServerPrefix = 79,              /* ServerPrefix  */
  YYSYMBOL_UserPrefix = 80,                /* UserPrefix  */
  YYSYMBOL_ServerDemux = 81,               /* ServerDemux  */
  YYSYMBOL_Import = 82,                    /* Import  */
  YYSYMBOL_ImportIndicant = 83,            /* ImportIndicant  */
  YYSYMBOL_RCSDecl = 84,                   /* RCSDecl  */
  YYSYMBOL_TypeDecl = 85,                  /* TypeDecl  */
  YYSYMBOL_NamedTypeSpec = 86,             /* NamedTypeSpec  */
  YYSYMBOL_TransTypeSpec = 87,             /* TransTypeSpec  */
  YYSYMBOL_TypeSpec = 88,                  /* TypeSpec  */
  YYSYMBOL_BasicTypeSpec = 89,             /* BasicTypeSpec  */
  YYSYMBOL_IPCFlags = 90,                  /* IPCFlags  */
  YYSYMBOL_PrimIPCType = 91,               /* PrimIPCType  */
  YYSYMBOL_IPCType = 92,                   /* IPCType  */
  YYSYMBOL_PrevTypeSpec = 93,              /* PrevTypeSpec  */
  YYSYMBOL_VarArrayHead = 94,              /* VarArrayHead  */
  YYSYMBOL_ArrayHead = 95,                 /* ArrayHead  */
  YYSYMBOL_StructHead = 96,                /* StructHead  */
  YYSYMBOL_CStringSpec = 97,               /* CStringSpec  */
  YYSYMBOL_IntExp = 98,                    /* IntExp  */
  YYSYMBOL_RoutineDecl = 99,               /* RoutineDecl  */
  YYSYMBOL_Routine = 100,                  /* Routine  */
  YYSYMBOL_SimpleRoutine = 101,            /* SimpleRoutine  */
  YYSYMBOL_Procedure = 102,                /* Procedure  */
  YYSYMBOL_SimpleProcedure = 103,          /* SimpleProcedure  */
  YYSYMBOL_Function = 104,                 /* Function  */
  YYSYMBOL_Arguments = 105,                /* Arguments  */
  YYSYMBOL_ArgumentList = 106,             /* ArgumentList  */
  YYSYMBOL_Argument = 107,                 /* Argument  */
  YYSYMBOL_Direction = 108,                /* Direction  */
  YYSYMBOL_ArgumentType = 109,             /* ArgumentType  */
  YYSYMBOL_LookString = 110,               /* LookString  */
  YYSYMBOL_LookFileName = 111,             /* LookFileName  */
  YYSYMBOL_LookQString = 112               /* LookQString  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   219

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  213

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   321


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   161,   161,   162,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   183,   185,   187,   188,   189,   190,   194,
     207,   219,   220,   223,   229,   237,   240,   243,   260,   266,
     274,   282,   290,   298,   306,   317,   318,   319,   322,   332,
     342,   346,   348,   368,   388,   403,   417,   426,   438,   440,
     442,   444,   446,   448,   450,   454,   460,   470,   471,   478,
     487,   493,   497,   499,   523,   527,   529,   531,   536,   540,
     544,   546,   551,   553,   555,   557,   559,   561,   566,   567,
     568,   569,   570,   573,   577,   581,   585,   589,   593,   595,
     600,   602,   609,   619,   620,   621,   622,   623,   624,   625,
     626,   627,   628,   629,   632,   638,   643,   647,   651
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "sySkip", "syRoutine",
  "sySimpleRoutine", "sySimpleProcedure", "syProcedure", "syFunction",
  "sySubsystem", "syKernelUser", "syKernelServer", "syMsgOption",
  "syMsgSeqno", "syWaitTime", "syNoWaitTime", "syErrorProc",
  "syServerPrefix", "syUserPrefix", "syServerDemux", "syRCSId", "syImport",
  "syUImport", "sySImport", "syIn", "syOut", "syInOut", "syRequestPort",
  "syReplyPort", "sySReplyPort", "syUReplyPort", "syType", "syArray",
  "syStruct", "syOf", "syInTran", "syOutTran", "syDestructor", "syCType",
  "syCUserType", "syCServerType", "syCString", "syColon", "sySemi",
  "syComma", "syPlus", "syMinus", "syStar", "syDiv", "syLParen",
  "syRParen", "syEqual", "syCaret", "syTilde", "syLAngle", "syRAngle",
  "syLBrack", "syRBrack", "syBar", "syError", "syNumber", "sySymbolicType",
  "syIdentifier", "syString", "syQString", "syFileName", "syIPCFlag",
  "$accept", "Statements", "Statement", "Subsystem", "SubsystemStart",
  "SubsystemMods", "SubsystemMod", "SubsystemName", "SubsystemBase",
  "MsgOption", "WaitTime", "Error", "ServerPrefix", "UserPrefix",
  "ServerDemux", "Import", "ImportIndicant", "RCSDecl", "TypeDecl",
  "NamedTypeSpec", "TransTypeSpec", "TypeSpec", "BasicTypeSpec",
  "IPCFlags", "PrimIPCType", "IPCType", "PrevTypeSpec", "VarArrayHead",
  "ArrayHead", "StructHead", "CStringSpec", "IntExp", "RoutineDecl",
  "Routine", "SimpleRoutine", "Procedure", "SimpleProcedure", "Function",
  "Arguments", "ArgumentList", "Argument", "Direction", "ArgumentType",
  "LookString", "LookFileName", "LookQString", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-106)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-109)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -106,     2,  -106,    -5,   -31,   -16,    27,    28,    30,    33,
    -106,  -106,    35,    49,    71,    72,    89,  -106,  -106,     6,
    -106,    60,    67,   107,   109,   110,   111,   112,   113,   114,
     115,  -106,  -106,  -106,  -106,  -106,    56,     9,    51,  -106,
    -106,   116,   117,   117,   117,   117,   117,  -106,  -106,  -106,
    -106,   118,  -106,  -106,   -10,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,    98,    99,  -106,  -106,  -106,
      95,   100,  -106,    48,  -106,  -106,  -106,  -106,   121,    47,
    -106,  -106,  -106,  -106,   105,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
     120,   124,   106,   119,  -106,   122,   123,   126,    -7,    47,
    -106,  -106,  -106,   101,  -106,  -106,   125,  -106,  -106,    47,
      47,    47,  -106,  -106,  -106,  -106,    88,   121,   118,  -106,
     -13,   -45,   -12,   127,  -106,   130,   131,   132,   133,   134,
     135,    -7,  -106,  -106,  -106,  -106,  -106,   -29,   -45,   146,
    -106,    -6,    10,   142,    36,   -45,   128,   129,   136,   137,
     138,   139,  -106,   141,   -45,   152,    82,  -106,   -45,   -45,
     -45,   -45,   153,   154,   -45,  -106,    97,   140,   143,   144,
    -106,  -106,  -106,   145,    74,  -106,  -106,    39,    39,  -106,
    -106,  -106,  -106,    78,    41,   147,   148,   150,   151,   155,
    -106,  -106,   156,   157,   158,   149,  -106,   159,   160,  -106,
    -106,  -106,  -106
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
      20,    29,     0,     0,     0,     0,     0,    17,     3,     0,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    78,    79,    80,    81,    82,     0,     0,     0,    18,
      13,     0,     0,     0,     0,     0,     0,    30,    31,    32,
      33,     0,    39,     4,     0,     6,     5,     7,     8,     9,
      10,    15,    16,    11,    12,     0,     0,    35,    36,    37,
       0,     0,    14,    93,    83,    84,    86,    85,     0,     0,
      23,    24,    25,    22,     0,    27,    28,    34,    38,   102,
     103,   101,    94,    95,    96,    97,    98,    99,   100,    88,
       0,    90,     0,     0,    87,     0,     0,     0,     0,     0,
      60,    61,    64,    40,    41,    48,    62,    55,    49,     0,
       0,     0,    54,    26,    19,    89,    93,     0,   104,   105,
       0,     0,     0,     0,    52,     0,     0,     0,     0,     0,
       0,     0,    50,    51,    53,    91,    57,     0,     0,     0,
      76,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    63,    92,     0,     0,     0,    65,     0,     0,
       0,     0,     0,     0,     0,    70,    57,     0,     0,     0,
      45,    46,    47,     0,     0,    66,    77,    72,    73,    74,
      75,    68,    69,     0,     0,     0,     0,     0,    58,     0,
      71,    56,     0,     0,     0,     0,    67,     0,     0,    44,
      59,    42,    43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,    91,
    -106,   -15,  -106,    16,    54,    96,  -106,  -106,  -106,  -106,
    -106,  -105,  -106,  -106,  -106,  -106,  -106,  -106,   103,    77,
    -106,  -106,    86,  -106,  -106,  -106
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    54,    83,    84,   124,    21,
      22,    23,    24,    25,    26,    27,    70,    28,    29,    52,
     113,   114,   115,   163,   116,   117,   118,   119,   120,   121,
     122,   151,    30,    31,    32,    33,    34,    35,    74,   100,
     101,   102,   104,    36,    37,    38
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      80,    81,     2,     3,   148,     4,     5,     6,     7,     8,
       9,    10,    40,   164,  -106,   150,  -106,    11,    12,    13,
      14,    15,  -108,  -107,  -107,  -107,   152,   154,   165,    41,
      67,    68,    69,    16,   147,   153,   148,   148,    39,   168,
     169,   170,   171,   166,   149,    17,    42,   150,   150,    53,
     176,   172,    82,   110,   111,   168,   169,   170,   171,   184,
      89,    90,    91,   187,   188,   189,   190,   173,    65,   193,
      66,    71,    92,    93,    94,    95,    96,    97,    98,   105,
     106,   168,   169,   170,   171,   183,   170,   171,   107,    43,
      44,   201,    45,   175,   134,    46,   108,    47,    99,   109,
      89,    90,    91,    55,   142,   143,   144,   110,   111,   112,
      56,    48,    92,    93,    94,    95,    96,    97,    98,   168,
     169,   170,   171,   168,   169,   170,   171,   168,   169,   170,
     171,   199,   186,    49,    50,   200,   135,   136,   137,   138,
     139,   140,   168,   169,   170,   171,    75,    76,    77,    78,
      57,    51,    58,    59,    60,    61,    62,    63,    64,    72,
      87,    85,    86,   103,    88,   123,    73,   126,   127,    79,
     125,   155,   156,   157,   158,   159,   160,   161,   130,   131,
     167,   128,   132,   141,   174,   183,   185,   191,   192,   206,
     177,   178,   194,   197,   129,   162,   202,   203,   179,   180,
     181,   182,   195,   145,   133,   196,   210,   205,   209,   211,
     212,   198,   204,   146,     0,     0,     0,     0,   207,   208
};

static const yytype_int16 yycheck[] =
{
      10,    11,     0,     1,    49,     3,     4,     5,     6,     7,
       8,     9,    43,    42,    12,    60,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,   131,   132,    57,    60,
      21,    22,    23,    31,    47,    47,    49,    49,    43,    45,
      46,    47,    48,   148,    57,    43,    62,    60,    60,    43,
     155,    57,    62,    60,    61,    45,    46,    47,    48,   164,
      12,    13,    14,   168,   169,   170,   171,    57,    12,   174,
      14,    20,    24,    25,    26,    27,    28,    29,    30,    32,
      33,    45,    46,    47,    48,    44,    47,    48,    41,    62,
      62,    50,    62,    57,   109,    62,    49,    62,    50,    52,
      12,    13,    14,    43,   119,   120,   121,    60,    61,    62,
      43,    62,    24,    25,    26,    27,    28,    29,    30,    45,
      46,    47,    48,    45,    46,    47,    48,    45,    46,    47,
      48,    57,    50,    62,    62,    57,    35,    36,    37,    38,
      39,    40,    45,    46,    47,    48,    43,    44,    45,    46,
      43,    62,    43,    43,    43,    43,    43,    43,    43,    43,
      65,    63,    63,    42,    64,    60,    49,    43,    62,    51,
      50,    44,    42,    42,    42,    42,    42,    42,    56,    56,
      34,    62,    56,    58,    42,    44,    34,    34,    34,    34,
      62,    62,   176,    49,   103,   141,    49,    49,    62,    62,
      62,    62,    62,   126,   108,    62,    57,    56,    50,    50,
      50,    66,    62,   127,    -1,    -1,    -1,    -1,    62,    62
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    68,     0,     1,     3,     4,     5,     6,     7,     8,
       9,    15,    16,    17,    18,    19,    31,    43,    69,    70,
      71,    76,    77,    78,    79,    80,    81,    82,    84,    85,
      99,   100,   101,   102,   103,   104,   110,   111,   112,    43,
      43,    60,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    86,    43,    72,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    12,    14,    21,    22,    23,
      83,    20,    43,    49,   105,   105,   105,   105,   105,    51,
      10,    11,    62,    73,    74,    63,    63,    65,    64,    12,
      13,    14,    24,    25,    26,    27,    28,    29,    30,    50,
     106,   107,   108,    42,   109,    32,    33,    41,    49,    52,
      60,    61,    62,    87,    88,    89,    91,    92,    93,    94,
      95,    96,    97,    60,    75,    50,    43,    62,    62,    86,
      56,    56,    56,    92,    88,    35,    36,    37,    38,    39,
      40,    58,    88,    88,    88,   106,   109,    47,    49,    57,
      60,    98,    98,    47,    98,    44,    42,    42,    42,    42,
      42,    42,    91,    90,    42,    57,    98,    34,    45,    46,
      47,    48,    57,    57,    42,    57,    98,    62,    62,    62,
      62,    62,    62,    44,    98,    34,    50,    98,    98,    98,
      98,    34,    34,    98,    90,    62,    62,    49,    66,    57,
      57,    50,    49,    49,    62,    56,    34,    62,    62,    50,
      57,    50,    50
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    67,    68,    68,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    70,
      71,    72,    72,    73,    73,    74,    75,    76,    77,    77,
      78,    79,    80,    81,    82,    83,    83,    83,    84,    85,
      86,    87,    87,    87,    87,    87,    87,    87,    88,    88,
      88,    88,    88,    88,    88,    89,    89,    90,    90,    90,
      91,    91,    92,    92,    93,    94,    94,    94,    95,    96,
      97,    97,    98,    98,    98,    98,    98,    98,    99,    99,
      99,    99,    99,   100,   101,   102,   103,   104,   105,   105,
     106,   106,   107,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   109,   109,   110,   111,   112
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     3,     2,     2,     1,     2,     4,
       1,     0,     2,     1,     1,     1,     1,     3,     3,     1,
       2,     2,     2,     2,     3,     1,     1,     1,     3,     2,
       3,     1,     8,     8,     7,     4,     4,     4,     1,     1,
       2,     2,     2,     2,     1,     1,     6,     0,     3,     5,
       1,     1,     1,     3,     1,     4,     5,     7,     5,     5,
       4,     6,     3,     3,     3,     3,     1,     3,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     4,     2,     3,
       1,     3,     4,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     0,     0,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 12: /* Statement: RoutineDecl sySemi  */
#line 174 "parser.y"
{
    register statement_t *st = stAlloc();

    st->stKind = skRoutine;
    st->stRoutine = (yyvsp[-1].routine);
    rtCheckRoutine((yyvsp[-1].routine));
    if (BeVerbose)
	rtPrintRoutine((yyvsp[-1].routine));
}
#line 1553 "y.tab.c"
    break;

  case 13: /* Statement: sySkip sySemi  */
#line 184 "parser.y"
                                { rtSkip(1); }
#line 1559 "y.tab.c"
    break;

  case 14: /* Statement: sySkip syNumber sySemi  */
#line 186 "parser.y"
                                { rtSkip((yyvsp[-1].number)); }
#line 1565 "y.tab.c"
    break;

  case 18: /* Statement: error sySemi  */
#line 191 "parser.y"
                                { yyerrok; }
#line 1571 "y.tab.c"
    break;

  case 19: /* Subsystem: SubsystemStart SubsystemMods SubsystemName SubsystemBase  */
#line 196 "parser.y"
{
    if (BeVerbose)
    {
	printf("Subsystem %s: base = %u%s%s\n\n",
	       SubsystemName, SubsystemBase,
	       IsKernelUser ? ", KernelUser" : "",
	       IsKernelServer ? ", KernelServer" : "");
    }
}
#line 1585 "y.tab.c"
    break;

  case 20: /* SubsystemStart: sySubsystem  */
#line 208 "parser.y"
{
    if (SubsystemName != strNULL)
    {
	warn("previous Subsystem decl (of %s) will be ignored", SubsystemName);
	IsKernelUser = FALSE;
	IsKernelServer = FALSE;
	strfree((string_t) SubsystemName);
    }
}
#line 1599 "y.tab.c"
    break;

  case 23: /* SubsystemMod: syKernelUser  */
#line 224 "parser.y"
{
    if (IsKernelUser)
	warn("duplicate KernelUser keyword");
    IsKernelUser = TRUE;
}
#line 1609 "y.tab.c"
    break;

  case 24: /* SubsystemMod: syKernelServer  */
#line 230 "parser.y"
{
    if (IsKernelServer)
	warn("duplicate KernelServer keyword");
    IsKernelServer = TRUE;
}
#line 1619 "y.tab.c"
    break;

  case 25: /* SubsystemName: syIdentifier  */
#line 237 "parser.y"
                                                { SubsystemName = (yyvsp[0].identifier); }
#line 1625 "y.tab.c"
    break;

  case 26: /* SubsystemBase: syNumber  */
#line 240 "parser.y"
                                                { SubsystemBase = (yyvsp[0].number); }
#line 1631 "y.tab.c"
    break;

  case 27: /* MsgOption: LookString syMsgOption syString  */
#line 244 "parser.y"
{
    if (streql((yyvsp[0].string), "MACH_MSG_OPTION_NONE"))
    {
	MsgOption = strNULL;
	if (BeVerbose)
	    printf("MsgOption: canceled\n\n");
    }
    else
    {
	MsgOption = (yyvsp[0].string);
	if (BeVerbose)
	    printf("MsgOption %s\n\n",(yyvsp[0].string));
    }
}
#line 1650 "y.tab.c"
    break;

  case 28: /* WaitTime: LookString syWaitTime syString  */
#line 261 "parser.y"
{
    WaitTime = (yyvsp[0].string);
    if (BeVerbose)
	printf("WaitTime %s\n\n", WaitTime);
}
#line 1660 "y.tab.c"
    break;

  case 29: /* WaitTime: syNoWaitTime  */
#line 267 "parser.y"
{
    WaitTime = strNULL;
    if (BeVerbose)
	printf("NoWaitTime\n\n");
}
#line 1670 "y.tab.c"
    break;

  case 30: /* Error: syErrorProc syIdentifier  */
#line 275 "parser.y"
{
    ErrorProc = (yyvsp[0].identifier);
    if (BeVerbose)
	printf("ErrorProc %s\n\n", ErrorProc);
}
#line 1680 "y.tab.c"
    break;

  case 31: /* ServerPrefix: syServerPrefix syIdentifier  */
#line 283 "parser.y"
{
    ServerPrefix = (yyvsp[0].identifier);
    if (BeVerbose)
	printf("ServerPrefix %s\n\n", ServerPrefix);
}
#line 1690 "y.tab.c"
    break;

  case 32: /* UserPrefix: syUserPrefix syIdentifier  */
#line 291 "parser.y"
{
    UserPrefix = (yyvsp[0].identifier);
    if (BeVerbose)
	printf("UserPrefix %s\n\n", UserPrefix);
}
#line 1700 "y.tab.c"
    break;

  case 33: /* ServerDemux: syServerDemux syIdentifier  */
#line 299 "parser.y"
{
    ServerDemux = (yyvsp[0].identifier);
    if (BeVerbose)
	printf("ServerDemux %s\n\n", ServerDemux);
}
#line 1710 "y.tab.c"
    break;

  case 34: /* Import: LookFileName ImportIndicant syFileName  */
#line 307 "parser.y"
{
    register statement_t *st = stAlloc();
    st->stKind = (yyvsp[-1].statement_kind);
    st->stFileName = (yyvsp[0].string);

    if (BeVerbose)
	printf("%s %s\n\n", import_name((yyvsp[-1].statement_kind)), (yyvsp[0].string));
}
#line 1723 "y.tab.c"
    break;

  case 35: /* ImportIndicant: syImport  */
#line 317 "parser.y"
                                                { (yyval.statement_kind) = skImport; }
#line 1729 "y.tab.c"
    break;

  case 36: /* ImportIndicant: syUImport  */
#line 318 "parser.y"
                                                { (yyval.statement_kind) = skUImport; }
#line 1735 "y.tab.c"
    break;

  case 37: /* ImportIndicant: sySImport  */
#line 319 "parser.y"
                                                { (yyval.statement_kind) = skSImport; }
#line 1741 "y.tab.c"
    break;

  case 38: /* RCSDecl: LookQString syRCSId syQString  */
#line 323 "parser.y"
{
    if (RCSId != strNULL)
	warn("previous RCS decl will be ignored");
    if (BeVerbose)
	printf("RCSId %s\n\n", (yyvsp[0].string));
    RCSId = (yyvsp[0].string);
}
#line 1753 "y.tab.c"
    break;

  case 39: /* TypeDecl: syType NamedTypeSpec  */
#line 333 "parser.y"
{
    register identifier_t name = (yyvsp[0].type)->itName;

    if (itLookUp(name) != itNULL)
	warn("overriding previous definition of %s", name);
    itInsert(name, (yyvsp[0].type));
}
#line 1765 "y.tab.c"
    break;

  case 40: /* NamedTypeSpec: syIdentifier syEqual TransTypeSpec  */
#line 343 "parser.y"
                                { itTypeDecl((yyvsp[-2].identifier), (yyval.type) = (yyvsp[0].type)); }
#line 1771 "y.tab.c"
    break;

  case 41: /* TransTypeSpec: TypeSpec  */
#line 347 "parser.y"
                                { (yyval.type) = itResetType((yyvsp[0].type)); }
#line 1777 "y.tab.c"
    break;

  case 42: /* TransTypeSpec: TransTypeSpec syInTran syColon syIdentifier syIdentifier syLParen syIdentifier syRParen  */
#line 350 "parser.y"
{
    (yyval.type) = (yyvsp[-7].type);

    if (((yyval.type)->itTransType != strNULL) && !streql((yyval.type)->itTransType, (yyvsp[-4].identifier)))
	warn("conflicting translation types (%s, %s)",
	     (yyval.type)->itTransType, (yyvsp[-4].identifier));
    (yyval.type)->itTransType = (yyvsp[-4].identifier);

    if (((yyval.type)->itInTrans != strNULL) && !streql((yyval.type)->itInTrans, (yyvsp[-3].identifier)))
	warn("conflicting in-translation functions (%s, %s)",
	     (yyval.type)->itInTrans, (yyvsp[-3].identifier));
    (yyval.type)->itInTrans = (yyvsp[-3].identifier);

    if (((yyval.type)->itServerType != strNULL) && !streql((yyval.type)->itServerType, (yyvsp[-1].identifier)))
	warn("conflicting server types (%s, %s)",
	     (yyval.type)->itServerType, (yyvsp[-1].identifier));
    (yyval.type)->itServerType = (yyvsp[-1].identifier);
}
#line 1800 "y.tab.c"
    break;

  case 43: /* TransTypeSpec: TransTypeSpec syOutTran syColon syIdentifier syIdentifier syLParen syIdentifier syRParen  */
#line 370 "parser.y"
{
    (yyval.type) = (yyvsp[-7].type);

    if (((yyval.type)->itServerType != strNULL) && !streql((yyval.type)->itServerType, (yyvsp[-4].identifier)))
	warn("conflicting server types (%s, %s)",
	     (yyval.type)->itServerType, (yyvsp[-4].identifier));
    (yyval.type)->itServerType = (yyvsp[-4].identifier);

    if (((yyval.type)->itOutTrans != strNULL) && !streql((yyval.type)->itOutTrans, (yyvsp[-3].identifier)))
	warn("conflicting out-translation functions (%s, %s)",
	     (yyval.type)->itOutTrans, (yyvsp[-3].identifier));
    (yyval.type)->itOutTrans = (yyvsp[-3].identifier);

    if (((yyval.type)->itTransType != strNULL) && !streql((yyval.type)->itTransType, (yyvsp[-1].identifier)))
	warn("conflicting translation types (%s, %s)",
	     (yyval.type)->itTransType, (yyvsp[-1].identifier));
    (yyval.type)->itTransType = (yyvsp[-1].identifier);
}
#line 1823 "y.tab.c"
    break;

  case 44: /* TransTypeSpec: TransTypeSpec syDestructor syColon syIdentifier syLParen syIdentifier syRParen  */
#line 390 "parser.y"
{
    (yyval.type) = (yyvsp[-6].type);

    if (((yyval.type)->itDestructor != strNULL) && !streql((yyval.type)->itDestructor, (yyvsp[-3].identifier)))
	warn("conflicting destructor functions (%s, %s)",
	     (yyval.type)->itDestructor, (yyvsp[-3].identifier));
    (yyval.type)->itDestructor = (yyvsp[-3].identifier);

    if (((yyval.type)->itTransType != strNULL) && !streql((yyval.type)->itTransType, (yyvsp[-1].identifier)))
	warn("conflicting translation types (%s, %s)",
	     (yyval.type)->itTransType, (yyvsp[-1].identifier));
    (yyval.type)->itTransType = (yyvsp[-1].identifier);
}
#line 1841 "y.tab.c"
    break;

  case 45: /* TransTypeSpec: TransTypeSpec syCType syColon syIdentifier  */
#line 404 "parser.y"
{
    (yyval.type) = (yyvsp[-3].type);

    if (((yyval.type)->itUserType != strNULL) && !streql((yyval.type)->itUserType, (yyvsp[0].identifier)))
	warn("conflicting user types (%s, %s)",
	     (yyval.type)->itUserType, (yyvsp[0].identifier));
    (yyval.type)->itUserType = (yyvsp[0].identifier);

    if (((yyval.type)->itServerType != strNULL) && !streql((yyval.type)->itServerType, (yyvsp[0].identifier)))
	warn("conflicting server types (%s, %s)",
	     (yyval.type)->itServerType, (yyvsp[0].identifier));
    (yyval.type)->itServerType = (yyvsp[0].identifier);
}
#line 1859 "y.tab.c"
    break;

  case 46: /* TransTypeSpec: TransTypeSpec syCUserType syColon syIdentifier  */
#line 418 "parser.y"
{
    (yyval.type) = (yyvsp[-3].type);

    if (((yyval.type)->itUserType != strNULL) && !streql((yyval.type)->itUserType, (yyvsp[0].identifier)))
	warn("conflicting user types (%s, %s)",
	     (yyval.type)->itUserType, (yyvsp[0].identifier));
    (yyval.type)->itUserType = (yyvsp[0].identifier);
}
#line 1872 "y.tab.c"
    break;

  case 47: /* TransTypeSpec: TransTypeSpec syCServerType syColon syIdentifier  */
#line 428 "parser.y"
{
    (yyval.type) = (yyvsp[-3].type);

    if (((yyval.type)->itServerType != strNULL) && !streql((yyval.type)->itServerType, (yyvsp[0].identifier)))
	warn("conflicting server types (%s, %s)",
	     (yyval.type)->itServerType, (yyvsp[0].identifier));
    (yyval.type)->itServerType = (yyvsp[0].identifier);
}
#line 1885 "y.tab.c"
    break;

  case 48: /* TypeSpec: BasicTypeSpec  */
#line 439 "parser.y"
                                { (yyval.type) = (yyvsp[0].type); }
#line 1891 "y.tab.c"
    break;

  case 49: /* TypeSpec: PrevTypeSpec  */
#line 441 "parser.y"
                                { (yyval.type) = (yyvsp[0].type); }
#line 1897 "y.tab.c"
    break;

  case 50: /* TypeSpec: VarArrayHead TypeSpec  */
#line 443 "parser.y"
                                { (yyval.type) = itVarArrayDecl((yyvsp[-1].number), (yyvsp[0].type)); }
#line 1903 "y.tab.c"
    break;

  case 51: /* TypeSpec: ArrayHead TypeSpec  */
#line 445 "parser.y"
                                { (yyval.type) = itArrayDecl((yyvsp[-1].number), (yyvsp[0].type)); }
#line 1909 "y.tab.c"
    break;

  case 52: /* TypeSpec: syCaret TypeSpec  */
#line 447 "parser.y"
                                { (yyval.type) = itPtrDecl((yyvsp[0].type)); }
#line 1915 "y.tab.c"
    break;

  case 53: /* TypeSpec: StructHead TypeSpec  */
#line 449 "parser.y"
                                { (yyval.type) = itStructDecl((yyvsp[-1].number), (yyvsp[0].type)); }
#line 1921 "y.tab.c"
    break;

  case 54: /* TypeSpec: CStringSpec  */
#line 451 "parser.y"
                                { (yyval.type) = (yyvsp[0].type); }
#line 1927 "y.tab.c"
    break;

  case 55: /* BasicTypeSpec: IPCType  */
#line 455 "parser.y"
{
    (yyval.type) = itShortDecl((yyvsp[0].symtype).innumber, (yyvsp[0].symtype).instr,
		     (yyvsp[0].symtype).outnumber, (yyvsp[0].symtype).outstr,
		     (yyvsp[0].symtype).size);
}
#line 1937 "y.tab.c"
    break;

  case 56: /* BasicTypeSpec: syLParen IPCType syComma IntExp IPCFlags syRParen  */
#line 462 "parser.y"
{
    (yyval.type) = itLongDecl((yyvsp[-4].symtype).innumber, (yyvsp[-4].symtype).instr,
		    (yyvsp[-4].symtype).outnumber, (yyvsp[-4].symtype).outstr,
		    (yyvsp[-4].symtype).size, (yyvsp[-2].number), (yyvsp[-1].flag));
}
#line 1947 "y.tab.c"
    break;

  case 57: /* IPCFlags: %empty  */
#line 470 "parser.y"
                                { (yyval.flag) = flNone; }
#line 1953 "y.tab.c"
    break;

  case 58: /* IPCFlags: IPCFlags syComma syIPCFlag  */
#line 472 "parser.y"
{
    if ((yyvsp[-2].flag) & (yyvsp[0].flag))
	warn("redundant IPC flag ignored");
    else
	(yyval.flag) = (yyvsp[-2].flag) | (yyvsp[0].flag);
}
#line 1964 "y.tab.c"
    break;

  case 59: /* IPCFlags: IPCFlags syComma syIPCFlag syLBrack syRBrack  */
#line 479 "parser.y"
{
    if ((yyvsp[-2].flag) != flDealloc)
	warn("only Dealloc is variable");
    else
	(yyval.flag) = (yyvsp[-4].flag) | flMaybeDealloc;
}
#line 1975 "y.tab.c"
    break;

  case 60: /* PrimIPCType: syNumber  */
#line 488 "parser.y"
{
    (yyval.symtype).innumber = (yyval.symtype).outnumber = (yyvsp[0].number);
    (yyval.symtype).instr = (yyval.symtype).outstr = strNULL;
    (yyval.symtype).size = 0;
}
#line 1985 "y.tab.c"
    break;

  case 61: /* PrimIPCType: sySymbolicType  */
#line 494 "parser.y"
                                { (yyval.symtype) = (yyvsp[0].symtype); }
#line 1991 "y.tab.c"
    break;

  case 62: /* IPCType: PrimIPCType  */
#line 498 "parser.y"
                                { (yyval.symtype) = (yyvsp[0].symtype); }
#line 1997 "y.tab.c"
    break;

  case 63: /* IPCType: PrimIPCType syBar PrimIPCType  */
#line 500 "parser.y"
{
    if ((yyvsp[-2].symtype).size != (yyvsp[0].symtype).size)
    {
	if ((yyvsp[-2].symtype).size == 0)
	    (yyval.symtype).size = (yyvsp[0].symtype).size;
	else if ((yyvsp[0].symtype).size == 0)
	    (yyval.symtype).size = (yyvsp[-2].symtype).size;
	else
	{
	    error("sizes in IPCTypes (%d, %d) aren't equal",
		  (yyvsp[-2].symtype).size, (yyvsp[0].symtype).size);
	    (yyval.symtype).size = 0;
	}
    }
    else
	(yyval.symtype).size = (yyvsp[-2].symtype).size;
    (yyval.symtype).innumber = (yyvsp[-2].symtype).innumber;
    (yyval.symtype).instr = (yyvsp[-2].symtype).instr;
    (yyval.symtype).outnumber = (yyvsp[0].symtype).outnumber;
    (yyval.symtype).outstr = (yyvsp[0].symtype).outstr;
}
#line 2023 "y.tab.c"
    break;

  case 64: /* PrevTypeSpec: syIdentifier  */
#line 524 "parser.y"
                                { (yyval.type) = itPrevDecl((yyvsp[0].identifier)); }
#line 2029 "y.tab.c"
    break;

  case 65: /* VarArrayHead: syArray syLBrack syRBrack syOf  */
#line 528 "parser.y"
                                { (yyval.number) = 0; }
#line 2035 "y.tab.c"
    break;

  case 66: /* VarArrayHead: syArray syLBrack syStar syRBrack syOf  */
#line 530 "parser.y"
                                { (yyval.number) = 0; }
#line 2041 "y.tab.c"
    break;

  case 67: /* VarArrayHead: syArray syLBrack syStar syColon IntExp syRBrack syOf  */
#line 533 "parser.y"
                                { (yyval.number) = (yyvsp[-2].number); }
#line 2047 "y.tab.c"
    break;

  case 68: /* ArrayHead: syArray syLBrack IntExp syRBrack syOf  */
#line 537 "parser.y"
                                { (yyval.number) = (yyvsp[-2].number); }
#line 2053 "y.tab.c"
    break;

  case 69: /* StructHead: syStruct syLBrack IntExp syRBrack syOf  */
#line 541 "parser.y"
                                { (yyval.number) = (yyvsp[-2].number); }
#line 2059 "y.tab.c"
    break;

  case 70: /* CStringSpec: syCString syLBrack IntExp syRBrack  */
#line 545 "parser.y"
                                { (yyval.type) = itCStringDecl((yyvsp[-1].number), FALSE); }
#line 2065 "y.tab.c"
    break;

  case 71: /* CStringSpec: syCString syLBrack syStar syColon IntExp syRBrack  */
#line 548 "parser.y"
                                { (yyval.type) = itCStringDecl((yyvsp[-1].number), TRUE); }
#line 2071 "y.tab.c"
    break;

  case 72: /* IntExp: IntExp syPlus IntExp  */
#line 552 "parser.y"
                                { (yyval.number) = (yyvsp[-2].number) + (yyvsp[0].number);	}
#line 2077 "y.tab.c"
    break;

  case 73: /* IntExp: IntExp syMinus IntExp  */
#line 554 "parser.y"
                                { (yyval.number) = (yyvsp[-2].number) - (yyvsp[0].number);	}
#line 2083 "y.tab.c"
    break;

  case 74: /* IntExp: IntExp syStar IntExp  */
#line 556 "parser.y"
                                { (yyval.number) = (yyvsp[-2].number) * (yyvsp[0].number);	}
#line 2089 "y.tab.c"
    break;

  case 75: /* IntExp: IntExp syDiv IntExp  */
#line 558 "parser.y"
                                { (yyval.number) = (yyvsp[-2].number) / (yyvsp[0].number);	}
#line 2095 "y.tab.c"
    break;

  case 76: /* IntExp: syNumber  */
#line 560 "parser.y"
                                { (yyval.number) = (yyvsp[0].number);	}
#line 2101 "y.tab.c"
    break;

  case 77: /* IntExp: syLParen IntExp syRParen  */
#line 562 "parser.y"
                                { (yyval.number) = (yyvsp[-1].number);	}
#line 2107 "y.tab.c"
    break;

  case 78: /* RoutineDecl: Routine  */
#line 566 "parser.y"
                                                        { (yyval.routine) = (yyvsp[0].routine); }
#line 2113 "y.tab.c"
    break;

  case 79: /* RoutineDecl: SimpleRoutine  */
#line 567 "parser.y"
                                                        { (yyval.routine) = (yyvsp[0].routine); }
#line 2119 "y.tab.c"
    break;

  case 80: /* RoutineDecl: Procedure  */
#line 568 "parser.y"
                                                        { (yyval.routine) = (yyvsp[0].routine); }
#line 2125 "y.tab.c"
    break;

  case 81: /* RoutineDecl: SimpleProcedure  */
#line 569 "parser.y"
                                                        { (yyval.routine) = (yyvsp[0].routine); }
#line 2131 "y.tab.c"
    break;

  case 82: /* RoutineDecl: Function  */
#line 570 "parser.y"
                                                        { (yyval.routine) = (yyvsp[0].routine); }
#line 2137 "y.tab.c"
    break;

  case 83: /* Routine: syRoutine syIdentifier Arguments  */
#line 574 "parser.y"
                                { (yyval.routine) = rtMakeRoutine((yyvsp[-1].identifier), (yyvsp[0].argument)); }
#line 2143 "y.tab.c"
    break;

  case 84: /* SimpleRoutine: sySimpleRoutine syIdentifier Arguments  */
#line 578 "parser.y"
                                { (yyval.routine) = rtMakeSimpleRoutine((yyvsp[-1].identifier), (yyvsp[0].argument)); }
#line 2149 "y.tab.c"
    break;

  case 85: /* Procedure: syProcedure syIdentifier Arguments  */
#line 582 "parser.y"
                                { (yyval.routine) = rtMakeProcedure((yyvsp[-1].identifier), (yyvsp[0].argument)); }
#line 2155 "y.tab.c"
    break;

  case 86: /* SimpleProcedure: sySimpleProcedure syIdentifier Arguments  */
#line 586 "parser.y"
                                { (yyval.routine) = rtMakeSimpleProcedure((yyvsp[-1].identifier), (yyvsp[0].argument)); }
#line 2161 "y.tab.c"
    break;

  case 87: /* Function: syFunction syIdentifier Arguments ArgumentType  */
#line 590 "parser.y"
                                { (yyval.routine) = rtMakeFunction((yyvsp[-2].identifier), (yyvsp[-1].argument), (yyvsp[0].type)); }
#line 2167 "y.tab.c"
    break;

  case 88: /* Arguments: syLParen syRParen  */
#line 594 "parser.y"
                                { (yyval.argument) = argNULL; }
#line 2173 "y.tab.c"
    break;

  case 89: /* Arguments: syLParen ArgumentList syRParen  */
#line 596 "parser.y"
                                { (yyval.argument) = (yyvsp[-1].argument); }
#line 2179 "y.tab.c"
    break;

  case 90: /* ArgumentList: Argument  */
#line 601 "parser.y"
                                { (yyval.argument) = (yyvsp[0].argument); }
#line 2185 "y.tab.c"
    break;

  case 91: /* ArgumentList: Argument sySemi ArgumentList  */
#line 603 "parser.y"
{
    (yyval.argument) = (yyvsp[-2].argument);
    (yyval.argument)->argNext = (yyvsp[0].argument);
}
#line 2194 "y.tab.c"
    break;

  case 92: /* Argument: Direction syIdentifier ArgumentType IPCFlags  */
#line 610 "parser.y"
{
    (yyval.argument) = argAlloc();
    (yyval.argument)->argKind = (yyvsp[-3].direction);
    (yyval.argument)->argName = (yyvsp[-2].identifier);
    (yyval.argument)->argType = (yyvsp[-1].type);
    (yyval.argument)->argFlags = (yyvsp[0].flag);
}
#line 2206 "y.tab.c"
    break;

  case 93: /* Direction: %empty  */
#line 619 "parser.y"
                                                { (yyval.direction) = akNone; }
#line 2212 "y.tab.c"
    break;

  case 94: /* Direction: syIn  */
#line 620 "parser.y"
                                                { (yyval.direction) = akIn; }
#line 2218 "y.tab.c"
    break;

  case 95: /* Direction: syOut  */
#line 621 "parser.y"
                                                { (yyval.direction) = akOut; }
#line 2224 "y.tab.c"
    break;

  case 96: /* Direction: syInOut  */
#line 622 "parser.y"
                                                { (yyval.direction) = akInOut; }
#line 2230 "y.tab.c"
    break;

  case 97: /* Direction: syRequestPort  */
#line 623 "parser.y"
                                                { (yyval.direction) = akRequestPort; }
#line 2236 "y.tab.c"
    break;

  case 98: /* Direction: syReplyPort  */
#line 624 "parser.y"
                                                { (yyval.direction) = akReplyPort; }
#line 2242 "y.tab.c"
    break;

  case 99: /* Direction: sySReplyPort  */
#line 625 "parser.y"
                                                { (yyval.direction) = akSReplyPort; }
#line 2248 "y.tab.c"
    break;

  case 100: /* Direction: syUReplyPort  */
#line 626 "parser.y"
                                                { (yyval.direction) = akUReplyPort; }
#line 2254 "y.tab.c"
    break;

  case 101: /* Direction: syWaitTime  */
#line 627 "parser.y"
                                                { (yyval.direction) = akWaitTime; }
#line 2260 "y.tab.c"
    break;

  case 102: /* Direction: syMsgOption  */
#line 628 "parser.y"
                                                { (yyval.direction) = akMsgOption; }
#line 2266 "y.tab.c"
    break;

  case 103: /* Direction: syMsgSeqno  */
#line 629 "parser.y"
                                                { (yyval.direction) = akMsgSeqno; }
#line 2272 "y.tab.c"
    break;

  case 104: /* ArgumentType: syColon syIdentifier  */
#line 633 "parser.y"
{
    (yyval.type) = itLookUp((yyvsp[0].identifier));
    if ((yyval.type) == itNULL)
	error("type '%s' not defined", (yyvsp[0].identifier));
}
#line 2282 "y.tab.c"
    break;

  case 105: /* ArgumentType: syColon NamedTypeSpec  */
#line 639 "parser.y"
                                { (yyval.type) = (yyvsp[0].type); }
#line 2288 "y.tab.c"
    break;

  case 106: /* LookString: %empty  */
#line 643 "parser.y"
                                { LookString(); }
#line 2294 "y.tab.c"
    break;

  case 107: /* LookFileName: %empty  */
#line 647 "parser.y"
                                { LookFileName(); }
#line 2300 "y.tab.c"
    break;

  case 108: /* LookQString: %empty  */
#line 651 "parser.y"
                                { LookQString(); }
#line 2306 "y.tab.c"
    break;


#line 2310 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 654 "parser.y"


static const char *
import_name(statement_kind_t sk)
{
    switch (sk)
    {
      case skImport:
	return "Import";
      case skSImport:
	return "SImport";
      case skUImport:
	return "UImport";
      default:
	fatal("import_name(%d): not import statement", (int) sk);
	/*NOTREACHED*/
    }
}
