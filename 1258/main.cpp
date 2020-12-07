#include <iostream>
using namespace std;

int main() {
    int sum=0,n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++) cin>>a[i];
    int j;
    for(int i=0;i<n-1;i++){
        for(j=i+1;j<n;j++){
            if(a[j]<a[i]) sum++;
        }
    }
    cout<<sum;
    return 0;
}