#include <bits/stdc++.h>
using namespace std;
#define MAX 200
#define f(i,a,b) for(int i=a;i<b;i++)
#define F(i,a,b,c) for(int i=a;i<b;i+=c)
void show(double A[MAX][MAX]){
	f(i,0,MAX){
    	f(j,0,MAX){
    		cout<<A[i][j]<<" ";
    	}
    	cout<<endl;
    }
    cout<<endl;
}
void matrix_multiply(double A[MAX][MAX],double B[MAX][MAX]){
	double C[MAX][MAX];
	f(i,0,MAX){
		f(j,0,MAX){ 
			C[i][j]=0;
         	f(k,0,MAX){
         		C[i][j]=C[i][j]+A[i][k]*B[k][j];
            }
        }
    }
}
void block_multiply(double A[MAX][MAX],double B[MAX][MAX],int b_size){
	double C[MAX][MAX];
	F(i0,0,MAX,b_size)
		F(j0,0,MAX,b_size)
			F(k0,0,MAX,b_size)
				f(i,i0,min(i0+b_size,MAX))
			      	f(j,j0,min(j0+b_size,MAX))
			      		f(k,k0,min(k0+b_size,MAX))
			      			C[i][j]+=(A[i][k]*B[k][j]);
}

int main(){
    double A[MAX][MAX],B[MAX][MAX],x[MAX],y[MAX];
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
    /*
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


    f(i,0,MAX){
        f(j,0,MAX){
            B[i][j]=rand()%10;
        }
    }
    */
    start= chrono::system_clock::now();
    t0=clock();
    matrix_multiply(A,B);
    cout<<"TIEMPO: "<<(chrono::system_clock::now()-start).count()<<endl;
    cout<<"TIEMPO: "<<clock()-t0<<endl;
    start= chrono::system_clock::now();
    t0=clock();
    block_multiply(A,B,80);
    cout<<"TIEMPO: "<<(chrono::system_clock::now()-start).count()<<endl;
    cout<<"TIEMPO: "<<clock()-t0<<endl;
}

