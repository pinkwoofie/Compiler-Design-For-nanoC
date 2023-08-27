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
    int n = 5; // Number of elements
    arr[0] = 2;
    arr[1] = 3;
    arr[2] = 4;
    arr[3] =10;
    arr[4] = 40;
    int x = 11; // Key to search
    int result = binarySearch(arr, 0, n - 1, x);
    if(result == -1) printStr("Element is not present in array\n");
    else
    {
        printStr("Element is present in array at index\n");
        printInt(result);
    }
    printStr("\n");
}