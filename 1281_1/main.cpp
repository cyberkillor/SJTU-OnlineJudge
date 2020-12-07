#include <iostream>
using namespace std;
int m,n,M1,M2;
long minsum = 10000;
int **a;
bool **flag;

void search(int i,int j,int s,bool b[30][30]){
    int tmp = s;
    if(a[i][j]==4 && tmp<=minsum) {minsum = tmp;return;}
    if(tmp>=minsum) return;

    b[i][j] = false;
    bool t[30][30];
    for(int k1=0;k1<m;k1++)
        for(int k2=0;k2<n;k2++)
            t[k1][k2] = b[k1][k2];
    tmp+=1;

    if(i-M1>=0 && j-M2>=0 && (a[i-M1][j-M2]==1 || a[i-M1][j-M2]==4) && b[i-M1][j-M2])
        search(i-M1,j-M2,tmp,t);
    if(i-M1>=0 && j+M2<n && (a[i-M1][j+M2]==1 || a[i-M1][j+M2]==4) && b[i-M1][j+M2])
        search(i-M1,j+M2,tmp,t);
    if(i+M1<m && j-M2>=0 && (a[i+M1][j-M2]==1 || a[i+M1][j-M2]==4) && b[i+M1][j-M2])
        search(i+M1,j-M2,tmp,t);
    if(i+M1<m && j+M2<n && (a[i+M1][j+M2]==1 || a[i+M1][j+M2]==4) && b[i+M1][j+M2])
        search(i+M1,j+M2,tmp,t);

    if(i-M2>=0 && j-M1>=0 && (a[i-M2][j-M1]==1 || a[i-M2][j-M1]==4) && b[i-M2][j-M1])
        search(i-M2,j-M1,tmp,t);
    if(i+M2<m && j-M1>=0 && (a[i+M2][j-M1]==1 || a[i+M2][j-M1]==4) && b[i+M2][j-M1])
        search(i+M2,j-M1,tmp,t);
    if(i-M2>=0 && j+M1<n && (a[i-M2][j+M1]==1 || a[i-M2][j+M1]==4) && b[i-M2][j+M1])
        search(i-M2,j+M1,tmp,t);

    if(i+M2<m && j+M1<n && (a[i+M2][j+M1]==1 || a[i+M2][j+M1]==4) && b[i+M2][j+M1])
        search(i+M2,j+M1,tmp,t);

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int i,j;
    cin>>m>>n>>M1>>M2;
    a = new int*[m];
    bool flag[30][30];
    for(i=0;i<m;i++) {a[i] = new int[n];}

    for(i=0;i<m;i++)
        for(j=0;j<n;j++){
            cin>>a[i][j];
            flag[i][j] = true;
        }

    for(i=0;i<m;i++)
        for(j=0;j<n;j++){
            if(a[i][j]==3){

                if(i-M1>=0 && j-M2>=0 && (a[i-M1][j-M2]==1 || a[i-M1][j-M2]==4))
                    search(i-M1,j-M2,1,flag);
                if(i-M1>=0 && j+M2<n && (a[i-M1][j+M2]==1 || a[i-M1][j+M2]==4))
                    search(i-M1,j+M2,1,flag);
                if(i+M1<m && j-M2>=0 && (a[i+M1][j-M2]==1 || a[i+M1][j-M2]==4))
                    search(i+M1,j-M2,1,flag);
                if(i+M1<m && j+M2<n && (a[i+M1][j+M2]==1 || a[i+M1][j+M2]==4))
                    search(i+M1,j+M2,1,flag);
                if(i-M2>=0 && j-M1>=0 && (a[i-M2][j-M1]==1 || a[i-M2][j-M1]==4))
                    search(i-M2,j-M1,1,flag);
                if(i+M2<m && j-M1>=0 && (a[i+M2][j-M1]==1 || a[i+M2][j-M1]==4))
                    search(i+M2,j-M1,1,flag);
                if(i-M2>=0 && j+M1<n && (a[i-M2][j+M1]==1 || a[i-M2][j+M1]==4))
                    search(i-M2,j+M1,1,flag);
                if(i+M2<m && j+M1<n && (a[i+M2][j+M1]==1 || a[i+M2][j+M1]==4))
                    search(i+M2,j+M1,1,flag);

                break;
            }
        }

    cout<<minsum;

    for(i=0;i<m;i++) delete []a[i];
    delete []a;
    return 0;
}
