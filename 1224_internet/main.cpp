#include<cstdlib>
#include<cstdio>
#include<iostream>
using namespace std;
int s[4000003] = {0};//-2000000-2000003...0-4000003
int a[510];
int la;
int b[510];
int lb;
int c[510];
int lc;
int d[510];
int ld;
void init()
{
    la = lb = lc = ld = 0;
}
int main()
{
    ios::sync_with_stdio(false);
    init();
    int n,t1,t2,t3,t4;
    int cou = 0;
    cin >> n;
    for (int i = 0; i < n;i++)
    {
        cin >> t1 >> t2 >> t3 >> t4;
        a[la++] = t1;
        b[lb++] = t2;
        c[lc++] = t3;
        d[ld++] = t4;
    }
    for (int i = 0; i < la; i++)
    {
        for (int j = 0; j < lb; j++)
        {
            s[(a[i] + b[j] + 2000000)] ++;
        }
    }
    for (int i = 0; i < lc; i++)
        for (int j = 0; j < ld; j++)
        {

            if (s[-((c[i] + d[j]) - 2000000)] != 0)cou+= s[-((c[i] + d[j]) - 2000000)];
        }

    cout << cou << endl;
    //system("pause");
    return 0;
}