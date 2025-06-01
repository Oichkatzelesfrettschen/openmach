/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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
#line 139 "../../mig/parser.y"

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

#line 219 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
