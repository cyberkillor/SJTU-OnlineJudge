#include <iostream>
using namespace std;
//归并排序

int sum=0;

void Msort(int *arr,int L,int M,int R){
    int *t = new int[R-L+1];
    int i = L,j = M+1,k=0;
    while(i<=M && j<=R){
        if(arr[i]<=arr[j])
            t[k++] = arr[i++];
        else {
            t[k++] = arr[j++];
            sum++;
        }
    }

    if (i == M+1)
    {
        while (j <= R)
            t[k++] = arr[j++];
    }
    else
    {
        while (i <= M)
            t[k++] = arr[i++];
    }

    for (i=L,k=0; i<=R; i++,k++)
        arr[i] = t[k];

    delete []t;

}

void mysort(int *arr,int left,int right){
    if(left>=right) return;
    int mid = (left+right)/2;
    mysort(arr,left,mid);
    mysort(arr,mid+1,right);
    Msort(arr,left,mid,right);
}

int main() {
    int n;
    cin>>n;
    int *array = new int[n];
    for(int i = 0;i<n;i++) cin>>array[i];

    mysort(array,0,n-1);

    cout<<sum;
    return 0;
}