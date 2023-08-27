//Declarations
int x=0;
int arr[100];
int y = -112;

//function declaration
int *func(int, int*);

//function
int *func(int a, int* b)int x;{
    int i;
    for(i=a; i>0; i=i-1)
        printf("*");
    return a+b/x;
}

int main()
{
    // TEST FOR COMMENTS
    /*
        MULTI LINE TEST
    */

   void* _a_b_c;
   int line;
   int a = 1;
   _a_b_c = &a;

   int* ptr = &a;
   line = *ptr;

    char _a_b_c_2 = '\0';

    int apple[4];
    apple[0] = 1;
    apple[1] = 5;
    apple[2] = 3;
    apple[3] = 4;

    char* _a_b_c = "_a_b_c here ";
    func(5,apple);   
    char t = 'h';

    if (t != 'h')
    {
        printf("False\n");
    }
    else
    {
        printf("True\n");
    } 

    //character constants
    char _a_5 = '@';
    char _a_6 = '\?', _a_7 = '\n', _a_8 = '\v', _a_9 = 'Q';

    // string literals
    char *s1 = "Testing string literal s1. //This is not a comment.\n";
    char *s2 = "Testing string literal s2. /* This is not a comment. */";
    char s3[] = ""; /* Empty string check */

    //conditional operator
    int flag = 1;
    (flag != 1) ? printf("flag is not 1\n") : printf("flag is 1\n");
   return 0;
}