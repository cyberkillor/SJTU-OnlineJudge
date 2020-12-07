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
            if(child != currentSize && array[child+1]<array[child])  //
                child++;
            if(array[child]<tmp) array[hole] = array[child];         //
            else break;
        }
        array[hole] = tmp;
    }
};

double func(double a,double b,double c,int x){
    return (a*x*x+b*x+c);
}
int main() {
    int n,k;cin>>n>>k;
    int i;
    double A[n],B[n],C[n];

    for(i=0;i<n;i++)
        cin>>A[i]>>B[i]>>C[i];

    priorityQueue<double> q;
    for(i=0;i<n;i++){
        if(B[i]==0){
            for(int j=0;j<=k/2;j++)
                q.enQueue(func(A[i],B[i],C[i],j));
            for(int j =-1*(k/2);j<0;j++)
                q.enQueue(func(A[i],B[i],C[i],j));
        }
        else{
            int x= int( B[i] /(2*A[i]) )*(-1);
            //cout<<x<<'\n';
            for(int j=0;j<=k/2;j++)
                q.enQueue(func(A[i],B[i],C[i],j+x));
            for(int j =-1*(k/2);j<0;j++)
                q.enQueue(func(A[i],B[i],C[i],j+x));
        }
    }

    for(i=0;i<k;i++)
        cout<<q.deQueue()<<' ';
    return 0;
}