#include <iostream>
using namespace std;

int startNode,endNode,min_cost=1000000;

template <class TypeOfVer,class TypeOfEdge>
class adjListGraph{
public:
    adjListGraph(int vSize,TypeOfVer d[]){
        Vers = vSize;Edges = 0;  //Vers = 5
        verList = new verNode[vSize];
        for(int i=1;i<Vers;++i) verList[i].ver = d[i];
    }

    void insert(TypeOfVer x,TypeOfVer y,TypeOfEdge w){
        int u=find(x),v=find(y);
        verList[u].head = new edgeNode(v,w,verList[u].head);
        ++Edges;
    }

    void dfs(int SN)const{
        bool *visited = new bool[Vers];
        for(int i=1;i<Vers;++i) visited[i] = false;
        int c=0;
        dfs(SN,visited,c);

        cout<<min_cost;
    }

    ~adjListGraph(){
        int i;
        edgeNode *p;
        for(i=0;i<Vers;++i)
            while((p=verList[i].head)!=nullptr){
                verList[i].head = p->next;
                delete p;
            }
        delete []verList;
    }

private:
    int Vers,Edges;
    struct edgeNode{
        int end;
        TypeOfEdge weight;
        edgeNode *next;

        edgeNode(int e,TypeOfEdge w,edgeNode *n=nullptr)
        {end = e;weight = w;next =n;}
    };
    struct verNode{
        TypeOfVer ver;
        edgeNode *head;

        verNode(edgeNode *h=nullptr){head=h;}
    };

    verNode *verList;
    int find(TypeOfVer v)const{
        for(int i=0;i<Vers;++i)
            if(verList[i].ver==v) return i;
    }

    bool decide(bool visited[])const{
        for(int i=1;i<Vers;++i)
            if(!visited[i]) return false;

        return true;
    }

    void dfs(int start,bool visited[],int c)const{
        visited[start] = true;
        if(decide(visited)) {
            edgeNode *tmp = verList[start].head;
            while(tmp->end!=1) tmp=tmp->next;
           // cout<<start<<' '<<c<<' ';
            c+=tmp->weight;
            if(c<min_cost) min_cost=c;
            return;
        }

        edgeNode *p = verList[start].head;


        int C;
        while(p!=nullptr){
            if(visited[p->end]==false) {
                C = c+p->weight;
                dfs(p->end,visited,C);
                visited[p->end] = false;
            }
            p=p->next;
        }
    }
};

int main() {
    int n,size;cin>>n;
    size = n+1;
    int a[size],i,j;

    for(i=1;i<size;i++) a[i]=i;
    adjListGraph<int,int> map(size,a);
    int w;
    for(i=1;i<size;++i)
        for(j=1;j<size;j++){
            cin>>w;
            if(i==j) continue;
            else{
                map.insert(i,j,w);
            }
        }
    startNode = endNode = 1;

    if(size==2) cout<<0;
    else map.dfs(startNode);
    return 0;
}