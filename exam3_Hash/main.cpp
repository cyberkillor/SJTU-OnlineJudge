#include <iostream>
using namespace std;

template <class KEY,class OTHER>
struct SET{
    KEY key;
    OTHER other;
};
//基于线性探测法的闭散列表的实现
template <class KEY,class OTHER>
class closeHashTable{
private:
    struct node{ //散列表的结点类
        SET<KEY,OTHER> data;
        int state; //0--empty  1--active  2--deleted

        node(){state=0;}
    };
    node *array;
    int size;
    int (*key)(const KEY &x);
    static int defaultKey(const int &x){return x;}

public:
    closeHashTable(int length = 101,int(*f)(const KEY &x)=defaultKey);
    ~closeHashTable(){delete []array;}
    SET<KEY,OTHER> *find(const KEY &x)const;
    void insert(const SET<KEY,OTHER> &x);
    void remove(const KEY &x);
};

template <class KEY,class OTHER>
closeHashTable<KEY,OTHER>::closeHashTable(int length, int (*f)(const KEY &x)) {
    size = length;
    array = new node[size];
    key = f;
}

template <class KEY,class OTHER>
void closeHashTable<KEY,OTHER>::insert(const SET<KEY, OTHER> &x) {
    int initPos,pos;

    initPos = pos = key(x.key) % size;
    do{
        if(array[pos].state!=1){  //找到空单元
            array[pos].data = x;
            array[pos].state = 1;
            return;
        }
        pos = (pos+1)%size;
    }while(pos!=initPos);
}

template <class KEY,class OTHER>
void closeHashTable<KEY,OTHER>::remove(const KEY &x) {
    int initPos,pos;

    initPos = pos = key(x)%size;
    do{
        if(array[pos].state == 0) return;
        if(array[pos].state == 1 && array[pos].data.key == x){ //找到，删除
            array[pos].state = 2;
            return;
        }
        pos = (pos+1)%size;
    }while(pos!=initPos);
}

template <class KEY,class OTHER>
SET<KEY,OTHER> *closeHashTable<KEY,OTHER>::find(const KEY &x) const {
    int initPos,pos;

    initPos = pos = key(x)%size;
    do{
        if(array[pos].state==0) return nullptr; //没有找到
        if(array[pos].state==1 && array[pos].data.key==x) //找到
            return (SET<KEY,OTHER> *)&array[pos];
        pos = (pos+1)%size;
    }while(pos!=initPos);
}


//开散列表
template <class KEY,class OTHER>
class openHashTable {
private:
    struct node{  //开散列表中链表的结点类
        SET<KEY,OTHER> data;
        node *next;

        node(const SET<KEY,OTHER> &d,node *n=nullptr){data = d;next = n;}
        node(){next = nullptr;}
    };

    node **array;  //指针数组
    int size;
    int (*key)(const int &x);
    static int defaultKey(const int &x){return x;}

public:
    openHashTable(int length = 101, int(*f)(const KEY &x) = defaultKey);
    ~openHashTable();
    SET<KEY,OTHER> *find(const KEY &x)const;
    void insert(const SET<KEY,OTHER> &x);
    void remove(const KEY &x);
};

template <class KEY,class OTHER>
openHashTable<KEY,OTHER>::openHashTable(int length, int (*f)(const KEY &x)) {
    size = length;
    array = new node*[size];
    key = f;
    for(int i=0;i<size;++i) array[i] = nullptr;
}

template <class KEY,class OTHER>
openHashTable<KEY,OTHER>::~openHashTable() {
    node *p,*q;

    for(int i=0;i<size;++i){
        p = array[i];
        while(p!=nullptr){q = p->next;delete p;p=q;};//
    }
    delete []array;
}

template <class KEY,class OTHER>
void openHashTable<KEY,OTHER>::insert(const SET<KEY, OTHER> &x) {
    int pos;
    node *p;

    pos = key(x.key)%size;
    array[pos] = new node(x,array[pos]);
}

template <class KEY,class OTHER>
void openHashTable<KEY,OTHER>::remove(const KEY &x) {
    int pos;
    node *p,*q;

    pos = key(x)%size;
    if(array[pos]==nullptr) return;
    p = array[pos];
    if(array[pos]->data.key==x){
        array[pos] = p->next;
        delete p;
        return;
    }

    while(p->next!=nullptr && !(p->next->data==x)) p = p->next;
    if(p->next!=nullptr){
        q = p->next;
        p->next = q->next;
        delete q;
    }
}

template <class KEY,class OTHER>
SET<KEY,OTHER> *openHashTable<KEY,OTHER>::find(const KEY &x) const {
    int pos;
    node *p;

    pos = key(x)%size;
    p=array[pos];
    while(p!=nullptr && !(p->data.key==x)) p=p->next;
    if(p==nullptr) return nullptr;
    else return (SET<KEY,OTHER> *)p;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}