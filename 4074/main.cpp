#include <iostream>
using namespace std;

struct SET{
    int h;
    bool flag=true;
};

int min(int a,int b,int c,int d){
    int min_num=a;
    if(b<min_num) min_num = b;
    if(c<min_num) min_num = c;
    if(d<min_num) min_num = d;
    return min_num;
}
int min_(int tmp,int a,int b,int c, int d){
    int aa[4];
    if(a==tmp) aa[0] = 10001;else aa[0]=a;
    if(b==tmp) aa[1] = 10001;else aa[1]=b;
    if(c==tmp) aa[2] = 10001;else aa[2]=c;
    if(d==tmp) aa[3] = 10001;else aa[3]=d;
    int min=10000;
    for(int i =0;i<4;i++)
        if(aa[i]<min && aa[i]>=tmp) min = aa[i];
    return min;
}



int m,n;
int main() {
    cin>>m>>n;
    SET a[m][n];
    int i,j,V=0;
    int S=1;

    for(i=0;i<m;i++){
        for(j=0;j<n;j++)
            cin>>a[i][j].h;
    }
/**
    for(i=1;i<m-1;i++){
        for(j=1;j<n-1;j++){
            if(a[i-1][j].h>a[i][j].h && a[i+1][j].h>a[i][j].h && a[i][j-1].h>a[i][j].h && a[i][j+1].h>a[i][j].h){
                V += ( min(a[i-1][j].h,a[i+1][j].h,a[i][j-1].h,a[i][j+1].h)-a[i][j].h );
                a[i][j].h = min(a[i-1][j].h,a[i+1][j].h,a[i][j-1].h,a[i][j+1].h);
                //cout<<a[i][j].h<<endl;
            }
        }
    }
**/
    a[0][0].flag = a[0][n-1].flag = a[m-1][0].flag = a[m-1][n-1].flag = false;
    for(i=1;i<n-1;i++){
        a[0][i].flag = false;
        int T=1,tmp = a[0][i].h;
        while(a[T][i].h>=tmp && T<m) {a[T][i].flag=false; tmp = a[T][i].h;T++;}
    }
    for(i=1;i<m-1;i++){
        a[i][0].flag = false;
        int T = 1,tmp = a[i][0].h;
        while(a[i][T].h>=tmp && T<n) {a[i][T].flag=false;tmp = a[i][T].h;T++;}
    }
    for(i=1;i<n;i++){
        a[m-1][i].flag =false;
        int T=m-2,tmp = a[m-1][i].h;
        while(a[T][i].h>=tmp && T>0) {a[T][i].flag=false;tmp = a[T][i].h;T--;}
    }
    for(i=1;i<m-1;i++){
        a[i][n-1].flag = false;
        int T=n-2,tmp = a[i][n-1].h;
        while(a[i][T].h>=tmp && T>0) {a[i][T].flag=false;tmp = a[i][T].h;T--;}
    }

    for(i=0;i<m;i++){
        for(j=0;j<n;j++)
            cout<<a[i][j].flag<<' ';
        cout<<endl;
    }

    for(i=1;i<m-1;i++){
        for(j=1;j<n-1;j++){
            if(!a[i][j].flag) continue;
            int min=a[i-1][j].h,L=j,R=j,H=i,k;

            int a[10000][2],ii=0;

            do{
                while(a[H][L].flag){L--;}
                if(L!=j && a[H][L].h<min) min = a[H][L].h;

                while(a[H][R].flag){R++;}
                if(R!=j && a[H][R].h<min) min = a[H][R].h;

                for(k=L+1;k<=R-1;k++){
                    int D=H,G=H;
                    while(a[D][k].flag){D--;}
                    if(D!=H && a[D][k].h<min) min = a[D][k].h;
                    while(a[G][k].flag){G++;}
                    if(G!=H && a[G][k].h<min) min= a[G][k].h;
                }

                H++;
                L=R = j;
            }while(a[H][j].flag);

            //cout<<i<<j<<' '<<min<<endl;
            L = R = j;H=i;
            do{
                do{V+=(min-a[H][L].h);
                   L--;
                }while(a[H][L].flag);
                do{V+=(min-a[H][R].h);
                   R++;
                }while(a[H][R].flag);
                V -= (min-a[H][j].h);

                for(k=L+1;k<=R-1;k++){
                    int D=H-1,G=H+1;
                    while(a[D][k].flag){V+=(min-a[D][k].h);D--;}
                    while(a[G][k].flag){V+=(min-a[G][k].h);G++;}
                }

                H++;
                L=R=j;
            }while(a[H][j].flag);
            cout<<"V="<<V<<endl;
            /**if(a[i-1][j].h==a[i][j].h || a[i+1][j].h==a[i][j].h || a[i][j-1].h==a[i][j].h || a[i][j+1].h==a[i][j].h){
                int L=j,R=j,H=i,D=i;

                if(!a[i][j].flag) continue;

                bool flagg=true;
                while(a[i][L].h<=a[i][j].h && L!=0) {if(!a[i][L].flag) flagg=false; L--;}
                if(!flagg || (L==0 && a[i][0].h<=a[i][j].h)) {a[i][j].flag=false;continue;}

                while(a[i][R].h<=a[i][j].h && R!=n-1) {if(!a[i][R].flag) flagg=false;R++;}
                if(!flagg || (R==n-1 && a[i][n-1].h<=a[i][j].h)) {a[i][j].flag=false;continue;}

                while(a[H][j].h<=a[i][j].h && H!=0) {if(!a[H][j].flag) flagg=false;H--;}
                if(!flagg || (H==0 && a[0][j].h<=a[i][j].h)) {a[i][j].flag=false;continue;}

                while(a[D][j].h<=a[i][j].h && D!=m-1) {if(!a[D][j].flag) flagg=false;D++;}
                if(!flagg || (D==m-1 && a[m-1][j].h<=a[i][j].h)) {a[i][j].flag=false;continue;}


                int HIGHT=10000,k;
                for(k=L+1;k<R;k++)
                    if(min_(a[i][j].h,a[i][k-1].h,a[i][k+1].h,a[i-1][k].h,a[i+1][k].h) < HIGHT)
                        HIGHT = min_(a[i][j].h,a[i][k-1].h,a[i][k+1].h,a[i-1][k].h,a[i+1][k].h);
                for(k=H+1;k<D;k++)
                    if(min_(a[i][j].h,a[k-1][j].h,a[k+1][j].h,a[k][j-1].h,a[k][j+1].h) < HIGHT)
                        HIGHT = min_(a[i][j].h,a[k-1][j].h,a[k+1][j].h,a[k][j-1].h,a[k][j+1].h);

                 cout<<i<<' '<<j<<endl;
                for(k=L+1;k<R;k++) {V+= (HIGHT-a[i][k].h);a[i][k].h = HIGHT;a[i][k].flag=false;}
                for(k=H+1;k<D;k++) {V+= (HIGHT-a[k][j].h);a[k][j].h = HIGHT;a[k][j].flag=false;}
                cout<<"V="<<V<<endl;

            }
             **/
        }
    }
    cout<<V;

    return 0;
}
