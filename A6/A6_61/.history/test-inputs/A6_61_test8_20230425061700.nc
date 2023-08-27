int printStr (char *ch);
int printInt (int n);
int readInt (int *eP);


// Find fibonacci by co-recursion
int f_odd(int n);
int f_even(int n);

int fibonacci(int n) {
    return (n )
}
int f_odd(int n) {
    if(n==1) return 1;
    return f_even(n-1) + f_odd(n-2);
}
int f_even(int n) {
    if(n==0) return 0;
    return f_odd(n-1) + f_even(n-2);
}
int main() {
    int n;
    printStr("Enter an integer:\n");
    n = readInt(&n);
    int r;
    r = fibonacci(n);
    printStr("fibo(");
    printInt(n);
    printStr(") = ");
    printInt(r);
    printStr("\n");
    return 0;
}