#include <iostream>
using namespace std;

int a[6][6];
int start_row,start_col,end_row,end_col,sum=100000;
int T=1,S=0;

template <class TypeOfVer>
class adjListGraph{
public:
    adjListGraph(int vSize,const TypeOfVer d[6][6]){
        Vers = vSize;Edges = 0;
        for(int i=0;i<6;i++)
            for(int j=0;j<6;j++)
                verList[i][j].ver = d[i][j];
    }
    ~adjListGraph(){
        int i,j;
        edgeNode *p;

        for(i=0;i<6;i++)
            for(j=0;j<6;j++)
                while((p=verList[i][j].head)!=nullptr){
                    //释放第i个结点的单链表
                    verList[i][j].head = p->next;
                    delete p;
            }
    }

    void insert(){
        int i,j;
        for(i=0;i<6;i++)
            for(j=0;j<6;j++){
                if(j-1>=0) verList[i][j].head = new edgeNode(i,j-1,verList[i][j].head);
                if(j+1<6) verList[i][j].head = new edgeNode(i,j+1,verList[i][j].head);
                if(i-1>=0) verList[i][j].head = new edgeNode(i-1,j,verList[i][j].head);
                if(i+1<6) verList[i][j].head = new edgeNode(i+1,j,verList[i][j].head);
            }
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
    /**
    bool exist(TypeOfVer x,TypeOfVer y)const{
        int u=find(x),v=find(y);
        edgeNode *p=verList[u].head;

        while(p!=nullptr && p->end!=v) p = p->next;
        if(p==nullptr) return false;
        else return true;
    }
**/
    //深度优先搜索
    void dfs()const{
        bool visited[6][6];  //记录每个结点是否已被访问
        for(int i=0;i<6;++i)
            for(int j=0;j<6;j++)
                visited[i][j] = false;


        //深度优先遍历
        dfs(start_row,start_col,visited,T,S);
    }
    void dfs(int startR,int startC,bool visited[6][6],int ZT,int C)const{

        if(startR==end_row && startC == end_col){
            if(C<sum) sum = C;
            return;
        }
        if(C>=sum) return;

        edgeNode *p=verList[startR][startC].head;
        //cout<<verList[start].ver<<'\t';  访问结点
        visited[startR][startC] = true;

        int cost;

        while(p!=nullptr){  //对start的后继结点执行dfs
            if(!visited[p->endR][p->endC]){
                cost = verList[p->endR][p->endC].ver*ZT;
                int ZT_ = (cost%4) +1;
                //cout<<cost<<' '<<ZT_<<' ';
                int C_= C+cost;

                bool visited_[6][6];
                for(int i=0;i<6;i++)
                    for(int j=0;j<6;j++)
                        visited_[i][j] = visited[i][j];

                //cout<<startR<<' '<<startC<<'\n';
                dfs(p->endR,p->endC,visited_,ZT_,C_);
            }
            p=p->next;
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
    verNode verList[6][6];

};

int main() {
    int n;cin>>n;
    int i,j,k;
    for(k=0;k<n;k++){
        for(i=0;i<6;i++)
            for(j=0;j<6;j++){
                cin>>a[i][j];
            }
        cin>>start_row>>start_col>>end_row>>end_col;

        adjListGraph<int> map(36,a);
        map.insert();
        map.dfs();
        cout<<sum<<'\n';
    }
    return 0;
}