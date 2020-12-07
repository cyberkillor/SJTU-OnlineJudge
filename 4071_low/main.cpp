#include <iostream>
#include <cmath>
using namespace std;

int main() {
    unsigned long long n;cin>>n;
    unsigned long long tmp1=1,tmp2=1,tmp,i;

    if(n==0 || n==1) cout<<1;
    else {
        for(i=1;i<n;i++){
            tmp = tmp2;
            tmp2 = tmp1;
            tmp1+=tmp;
        }
        cout<<tmp1%1000000007;
    }
    return 0;
}
