#include <iostream>
#include <string>
using namespace std;

int jud = 0;
bool flag = false;
template <class T>
class BinarySearchTree{
private:
    struct BinaryNode{
        T data;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const T & thedata,BinaryNode *L= nullptr,BinaryNode *R= nullptr)
        :data(thedata),left(L),right(R){}
    };
    BinaryNode *root;

public:
    BinarySearchTree(){root = nullptr;}
    ~BinarySearchTree(){
        makeEmpty(root);
    }
    void find(const T &x)const{find(x,root);}
    void find_ith(const int &x){
        find_ith(x,root);
        if(!flag) cout<<'N'<<'\n';
        flag = false;
        jud = 0;

    }
    void insert(const T &x){insert(x,root);}
    void remove(const T &x){remove(x,root);}
    void remove_less_than(const T &x){remove_less_than(x,root);}
    void remove_greater_than(const T &x){remove_greater_than(x,root);}
    void remove_interval(const T &x,const T &y){remove_interval(x,y,root);}

private:
    void find(const T &x,BinaryNode *t)const;
    void insert(const T &x,BinaryNode *&t);
    void remove(const T &x,BinaryNode *&t);
    void remove_less_than(const T &x,BinaryNode *&t){
        if(t==nullptr) return;
        if(x<=t->data)
            remove_less_than(x,t->left);
        else if(t->data<x) {
            t->left = nullptr;
            BinaryNode *tmp = t->right;
//!!!!
            if(tmp==nullptr) t = nullptr;
            else {
                while (tmp->left != nullptr) tmp = tmp->left;
                t->data = tmp->data;
                remove(t->data, t->right);
                remove_less_than(x, t);    // !
            }
        }
    }
    void remove_greater_than(const T &x,BinaryNode *&t){
        if(t==nullptr) return;
        if (t->data <= x) remove_greater_than(x, t->right);
        else if(x<t->data){
            if(t->left!=nullptr && t->right!=nullptr){
                t->right = nullptr;
                BinaryNode *tmp = t->left;

                if(tmp==nullptr) t = nullptr;
                else {
                    while (tmp->right != nullptr) tmp = tmp->right;
                    t->data = tmp->data;

                    remove(t->data, t->left);
                    remove_greater_than(x, t);    //  !
                }
            }
            else{
                BinaryNode *oldNode = t;
                t = (t->left!=nullptr) ? t->left:t->right;
                delete oldNode;
                remove_greater_than(x,t);
            }

        }
    }
    void remove_interval(const T &a,const T &b,BinaryNode *&t){
        if(t==nullptr) return;
        if(t->data<=a) remove_interval(a,b,t->right);
        else if(t->data>=b) remove_interval(a,b,t->left);
        else if(t->left!=nullptr && t->right!=nullptr){
            BinaryNode *tmp = t->left;
            while(tmp->right!=nullptr) tmp = tmp->right;
            t->data = tmp->data;
            remove(t->data,t->left);
            remove_interval(a,b,t);

        }
        else{
            BinaryNode *oldNode = t;
            t = (t->left!=nullptr) ? t->left:t->right;
            delete oldNode;
            remove_interval(a,b,t);
        }
    }
    void find_ith(const int &x,BinaryNode *t){
        if(t==nullptr) return;
        find_ith(x,t->left);
        jud++;
        if(jud==x) {
            cout<<t->data<<'\n';
            flag = true;
            return;
        }

        find_ith(x,t->right);
    }
    void makeEmpty(BinaryNode *t){
        if(t==nullptr) return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
};
template <class T>
void BinarySearchTree<T>::find(const T &x,BinaryNode *t) const {
    if(t==nullptr) {cout<<'N'<<'\n';return;}
    else if(t->data == x) {cout<<'Y'<<'\n';return;}

    if(x<t->data) find(x,t->left);
    else find(x,t->right);
}
template <class T>
void BinarySearchTree<T>::insert(const T &x,BinaryNode *&t) {
    if(t==nullptr) t = new BinaryNode(x,nullptr,nullptr);
    else if(x<=t->data) insert(x,t->left);
    else if(x>t->data) insert(x,t->right);
}
template <class T>
void BinarySearchTree<T>::remove(const T &x,BinaryNode *&t) {
    if(t==nullptr) return;
    if(x<t->data) remove(x,t->left);
    else if(x>t->data) remove(x,t->right);
    else if(t->left!=nullptr && t->right!=nullptr){
        BinaryNode *tmp = t->right;
        while(tmp->left!=nullptr) tmp = tmp->left;
        t->data = tmp->data;
        // ?
        remove(t->data,t->right);
    }
    else {
        BinaryNode *oldNode = t;
        t = (t->left!=nullptr) ? t->left:t->right;
        delete oldNode;
    }
}


int main() {
    BinarySearchTree<int> t;
    int n;
    cin>>n;
    string s;
    cin.get();

    for(int i = 1;i<=n;i++){
        cin>>s;
        if(s[0]=='i'){
            int a;
            cin>>a;
            t.insert(a);
        }
        else if(s[0]=='d'){
            if(s.length()<8) {
                int a;
                cin>>a;
                t.remove(a);
            }
            else if(s[7]=='g'){
                int a;cin>>a;
                t.remove_greater_than(a);
            }
            else if(s[7]=='l'){
                int a;cin>>a;
                t.remove_less_than(a);
            }
            else if(s[7]=='i'){
                int a,b;cin>>a>>b;
                t.remove_interval(a,b);
            }
        }
        else if(s[0]=='f'){
            if(s.length()<6){
                int a;cin>>a;
                t.find(a);
            }
            else if(s[5]=='i'){

                int a;cin>>a;

                t.find_ith(a);

            }
        }

    }

    return 0;
}