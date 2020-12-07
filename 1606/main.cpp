#include <iostream>
using namespace std;

int start_row,start_col,end_row,end_col,sum=100000;
int n,m;
char a[50][50];
int num=0;

template <class TypeOfVer>
class adjListGraph {
public:
    adjListGraph(int vSize, const TypeOfVer d[50][50]) {
        Vers = vSize;
        Edges = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                verList[i][j].ver = d[i][j];
    }

    ~adjListGraph() {
        int i, j;
        edgeNode *p;

        for (i = 0; i < n; i++)
            for (j = 0; j < m; j++)
                while ((p = verList[i][j].head) != nullptr) {
                    //释放第i个结点的单链表
                    verList[i][j].head = p->next;
                    delete p;
                }
    }

    void insert() {
        int i, j;
        for (i = 0; i < n; i++)
            for (j = 0; j < m; j++) {
                if (j - 1 >= 0) verList[i][j].head = new edgeNode(i, j - 1, verList[i][j].head);
                if (j + 1 < m) verList[i][j].head = new edgeNode(i, j + 1, verList[i][j].head);
                if (i - 1 >= 0) verList[i][j].head = new edgeNode(i - 1, j, verList[i][j].head);
                if (i + 1 < n) verList[i][j].head = new edgeNode(i + 1, j, verList[i][j].head);
            }
    }

    //深度优先搜索
    bool dfs(char d[50][50]) const {
        bool visited[50][50];  //记录每个结点是否已被访问
        int i, j;
        for (i = 0; i < n; ++i)
            for (j = 0; j < m; j++) {
                if (d[i][j] == '#') visited[i][j] = true;
                else visited[i][j] = false;
            }

        //深度优先遍历
        int a, b;
        for (i = 0; i < n; ++i)
            for (j = 0; j < m; j++) {
                if (visited[i][j]) continue;
                else {
                    a = i;
                    b = j;
                    break;
                }
            }
        dfs(a, b, visited);
        for (i = 0; i < n; ++i)
            for (j = 0; j < m; j++) {
                if (!visited[i][j]) {
                   // cout<<i<<' '<<j;
                    return false;
                }
            }
        return true;
    }

    void display(){
        int i,j;
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                if(verList[i][j].ver=='?') cout<<'.';
                else cout<<verList[i][j].ver;
            }
            cout<<'\n';
        }
    }

private:
    int Vers,Edges;
    struct edgeNode{  //邻接表中存储边的结点类
        int endR;      //终点编号
        int endC;
        //TypeOfEdge weight;     //边的权值
        edgeNode *next;

        edgeNode(int e,int e_,edgeNode *n=nullptr)
        {endR = e;endC=e_;next = n;}
    };

    struct verNode{  //保存顶点的数据元素类型
        TypeOfVer ver;     //顶点值
        edgeNode *head;     //对应的单链表的头指针

        verNode(edgeNode *h=nullptr){head = h;}
    };
    verNode verList[50][50];
    void dfs(int startR,int startC,bool visited[50][50])const{
        edgeNode *p=verList[startR][startC].head;
        visited[startR][startC] = true;

        while(p!=nullptr){  //对start的后继结点执行dfs
            if(!visited[p->endR][p->endC]){
                if(verList[p->endR][p->endC].ver=='?') num++;
                dfs(p->endR,p->endC,visited);
            }
            p=p->next;
        }
    }
};

int doubt_num=0;

int main() {
    cin>>n>>m;
    int i,j;
    bool f1=false,f2=false;

    for(i=0;i<n;++i)
        for(j=0;j<m;++j){
            cin>>a[i][j];
            if(a[i][j]=='.') f1=true;
            if(a[i][j]=='?') {f2=true;doubt_num++;}
        }

    adjListGraph<char> map(n*m,a);
    map.insert();

    if(!f1 && !f2) cout<<"Impossible";
    else if(!f1){
        cout<<"Ambiguous";
    }
    else if(!f2){
        if(!map.dfs(a)) cout<<"Impossible";
        else map.display();
    }
    else {
        for (i = 0; i < n; i++){
            for (j = 0; j < m; j++) {
                if(a[i][j]=='?'){

                    adjListGraph<char> MAP(n*m,a);
                }
            }
        }

    }
    return 0;
}
