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
			  '&' {printf("Line No : %d) unary_operator --> &\n",yylineno);}
			  |'*' {printf("Line No : %d) unary_operator --> *\n",yylineno);}
			  |'+' {printf("Line No : %d) unary_operator --> +\n",yylineno);}
			  |'-' {printf("Line No : %d) unary_operator --> -\n",yylineno);}
			  |'!' {printf("Line No : %d) unary_operator --> !\n",yylineno);}
			  ;

multplicative_expression:
						unary_expression 
						{printf("Line No : %d) multiplicative_expression --> unary_expression\n",yylineno);}
						|multplicative_expression '*' unary_expression
						{printf("Line No : %d) multiplicative_expression --> multplicative_expression '*' unary_expression\n",yylineno);}
						|multplicative_expression '/' unary_expression
						{printf("Line No : %d) multiplicative_expression --> multplicative_expression '/' unary_expression\n",yylineno);}
						|multplicative_expression '%' unary_expression
						{printf("Line No : %d) multiplicative_expression --> multplicative_expression '%%' unary_expression\n",yylineno);}
						;

additive_expression:
				   multplicative_expression
				   {printf("Line No : %d) additive_expression --> multiplicative_expression\n",yylineno);}
				   |additive_expression '+' multplicative_expression
				   {printf("Line No : %d) additive_expression --> additive_expression '+' multplicative_expression\n",yylineno);}
				   |additive_expression '-' multplicative_expression
				   {printf("Line No : %d) additive_expression --> additive_expression '-' multplicative_expression\n",yylineno);}
				   ;

relational_expression:
					 additive_expression
					 {printf("Line No : %d) relational_expression --> additive_expression\n",yylineno);}
					 |relational_expression '<' additive_expression
					 {printf("Line No : %d) relational_expression --> relational_expression '<' additive_expression\n",yylineno);}
					 |relational_expression '>' additive_expression
					 {printf("Line No : %d) relational_expression --> relational_expression '>' additive_expression\n",yylineno);}
					 |relational_expression LTE additive_expression
					 {printf("Line No : %d) relational_expression --> relational_expression LTE additive_expression\n",yylineno);}
					 |relational_expression GTE additive_expression
					 {printf("Line No : %d) relational_expression --> relational_expression GTE additive_expression\n",yylineno);}
					 ;

equality_expression:
				   relational_expression
				   {printf("Line No : %d) equality_expression --> relational_expression\n",yylineno);}
				   |equality_expression DOUBLE_EQUALS relational_expression
				   {printf("Line No : %d) equality_expression --> equality_expression DOUBLE_EQUALS relational_expression\n",yylineno);}
				   |relational_expression NOT_EQUAL relational_expression
				   {printf("Line No : %d) equality_expression --> relational_expression NOT_EQUAL relational_expression\n",yylineno);}
				   ;

logical_AND_expression:
					  equality_expression
					  {printf("Line No : %d) logical_AND_expression --> equality_expression\n",yylineno);}
					  |logical_AND_expression LOGICAL_AND equality_expression
					  {printf("Line No : %d) logical_AND_expression --> logical_AND_expression LOGICAL_AND equality_expression\n",yylineno);}
					  ;

logical_OR_expression:
					 logical_AND_expression
					 {printf("Line No : %d) logical_OR_expression --> logical_AND_expression\n",yylineno);}
					 |logical_OR_expression LOGICAL_OR logical_AND_expression
					 {printf("Line No : %d) logical_OR_expression --> logical_OR_expression LOGICAL_OR logical_AND_expression\n",yylineno);}
					 ;

conditional_expression:
					  logical_OR_expression
					  {printf("Line No : %d) conditional_expression --> logical_OR_expression\n",yylineno);}
					  |logical_OR_expression '?' expression ':' conditional_expression
					  {printf("Line No : %d) conditional_expression --> logical_OR_expression '?' expression ':' conditional_expression\n",yylineno);}
					  ;

assignment_expression:
					 conditional_expression
					 {printf("Line No : %d) assignment_expression --> conditional_expression\n",yylineno);}
					 |unary_expression '=' assignment_expression
					 {printf("Line No : %d) assignment_expression --> unary_expression '=' assignment_expression\n",yylineno);}
					 ;

expression:
		  assignment_expression
			{printf("Line No : %d) expression --> assignment_expression\n",yylineno);}
		  ;

//Remove	   
constant_expression:
				   conditional_expression
				   {printf("Line No : %d) constant_expression --> conditional_expression\n",yylineno);}
				   ;

expression_optional:
			  expression
			  {printf("Line No : %d) expression_optional --> expression\n",yylineno);}
			  |
			  {printf("Line No : %d) expression_optional --> epsilon\n",yylineno);}
			  ;



/* Declaration */

declaration:
			type_specifier init_declarator ';'
			  {printf("Line No : %d) declaration --> type_specifier init_declarator ';'\n",yylineno);}

			;

init_declarator:
			   declarator
			   {printf("Line No : %d) init_declarator --> declarator\n",yylineno);}
			   |declarator '=' initializer
			   {printf("Line No : %d) init_declarator --> declarator '=' initializer\n",yylineno);}
			   ;

type_specifier:
			  VOID {printf("Line No : %d) type_specifier --> VOID\n",yylineno);}
			  |CHAR {printf("Line No : %d) type_specifier --> CHAR\n",yylineno);}
			  |INT {printf("Line No : %d) type_specifier --> INT\n",yylineno);}
			  ;

declarator:
		   pointer_optional direct_declarator
		   {printf("Line No : %d) declarator --> pointer_optional direct_declarator\n",yylineno);}
		  ;

direct_declarator:
				   IDENTIFIER
				   {printf("Line No : %d) direct_declarator --> IDENTIFIER\n",yylineno);}
				   |IDENTIFIER '[' INTEGER_CONSTANT ']'
				   {printf("Line No : %d) direct_declarator --> IDENTIFIER '[' INTEGER_CONSTANT ']'\n",yylineno);}
				   |IDENTIFIER '(' parameter_list_optional ')'
				   {printf("Line No : %d) direct_declarator --> IDENTIFIER '(' parameter_list_optional ')'\n",yylineno);}
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
		 compound_statement {printf("Line No : %d) statement --> compound_statement\n",yylineno);}
		 |expression_statement {printf("Line No : %d) statement --> expression_statement\n",yylineno);}
		 |selection_statement {printf("Line No : %d) statement --> selection_statement\n",yylineno);}
		 |iteration_statement {printf("Line No : %d) statement --> iteration_statement\n",yylineno);}
		 |jump_statement {printf("Line No : %d) statement --> jump_statement\n",yylineno);}
		 ;

compound_statement:
				  '{' block_item_list_optional '}'
				  {printf("Line No : %d) compound_statement --> '{' block_item_list_optional '}'\n",yylineno);}
				  ;

block_item_list:
			   block_item 
			   {printf("Line No : %d) block_item_list --> block_item\n",yylineno);}
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
