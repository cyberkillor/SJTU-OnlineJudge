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
        for(;hole>1 ;hole/=2)
            array[hole] = array[hole/2];
        array[hole] = x;
        percolateDown(hole);
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
            if(child != currentSize && array[child+1]>array[child])
                child++;
            if(array[child]>tmp) array[hole] = array[child];
            else break;
        }
        array[hole] = tmp;
    }
};

int main() {
    string ss[31];
    char s;
    cin>>s;

    priorityQueue<string> q;
    int i = 0;
    while(cin>>ss[i] && ss[i]!="@"){
        string tmp;
        //cout<<ss[i]<<' ';
        for(int j = 0;j<ss[i].length();j++){
            if(ss[i][j]==s) continue;
            tmp += ss[i][j];
        }
        //cout<<tmp<<' ';
        i++;
        q.enQueue(tmp);
    }
    while(!q.isEmpty()) cout<<q.deQueue()<<'\n';
    return 0;
}