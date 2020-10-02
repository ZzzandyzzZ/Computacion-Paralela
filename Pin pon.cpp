// Pin pon.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include <iostream>

#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define f(i,a,b) for(int i=a;i<b;i++)
using namespace std;
const int MAX_STRING = 100;
/*
int main() {
	int comm_sz;
	int my_rank;
	int ball=0;
	int MAX = 8;
	int other;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	other = my_rank ^ 1;
	if (my_rank == 0) {
		printf("Proceso %d lanzo la pelota %d hacia proceso: %d\n", my_rank, ball, other);
		MPI_Send(&ball, 1, MPI_INT, other, 0, MPI_COMM_WORLD);
	}
	cout << "" << endl;
	while (ball<MAX) {
		MPI_Recv(&ball, 1, MPI_INT, other, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Proceso %d recibio la pelota %d de proceso %d\n", my_rank, ball, other);
		ball++;
		printf("Proceso %d lanzo la pelota %d hacia proceso: %d\n", my_rank, ball, other);
		MPI_Send(&ball, 1, MPI_INT, other, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
*/
/*
int main() {
	int comm_sz;
	int my_rank;
	int ball = 0;
	int MAX = 8;
	int other;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	other = my_rank ^ 1;
	for (int i = 0; i < MAX; i++) {
		if (my_rank == i % 2) {
			ball++;
			printf("Proceso %d lanzo la pelota %d hacia proceso: %d\n", my_rank, ball, other);
			MPI_Send(&ball, 1, MPI_INT, other, 0, MPI_COMM_WORLD);
		}
		else {
			MPI_Recv(&ball, 1, MPI_INT, other, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Proceso %d recibio la pelota %d de proceso %d\n", my_rank, ball, other);
		}	
	}
	MPI_Finalize();
	return 0;
}
*/
/*
double f(double x) {
	return x * x;
}
double Trap(double left_endpt ,double right_endpt ,int trap_count ,double base_len ) {
	double estimate, x;
	int i;
	estimate = (f(left_endpt) + f(right_endpt)) / 2.0;
	for (i = 1; i <= trap_count-1; i++) {
		x = left_endpt + i* base_len;
		estimate += f(x);
	}
	estimate = estimate*base_len;
	return estimate;} *//*
int main(void) {
	int my_rank, comm_sz, n = 1024, local_n;
	double a = 0.0, b = 3.0, h, local_a, local_b;
	double local_int, total_int;
	int source;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	h = (b-a) / n; 
	local_n = n / comm_sz; 
	local_a = a + my_rank*local_n*h;
	local_b = local_a + local_n*h;
	local_int = Trap(local_a, local_b, local_n, h);
	printf("Proceso %d calculo de %f hasta %f con area de : %d\n", my_rank, local_a, local_b,local_int);
	if (my_rank != 0) {
		MPI_Send(&local_int, 1, MPI_DOUBLE, 0, 0,MPI_COMM_WORLD);
		
	}
	else {
		total_int = local_int;
		for (source = 1; source < comm_sz; source++) {
			MPI_Recv(&local_int, 1, MPI_DOUBLE, source, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			total_int += local_int;
		}
		
	}
	if (my_rank == 0) {
		printf("With n = %d trapezoids, our estimate\n", n);
		printf("of the integral from %f to %f = %.15e\n",a, b, total_int);
	}
	MPI_Finalize();
	return 0;
}*/
/*
int main(void) {
	int my_rank, comm_sz, n = 1024, local_n;
	double a = 0.0, b = 3.0, h, local_a, local_b;
	double local_int, total_int;
	int source;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	h = (b - a) / n;
	local_n = n / comm_sz;
	local_a = a + my_rank * local_n*h;
	local_b = local_a + local_n * h;
	local_int = Trap(local_a, local_b, local_n, h);
	printf("Proceso %d calculo de %f hasta %f con area de : %d\n", my_rank, local_a, local_b, local_int);
	
	MPI_Reduce(&local_int,&total_int,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	if (my_rank == 0) {
		printf("With n = %d trapezoids, our estimate\n", n);
		printf("of the integral from %f to %f = %.15e\n", a, b, total_int);
	}
	MPI_Finalize();
	return 0;
}
*/
/*
void Mat vect mult(
	 double local A[] / ∗ in ∗ / ,
	 double local x[] / ∗ in ∗ / ,
	 double local y[] / ∗ out ∗ / ,
	 int local m / ∗ in ∗ / ,
	 int n / ∗ in ∗ / ,
	 int local n / ∗ in ∗ / ,
	 MPI Comm comm / ∗ in ∗ / ) {
	 double*x;
	 int local i, j;
	 int local ok = 1;
	 x = malloc(n∗sizeof(double));
	 MPI Allgather(local x, local n, MPI DOUBLE,
		 x, local n, MPI DOUBLE, comm);
		 for (local i = 0; local i < local m; local i++) {
		 local y[local i] = 0.0;
		 for (j = 0; j < n; j++)
			 local y[local i] += local A[local i∗n + j]∗x[j];
	}
	 free(x);
}
void Build_mpi_type(
	double* a_p / ∗ in ∗ / ,
	double* b_p / ∗ in ∗ / ,
	int* n_p / ∗ in ∗ / ,
	MPI_Datatype* input_mpi_t_p / ∗ out ∗ / ) {
	int array_of_blocklengths[3] = { 1, 1, 1 };
	MPI Datatype array of types[3] = { MPI DOUBLE, MPI DOUBLE, MPI INT };
	MPI Aint a addr, b addr, n addr;
	MPI Aint array of displacements[3] = { 0 };
	MPI Get address(a p, &a addr);
	MPI Get address(b p, &b addr);
	MPI Get address(n p, &n addr);
	array of displacements[1] = b addr−a addr;
	array of displacements[2] = n addr−a addr;
	MPI Type create struct(3, array of blocklengths,
		array of displacements, array of types,
		input mpi t p);
	MPI Type commit(input mpi t p);
} / ∗ Build mpi type ∗ /
void Get input(int my rank, int comm_sz, double* a_p, double* b_p,
	int∗ n_p) {
	MPI_Datatype_input_mpi_t;
	Build_mpi_type(a_p, b_p, n_p, &input_mpi_t);
	if (my rank == 0) {
		printf("Enter a, b, and n\n");
		scanf("%lf %lf %d", a p, b p, n p);
	}
	MPI_Bcast(a p, 1, input_mpi t, 0, MPI_COMM_WORLD);
	MPI_Type_free(&input mpi t);
}
*/
# define MAX 250
double total_time;
void show_vector(double A[MAX]) {

	f(i, 0, MAX) {
		cout << A[i] << " ";
	}
	cout << endl;
	
}
void show_matrix(double A[MAX][MAX]) {
	f(i, 0, MAX) {
		f(j, 0, MAX) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void Mutiply(const int dim, double *matrix_data, double *vector_data, double *result) {
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	double *localresult = new double[dim / size];
	double matrix[MAX][MAX];
	double timer = MPI_Wtime();
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Scatter(matrix_data, (dim*dim) / size, MPI_DOUBLE, matrix, (dim*dim) / size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(vector_data, dim, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	for (int i = 0; i < (dim / size); i++) {
	localresult[i] = 0.0;
		for (int j = 0; j < dim; j++)
			localresult[i] += vector_data[j] * matrix[i][j];
	}
	//printf("Local Result de %d:\n",rank);
	//show_vector(localresult);
	MPI_Gather(localresult, (dim) / size, MPI_DOUBLE, result, (dim) / size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	double local_time = MPI_Wtime() - timer;
	MPI_Reduce(&local_time, &total_time, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	timer = MPI_Wtime() - timer;
	//printf("Tiempo ejecucion de proceso %d= %f\n", rank, timer);
}
int main(int argc, char *argv[]) {
	int rank, size;                   
	MPI_Init(NULL,NULL);              
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	double matrix_data[MAX][MAX]; 
	double vector_data[MAX];       
	double result[MAX] = { 0.0 };
	if (rank == 0) {
		f(i, 0, MAX)
			f(j, 0, MAX) 
				matrix_data[i][j] = rand() % 10;
		f(i, 0, MAX) 
			vector_data[i] = rand() % 10;           
	}
	Mutiply(MAX, (double *)matrix_data, vector_data, result);

	if (rank == 0) {
		/*
		printf("Matrix  :\n");
		show_matrix(matrix_data);
		printf("Vector :\n");
		show_vector(vector_data);
		printf("Result :\n");
		show_vector(result);
		*/
		cout << "Size: " << MAX << endl;
		printf("Tiempo total:%f\n", total_time);
	}
	MPI_Finalize();
	return(0);
}

