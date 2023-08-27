int printInt(int num);
int printStr(char * c);
int readInt(int *eP);
// Swap two numbers
void swap(int *p, int *q) {
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
    printStr("Hello there\n")
    return 0;
}