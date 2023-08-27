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

str_literal \"([^"\\^\n]|{eseq})*\"

single_line_comment "//"[^\n]*
multi_line_comment "/*"([^*]|\*+[^*/])*\*+"/"
char "char"
else "else"
for "for"
if "if"
int "int"
return "return"
void "void"
identifier [a-z_A-Z][a-z_A-Z0-9]*
arrow "->"
lte "<="
gte ">="
double_equals "=="
not_equal "!="
logical_and "&&"
logical_or "||"
punctuator (\[|\]|\(|\)|\{|\}|&|\*|\+|\-|\/|\%|!|\?|<|>|=|:|;|,)
non_zero_integer (([1-9][0-9]*))
char_constant '([^'^\\^\n]|{eseq})'
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
{CHAR_CONSTANT}                 { yylval.charval = yytext[1]; return CHAR_CONSTANT; }
{STRING_LITERAL}                { yylval.str = new string(yytext); return STRING_LITERAL; }
{WS}                            { /* ignore whitespaces */ }

%%


********************************************************************************


str_literal \"([^"\\^\n]|{eseq})*\"

single_line_comment "//"[^\n]*
multi_line_comment "/*"([^*]|\*+[^*/])*\*+"/"
char "char"
else "else"
for "for"
if "if"
int "int"
return "return"
void "void"
identifier [a-z_A-Z][a-z_A-Z0-9]*
arrow "->"
lte "<="
gte ">="
double_equals "=="
not_equal "!="
logical_and "&&"
logical_or "||"
punctuator (\[|\]|\(|\)|\{|\}|&|\*|\+|\-|\/|\%|!|\?|<|>|=|:|;|,)
non_zero_integer (([1-9][0-9]*))
char_constant '([^'^\\^\n]|{eseq})'

%%
{char} {return CHAR;}
{else} {return ELSE;}
{for} {return FOR;}
{if} {return IF;}
{int} {return INT;}
{return} {return RETURN;}
{void} {return VOID;}
{arrow} {return ARROW;}
{lte} {return LTE;}
{gte} {return GTE;}
{double_equals} {return DOUBLE_EQUALS;}
{not_equal} {return NOT_EQUAL;}
{logical_and} {return LOGICAL_AND;}
{logical_or} {return LOGICAL_OR;}

{identifier}    {
                    yylval.symp = ST->lookup(yytext);
                    return IDENTIFIER;
                }

0|{non_zero_integer}    {
                            yylval.intval = atoi(yytext);
                            return INTEGER_CONSTANT;
                        }

{char_constant} {
                    yylval.char_value = yytext;
                    return CHARACTER_CONSTANT;
                }

{str_literal}   {
                    yylval.char_value = yytext;
                    return STRING_LITERAL;
                }
{punctuator} {return yytext[0];}
{single_line_comment} {}
{multi_line_comment} {}
[ \t\n]+ {}

. {printf("Parsing Error...: %s\n\n", yytext);}

%%