int printInt(int num);
int printStr(char * c);
int readInt(int *eP);
// Find factorial by recursion
 

 int main() {
    int n = 10;
    int r;
    r = (n == 10);
    printStr("fibo(");
    printInt(n);
    printStr(") = ");
    printInt(r);
    return 0;
 }