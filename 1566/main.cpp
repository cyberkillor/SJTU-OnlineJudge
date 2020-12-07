#include <iostream>
using namespace std;

template <class TypeOfVer,class TypeOfEdge>
class adjListGraph{
public:
    adjListGraph(int vSize,TypeOfVer d[]){
        Vers = vSize;Edges = 0;
        verList = new verNode[vSize];
        for(int i=0;i<Vers;++i) verList[i].ver = d[i];
    }

    void insert(TypeOfVer x,TypeOfVer y,TypeOfEdge w){
        int u=find(x),v=find(y);
        verList[u].head = new edgeNode(v,w,verList[u].head);
        ++Edges;
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
    //Prim算法求最小生成树
    void prim(TypeOfEdge noEdge)const{
        bool *flag = new bool[Vers];
        TypeOfEdge *lowCost = new TypeOfEdge[Vers];
        int *startNode = new int[Vers];
        int sum=0;

        edgeNode *p;
        TypeOfEdge min;
        int start,i,j;

        for(i=0;i<Vers;++i){
            flag[i] = false;
            lowCost[i] = noEdge;
        }

        start=0;
        for(i=1;i<Vers;++i){
            for(p=verList[start].head;p!=nullptr;p=p->next)
                if(!flag[p->end] && lowCost[p->end]>p->weight){
                    lowCost[p->end]=p->weight;
                    startNode[p->end]=start;
                }

            flag[start]=true;
            min=noEdge;
            for(j=0;j<Vers;++j)
                if(lowCost[j]<min) {min=lowCost[j];start=j;}

            edgeNode *pos;
            pos = verList[startNode[start]].head;
            while(pos->end!=(verList[start].ver-'A')) pos=pos->next;
            sum += pos->weight;
            //cout<<'('<<verList[startNode[start]].ver<<','<<verList[start].ver<<")\t";

            lowCost[start]=noEdge;
        }

        cout<<sum;
        delete []flag;
        delete []startNode;
        delete []lowCost;
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
};

int main() {
    int size;cin>>size;
    char ch[size];
    int i,j;
    for(i=0;i<size;++i)
        ch[i] = 'A'+i;

    adjListGraph<char,int> map(size,ch);

    char x,y;
    int weight;
    for(i=0;i<size-1;i++){
        cin>>x;
        cin>>j;
        for(int k=0;k<j;k++){
            cin>>y>>weight;
            map.insert(x,y,weight);
            map.insert(y,x,weight);
        }
    }
    map.prim(10000);
    return 0;
}