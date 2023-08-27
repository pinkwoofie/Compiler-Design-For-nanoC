int printStr (char *ch);
int printInt (int n);
int readInt (int *eP);

int main()
{
    int n;
    int a[10];
    int m;
    int i;
    printStr("Enter the number of elements whose maximum you would like to find:\n");
    n = readInt(&n);
    printStr("Enter the numbers separated by newline:\n");
    for(i = 0;i < n; i = i + 1)
    {
        m = readInt(&m);
        a[i] = m;
    }
    m = a[0];
    for(i = 1;i < n;i = i + 1)
    {
        if(a[i] > m)
            m = a[i];
    }
    printStr("Max of:");
    printInt(a[0]);
    for(i = 1;i < n;i = i + 1)
    {
        printStr(", ");printInt(a[i]);
    }
    printStr(": = ");
    printInt(m);
    printStr("\n");
    return 0;
}