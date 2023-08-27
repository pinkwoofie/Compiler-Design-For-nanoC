int printInt(int num);
int printStr(char * c);
int readInt(int *eP);
int fun(int a,int b,int c);
// Find max of n numbers using array

int add(int a , int b)
{
    int c = a + b;
    return c;
}

int main() {
    int n;
    int a[10];
    int m;
    int i;
    char ch;
    ch = 'a';
    int *iptr = &m;
    n = readInt(&n);
    for(i = 0; i < n; i = i + 1) {
        m =readInt(&m);
        a[i] = m;
    }
    printStr("Done\n");
    m = a[0];
    for(i = 1; i < n; i = i + 1) {
        if (a[i] > m)
        m = a[i];
    }
    char ch1;
    ch1 = 'b';
    printStr("Max of: ");
    printInt(a[0]);
    for(i = 1; i < n; i = i + 1) {
        printStr(", "); printInt(a[i]);
    }
    printStr(": = ");
    printInt(m);
    return 0;
}