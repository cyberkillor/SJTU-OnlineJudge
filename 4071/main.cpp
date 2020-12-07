#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
long long i,j,k,m,n;


struct data_
{
    long long arr[4][4];
}a,b;

long long r()
{
    long long aans=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        aans*=10;
        aans+=ch-'0';
        ch=getchar();
    }
    return aans*f+1;
}

data_ mul(data_ aa,data_ bb)
{
    data_ cc;
    memset(cc.arr,0,sizeof(cc.arr));
    for(i=1;i<=2;i++)
        for(j=1;j<=2;j++)
            for(k=1;k<=2;k++)
                cc.arr[i][j]+=(aa.arr[i][k]*bb.arr[k][j])%1000000007;
    return cc;
}

data_ ksm(long long x)
{
    data_ c,d;
    long long xx=x;
    c=(data_){{{},{0,0,1},{0,1,1}}};
    d=(data_){{{},{0,1,0},{0,0,1}}};
    if(xx==1)
        return c;

    while(x)
    {
        if(x&1!=0)
            d=mul(d,c);
        c=mul(c,c);
        x>>=1;
    }
    return d;
}



int main() {
    n = r();
    a = (data_) {{{}, {0, 1, 1}, {0, 0, 0}}};
    b = (data_) {{{}, {0, 0, 1}, {0, 1, 1}}};
    a = mul(a, ksm(n - 1));
    cout << a.arr[1][1] % 1000000007;
}