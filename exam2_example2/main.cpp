#include <iostream>
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

// 排队系统的模拟

class simulator{
    int noOfServer;   //服务台个数
    int arrivalLow;   //到达间隔时间的下界
    int arrivalHigh;  //到达间隔时间的上界
    int serviceTimeLow;     //服务间隔时间的下界
    int serviceTimeHigh;    //服务间隔时间的上界
    int customNum;    //模拟的顾客数

    struct eventT{
        int time;
        int type;
        bool oprerator<(const eventT &e)const {return time<e.time;}
    };

public:
    simulator()
    {
        cin>>noOfServer;
        cin>>arrivalLow>>arrivalHigh;
        cin>>serviceTimeLow>>serviceTimeHigh;

        srand(time(nullptr));
    }

    int avgWaitTime(){
        int serverBusy = 0        //正在工作的服务台数
        int currentTime;
        int totalWaitTime = 0;
        linkQueue<eventT> waitQueue;
        priorityQueue<eventT> eventQueue;

        eventT currentEvent;
    }
};
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}