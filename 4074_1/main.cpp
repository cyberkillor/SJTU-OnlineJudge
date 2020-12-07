#include <iostream>
using namespace std;

struct cell
{
    int row;
    int col;
    int height;
};

//最小化堆
class priority_queue{
    private:
        int current_size;
        cell array[10010];

        //void build_heap();
    public:
        void percolate_down(int hole);
        priority_queue(){current_size=0;}
        ~priority_queue(){}
        bool is_empty();
        void en_queue(cell x);
        cell de_queue();
        cell get_head();
        int length(){return current_size;}
};

bool priority_queue::is_empty(){
    return current_size==0;
}

cell priority_queue::get_head(){
    return array[1];
}

void priority_queue::en_queue(cell x){
    //if(current_size==max_size-1)doublespace();

    //œÚ…œπ˝¬À
    int hole=current_size+1;
    for(;hole>1&&x.height<array[hole/2].height;hole/=2){
        array[hole].col=array[hole/2].col;
        array[hole].height=array[hole/2].height;
        array[hole].row=array[hole/2].row;
    }
    array[hole].col=x.col;
    array[hole].height=x.height;
    array[hole].row=x.row;
    current_size++;
}

cell priority_queue::de_queue(){
    cell min_item;
    min_item=array[1];
    array[1]=array[current_size--];
    percolate_down(1);
    return min_item;
}

void priority_queue::percolate_down(int hole){
    int child;
    cell tmp;
    tmp.row=array[hole].row;
    tmp.col=array[hole].col;
    tmp.height=array[hole].height;

    for(;hole*2<=current_size;hole=child)
    {
        child=hole*2;
        if(child!=current_size&&array[child+1].height<array[child].height)child++;
        if(array[child].height<tmp.height)
        {
            array[hole].col=array[child].col;
            array[hole].row=array[child].row;
            array[hole].height=array[child].height;
        }
        else break;
    }
    array[hole].col=tmp.col;
    array[hole].row=tmp.row;
    array[hole].height=tmp.height;
}

/*void priority_queue::build_heap(){
    for(int i=current_size/2;i>0;i--){
        percolate_down(i);
    }
}*/


/*priority_queue<T>::priority_queue(T data[],int size){
    array=new T[];
    for(i=0;i<size;i++){
        array[i+1]=data[i];
    }
    build_heap();
}*/

/*template <class T>
void priority_queue<T>::doublespace(){
    T *tmp=array;
    max_size*=2;
    array=new T[max_size];
    for(int i=0;i<=current_size;i++){
        array[i]=tmp[i];
    }
    delete []tmp;
}*/

priority_queue queue;
int height[101][101];
bool v[101][101];

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n,m;
    cin>>m>>n;
    cell c;
    int ans=0;

    //方向
    int dy[]={-1,1,0,0};
    int dx[]={0,0,-1,1};

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>height[i][j];
            v[i][j]=false;
        }
    }

    //边界入列
    for(int i=0;i<m;i++)
    {
        v[i][0]=true;
        v[i][n-1]=true;
        c.row=i;
        c.col=0;
        c.height=height[i][0];
        queue.en_queue(c);
        c.col=n-1;
        c.height=height[i][n-1];
        queue.en_queue(c);
    }
    for(int i=0;i<n;i++)
    {
        v[0][i]=true;
        v[m-1][i]=true;
        c.col=i;
        c.row=0;
        c.height=height[0][i];
        queue.en_queue(c);
        c.row=m-1;
        c.height=height[m-1][i];
        queue.en_queue(c);
    }

    //cout<<queue.length()<<endl;

    while(!queue.is_empty())
    {
        cell x=queue.de_queue();
        //cout<<x.col<<' '<<x.row<<' '<<x.height<<endl;
        for(int i=0;i<4;i++)
        {
            int row=x.row+dy[i];
            int col=x.col+dx[i];
            if(row>=0&&row<m&&col>=0&&col<n&&!v[row][col])
                {
                    v[row][col]=true;
                    ans+=max(0,x.height-height[row][col]);
                    cell y;
                    y.row=row;
                    y.col=col;
                    y.height=max(x.height,height[row][col]);
                    queue.en_queue(y);
                }
            }
        }
        cout<<ans;
    return 0;
}