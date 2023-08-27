int printInt(int num);
int printStr(char * c);
int readInt(int *eP);

int binarySearch(int arr[10], int l, int r, int x) {
    if (r >= l) {
        int mid;
        mid = l + (r - l) / 2;
        
        // If the element is present at the middle itself
        if (arr[mid] == x)
        return mid;
        // If element is smaller than mid, then it can only be present in left subarray
        if (arr[mid] > x)
        return binarySearch(arr, l, mid - 1, x);
        // Else the element can only be present in right subarray
        return binarySearch(arr, mid + 1, r, x);
    }
    // We reach here when element is not present in array
    return -1;
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

    int result = binary_search(arr,0,n-1,key);
    if(result == -1) printStr("Element is not present in array\n");
    else
    {
        printStr("Element is present in array at index\n");
        printInt(result);
    }
    printStr("\n");
}