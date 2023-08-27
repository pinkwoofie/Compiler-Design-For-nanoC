//Declarations
int x=0;
int *arr;


//declaration
int x=0;
int *arr[100];

//function declaration
int *func(int, int*);

//function
int *func(int a, int* b)int x;{
    int i;
    for(i=a; i>0; i=i - 1)
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
    func();   
    char t = 'h';

    if (t != 'h')
    {
        printf("False\n");
    }
    else
    {
        printf("True\n");
    } 
   return 0;
}