/*
    /*
    our test file 
     to   check
    lex specifications
    *************
*/
 
//count length of string/
void function1(char *x){
    int count = 0;
    char c = 'a';
    char d = '\t';
    int _noLines = 1;
    for(;;){
        if(x!=0 && x[count]==0)
            return ;
        else if (x[count]=='\n') _noLines=_noLines + 1;
        else count=count + 1;
    }
    printf("Total characters count: \'%d\'\n",count);
    printf("Total Number of Lines:\t %d \n", _noLines);
}

int main(void)
{
    //factorial code
    int _n = 980;
    int i3 = -99009;
    int r = 5 % 6 * 7 + 99 - 33;
    r = 1;
    int arr[5] = {1,2,3,4,5};
    //reading into _n
    readInt(&_n);
    for(i3 = 1;i3<_n;i3 = i3 + 1) 
        r = r*i3;
    printInt(_n);
    printStr("! = ");
    printInt(r);
    function1("\' \" \? \\ \a \b \f \n \r \t \v");
    function1("Hello world!\n");
    return 0;
}
