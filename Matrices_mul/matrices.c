#include <stdio.h>
#include "matrices.h"
#include "synchronize.h"

#define N_MAX 10
#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)

void init_matrix(double* matrix, int dim_one, int dim_two)
{
	int i, j;

	for(i = 0; i < dim_one; i++)
		for(j = 0; j < dim_two; j++)
			*(matrix++) = (i > j) ? i : j;
}

void print_matrix(double* matrix, int dim_one, int dim_two)
{
	int i, j;
	int m = MIN(MIN(dim_one, dim_two), N_MAX);

	for(i = 0; i < m; i++)
	{
		printf("|");
		for(j = 0; j < m; j++)
			printf("%12.2lf", matrix[i * dim_one + j]);
		printf("|");
		printf("\n");
	}	
}

void matrices_mult(double* matrix_one, double* matrix_two, double* result,
						int dim_one, int dim_mid, int dim_two,
						int thread_num, int total_treads)
{
	int i, j, k, m;
	double *pc;
	int first_row, last_row, len;

	first_row = dim_one * thread_num / total_treads;
	last_row  = dim_one * (thread_num + 1) / total_treads - 1;

	len = (last_row - first_row + 1) * dim_one;
	pc = result + first_row * dim_one;
	for(m = 0; m < len; m++)
	{
		*pc = 0.;
		i = first_row + (int)(m / dim_two);
		k = m - (int)(m / dim_two) * dim_two; 
		for(j = 0; j < dim_mid; j++)
			*pc += matrix_one[i * dim_one + j] * matrix_two[j*dim_two + k];
		pc++;
	}
	synchronize(total_treads);
}