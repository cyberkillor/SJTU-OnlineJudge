#include <iostream>
using namespace std;

template<class T>
class seqDueue {
private:
    T *elem;
    int maxSize;
    int front, rear;

    void doublespace() {
        T *tmp = elem;
        elem = new T[2 * maxSize];
        for (int i = 1; i <= maxSize; ++i)
            elem[i] = tmp[(front + i) % maxSize];
        front = 0;
        rear = maxSize;
        maxSize *= 2;
        delete[]tmp;
    }

public:
    seqDueue(int initsize = 10) {
        elem = new T[initsize];
        front = rear = 0;
        maxSize = initsize;
    }

    ~seqDueue() {
        delete[]elem;
    }

    bool isEmpty() const {
        return (front == rear);
    }

    void enQueue(const T &x) {
        if ((rear + 1) % maxSize == front) doublespace();
        rear = (rear + 1) % maxSize;
        elem[rear] = x;
    }

    T deQueue() {
        front = (front + 1) % maxSize;
        return elem[front];
    }

    T getHead() {
        return elem[(front + 1) % maxSize];
    }
};

class stack{
private:
    seqDueue<int> l1,l2;
public:
    void push(const int &x){
        if(l1.isEmpty()) {
            l1.enQueue(x);

            if (!l2.isEmpty()) {
                while (!l2.isEmpty()) l1.enQueue(l2.deQueue());
            }
        }
        else {
            l2.enQueue(x);
            while(!l1.isEmpty()) l2.enQueue(l1.deQueue());
        }
    }

    int top(){
        if(l1.isEmpty()) return l2.getHead();
        else if(!l1.isEmpty()) return l1.getHead();
    }

    int pop(){
        if(l1.isEmpty()) return l2.deQueue();
        else if(l2.isEmpty()) return l1.deQueue();
    }
};
int main() {
    stack s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    cout<<s.pop()<<s.pop()<<s.pop()<<s.pop();

    return 0;
}