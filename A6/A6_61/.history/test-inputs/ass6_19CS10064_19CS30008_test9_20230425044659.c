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
    int n;
    int flag;
    printStr("Input array size:\n");
    n = readInt(&n);
    int arr[20];
    printStr("Enter array elements:\n");
    int i;
    for(i = 0;i < n;i = i + 1)
    {
        arr[i] = readInt(&flag);
    }

    printStr("Input array :\n");
    for(i = 0;i < n;i = i + 1)
    {
        printInt(arr[i]);
        printStr(" ");
    }
    printStr("\n");

    int j;
    for(i = 0;i < n - 1;i = i + 1)
    {
        for(j = 0;j < n - i - 1;j = j + 1)
        {
            if(arr[j] > arr[j + 1])
                swap(&arr[j + 1],&arr[j]);
        }
    }

    printStr("Input array :\n");
    for(i = 0;i < n;i = i + 1)
    {
        printInt(arr[i]);
        printStr(" ");
    }
    printStr("\n");
}