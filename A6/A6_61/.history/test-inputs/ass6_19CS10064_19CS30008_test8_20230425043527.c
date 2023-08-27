int printStr (char *ch);
int printInt (int n);
int readInt (int *eP);

int f_odd(int n);
int f_even(int n);

int fibonnaci(int n)
{
    if(n%2 == 0) return f_even(n);
    else return f_odd(n);
}

int f_odd(int n)
{
    if(n == 1) return 1;
    return f_even(n - 1) + f_odd(n - 2);
}

int f_even(int n)
{
    if(n == 0) return 0;
    return f_even(n - 2) + f_odd(n - 1);
}

int main()
{
    int n;
    printStr("Enter an integer:\n");
    n = readInt(&n);
    int r;
    r = fibonacci(n);
    printStr("fibo(");
    printInt(n)
}