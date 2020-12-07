#include <iostream>
using namespace std;

void merge(long a[],long left,long mid,long right){
    long *tmp=new long[right-left+1];

    long i=left,j=mid,k=0;
    while(i<mid && j<=right)
        if(a[i]<a[j]) tmp[k++]=a[i++];
        else tmp[k++] = a[j++];

    while(i<mid) tmp[k++] = a[i++];
    while(j<=right) tmp[k++] = a[j++];

    for(i=0,k=left;k<=right;) a[k++]=tmp[i++];
    delete []tmp;
}

void mergeSort(long a[],long left,long right){
    long mid = (left+right)/2;

    if(left==right) return;
    mergeSort(a,left,mid);
    mergeSort(a,mid+1,right);
    merge(a,left,mid+1,right);
}

long func(long a,long b,long c,int x){
    return (a*x*x+b*x+c);
}

int main() {
    int n,k;cin>>n>>k;
    int i;
    long A[n],B[n],C[n];

    for(i=0;i<n;i++)
        cin>>A[i]>>B[i]>>C[i];

    long *a=new long [n*k];
    int kk=0;

    for(i=0;i<n;i++){
        if(B[i]==0){
            for(int j=0;j<=k/2;j++)
                a[kk++]=func(A[i],B[i],C[i],j);
            for(int j =-1*(k/2);j<0;j++)
                a[kk++]=func(A[i],B[i],C[i],j);
        }
        else{
            int x= int( B[i]/(2*A[i]) *(-1));
            for(int j=0;j<=k/2;j++)
                a[kk++]=func(A[i],B[i],C[i],j+x);
            for(int j =-k/2;j<0;j++)
                a[kk++]=func(A[i],B[i],C[i],j+x);
        }
    }
    mergeSort(a,0,kk-1);
    for(int j=0;j<k;j++)
        cout<<a[j]<<' ';

    delete []a;
    return 0;
}