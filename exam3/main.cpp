#include <iostream>
using namespace std;

//直接插入排序
template <class KEY,class OTHER>
struct SET{
    KEY key;
    OTHER other;
};
template <class KEY,class OTHER>
void simpleInsertSort(SET<KEY,OTHER>a[],int size)
{
    int k;
    SET<KEY,OTHER> tmp;

    for(int j=1;j<size;j++){
        tmp=a[j];
        for(k=j-1;tmp.key<a[k].key && k>=0;--k)
            a[k+1] = a[k];
        a[k+1]=tmp;
    }
}

//希尔排序
template <class KEY,class OTHER>
void shellSort(SET<KEY,OTHER> a[],int size){
    int step,i,j;
    SET<KEY,OTHER> tmp;

    for(step=size/2;step>0;step/=2)  //shell为希尔增量
        for(i=step;i<size;++i){  //对相距为step的元素序列采用直接插入排序
            tmp=a[i];
            for(j=i-step;j>=0 && a[j].key>tmp;j-=step)
                a[j+step]=a[j];
            a[j+step]=tmp;
        }
}

//归并
template <class KEY,class OTHER>
void merge(SET<KEY,OTHER> a[],int left,int mid,int right){
    SET<KEY,OTHER> *tmp=new SET<KEY,OTHER>[right-left+1];

    int i=left,j=mid,k=0;
    while(i<mid && j<=right)
        if(a[i].key<a[j].key) tmp[k++]=a[i++];
        else tmp[k++] = a[j++];

        while(i<mid) tmp[k++] = a[i++];
        while(j<=right) tmp[k++] = a[j++];

        for(i=0,k=left;k<=right;) a[k++]=tmp[i++];
        delete []tmp;
}
template <class KEY,class OTHER>
void mergeSort(SET<KEY,OTHER>a[],int left,int right){
    int mid = (left+right)/2;

    if(left==right) return;
    mergeSort(a,left,mid);
    mergeSort(a,mid+1,right);
    merge(a,left,mid+1,right);
}

//快速排序
template <class KEY,class OTHER>
void quickSort(SET<KEY,OTHER>a[],int low,int high){
    int mid;
    if(low>=high) return;
    mid = divide(a,low,high);
    quickSort(a,low,mid-1);
    quickSort(a,mid+1,high);
}
template <class KEY,class OTHER>
void quickSort(SET<KEY,OTHER>a[],int size){
    quickSort(a,0,size-1);
}
template <class KEY,class OTHER>
int divide(SET<KEY,OTHER>a[],int low,int high){
    SET<KEY,OTHER> k =a[low];
    do{
        while(low<high && a[high].key>=k.key) --high;
        if(low<high){a[low]=a[high];++low;}

        while(low<high && a[low].key<=k.key) ++low;
        if(low<high) {a[high]=a[low];--high;}
    }while(low!=high);
    a[low] =k;
    return low;
}

//基数排序
template <class OTHER>
struct node{
        SET<int,OTHER> data;
        node *next;
        node(){next=nullptr;}
        node(SET<int,OTHER> d):data(d){next=nullptr;}
    };
template <class OTHER>
void bucketSort(node<OTHER> *&p)
{
    node<OTHER> *bucket[10],*last[10],*tail;
    int i,j,k,base=1,max=0,len=0;

    for(tail=p;tail!=nullptr;tail=tail->next)
        if(tail->data.key>max) max = tail->data.key;


    if(max==0) len=0;
    else while(max>0){++len;max/=10;}

    for(i=1;i<len;++i){
        for(j=0;j<=9;++j) bucket[j]=last[j]=nullptr;
        while(p!=nullptr){
            k=p->data.key/base % 10;
            if(bucket[k]==nullptr) bucket[k]=last[k]=p;
            else last[k]=last[k]->next=p;
            p=p->next;
        }

        p=nullptr;
        for(j=0;j<=9;++j){
            if(bucket[j]==nullptr) continue;
            if(p==nullptr) p = bucket[j];
            else tail->next=bucket[j];
            tail = last[j];
        }
        tail->next = nullptr;
        base*=10;
    }
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}