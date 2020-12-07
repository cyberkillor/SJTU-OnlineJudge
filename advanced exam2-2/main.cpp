#include <iostream>
using namespace std;
//邻接表储存树，也可看做孩子链表法
struct Node{
    int id;
    Node *next;
    Node(int _id,Node *_next=nullptr):id(_id),next(_next){}
};

int n;
int *father,*cnt;
Node **head;

void traverse(int x){
    //递归遍历树，同时确定每个结点的父亲节点（father）以及其子树的节点个数（cnt）
    for(Node *p = head[x]->next; p!=nullptr;p=p->next){
        if(father[p->id]==0 && p->id != 1){
            father[p->id] = x;
            traverse(p->id);
            cnt[x] += cnt[p->id];
        }
    }
    ++cnt[x];
}

int main() {
    cin>>n;
    father = new int[n+1]{0};
    cnt = new int[n+1]{0};
    head = new Node *[n+1];

    for(int i =1;i<=n;++i)
        head[i] = new Node(0);

    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        Node *temp;
        temp = new Node(v,head[u]->next);
        head[u]->next = temp;
        temp = new Node(u,head[v]->next);
        head[v]->next = temp;
    }
    //以1为根节点遍历
    traverse(1);

    //注意这里的时间复杂度是O（n）
    for(int i=1;i<=n;i++){
        bool check =true;
        for(Node *p= head[i]->next;p!=nullptr;p=p->next){
            if(p->id == father[i]){
                if(cnt[i]<n/2) check = false;
            }
            else{
                if(cnt[p->id] > n/2) check = false;
            }
        }
        if(check) cout<<i<<'\n';
    }
    return 0;
}