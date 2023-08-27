int printInt(int num);
int printStr(char * c);
int readInt(int *eP);
// Swap two numbers
void swap(int* p, int* q) {
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
    x = readInt(&x);
    y = readInt(&y);
    printInt(x);
    printStr("%");
    printInt(y);
    printStr(" = ");
    int z;
    z = x%y;
    printInt(z);
    printStr("\n");
    if(x > 12)
    {
        printStr("In if\n");
    }
    else
    {
        printStr("In else\n");
    }
    return 0;
}