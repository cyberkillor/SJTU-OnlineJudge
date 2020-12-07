#include <iostream>
#include <string>
using namespace std;

string max_title;
int max_num = 0;

struct SET{
    string title;
    int num=1;
};

class BinarySearchTree{
private:
    struct BinaryNode{
        SET data;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const SET &thedata,BinaryNode *lt=nullptr,BinaryNode *rt=nullptr)
        :data(thedata),left(lt),right(rt){}
    };
    BinaryNode *root;
public:
    BinarySearchTree(){root=nullptr;}
    ~BinarySearchTree(){
        makeEmpty(root);
    }

    SET *find(const string &x)const{
        return find(x,root);
    }

    void insert(const SET &x){insert(x,root);}

private:
    void makeEmpty(BinaryNode *t){
        if(t==nullptr) return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    SET *find(const string &x,BinaryNode *t)const{
        if(t==nullptr || t->data.title==x)
            return (SET *) t;
        if(x<t->data.title)
            return find(x,t->left);
        else return find(x,t->right);
    }
    void insert(const SET &x,BinaryNode *&t){
        if(t==nullptr){
            t = new BinaryNode(x,nullptr,nullptr);
            if(max_num==0){
                max_num = 1;
                max_title = x.title;
            }
            else if(max_num==1){
                if(x.title<max_title)
                    max_title = x.title;
            }
        }
        else if(x.title<t->data.title)
            insert(x,t->left);
        else if(t->data.title<x.title)
            insert(x,t->right);

        else if(t->data.title == x.title){
            t->data.num++;
            if(t->data.num>max_num){
                max_num = t->data.num;
                max_title = t->data.title;
            }
            else if(t->data.num == max_num){
                if(t->data.title < max_title)
                    max_title = t->data.title;
            }
        }
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    SET S;
    BinarySearchTree T;
    string s;
    while(cin>>s && s[0]!='f'){
        if(s[0]=='c'){
            cin.get();
            getline(cin,S.title);
            T.insert(S);
        }
        else if(s[0]=='q'){
            cout<<max_num<<' '<<max_title<<'\n';
        }
    }
    return 0;
}