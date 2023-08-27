int printStr (char *ch);
int printInt (int n);
int readInt (int *eP);

int main()
{
    int n;
    int a[10];
    int m;
    int i;
    printStr("Enter the number of elements whose maximum you would like to find\n:");
    n = readInt(&n);
    for(i = 0;i < n; i = i + 1)
    {
        m = readInt(&m);
        a[i] = m;
    }
    m = a[0];
    for(i = 1;i < n;i = i + 1)
    {
        if(a[i] > m)
    }
}