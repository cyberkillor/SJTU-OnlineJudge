#include <iostream>
using namespace std;

int M,N,M1,M2;
int start_row,start_col,end_row,end_col,sum=900;
int num=0;

template <class TypeOfVer>
class adjListGraph{
public:
    adjListGraph(int vSize,const TypeOfVer d[30][30]){
        Vers = vSize;Edges = 0;
        for(int i=0;i<M;i++)
            for(int j=0;j<N;j++)
                verList[i][j].ver = d[i][j];
    }
    ~adjListGraph(){
        int i,j;
        edgeNode *p;

        for(i=0;i<M;i++)
            for(j=0;j<N;j++)
                while((p=verList[i][j].head)!=nullptr){
                    //释放第i个结点的单链表
                    verList[i][j].head = p->next;
                    delete p;
                }
    }

    void insert(){
        int i,j;
        for(i=0;i<M;i++)
            for(j=0;j<N;j++) {
                if (verList[i][j].ver == 1 || verList[i][j].ver == 3) {
                    if (i - M1 >= 0 && j - M2 >= 0 &&
                        (verList[i - M1][j - M2].ver == 1 || verList[i - M1][j - M2].ver == 4))
                        verList[i][j].head = new edgeNode(i - M1, j - M2, verList[i][j].head);
                    if (i - M1 >= 0 && j + M2 < N &&
                        (verList[i - M1][j + M2].ver == 1 || verList[i - M1][j + M2].ver == 4))
                        verList[i][j].head = new edgeNode(i - M1, j + M2, verList[i][j].head);
                    if (i + M1 < M && j - M2 >= 0 &&
                        (verList[i + M1][j - M2].ver == 1 || verList[i + M1][j - M2].ver == 4))
                        verList[i][j].head = new edgeNode(i + M1, j - M2, verList[i][j].head);
                    if (i + M1 < M && j + M2 < N &&
                        (verList[i + M1][j + M2].ver == 1 || verList[i + M1][j + M2].ver == 4))
                        verList[i][j].head = new edgeNode(i + M1, j + M2, verList[i][j].head);

                    if (i - M2 >= 0 && j - M1 >= 0 &&
                        (verList[i - M2][j - M1].ver == 1 || verList[i - M2][j - M1].ver == 4))
                        verList[i][j].head = new edgeNode(i - M2, j - M1, verList[i][j].head);
                    if (i - M2 >= 0 && j + M1 < N &&
                        (verList[i - M2][j + M1].ver == 1 || verList[i - M2][j + M1].ver == 4))
                        verList[i][j].head = new edgeNode(i - M2, j + M1, verList[i][j].head);
                    if (i + M2 < M && j - M1 >= 0 &&
                        (verList[i + M2][j - M1].ver == 1 || verList[i + M2][j - M1].ver == 4))
                        verList[i][j].head = new edgeNode(i + M2, j - M1, verList[i][j].head);
                    if (i + M2 < M && j + M1 < N &&
                        (verList[i + M2][j + M1].ver == 1 || verList[i + M2][j + M1].ver == 4))
                        verList[i][j].head = new edgeNode(i + M2, j + M1, verList[i][j].head);


                }
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

    //深度优先搜索
    void dfs()const{
        bool visited[30][30];  //记录每个结点是否已被访问
        for(int i=0;i<M;++i)
            for(int j=0;j<N;j++)
                visited[i][j] = false;


        //深度优先遍历
        dfs(start_row,start_col,visited,num);
    }
    void dfs(int &startR,int &startC,bool visited[30][30],int n)const{

        if(startR==end_row && startC == end_col){
            if(n<sum) sum = n;
            return;
        }
        if(n>=sum) return;

        edgeNode *p=verList[startR][startC].head;
        visited[startR][startC] = true;

        while(p!=nullptr){  //对start的后继结点执行dfs
            if(!visited[p->endR][p->endC]){
                int n_= n+1;

                //cout<<startR<<' '<<startC<<'\n';
                dfs(p->endR,p->endC,visited,n_);
                visited[p->endR][p->endC]=false;
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
    verNode verList[30][30];

};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>M>>N>>M1>>M2;
    int i,j,k;
    int a[30][30];
    for(i=0;i<M;i++)
        for(j=0;j<N;j++){
            cin>>a[i][j];
            if(a[i][j]==3){start_row=i;start_col=j;}
            if(a[i][j]==4){end_row=i;end_col=j;}
        }
    adjListGraph<int> map(M*N,a);
    map.insert();
    map.dfs();

    cout<<sum;
    return 0;
}