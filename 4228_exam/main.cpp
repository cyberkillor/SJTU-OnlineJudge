#include <iostream>
#include <string>
using namespace std;

struct SET {
    string email;
    string name;
};

class openHashTable {
private:
    struct node{  //开散列表中链表的结点类
        SET data;
        node *next;

        node(const SET &d,node *n=nullptr){data = d;next = n;}
        node(){next = nullptr;}
    };

    node **array;  //指针数组
    int size;
    //int (*key)(const int &x);
    //static int defaultKey(const int &x){return x;}

public:
    openHashTable(int length = 1001);
    ~openHashTable();
    SET *find(const string &x)const;
    void insert(const SET &x);
};

openHashTable::openHashTable(int length) {
    size = length;
    array = new node*[size];
    for(int i=0;i<size;++i) array[i] = nullptr;
}

openHashTable::~openHashTable() {
    node *p,*q;

    for(int i=0;i<size;++i){
        p = array[i];
        while(p!=nullptr){q = p->next;delete p;p=q;};//
    }
    delete []array;
}

void openHashTable::insert(const SET &x) {
    int pos;
    int num = int(x.email[0])*int(x.email[1]);

    pos = num%size;
    array[pos] = new node(x,array[pos]);
}
/**
void openHashTable::remove(const long long &x) {
    int pos;
    node *p,*q;

    pos = x%size;
    if(array[pos]==nullptr) return;
    p = array[pos];
    if(array[pos]->data.d==x){
        array[pos] = p->next;
        delete p;
        return;
    }

    while(p->next!=nullptr && !(p->next->data.d==x)) p = p->next;
    if(p->next!=nullptr){
        q = p->next;
        p->next = q->next;
        delete q;
    }
}
**/
SET *openHashTable::find(const string &x) const {
    int pos;
    node *p;

    pos = int(x[0])*int(x[1])%size;
    p=array[pos];
    while(p!=nullptr && !(p->data.email==x)) p=p->next;
    if(p==nullptr) return nullptr;
    else return (SET *)p;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;cin>>n;cin.get();
    SET s;
    openHashTable h;

    string email[n];
    int k=0;

    for(int i=0;i<n;i++){
        cin>>s.name>>s.email;
        if(h.find(s.email)) {
            h.find(s.email)->name+=(" "+s.name);
        }
        else {
            h.insert(s);
            email[k++] = s.email;
        }
    }

    for(int i=0;i<k;i++) cout<<h.find(email[i])->name<<'\n';
    return 0;
}