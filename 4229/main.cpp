#include <iostream>
#include <string>
using namespace std;

template<class KEY,class OTHER>
struct SET{
    KEY key;
    OTHER other;
};

template <class KEY,class OTHER>
class AvlTree{
    struct AvlNode{
        SET<KEY,OTHER> data;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const SET<KEY,OTHER> &element,AvlNode *lt,AvlNode *rt,int h=1)
        :data(element),left(lt),right(rt),height(h){}
    };

    AvlNode *root,*min;
public:
    AvlTree(){root = nullptr;}
    ~AvlTree(){makeEmpty(root);}

    void insert(const SET<KEY,OTHER> &x){insert(x,root);}
    void query(){
        min = root;
        midOrder(root);
        cout<<min->data.key<<' '<<min->data.other<<'\n';
    }

    SET<KEY,OTHER> *find(const KEY &x)const{
        AvlNode *t = root;

        while(t!=nullptr&&t->data.key!=x){
            if(t->data.key>x) t = t->left;
            else t = t->right;
        }
        if(t==nullptr) return nullptr;
        else return (SET<KEY,OTHER> *) t;
    }
    void add(const KEY &i,const KEY &j){
        find(j)->other++;
    }

private:
    void insert(const SET<KEY,OTHER> &x,AvlNode *&t);
    void makeEmpty(AvlNode *t){
        if(t==nullptr) return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    int height(AvlNode *t)const{return t==nullptr? 0:t->height;}
    void LL(AvlNode *&t);
    void LR(AvlNode *&t);
    void RL(AvlNode *&t);
    void RR(AvlNode *&t);
    int max(int a,int b){return (a>b)? a:b;}
    void midOrder(AvlNode *t){
        if(t==nullptr) return;
        midOrder(t->left);
        if(t->data.other>min->data.other) min = t;
        midOrder(t->right);
    }
};
template <class KEY,class OTHER>
void AvlTree<KEY,OTHER>::LL(AvlNode *&t) {
    AvlNode *t1 = t->left;
    t->left = t1->right;
    t1->right = t;
    t->height = max(height(t->left),height(t->right)) +1;
    t1->height = max(height(t1->left),height(t)) +1;
    t = t1;
}
template <class KEY,class OTHER>
void AvlTree<KEY,OTHER>::RR(AvlNode *&t) {
    AvlNode *t1 = t->right;
    t->right = t1->left;
    t1->left = t;
    t->height = max(height(t->left),height(t->right)) +1;
    t1->height = max(height(t1->right),height(t)) +1;
    t = t1;
}
template <class KEY,class OTHER>
void AvlTree<KEY,OTHER>::LR(AvlNode *&t){
    RR(t->left);
    LL(t);
}
template <class KEY,class OTHER>
void AvlTree<KEY,OTHER>::RL(AvlNode *&t){
    LL(t->right);
    RR(t);
}

template <class KEY,class OTHER>
void AvlTree<KEY,OTHER>::insert(const SET<KEY, OTHER> &x, AvlNode *&t) {
    if(t==nullptr)
        t = new AvlNode(x,nullptr,nullptr);
    else if(x.key<t->data.key){
        insert(x,t->left);
        if(height(t->left)-height(t->right)==2)
        {if(x.key<t->left->data.key) LL(t);else LR(t);}
    }
    else if(t->data.key<x.key){
        insert(x,t->right);
        if(height(t->right)-height(t->left)==2)
        {if(t->right->data.key<x.key) RR(t);else RL(t);}
    }
    t->height = max(height(t->left),height(t->right)) +1;
}



int main() {
    int n;
    cin>>n;cin.get();
    AvlTree<int,int> t;

    for(int i = 0;i<n;i++){
        SET<int,int> s;
        s.key = i;
        s.other = 0;
        t.insert(s);
    }

    string s;
    while(cin>>s && s[0]!='f'){
        if(s[0]=='a'){
            int i,j;
            cin>>i>>j;
            t.add(i,j);
        }
        else if(s[0]=='q'){
            t.query();
        }
    }
    return 0;
}