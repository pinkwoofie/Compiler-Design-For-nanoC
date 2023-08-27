/* C Declarations and Definitions */
%{  
    
    #include <stdio.h>
    #include "A5_61.h"
    #include "A5_61.h"
%}

%option yylineno
%option noyywrap

eseq	\\'|\\\"|\\\?|\\\\|\\a|\\b|\\f|\\n|\\r|\\t|\\v

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
{char} {return CHAR_;}
{else} {return ELSE;}
{for} {return FOR;}
{if} {return IF;}
{int} {return INT_;}
{return} {return RETURN_;}
{void} {return VOID_;}
{arrow} {return ARROW;}
{lte} {return LTE;}
{gte} {return GTE;}
{double_equals} {return DOUBLE_EQUALS;}
{not_equal} {return NOT_EQUAL;}
{logical_and} {return LOGICAL_AND;}
{logical_or} {return LOGICAL_OR;}

{identifier}    {
                    yylval.str = new string(yytext);
                    return IDENTIFIER;
                }

0|{non_zero_integer}    {
                            yylval.intval = atoi(yytext);
                            return INTEGER_CONSTANT;
                        }

{char_constant} {
                    yylval.charval = yytext[1];
                    return CHAR_CONSTANT;
                }

{str_literal}   {
                    yylval.str = new string(yytext);
                    return STRING_LITERAL;
                }
{punctuator} {return yytext[0];}
{single_line_comment} {}
{multi_line_comment} {}
[ \t\n]+ {}

. {printf("Parsing Error...: %s\n\n", yytext);}

%%
