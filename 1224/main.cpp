#include <iostream>
using namespace std;
//开散列表
struct SET {
    long long d;
    int num=1;
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
    openHashTable(int length = 10001);
    ~openHashTable();
    SET *find(const long long &x)const;
    void insert(const SET &x);
    void remove(const long long &x);
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
    node *p;

    pos = x.d%size;
    array[pos] = new node(x,array[pos]);
}

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

SET *openHashTable::find(const long long &x) const {
    int pos;
    node *p;

    pos = x%size;
    p=array[pos];
    while(p!=nullptr && !(p->data.d==x)) p=p->next;
    if(p==nullptr) return nullptr;
    else return (SET *)p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;

    long long A[n],B[n],C[n],D[n];
    int i,j;
    for(i = 0;i<n;i++){
        cin>>A[i]>>B[i]>>C[i]>>D[i];
    }

    openHashTable h1,h2;
    SET s;
    for(i = 0;i<n;i++)
        for(j=0;j<n;j++){
            s.d = A[i]+B[j];
            //cout<<s.d<<' ';
            if(s.d>0){
            if(h1.find(s.d)) h1.find(s.d)->num++;
            else h1.insert(s);
            }
            else{
                s.d*=(-1);
                if(h2.find(s.d)) h2.find(s.d)->num++;
                else h2.insert(s);
            }
        }


    long long sum=0;

    for(i=0;i<n;i++)
        for(j=0;j<n;j++){
            long long dd;
            dd = C[i]+D[j];
            if(dd>=0) {
                if (h2.find(dd)) { sum += h2.find(dd)->num; }
            }
            else{
                dd*=(-1);
                if(h1.find(dd)) sum+= h1.find(dd)->num;
            }
        }

    cout<<sum;

    return 0;
}