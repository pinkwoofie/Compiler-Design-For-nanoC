#include <stdio.h>
#include "y.tab.h"
int main(){
  // 	extern int yydebug;
	// yydebug=1;
	int val=yyparse();
	printf("\n+---------------------------------------+\n\n");
	if(!val)
		printf("Successs :)\n\n");
	else
		printf("Error :(\n\n");
	return 0;
}