#include <iostream>
using namespace std;

int main() {
    int n,k;
    cin>>n>>k;
    int a[k];
    for(int i=0;i<k;i++) a[i]=1;

    int tmp1=1;
    if(k==1){
        while(tmp1<n) tmp1*=2;
        cout<<tmp1-n;
    }
    else if(k>n) cout<<k-n;
    else{
        for(int i =0;i<k;i++){
            if(i<k-1) {
                while (a[i] <= n) a[i] *= 2;
                n -= (a[i] / 2);
            }
            else {
                while (a[i] < n) a[i] *= 2;
                n = a[i]-n;
            }

            if(n==0) break;
        }
        cout<<n;
    }
    return 0;
}