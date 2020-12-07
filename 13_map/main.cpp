#include <iostream>
using namespace std;

int footNum;
int min_footNum = 100000;
int M1,M2;
int start,finish;

template <class TypeOfVer,class TypeOfEdge>
class adjListGraph{
public:
    adjListGraph(int vSize,const TypeOfVer d[]){
        Vers = vSize;Edges = 0;
        verList = new verNode[vSize];
        for(int i=0;i<vSize;i++) verList[i].ver=d[i];
    }
    ~adjListGraph(){
        int i;
        edgeNode *p;

        for(i=0;i<Vers;i++)
            while((p=verList[i].head)!=nullptr){
                //释放第i个结点的单链表
                verList[i].head = p->next;
                delete p;
            }
        delete []verList;
    }

    void insert(TypeOfVer x,TypeOfVer y,TypeOfEdge w){
        int u = find(x),v = find(y);
        verList[u].head = new edgeNode(v,w,verList[u].head);
        ++Edges;
    }
    void remove(TypeOfVer x,TypeOfVer y){
        int u = find(x),v=find(y);
        edgeNode *p=verList[u].head,*q;
        if(p==nullptr) return;  //结点u没有相连的边

        if(p->end == v){        //单链表中第一个结点就是被删除的边
            verList[u].head = p->next;
            delete p;--Edges;
            return;
        }

        while(p->next!=nullptr && p->next->end!=v) p=p->next;//查找被删除的边
        if(p->next!=nullptr){
            q=p->next;
            p->next = q->next;
            delete q;
            --Edges;
        }
    }
    bool exist(TypeOfVer x,TypeOfVer y)const{
        int u=find(x),v=find(y);
        edgeNode *p=verList[u].head;

        while(p!=nullptr && p->end!=v) p = p->next;
        if(p==nullptr) return false;
        else return true;
    }

    //深度优先搜索
    void dfs()const{
        bool *visited = new bool[Vers];  //记录每个结点是否已被访问
        for(int i=0;i<Vers;++i) visited[i] = false;


        //深度优先遍历
        dfs(start,visited);
    }
    void dfs(int start,bool visited[])const{
        edgeNode *p=verList[start].head;
        //cout<<verList[start].ver<<'\t';  访问结点
        visited[start] = true;

        while(p!=nullptr){  //对start的后继结点执行dfs
            if(visited[p->end]==false) dfs(p->end,visited);
            p=p->next;
        }
    }

private:
    int Vers,Edges;
    struct edgeNode{  //邻接表中存储边的结点类
        int end;      //终点编号
        TypeOfEdge weight;     //边的权值
        edgeNode *next;

        edgeNode(int e,TypeOfEdge w,edgeNode *n=nullptr)
        {end = e;weight = w;next = n;}
    };

    struct verNode{  //保存顶点的数据元素类型
        TypeOfVer ver;     //顶点值
        edgeNode *head;     //对应的单链表的头指针

        verNode(edgeNode *h=nullptr){head = h;}
    };
    verNode *verList;
    int find(int v)const{
        for(int i=0;i<Vers;i++)
            if(verList[i].ver == v) return i;
    }
};
int main() {
    int m,n;
    cin>>m>>n;
    int a[m*n];
    cin>>M1>>M2;
    for(int i =0;i< m*n;i++) {
        cin>>a[i];
        if(a[i]==3) start = i;
        if(a[i]==4) finish = i;
    }

    adjListGraph<int,int> map(m*n,a);
    map.dfs();
    return 0;
}