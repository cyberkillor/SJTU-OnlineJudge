#include <iostream>
using namespace std;
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
        for(;hole>1 && x<array[hole/2];hole/=2)
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

int main() {
    int n,x,sum=0,tmp,num=0;
    cin>>n;
    priorityQueue<int> q;
    for(int i = 0;i<n;i++){
        cin>>x;
        q.enQueue(x);
    }

    int n1,n2;
    for(int j = 0;j<n-1;j++){
        n1 = q.deQueue();
        n2 = q.deQueue();

        tmp=(n1+n2);
        q.enQueue(tmp);
        sum+=tmp;
    }
    cout<<sum;
    return 0;
}