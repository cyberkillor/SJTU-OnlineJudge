 #include <iostream>
#include <string>
using namespace std;

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

//第六章第七章 树+优先级队列

//二叉链表类
template <class T>
class binaryTree{
    friend void printTree(const binaryTree &t,T flag){
        linkQueue<T> q;
        q.enQueue(t.root->data);

        while(!q.isEmpty()){
            char p,l,r;
            p = q.deQueue();
            l = t.lchild(p,flag);
            r = t.rchild(p,flag);
            cout<<p<<' '<<l<<' '<<r<<'\n';
            if(l!='@') q.enQueue(l);
            if(r!='@') q.enQueue(r);         // !!!
        }
    }


private:
    struct Node{
        Node *left,*right;
        T data;
        Node():left(nullptr),right(nullptr){}
        Node(T item,Node *L=nullptr,Node *R=nullptr):data(item),left(L),right(R){}
        ~Node(){}
    };
    Node *root;

public:
    binaryTree():root(nullptr){}
    binaryTree(T x){root = new Node(x);}
    ~binaryTree(){clear(root);}
    void clear(){clear(root);}
    bool isEmpty()const{return root==nullptr;}

    T Root(T flag)const{
        if(root==nullptr) return flag;
        else return root->data;
    }
    T lchild(T x,T flag)const{
        Node *tmp;
        tmp = find(x, root);
        if(tmp==nullptr || tmp->left==nullptr) return flag;
        return tmp->left->data;
    }
    T rchild(T x,T flag)const{
        Node *tmp = find(x,root);
        if(tmp==nullptr || tmp->right==nullptr) return flag;
        return tmp->right->data;
    }

    void delLeft(T x){
        Node *tmp = find(x,root);
        if(tmp==nullptr) return;
        clear(tmp->left);
    }
    void delRight(T x){
        Node *tmp = find(x,root);
        if(tmp==nullptr) return;
        clear(tmp->right);
    }

    void preOrder()const{preOrder(root);}      //根左右
    void midOrder()const{midOrder(root);}       //左根右
    void postOrder()const{postOrder(root);}     //左右根

    void levelOrder()const{
        linkQueue<Node *> que;
        Node *tmp;

        que.enQueue(root);

        while(!que.isEmpty()){
            tmp = que.deQueue();
            cout<<tmp->data<<' ';
            if(tmp->left) que.enQueue(tmp->left);
            if(tmp->right) que.enQueue(tmp->right);
        }
    }
    void createTree(T flag){
        linkQueue<Node *> que;
        Node *tmp;
        T x,ldata,rdata;

        cin>>x;
        root = new Node(x);
        que.enQueue(root);

        while(!que.isEmpty()){
            tmp = que.deQueue();
            cin>>ldata>>rdata;          //输入tmp的两个儿子  flag表示空节点
            if(ldata!=flag) que.enQueue(tmp->left = new Node(ldata));
            if(rdata!=flag) que.enQueue(tmp->right = new Node(rdata));
        }
    }

private:
    Node *find(T x,Node *t)const{
        Node *tmp;
        if(t==nullptr) return nullptr;
        if(t->data==x) return t;
        if(tmp = find(x,t->left)) return tmp;       // ???
        else return find(x,t->right);
    }

    void clear(Node *&t){
        if(t==nullptr) return;
        clear(t->left);
        clear(t->right);
        delete t;
        t = nullptr;
    }

    void preOrder(Node *t)const{
        if(t==nullptr) return;
        cout<<t->data<<' ';
        preOrder(t->left);
        preOrder(t->right);
    }
    void midOrder(Node *t)const{
        if(t==nullptr) return;
        midOrder(t->left);
        cout<<t->data<<' ';
        midOrder(t->right);
    }
    void postOrder(Node *t)const{
        if(t==nullptr) return;
        postOrder(t->left);
        postOrder(t->right);
        cout<<t->data<<' ';
    }
};

//求二叉树高度和规模函数
/**
template <class T>
int binaryTree<T>::size()const{
    return size(root);
}
template <class T>
int binaryTree<T>::size(binaryTree<T>::Node *t)const{
    if(t==nullptr) return 0;
    return 1+size(t->left)+size(t->right);
}

template <class T>
int height(Node *t)const{
    if(t==nullptr) return 0;
    else{
        int lt = height(t->left),rt = height(t->right);
        return 1+((lt>rt)?lt:rt);
    }
}
**/
//----------------------------------------------------------

//优先级队列     二叉堆
template <class T>
class priorityQueue{
public:
    priorityQueue(int capacity = 100){
        array = new T[capacity];
        maxSize = capacity;
        currentSize = 0;
    }

    priorityQueue(const T *data,int size):maxSize(size+10),currentSize(size){           // O(N) 直接对数组操作
        array = new T [maxSize];
        for(int i = 0;i<size;i++)
            array[i+1] = data[i];
        buildHeap();
    }
    ~priorityQueue(){delete []array;}

    bool isEmpty()const{return currentSize == 0;}
    void enQueue(const T &x){
        if(currentSize == maxSize-1) doubleSpace();

        int hole = ++currentSize;
        for(;hole>1 && array[hole/2];hole/=2)
            array[hole] = array[hole/2];
        array[hole] = x;
    }

    T deQueue(){
        T minItem;
        minItem = array[1];
        array[1] = array[currentSize--];
        percolateDown(1);
        return minItem;
    }
    T getHead()const{return array[1];}

private:
    int currentSize;
    T *array;
    int maxSize;

    void doubleSpace(){
        T *tmp = array;
        maxSize*=2;
        array = new T [maxSize];
        for(int i = 0;i<=currentSize;++i)
            array[i] = tmp[i];
        delete []tmp;
    }
    void buildHeap(){
        for(int i = currentSize/2;i>0;i--)
            percolateDown(i);
    }

    void percolateDown(int hole){
        int child;
        T tmp = array[hole];

        for(;hole*2<=currentSize;hole = child){
            child = hole*2;
            if(child != currentSize && array[child+1]<array[child])
                child++;
            if(array[child]<tmp) array[hole] = array[child];
            else break;
        }
        array[hole] = tmp;
    }
};

//----------------------------------------------------------------------------

//哈夫曼树
template <class T>
class hfTree{
private:
    struct Node{
        T data;
        int weight;
        int parent,left,right;
    };
    Node *elem;
    int length;

public:
    struct hfCode{
        T data;                  //待编码的字符
        string code;             //对应的哈夫曼编码
    };
    hfTree(const T *v,const int *w,int size){
        const int MAX_INT = 32767;
        int min1,min2;
        int x,y;

        length = 2*size;
        elem = new Node[length];

        for(int i=size;i<length;i++){
            elem[i].weight = w[i-size];
            elem[i].data = v[i-size];
            elem[i].parent = elem[i].left = elem[i].right = 0;
        }

        // 归并森林中的树
        for(int i = size-1;i>0;--i) {
            min1 = min2 = MAX_INT;
            x = y = 0;
            for (int j = i + 1; j < length; ++j)
                if (elem[j].parent == 0){
                    if (elem[j].weight < min1) {
                        min2 = min1;
                        min1 = elem[j].weight;
                        x = y;
                        y = j;
                    }
                    else if (elem[j].weight < min2) {
                        min2 = elem[j].weight;
                        x = j;
                    }
                }
                    elem[i].weight = min1+min2;
                    elem[i].left = x;
                    elem[i].right = y;
                    elem[i].parent = 0;
                    elem[x].parent = i;
                    elem[y].parent = i;
        }
    }

    void getCode(hfCode result[])
    {
        int size = length/2;
        int p,s;

        for(int i = size;i<length;++i){
            result[i-size].data = elem[i].data;
            result[i-size].code = "";
            p = elem[i].parent;s = i;
            while(p){
                if(elem[p].left==s)
                    result[i-size].code = '0' + result[i-size].code;
                else result[i-size].code = '1' + result[i-size].code;
                s = p;
                p = elem[p].parent;
            }
        }
    }
    ~hfTree(){delete []elem;}
};

int main() {
    /**
    binaryTree<char> t;
    t.createTree('@');
    t.preOrder();
    t.midOrder();
    t.postOrder();
    t.levelOrder();
    printTree(t,'@');
    t.delLeft('L');
    t.delRight('C');
    printTree(t,'@');
    **/

    char ch[] = {"aeistdn"};
    int w[]={10,15,12,3,4,13,1};
    hfTree<char> t(ch,w,7);
    hfTree<char>::hfCode result[7];

    t.getCode(result);

    for(int i = 0;i<7;++i)
        cout<<result[i].data<<' '<<result[i].code<<endl;
    return 0;
}
