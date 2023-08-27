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
    int arr
}