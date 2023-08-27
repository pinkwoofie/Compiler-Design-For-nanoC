#include <stdio.h>
#include "y.tab.h"
int main(){
  	extern int yydebug;
	yydebug=0;
	int val=yyparse();
	printf("\n+---------------------------------------+\n\n");
	if(!val)
		printf("Successs :)\n\n");
	else
		printf("Error :(\n\n");
	sym
	return 0;
}