#include<iostream>
#include<cstring>
using namespace std;
char a[52][52];
int visited[52][52],landnum=0,doubtnum=0,queue[50000][2],n,m;
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
int und[50000];
int markpos[50000][2];
int bfs(int bx,int by);
int main()
{
    cin>>n>>m;
    int bx=1,by=1,ur=0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
        {
            cin>>a[i][j];
            if(a[i][j]=='.')
            {
                ++landnum;
                bx=i;
                by=j;
            }
            if(a[i][j]=='?')
            {
                ++doubtnum;
                markpos[doubtnum][0]=i;
                markpos[doubtnum][1]=j;
            }
        }
    int times=0,x,y;
    if(landnum==0&doubtnum!=0)
    {
        cout<<"Ambiguous";
        return 0;
    }
    if(bfs(bx,by)==landnum)
    {
        for(int i=1;i<=doubtnum;++i)
        {
            x=markpos[i][0];
            y=markpos[i][1];
            if(visited[x][y]==0)
                a[x][y]='#';
            if(visited[x][y]==1)
                a[x][y]='.',und[++ur]=i,++landnum;
        }
        for(int i=1;i<=ur;++i)
        {
            x=markpos[und[i]][0];
            y=markpos[und[i]][1];
            a[x][y]='#';
            --landnum;
            if(bfs(bx,by)==landnum)
            {
                cout<<"Ambiguous";
                return 0;
            }
            a[x][y]='.';
            ++landnum;
        }
    }
    else
    {
        cout<<"Impossible";
        return 0;
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
            cout<<a[i][j];
        if(i!=n)
            cout<<endl;
    }
    return 0;
}
int bfs(int bx,int by)
{
    memset(visited,0,sizeof(visited));
    int lnum=0;
    int l=0,r=0;
    queue[++r][0]=bx;
    queue[r][1]=by;
    visited[bx][by]=1;
    int x,y,xx,yy;
    while(l<r)
    {
        x=queue[++l][0];
        y=queue[l][1];
        if(a[x][y]=='.')
            ++lnum;
        for(int i=0;i<4;++i)
        {
            xx=x+dx[i];
            yy=y+dy[i];
            if(xx>0&&xx<=n&&yy>0&&yy<=m&&a[xx][yy]!='#'&&visited[xx][yy]==0)
            {
                queue[++r][0]=xx;
                queue[r][1]=yy;
                visited[xx][yy]=1;
            }
        }
    }
    return lnum;
}