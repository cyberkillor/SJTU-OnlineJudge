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
int sum = 0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

   int n;cin>>n;
   Stack<int> s1,s2;

   int a[n];
   for(int j =0;j<n;j++) cin>>a[j];
   for(int i =n-1;i>=0;i--){
       if(i==n-1) s1.push(a[i]);
       else {
           while (!s1.isEmpty() && a[i] > s1.top()) {
               s2.push(s1.pop());
               sum++;
           }

           s1.push(a[i]);
           while (!s2.isEmpty()) s1.push(s2.pop());
       }
   }
   cout<<sum;

   return 0;
}