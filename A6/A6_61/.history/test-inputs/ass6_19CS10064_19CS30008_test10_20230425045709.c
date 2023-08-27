int printInt(int num);
int printStr(char * c);
int readInt(int *eP);

int binarySearch(int arr[10],int l,int r,int x)
{
    if(r >= l)
    {
        int mid;
        mid = l + (r - l)/2;
        if(arr[mid] == x) 
            return mid;
        if(arr[mid] > x)
            return binarySearch(arr,l,mid - 1,x);
        return binarySearch(arr,mid + 1,r,x);
    }
}

int main()
{
    int arr[10];
    int n;
    int flag;
    int key;
    printStr("Input array size(max 10):\n");
    n = readInt(&n);
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
    printStr("Enter key to be searched:\n");
    key = readInt(&flag);
    
}