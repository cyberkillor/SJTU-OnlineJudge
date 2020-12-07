#include <vector>
#include <queue>
#include <iostream>
using namespace std;

int map[31][31]={0};

int M,N,M1,M2;

struct Point
{
    int x;
    int y;
    int lay;//层数 用来计算结果
};
Point s;//起点
Point e;//终点

int Graph[31*31][31*31]={0};


inline int getID(int x,int y){
    if(x<=M and x>=1  and y>=1 and y<=N){
        if(map[x][y]!=0 and map[x][y]!=2)//不是水和沼泽才返回
            return (x-1) * N + y;
    }
    return -1;
}

inline void getPoint(int id, int& x,int& y){
    y = id % N;
    if(y==0)
        y = N;
    x = id / N ;
}

void init(){
    cin>>M>>N>>M1>>M2;
    for (int i = 1; i <= M; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            cin>>map[i][j];
            if(map[i][j]==3){
                s.x = i;
                s.y = j;
            }else if(map[i][j]==4){
                e.x = i;
                e.y = j;
            }
        }
    }
}



int bfs(){
    //八个方向
    int dx[8] = {M1,M1,-M1,-M1,M2,M2,-M2,-M2};
    int dy[8] = {M2,-M2,M2,-M2,M1,-M1,M1,-M1};

    queue<Point> q;//BFS的队列
    s.lay = 0;//表示层数
    q.push(s);
    bool vis[31*31] = {0};
    int res=0;
    while(!q.empty()){
        Point cur = q.front();
        if(cur.x == e.x and cur.y == e.y)//其实这步没必要..早期代码遗留
            break;
        q.pop();
        res = cur.lay;
        vis[getID(cur.x,cur.y)] = true; //访问状态更改
        for (int i = 0; i < 8; ++i)
        {
            int x = cur.x + dx[i];
            int y = cur.y + dy[i];
            int newid = getID(x,y);
            if(newid!=-1 and !vis[newid]){
                Point p;
                p.x = x ;
                p.y = y;
                p.lay = cur.lay + 1;
                if(x==e.x and y==e.y)//找到终点了
                    return p.lay;
                q.push(p);
                vis[newid] = true;//访问状态更改
            }
        }
    }

    return res;
}

int main(int argc, char const *argv[])
{

    //最短路径问题
    init();
    cout<<bfs()<<endl;

    return 0;
}