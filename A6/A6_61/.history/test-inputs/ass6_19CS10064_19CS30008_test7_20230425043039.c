int printStr (char *ch);
int printInt (int n);
int readInt (int *eP);

int factorial(int n)
{
    if(n == 0)
        return 1;
    else 
        return n * factorial(n-1);
}

int main()
{
    int n;
    printStr("Enter an integer:\n");
    n = readInt(&n);
    int r;
    r = factorial(n)
}