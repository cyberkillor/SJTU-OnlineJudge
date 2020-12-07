#include <iostream>
using namespace std;
/**
template <class KEY,class OTHER>
struct SET{
    KEY key;
    OTHER other;
};

//堆排序
template <class KEY,class OTHER>
void heapSort(SET<KEY,OTHER> a[], int size){
    int i;
    SET<KEY,OTHER> tmp;

    //创建初始的堆
    for(i = size/2;i>=0;i--)
        percolateDown(a,i,size);
    //执行n-1次dequeue
    for(i = size-1;i>0;--i){
        tmp = a[0];a[0] = a[i];a[i] = tmp;
        percolateDown(a,0,i);
    }
}

template <class KEY,class OTHER>
void percolateDown(SET<KEY,OTHER> a[],int hole,int size){
    int child;
    SET<KEY,OTHER> tmp = a[hole];

    for(;hole*2+1 < size;hole = child){
        child = hole*2+1;
        if(child!=size-1 && a[child+1].key<a[child].key)
            child++;
        if(a[child].key<tmp.key) a[hole] = a[child];
        else break;
    }
    a[hole] = tmp;
}

void percolateDown(int a[],int hole,int size){
    int child;
    int tmp = a[hole];

    for(;hole*2+1 < size;hole = child){
        child = hole*2+1;
        sum++;
        if(child!=size-1 && a[child+1]<a[child])
            child++;
        if(a[child]<tmp) a[hole] = a[child];
        else break;
    }
    a[hole] = tmp;
}
void heapSort(int a[], int size){
    int i;
    int tmp;

    //创建初始的堆
    for(i = size/2;i>=0;i--)
        percolateDown(a,i,size);
    //执行n-1次dequeue
    for(i = size-1;i>0;--i){
        tmp = a[0];a[0] = a[i];a[i] = tmp;
        percolateDown(a,0,i);
    }
}
**/
int sum=0;
template <class T>
class priorityQueue{
public:
    priorityQueue(int capacity = 100000){
        array = new T[capacity];
        maxSize = capacity;
        currentSize = 0;
    }

    ~priorityQueue(){delete []array;}

    bool isEmpty()const{return currentSize == 0;}
    void enQueue(const T &x){
        if(currentSize == maxSize-1) doubleSpace();

        int hole = ++currentSize;
        for(;hole>1;hole/=2)
        {
            sum++;
            if(x<array[hole/2])
                array[hole] = array[hole/2];
            else break;
        }
        array[hole] = x;
    }

    void deQueue(){
        T tmp;
        for(int i = currentSize-1;i>0;i--){
            tmp = array[0];array[0]=array[i];array[i]=tmp;
            percolateDown(0,i);
        }
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
    void percolateDown(int hole,int size){
        int child;
        T tmp = array[hole];

        for(;hole*2<=currentSize;hole = child){
            sum++;
            child = hole*2;
            if(child != currentSize && array[child+1]<array[child])
                child++;
            if(array[child]<tmp) array[hole] = array[child];
            else break;
        }
        array[hole] = tmp;
    }
};
int main() {
    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;++i)
        cin>>a[i];

    return 0;
}