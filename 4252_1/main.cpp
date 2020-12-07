#include <iostream>
using namespace std;

template <class T>
class priorityQueue{
public:
    priorityQueue(long capacity = 1000){
        array = new T[capacity];
        maxSize = capacity;
        currentSize = 0;
    }

    ~priorityQueue(){delete []array;}

    bool isEmpty()const{return currentSize == 0;}
    void enQueue(const T &x){
        if(currentSize == maxSize-1) doubleSpace();

        long hole = ++currentSize;
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

private:
    long currentSize;
    T *array;
    long maxSize;

    void doubleSpace(){
        T *tmp = array;
        maxSize*=2;
        array = new T [maxSize];
        for(long i = 0;i<=currentSize;++i)
            array[i] = tmp[i];
        delete []tmp;
    }

    void percolateDown(long hole){
        long child;
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

long func(long a,long b,long c,long x){
    return (a*x*x+b*x+c);
}
long max(long a,long b){
    return (a>b)? a:b;
}
int main() {
    int n,k;cin>>n>>k;
    int i;
    long A[n],B[n],C[n];

    for(i=0;i<n;i++)
        cin>>A[i]>>B[i]>>C[i];

    long min;

    priorityQueue<long> q;
    for(i=0;i<n;i++){
        if(i==0) {
            if (B[i] == 0) {
                for (long j = 0; j <= k / 2; j++)
                    q.enQueue(func(A[i], B[i], C[i], j));
                for (long j = -1 * (k / 2); j < 0; j++)
                    q.enQueue(func(A[i], B[i], C[i], j));
                min = max(func(A[i],B[i],C[i],k/2),func(A[i],B[i],C[i],-k/2));
            } else {
                long x = B[i] / A[i] / 2 * (-1);
                for (long j = 0; j <= k / 2; j++)
                    q.enQueue(func(A[i], B[i], C[i], j + x));
                for (long j = -1 * (k / 2); j < 0; j++)
                    q.enQueue(func(A[i], B[i], C[i], j + x));
                min = max(func(A[i],B[i],C[i],x+k/2),func(A[i],B[i],C[i],x-k/2));
            }
        }
        else {
            if (B[i] == 0) {
                for (long j = 0; j <= k / 2; j++)
                    if (func(A[i], B[i], C[i], j) < min)
                        q.enQueue(func(A[i], B[i], C[i], j));
                for (long j = -1 * (k / 2); j < 0; j++)
                    if (func(A[i], B[i], C[i], j) < min)
                        q.enQueue(func(A[i], B[i], C[i], j));
            } else {
                long x = B[i] / A[i] / 2 * (-1);
                for (long j = 0; j <= k / 2; j++)
                    if (func(A[i], B[i], C[i], j + x) < min)
                        q.enQueue(func(A[i], B[i], C[i], j + x));
                for (long j = -1 * (k / 2); j < 0; j++)
                    if (func(A[i], B[i], C[i], j + x) < min)
                        q.enQueue(func(A[i], B[i], C[i], j + x));
            }
        }
    }

    for(i=0;i<k;i++)
        cout<<q.deQueue()<<' ';
    return 0;
}