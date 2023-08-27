%{
#include <stdio.h>
extern int yylex();
void yyerror(const char*);
extern int yylineno;
%}

%union {
  int intval;
  char charval;
  char *strval;
}

%token ARROW
%token LTE
%token GTE
%token DOUBLE_EQUALS
%token NOT_EQUAL
%token LOGICAL_AND
%token LOGICAL_OR
%token CHAR
%token ELSE
%token FOR
%token IF
%token INT
%token RETURN
%token VOID
%token IDENTIFIER
%token <intval> INTEGER_CONSTANT
%token <charval> CHARACTER_CONSTANT
%token <strval> STRING_LITERAL

%start translation_unit

%%

primary_expression:
					IDENTIFIER {printf("Line No : %d) primary_expression -> identifier\n",yylineno);}
					|INTEGER_CONSTANT {printf("Line No : %d) primary_expression --> integer constant\n",yylineno);}
					|CHARACTER_CONSTANT {printf("Line No : %d) primary_expression --> character constant\n",yylineno);}
					|STRING_LITERAL {printf("Line No : %d) primary_expression --> string literal\n",yylineno);}
					|'(' expression ')'
					;

postfix_expression:
					primary_expression {printf("Line No : %d) postfix_expression --> primary_expression\n",yylineno);}
					|IDENTIFIER '[' expression ']' {printf("Line No : %d) postfix_expression --> identifier\n",yylineno);}
					|IDENTIFIER '(' argument_expression_list_optional ')' {printf("Line No : %d) postfix_expression --> identifier\n",yylineno);}
				  	|IDENTIFIER ARROW IDENTIFIER {printf("Line No : %d) postfix_expression --> identifier\n",yylineno);}
				  ;
// Only a single postfix op is allowed in an expression here

argument_expression_list_optional:
						  argument_expression_list
						  {printf("Line No : %d) argument_expression_list_opt --> argument_expression_list\n",yylineno);}
						  |
						  {printf("Line No : %d) argument_expression_list_opt --> epsilon\n",yylineno);}
						  ;

argument_expression_list:
					  assignment_expression 
					  {printf("Line No : %d) argument_expression_list --> argument_expression\n",yylineno);}
					  |argument_expression_list ',' assignment_expression
					  {printf("Line No : %d) argument_expression_list --> argument_expression_list ',' assignment_expression\n",yylineno);}
					  ;

unary_expression:
				postfix_expression {printf("Line No : %d) unary_expression --> postfix_expression\n",yylineno);}
				|unary_operator unary_expression 
				{printf("Line No : %d) unary_expression --> unary_operator unary_expression\n",yylineno);}
				;

unary_operator:
			  '&'
			  |'*'
			  |'+'
			  |'-'
			  |'!'
			  ;

multplicative_expression:
						unary_expression
						|multplicative_expression '*' unary_expression
						|multplicative_expression '/' unary_expression
						|multplicative_expression '%' unary_expression
						;

additive_expression:
				   multplicative_expression
				   |additive_expression '+' multplicative_expression
				   |additive_expression '-' multplicative_expression
				   ;

relational_expression:
					 additive_expression
					 |relational_expression '<' additive_expression
					 |relational_expression '>' additive_expression
					 |relational_expression LTE additive_expression
					 |relational_expression GTE additive_expression
					 ;

equality_expression:
				   relational_expression
				   |equality_expression DOUBLE_EQUALS relational_expression
				   |relational_expression NOT_EQUAL relational_expression
				   ;

logical_AND_expression:
					  equality_expression
					  |logical_AND_expression LOGICAL_AND equality_expression
					  ;

logical_OR_expression:
					 logical_AND_expression
					 |logical_OR_expression LOGICAL_OR logical_AND_expression
					 ;

conditional_expression:
					  logical_OR_expression
					  |logical_OR_expression '?' expression ':' conditional_expression
					  ;

assignment_expression:
					 conditional_expression
					 |unary_expression '=' assignment_expression
					 ;

expression:
		  assignment_expression
		  ;

//Remove	   
constant_expression:
				   conditional_expression
				   ;

expression_optional:
			  expression
			  |
			  ;



/* Declaration */

declaration:
			type_specifier init_declarator ';'
			;

init_declarator:
			   declarator
			   |declarator '=' initializer
			   ;

type_specifier:
			  VOID
			  |CHAR
			  |INT
			  ;

declarator:
		   pointer_optional direct_declarator
		  ;

direct_declarator:
				   IDENTIFIER
				   |IDENTIFIER '[' INTEGER_CONSTANT ']'
				   |IDENTIFIER '(' parameter_list_optional ')'
				   ;

pointer_optional:
		   '*'
		   |
		   ;

parameter_list_optional:
			parameter_list
			|
			;

parameter_list:
			parameter_declaration
			| parameter_list ',' parameter_declaration
			;

parameter_declaration:
			type_specifier pointer_optional identifier_optional
			;

initializer:
		   assignment_expression
		   ;


/* Statements */

statement:
		 compound_statement
		 |expression_statement
		 |selection_statement
		 |iteration_statement
		 |jump_statement
		 ;

compound_statement:
				  '{' block_item_list_optional '}'
				  ;

block_item_list:
			   block_item 
			   |block_item_list block_item
			   ;

block_item_list_optional:
				   block_item_list
				   |
				   ;

block_item:
		  declaration
		  |statement
		  ;

expression_statement:
					expression_optional ';'
					;

selection_statement:
				   IF '(' expression ')' statement
				   |IF '(' expression ')' statement ELSE statement
				   ;

iteration_statement:
				   FOR '(' expression_optional ';' expression_optional ';' expression_optional ')' statement 
				   ;
jump_statement:
			  RETURN expression_optional ';'
			  ;

/* Translation Unit */

translation_unit:
				external_declaration
				|translation_unit external_declaration
				;

external_declaration:
					function_definition
					|declaration
					;

function_definition:
				   type_specifier declarator  declaration_list_optional  compound_statement
				   ;

declaration_list:
				declaration
				|declaration_list declaration
				;

declaration_list_optional:
				declaration_list
				|
				;

identifier_optional:
			  IDENTIFIER
			  |
			  ;



%%

void yyerror(const char *s) {
    printf("Error occured : %s\n Line no : %d\n",s,yylineno);
}
