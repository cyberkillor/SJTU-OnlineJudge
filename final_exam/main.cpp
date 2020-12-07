#include <iostream>
using namespace std;

//最大连续和子序列 O(N)
int maxSubsequenceSum(int a[],int size,int &start,int &end){
    int maxSum,starttmp,thisSum;
    start = end = maxSum = starttmp =thisSum = 0;
    for(int j=0;j<size;j++){
        thisSum+=a[j];
        if(thisSum<=0){
            thisSum=0;
            starttmp = j+1;
        }
        else if(thisSum>maxSum){
            maxSum = thisSum;
            start = starttmp;
            end = j;
        }
    }
    return maxSum;
}

//打印正整数的递归函数
void printInt(int num){
    if(num<10)
        cout.put(num+'0');
    else{
        printInt(num/10);
        cout.put(num%10+'0');
    }
}

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
int main() {
    linkQueue<int> q;
    q.enQueue(1);
    q.enQueue(2);
    q.enQueue(3);
    cout<<q.getHead()<<q.deQueue()<<q.deQueue()<<q.isEmpty();
    return 0;
}