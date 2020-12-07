#include <iostream>
using namespace std;
struct Node {
    long data;
    Node *next;
    Node(long d,Node *n = nullptr){
        data = d;
        next = n;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Node *head,*tmp1,*tmp2,*p,*q;
    long n,i,m,k,value=0;

    cin>>n;

    head = p =new Node(0);
    for(i=1;i<n;i++)
        p = p->next = new Node(i);
    tmp1 = p;
    p->next = head;

    q = head;
    k = n;
    for(long j =1;j<=n-1;j++) {
        cin>>m;

        if(m%k==0) m = k;
        else m = m%k;

        for (i = 1; i < m; ++i) {q = q->next;tmp1 = tmp1->next;}
            tmp2 = q;
            tmp1->next = q->next;

            delete tmp2;
            q = tmp1->next;
            value = q->data;
            k--;
    }
    cout<<value+1;
    return 0;
}