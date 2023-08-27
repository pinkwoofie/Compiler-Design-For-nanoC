int printInt(int num);
int printStr(char * c);
int readInt(int *eP);
// Find factorial by recursion
 int fibonacci(int n) {
 return n % 2 == 0? f_even(n): f_odd(n);
 }

 int main() {
    int n = 10;
    int r;
    r = fibonacci(n);
    printStr("fibo(");
    printInt(n);
    printStr(") = ");
    printInt(r);
    return 0;
 }