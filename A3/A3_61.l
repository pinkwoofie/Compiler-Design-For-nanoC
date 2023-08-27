%{
    
    #define SLC 1
    #define MLC 2
    #define KEYWORD 3
    #define IDENTIFIER 4
    #define STRING_LITERAL 5
    #define PUNCTUATOR 6
    #define INTEGER_CONSTANT 7
    #define CHARACTER_CONSTANT 8
    #define WS 9
    #define ERROR -1
%}

%option yylineno

eseq	\\'|\\\"|\\\?|\\\\|\\a|\\b|\\f|\\n|\\r|\\t|\\v

str_literal \"([^"\\^\n]|{eseq})*\"

single_line_comment "//"[^\n]*
multi_line_comment "/*"([^*]|\*+[^*/])*\*+"/"
keyword (char|else|for|if|int|return|void)
identifier [_a-zA-Z][a-zA-Z0-9_]*
punctuator (\[|\]|\(|\)|\{|\}|->|&|\*|\+|\-|\/|\%|!|\?|<|>|<=|>=|==|!=|&&|\|\||=|:|;|,)
non_zero_integer ((\+|\-)?([1-9][0-9]*))
char_constant '([^'^\\^\n]|{eseq})'

%%
[ \t\n]+ { return WS;}
{single_line_comment} {return SLC;}
{multi_line_comment} {return MLC;}
{keyword} {return KEYWORD;}
{str_literal} {
    
    return STRING_LITERAL;
    }
{identifier} {return IDENTIFIER;}
{punctuator} {return PUNCTUATOR;}
0|{non_zero_integer}   {return INTEGER_CONSTANT;}
{char_constant} {return CHARACTER_CONSTANT;}

. {return ERROR;}

%%

