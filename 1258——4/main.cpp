#include <iostream>
using namespace std;
//归并
long sum = 0;
void merge(int a[],int left,int mid,int right){
    int *tmp=new int[right-left+1];
    int i=left,j=mid,k=0;

    while(i<mid && j<=right){
        if(a[i]<=a[j]) tmp[k++]=a[i++];
        else{
            sum+=(mid-i);
            tmp[k++]=a[j++];
        }
    }
    while(i<mid) tmp[k++]=a[i++];
    while(j<=right) tmp[k++]=a[j++];

    for(i=0,k=left;k<=right;) a[k++]=tmp[i++];

    delete []tmp;
}
void mergeSort(int a[],int left,int right){
    int mid = (left+right)/2;

    if(left==right) return;
    mergeSort(a,left,mid);
    mergeSort(a,mid+1,right);
    merge(a,left,mid+1,right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    int a[n];
    for(int i = 0;i<n;i++) cin>>a[i];
    mergeSort(a,0,n-1);
    cout<<sum;
    return 0;
}