#include <iostream>
using namespace std;

int startNode,endNode;
long min_distance=10000000,min_cost=100000000;

template <class TypeOfVer,class TypeOfEdge>
class adjListGraph{
public:
    adjListGraph(int vSize,TypeOfVer d[]){
        Vers = vSize;Edges = 0;
        verList = new verNode[vSize];
        for(int i=1;i<Vers;++i) verList[i].ver = d[i];
    }

    void insert(TypeOfVer x,TypeOfVer y,int l,TypeOfEdge w){
        int u=find(x),v=find(y);
        verList[u].head = new edgeNode(v,l,w,verList[u].head);
        ++Edges;
    }

    void dfs(int SN)const{
        bool *visited = new bool[Vers];
        for(int i=0;i<Vers;++i) visited[i] = false;
        long d=0,c=0;
        dfs(SN,visited,d,c);

        cout<<min_distance<<' '<<min_cost;
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
        int length;
        TypeOfEdge weight;
        edgeNode *next;

        edgeNode(int e,int l,TypeOfEdge w,edgeNode *n=nullptr)
        {end = e;length=l;weight = w;next =n;}
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

    void dfs(int start,bool visited[],long d,long c)const{

        if(start == endNode){
            if(d<min_distance) {
                min_distance=d;
                min_cost=c;
            }
            else if(d==min_distance && c<min_cost) min_cost=c;
            return;
        }
        if(d>min_distance) return;

        edgeNode *p = verList[start].head;
        visited[start] = true;
        long D,C;
        while(p!=nullptr){
            if(visited[p->end]==false) {
                D = d+p->length;
                C = c+p->weight;
                dfs(p->end,visited,D,C);
                visited[p->end] = false;
            }
            p=p->next;
        }
    }
};

int main() {
    int n,m;cin>>n>>m;
    int size = n+1;
    int a[size],i;
    for(i=1;i<size;i++) a[i]=i;

    adjListGraph<int,int> map(size,a);
    for(i=0;i<m;i++){
        int x,y,l,w;
        cin>>x>>y>>l>>w;
        map.insert(x,y,l,w);
        map.insert(y,x,l,w);
    }
    cin>>startNode>>endNode;

    map.dfs(startNode);
    return 0;
}