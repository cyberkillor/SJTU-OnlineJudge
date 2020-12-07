#include <iostream>
using namespace std;

class priorityQueue{
private:
    int currentSize;
    int array[20000];

public:
    priorityQueue(){
        currentSize = 0;
    }
    ~priorityQueue(){}
    void enQueue(const int &x);

    void decrease(const int &x,const int &y){
        array[x] -= y;
        int tmp = array[x];

        int hole = x;
        for(;hole>1 && tmp<array[hole/2];hole/=2)
            array[hole] = array[hole/2];

        array[hole] = tmp;
    }

    int find(const int &x){
        int i = 1;
        while(array[i]<=x && i<currentSize) i++;
        int min = i,tmp = array[i];
        for(int j = i;j<=currentSize;j++){
            if(array[j]>x && array[j]<tmp ) {
                min = j;
                tmp = array[j];
            }
        }
        return min;
    }
};
void priorityQueue::enQueue(const int &x) {
    int hole = ++currentSize;
    for(;hole>1 && x<array[hole/2];hole/=2)
        array[hole] = array[hole/2];
    array[hole] = x;
}

int main() {
    int n,x;
    char s[20];
    cin>>n;
    cin.get();

    priorityQueue q;
    for(int i =1;i<=n;++i){
        cin>>s;
        switch(s[0]){
            case 'i':
                cin>>x;
                q.enQueue(x);
                break;
            case 'f':
                cin>>x;
                cout<<q.find(x)<<'\n';
                break;
            case 'd':
                int k;
                cin>>x>>k;
                q.decrease(x,k);
        }
    }
    return 0;
}