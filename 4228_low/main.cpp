#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string email[100000],name[100000],n,e;
    int n_,j,max;
    cin>>n_;cin.get();

    for(int i = 0;i<n_;i++){
        bool flag = false;
        cin>>n>>e;

        for(j = 0;j<i;j++){
            if(email[j]==e)
            {flag = true;break;}
        }

        if(!flag) {email[i]=e;name[i] = n;max = i;}
        else {
            name[j] = name[j]+' '+n;
        }
    }

    for(int n = 0;n<=max;n++)
        cout<<name[n]<<'\n';
    return 0;
}