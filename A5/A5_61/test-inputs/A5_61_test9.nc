int printStr (char *ch);
int printInt (int n);
int readInt (int *eP);

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
    int temp;
    for(i = 0;i < n - 1;i = i + 1)
    {
        for(j = 0;j < n - i - 1;j = j + 1)
        {
            if(arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

    printStr("Sorted array :\n");
    for(i = 0;i < n;i = i + 1)
    {
        printInt(arr[i]);
        printStr(" ");
    }
    printStr("\n");
}