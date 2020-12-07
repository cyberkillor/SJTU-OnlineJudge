#include <iostream>
#include <string>
using namespace std;
template <class KEY,class OTHER>


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    while(cin>>s && s[0]!='f'){
        if(s[0]=='a'){

            cin>>i>>j;
            ss[j]++;
            if(ss[j]>max_l){
                max_n = j;
                max_l = ss[j];
            }
            else if(ss[j]==max_l && j<max_n)
                max_n = j;
        }
        else if(s[0]=='q'){
            cout<<max_n<<' '<<max_l<<'\n';
        }
    }
    return 0;
}