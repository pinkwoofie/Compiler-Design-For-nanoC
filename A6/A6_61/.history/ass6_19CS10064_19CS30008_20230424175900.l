/* C Declarations and Definitions */
%{  
    /**
    * Vanshita Garg | 19CS10064
    * Ashutosh Kumar Singh | 19CS30008
    * Compilers Laboratory
    * Assignment 6
    *
    * Lexer for tinyC using Flex
    */
    #include <stdio.h>
    #include "ass6_19CS10064_19CS30008_translator.h"
    #include "ass6_19CS10064_19CS30008.tab.h"
%}

%option yylineno
%option noyywrap

%x SINGLE_LINE_COMMENT
%x MULTI_LINE_COMMENT

/* Regular Expression Definitions */

IDENTIFIER                      [_a-zA-Z][_a-zA-Z0-9]*

INTEGER_CONSTANT                [1-9][0-9]*|[0]

DIGIT_SEQUENCE                  [0-9]+
EXPONENT_PART                   [eE]([+-]?){DIGIT_SEQUENCE}
FRACTIONAL_CONSTANT             ({DIGIT_SEQUENCE}?\.{DIGIT_SEQUENCE})|({DIGIT_SEQUENCE}\.)
FLOATING_CONSTANT               ({FRACTIONAL_CONSTANT}{EXPONENT_PART}?)|({DIGIT_SEQUENCE}{EXPONENT_PART})

ENUM_CONSTANT                   {IDENTIFIER}

ESCAPE_SEQUENCE                 \\['"?\\abfnrtv]
C_CHAR                          [^\'\\\n]|{ESCAPE_SEQUENCE}
C_CHAR_SEQUENCE                 {C_CHAR}+
CHAR_CONSTANT                   \'({C_CHAR_SEQUENCE})\'

CONSTANT                        {INTEGER_CONSTANT}|{FLOATING_CONSTANT}|{ENUM_CONSTANT}|{CHAR_CONSTANT}

S_CHAR                          [^\"\\\n]|{ESCAPE_SEQUENCE}
S_CHAR_SEQUENCE                 {S_CHAR}+
STRING_LITERAL                  \"({S_CHAR_SEQUENCE}?)\"

WS                              [ \t\n]

/* Definitions of Rules and Actions */
%%

"//"                            { BEGIN(SINGLE_LINE_COMMENT); }
<SINGLE_LINE_COMMENT>.          { /* eat up the comment */ }
<SINGLE_LINE_COMMENT>\n         { BEGIN(INITIAL); }
<SINGLE_LINE_COMMENT><<EOF>>    { BEGIN(INITIAL); }

"/*"                            { BEGIN(MULTI_LINE_COMMENT); }
<MULTI_LINE_COMMENT>"*/"        { BEGIN(INITIAL); }
<MULTI_LINE_COMMENT>.           { /* eat up the comment */ }
<MULTI_LINE_COMMENT>\n          { /* eat up the comment */ }

"char"                          { return CHAR_; }
"else"                          { return ELSE; }
"for"                           { return FOR; }
"if"                            { return IF; }
"int"                           { return INT_; }
"return"                        { return RETURN_;}
"void"                          { return VOID_; }

"["                             { return SQUARE_BRACE_OPEN; }
"]"                             { return SQUARE_BRACE_CLOSE; }
"("                             { return PARENTHESIS_OPEN; }
")"                             { return PARENTHESIS_CLOSE; }
"{"                             { return CURLY_BRACE_OPEN; }
"}"                             { return CURLY_BRACE_CLOSE; }
"&"                             { return BITWISE_AND; }
"*"                             { return MULTIPLY; }
"+"                             { return ADD_; }
"-"                             { return SUBTRACT; }
"!"                             { return NOT; }
"/"                             { return DIVIDE; }
"%"                             { return MODULO; }
"<"                             { return LESS_THAN; }
">"                             { return GREATER_THAN; }
"<="                            { return LESS_THAN_EQUAL; }
">="                            { return GREATER_THAN_EQUAL; }
"=="                            { return EQUAL; }
"!="                            { return NOT_EQUAL; }
"&&"                            { return LOGICAL_AND; }
"||"                            { return LOGICAL_OR; }
"?"                             { return QUESTION_MARK; }
":"                             { return COLON; }
";"                             { return SEMICOLON; }
"="                             { return ASSIGN_; }
","                             { return COMMA; }

{IDENTIFIER}                    { yylval.str = new string(yytext); return IDENTIFIER; }
{INTEGER_CONSTANT}              { yylval.intval = atoi(yytext); return INTEGER_CONSTANT; }
{FLOATING_CONSTANT}             { yylval.floatval = atof(yytext); return FLOATING_CONSTANT; }
{CHAR_CONSTANT}                 { yylval.charval = yytext[1]; return CHAR_CONSTANT; }
{STRING_LITERAL}                { yylval.str = new string(yytext); return STRING_LITERAL; }
{WS}                            { /* ignore whitespaces */ }

%%
