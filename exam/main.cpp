#include <iostream>
using namespace std;

//单链表
template <class T>
class List{
private:
    struct node {
        T data;
        node *next;
        node(const T &x,node *n = nullptr)
        {data = x;next = n;}
        node():next(nullptr){}
        ~node(){}
    };

    node *head;
    int currentlength;

    node *move(int i)const//返回第i个节点的地址
    {
        node *p = head;
        while(i-->=0) p = p->next;
        return p;
    }
public:
    List();
    ~List(){clear();delete head;}

    void clear();
    int len()const{return currentlength;}
    void insert(int i,const T &x);
    void remove(int i);
    int search(const T &x)const;
    T visit(int i)const;
    void traverse()const;

    void erase(int i); //删除所有等于第i个元素的元素

};
template <class T>
List<T>::List() {
    head = new node;
    currentlength = 0;
}
template <class T>
void List<T>::clear() {
    node *p = head->next,*q;
    head->next = nullptr;
    while(p!= nullptr){
        q = p->next;
        delete p;
        p = q;
    }
    currentlength = 0;
}
template <class T>
void List<T>::insert(int i, const T &x) {
    node *pos;

    pos = move(i-1); //i从1开始
    pos->next = new node(x,pos->next);
    ++currentlength;
}
template <class T>
void List<T>::remove(int i) {
    node *pos,*delp;

    pos = move(i-1);
    delp = pos->next;
    pos->next = delp->next;
    delete delp;
    --currentlength;
}
template <class T>
int List<T>::search(const T &x) const {
    node *p = head->next;
    int i = 0;
    while(p!=nullptr && p->data!=x) {p = p->next;++i;}
    if(p== nullptr) return -1;else return i;
}
template <class T>
T List<T>::visit(int i) const {
    return move(i)->data;
}
template <class T>
void List<T>::traverse() const {
    node *p = head->next;
    cout<<'\n';
    while(p!=nullptr){
        cout<<p->data<<' ';
        p=p->next;
    }
    cout<<'\n';
}
template <class T>
void List<T>::erase(int i) {
    node *pre = move(i-1),*delp = pre->next;
    T tmp = delp->data;
    int cnt = 1;

    pre->next = delp->next;  //删除第i个结点
    delete delp;

    pre = head;
    while(pre->next!= nullptr){
        if(pre->next->data == tmp){
            delp = pre->next;
            pre->next = delp->next;
            delete delp;
            ++cnt;
        }
        else pre = pre->next;
    }

    currentlength-=cnt;
}
//————————————————————————————————————————————————————

//双链表
template <class T>
class dList {
private:
    struct node{
        T data;
        node *prev,*next;

        node(const T &x,node *p=nullptr,node *n = nullptr)
        {data = x;prev = p;next = n;}
        node():next(nullptr),prev(nullptr){}
        ~node(){}
    };

    node *head,*tail;
    int currentLength;

    node *move(int i)const{
        node *p = head;
        while(i-->=0) p = p->next;
        return p;
    }

public:
    dList();
    ~dList(){clear();delete head;delete tail;}

    void clear();
    int length()const {return currentLength;}
    void insert(int i,const T&x);
    void remove(int i);
    int search(const T &x)const;
    T visit(int i)const;
    void traverse()const;

    void reverse()const;  //逆序输出
};
template <class T>
dList<T>::dList() {
    head = new node;
    head->next = tail = new node;
    tail->prev = head;
    currentLength = 0;
}
template <class T>
void dList<T>::insert(int i, const T &x) {
    node *pos,*tmp;
    pos = move(i);
    tmp = new node(x,pos->prev,pos);
    pos->prev->next = tmp;
    pos->prev = tmp;
    ++currentLength;
}
template <class T>
void dList<T>::remove(int i) {
    node *pos;

    pos = move(i);
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
    delete pos;
    --currentLength;
}
template <class T>
void dList<T>::clear() {
    node *p = head->next,*q;
    head->next = tail;
    tail->prev = head;
    while(p!= nullptr){
        q = p->next;
        delete p;
        p = q;
    }
    currentLength = 0;
}
template <class T>
int dList<T>::search(const T &x) const {
    node *p = head->next;
    int i;
    for(i=0;p!=tail && p->data!=x; ++i) p = p->next;
    if(p==tail)return -1;else return i;
}
template <class T>
T dList<T>::visit(int i) const {
    return move(i)->data;
}
template <class T>
void dList<T>::traverse() const {
    node *p = head->next;
    cout<<'\n';
    while(p!=tail){
        cout<<p->data<<' ';
        p = p->next;
    }
    cout<<'\n';
}
template <class T>
void dList<T>::reverse() const {
    node *p;
    cout<<'\n';
    for(p = tail->prev;p!=head;p = p->prev)
        cout<<p->data<<' ';
    cout<<'\n';
}
//————————————————————————————————————-————

// 单循环链表 (*head)->next = *head

//栈
template <class T>
class Stack {
private:
    struct node{
        T data;
        node *next;
        node(const T &x,node *N = nullptr)
        {data = x;next = N;}
        node():next(nullptr){}
        ~node(){}
    };
    node *top_p;
public:
    Stack();
    ~Stack();
    bool isEmpty()const;
    void push(const T &x);
    T pop();
    T top()const;
};
template <class T>
Stack<T>::Stack() {
    top_p = nullptr;
}
template  <class T>
Stack<T>::~Stack() {
    node *tmp;
    while(top_p!= nullptr){
        tmp = top_p;
        top_p = top_p->next;
        delete tmp;
    }
}
template <class T>
bool Stack<T>::isEmpty() const {
    return top_p == nullptr;
}
template <class T>
void Stack<T>::push(const T &x) {
    top_p = new node(x,top_p);
}
template <class T>
T Stack<T>::pop() {
    node *tmp = top_p;
    T x = tmp->data;
    top_p = top_p->next;
    delete tmp;
    return x;
}
template <class T>
T Stack<T>::top() const {
    return top_p->data;
}
//————————————————————————————————————————

//链接队列
template <class T>
class linkQueue{
private:
    struct node{
        T data;
        node *next;
        node(const T &x,node *N = nullptr)
        {data = x;next = N;}
        node():next(nullptr){}
        ~node(){}
    };
    node *rear;

public:
    linkQueue(){rear = nullptr;}
    ~linkQueue();
    bool isEmpty()const{return rear == nullptr;}
    void enQueue(const T &x);
    T deQueue();
    T getHead()const{return rear->next->data;}
};
template <class T>
linkQueue<T>::~linkQueue() {
    node *tmp,*delp;

    if(rear== nullptr) return;
    delp = rear->next;
    rear->next = nullptr;
    while(delp!=nullptr){
        tmp = delp;
        delp = delp->next;
        delete tmp;
    }
}
template <class T>
void linkQueue<T>::enQueue(const T &x) {
    if(rear==nullptr){
        rear = new node(x);
        rear->next = rear;
    }
    else
        rear = rear->next = new node(x,rear->next);
}
template <class T>
T linkQueue<T>::deQueue() {
    node *tmp = rear->next;
    T value = tmp->data;
    if(rear == tmp) rear = nullptr;
    else rear->next = tmp->next;
    delete tmp;
    return value;
}
//——————————————————————————————-————————————————————————-

//约瑟夫环
struct Node {
    int data;
    Node *next;
    Node(int d,Node *n = nullptr){
        data = d;
        next = n;
    }
};
int main() {
    Node *head,*tmp1,*tmp2,*p,*q;
    int n,i,m,k,value=0;

    cin>>n>>m>>k;

    head = p =new Node(0);
    for(i=1;i<n;i++)
        p = p->next = new Node(i);
    tmp1 = p;
    p->next = head;

    q = head;
    for(int j =1;j<=k;j++) {
        for (i = 1; i < m; ++i) {q = q->next;tmp1 = tmp1->next;}
            tmp2 = q;
            tmp1->next = q->next;
            value = q->data;
            delete tmp2;
            q = tmp1->next;
    }
    cout<<value+1;
    return 0;
}