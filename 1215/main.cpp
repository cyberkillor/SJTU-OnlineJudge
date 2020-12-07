#include <iostream>
#include <string>
using namespace std;

template <class T>
class priorityQueue{
private:
    int currentSize;
    T *array;
    int maxSize;

    void doubleSpace(){
        T *tmp;
        tmp = array;
        array = new T[maxSize*2];
        for(int i = 0;i<maxSize;i++)
            array[i] = tmp[i];
        maxSize *= 2;
    }

    void percolateDown(int hole);
public:
    priorityQueue(int capacity = 100){
        array = new T[capacity];
        maxSize = capacity;
        currentSize = 0;
    }
    ~priorityQueue(){delete []array;}
    bool isEmpty()const{return currentSize == 0;}
    void enQueue(const T &x);
    T deQueue();
    T getHead(){return array[1];}
};
template <class T>
void priorityQueue<T>::enQueue(const T &x) {
    if(currentSize == maxSize-1) doubleSpace();

    int hole = ++currentSize;
    for(;hole>1 && x<array[hole/2];hole/=2)
        array[hole] = array[hole/2];
    array[hole] = x;
}
template <class T>
T priorityQueue<T>::deQueue() {
    T value;
    value = array[1];
    array[1] = array[currentSize--];   // ?
    percolateDown(1);
    return value;
}
template <class T>
void priorityQueue<T>::percolateDown(int hole) {
    int child;
    T tmp = array[hole];

    for(;hole*2<=currentSize;hole = child){
        child = hole*2;
        if(child!=currentSize && array[child+1]<array[child])
            child++;
        if(array[child]<tmp) array[hole] = array[child];
        else break;
    }
    array[hole] = tmp;
}

int main() {
    int n;
    cin>>n;
    cin.get();

    priorityQueue<int> q;
    string s;int x;
    for(int i = 1;i<=n;++i){
        cin>>s;
        switch(s[0]){
            case 'i':
                cin>>x;
                q.enQueue(x);
                break;
            case 'd':
                q.deQueue();
                break;
            case 'm':
                cout<<q.getHead()<<'\n';
        }
    }
    return 0;
}
