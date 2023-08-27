#include <stdio.h>
#include "lex.yy.c"
extern char* yytext;
extern char* string;
extern int yylineno;

int main()
{
    int token, key = 0,id = 0,ic = 0,cc = 0,str = 0,punc = 0,slc = 0,mlc = 0;
    while(token = yylex())
    {
        switch(token)
        {
            case SLC:
                {
                    printf("<Single-line Comment , %s>\n", yytext);
                    slc++;
                    break;
                }
            case MLC:
                {
                    printf("<Multi-line Comment , %s>\n", yytext);
                    mlc++;
                    break;
                }
            case KEYWORD:
                {
                    printf("<keyword , %s>\n", yytext);
                    key++;
                    break;
                }
            case IDENTIFIER:
                {
                    printf("<identifier , %s>\n", yytext);
                    id++;
                    break;
                }
            case STRING_LITERAL:
                {
                    char* string = yytext+1;
                    int size =  strlen(string);;
                    string[size-1]='\0';
                    printf("<string-literal , %s>\n", string);
                    str++;
                    break;
                }
                
            case PUNCTUATOR:
                {
                    printf("<punctuator , %s>\n", yytext);
                    punc++;
                    break;
                }
            case INTEGER_CONSTANT:
                {
                    printf("<integer-constant , %s>\n", yytext);
                    ic++;
                    break;
                }
            case CHARACTER_CONSTANT:
                {
                    printf("<character-constant , %s>\n", yytext);
                    cc++;
                    break;
                }
            case WS:
                break;
            default:
                {
                    printf("Error on line no : %d, %d\n",yylineno, yytext[0]);
                    break;
                }  
        }
    }
    
}
