#include <iostream>
using namespace std;
template <class T>
class Stack {
private:
    struct node{
        T data;
        node *next;
        node(const T &x,node *N = nullptr)
        {data = x;next = N;}
        node():next(nullptr){}
        ~node(){}
    };
    node *top_p;
public:
    Stack();
    ~Stack();
    bool isEmpty()const;
    void push(const T &x);
    T pop();
    T top()const;
};
template <class T>
Stack<T>::Stack() {
    top_p = nullptr;
}
template  <class T>
Stack<T>::~Stack() {
    node *tmp;
    while(top_p!= nullptr){
        tmp = top_p;
        top_p = top_p->next;
        delete tmp;
    }
}
template <class T>
bool Stack<T>::isEmpty() const {
    return top_p == nullptr;
}
template <class T>
void Stack<T>::push(const T &x) {
    top_p = new node(x,top_p);
}
template <class T>
T Stack<T>::pop() {
    node *tmp = top_p;
    T x = tmp->data;
    top_p = top_p->next;
    delete tmp;
    return x;
}
template <class T>
T Stack<T>::top() const {
    return top_p->data;
}

int main() {
    int n,x,jud,L=-1,R=1;
    cin>>n;jud = n;
    bool flag = true;

    int ch[n+1];
    ch[0] = 0;
    for(int i = 1;i<=n;i++)
        ch[i] = i;

    Stack<int> s;
    while(n-->0){
        cin>>x;
        if(flag) {s.push(x);flag = false;ch[x] = 0;}
        else if(x>s.top()){s.push(x);ch[x]=0;}
        else{
            L = R =s.top();
            while(ch[L]==0 && L>1) L--;
            while(ch[R]==0 && R<jud) R++;

            if(x == ch[L]) {s.push(x);ch[x]=0;}
            else if(x == ch[R]) {s.push(x);ch[x]=0;}
            else{cout<<"No";exit(0);}
        }

    }
    cout<<"Yes";
    return 0;
}
