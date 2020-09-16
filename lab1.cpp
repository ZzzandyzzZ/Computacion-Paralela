#include <bits/stdc++.h>
using namespace std;
#define MAX 1000
#define f(i,a,b) for(int i=a;i<b;i++)
int main(){
    double A[MAX][MAX],x[MAX],y[MAX];
    f(i,0,MAX){
        f(j,0,MAX){
            A[i][j]=rand()%10;
        }
    }
    f(i,0,MAX){
        x[i]=rand()%10;
    }
    auto start= chrono::system_clock::now();
    unsigned t0=clock();
    f(i,0,MAX){
        f(j,0,MAX){
            y[i]+=A[i][j]*x[j];
        }
    }
    cout<<"TIEMPO: "<<(chrono::system_clock::now()-start).count()<<endl;
    cout<<"TIEMPO: "<<clock()-t0<<endl;

    start= chrono::system_clock::now();
    t0=clock();
    for(int j=0;j<MAX;j++){
        for(int i=0;i<MAX;i++){
            y[i]+=A[i][j]*x[j];
        }
    }
    cout<<"TIEMPO: "<<(chrono::system_clock::now()-start).count()<<endl;
    cout<<"TIEMPO: "<<clock()-t0<<endl;
}
