#include <iostream>
#include <string>
using namespace std;

template <class KEY,class OTHER>
struct SET{
    KEY key;
    OTHER other;
};
template <class KEY,class OTHER>
class BinarySearchTree{
private:
    struct BinaryNode{
        SET<KEY,OTHER> data;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const SET<KEY,OTHER> &thedata,BinaryNode *lt=nullptr,BinaryNode *rt=nullptr)
        :data(thedata),left(lt),right(rt){}
    };
    BinaryNode *root,*min;

public:
    BinarySearchTree(){root = nullptr;}
    ~BinarySearchTree(){makeEmpty(root);}
    void add(const OTHER &x){add(x,root);}
    void insert(const SET<KEY,OTHER> &x){insert(x,root);}

    void query(){
        min = root;
        midOrder(root);
        cout<<min->data.other<<' '<<min->data.key<<'\n';
    }

private:
    void midOrder(BinaryNode *t){
        if(t==nullptr) return;
        midOrder(t->left);
        if(t->data.key>min->data.key) min = t;
        midOrder(t->right);
    }

    void add(const OTHER &x,BinaryNode *t)const{
        if(t==nullptr) return;
        else if(t->data.other==x){
            t->data.key++;
        }
        if(x<t->data.other)
            return add(x,t->left);
        else return add(x,t->right);
    }
    void insert(const SET<KEY,OTHER> &x,BinaryNode *&t){
        if(t==nullptr)
            t = new BinaryNode(x,nullptr,nullptr);
        else if(x.other<t->data.other)
            insert(x,t->left);
        else if(t->data.other<x.other)
            insert(x,t->right);
    }
    void makeEmpty(BinaryNode *t){
        if(t==nullptr) return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;cin.get();
    SET<int,int> S[n];
    BinarySearchTree<int,int> t;
    for(int i = 0;i<n;i++){
        S[i].key = 0;
        S[i].other = i;
        t.insert(S[i]);
    }
    string s;

    while(cin>>s && s[0]!='f'){
        if(s[0]=='a'){
            int i,j;
            cin>>i>>j;
            t.add(j);
        }
        else if(s[0]=='q'){
            t.query();
        }
    }
    return 0;
}