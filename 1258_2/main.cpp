#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    bool flag = true;
    int n,tmp,sum=0;
    cin>>n;
    int num[n];
    for(int i = 0;i<n;i++) cin>>num[i];

    int R = 0,L = n-1;

    while(R<L){
        flag = true;
        for(int k = 0;k<L;k++){
            if(num[k]>num[k+1]){
                tmp = num[k];
                num[k] = num[k+1];
                num[k+1] = tmp;
                flag = false;
                sum++;
            }
        }
        L--;
        if(flag) break;

        flag = true;
        for(int j=L;j>R;j--){
            if(num[j-1]>num[j]){
                tmp = num[j-1];
                num[j-1] = num[j];
                num[j] = tmp;
                sum++;
                flag = false;
            }
        }
        R++;
        if(flag) break;
    }
    cout<<sum;
    return 0;
}