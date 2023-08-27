// Testing various functionalities through merge sort

int printStr (char *ch);
int printInt (int n);
int readInt (int *eP);

int main()
{
    int n;
    int i = 0;
    int r = 1;
    printStr("Enter an integer:\n")
    readInt(&n);
    for(i = 1;i <= n;i = i + 1)
    {
        r = r*i;
    }
    printInt(n);
    printStr(" ! = ");
    printInt(r);
    return 0;
}