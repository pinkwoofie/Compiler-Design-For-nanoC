// Include predefined functions 
int printStr (char *ch);
int printInt (int n);
int readInt (int *eP);

void swap(int* p,int* q)
{
    int t;
    t = *p;
    *p = *q;
    *q = t;
    return;
}

int main()
{
    int x;
    int y;
    printStr("Enter x:\n");
    x = readInt(&x);
    printStr("Enter y:\n");
    y = readInt(&y);
}