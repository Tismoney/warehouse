#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrices.h"
#include "synchronize.h"
#include "get_time.h"

#define ERROR(str, n) \
	{\
		fprintf(stderr, str);\
		return n;\
	}

#define MALLOC(name, type, n, m) \
	if(!(name = (type*) malloc(n * sizeof(type)) )) \
		ERROR("Not enough memory!", m)

typedef struct _ARGS
{
	double* matrix_one;
	double* matrix_two;
	double* result;
	int dim_one;
	int dim_mid;
	int dim_two;
	int thread_num;
	int total_treads;
}ARGS;

static long int thread_total_time = 0;
static pthread_mutex_t thread_total_time_mutex = PTHREAD_MUTEX_INITIALIZER;

void* matrices_mult_threaded(void *pa)
{
	ARGS *pargs = (ARGS*)pa;
	long int time_wall;
	int i;

	printf("Thread %d started\n", pargs->thread_num);
	time_wall = get_time();
	matrices_mult(pargs->matrix_one, pargs->matrix_two, pargs->result,
					pargs->dim_one, pargs->dim_mid, pargs->dim_two,
					pargs->thread_num, pargs->total_treads);
	time_wall = get_time() - time_wall;

	pthread_mutex_lock(&thread_total_time_mutex);
	thread_total_time += time_wall;
	pthread_mutex_unlock(&thread_total_time_mutex);

	printf("Thread %d finished, time = %ld\n", pargs->thread_num, time_wall);

	return 0;
}

int main()
{
	pthread_t* threads;
	ARGS* args;
	int nthreads;
	long int t_full;

	double* matrix_one;
	double* matrix_two;
	double* result;
	int dim_one;
	int dim_mid, dim_mid_tmp;
	int dim_two;
	int i;

	printf("Input threads number: ");
	scanf("%d", &nthreads);
	MALLOC(threads, pthread_t, nthreads, 1)
	MALLOC(args, ARGS, nthreads, 2)

	printf("Input dim of first matrix (dim1, dim2): ");
	scanf("%d %d", &dim_one, &dim_mid);
	printf("Input dim of second matrix (dim1, dim2): ");
	scanf("%d %d", &dim_mid_tmp, &dim_two);
	if(dim_mid != dim_mid_tmp)
		ERROR("Cannot multiplicate matrices", 3)

	MALLOC(matrix_one, double, dim_one * dim_mid, 4)
	MALLOC(matrix_two, double, dim_two * dim_mid, 5)
	MALLOC(result, double, dim_one * dim_two, 6)

	init_matrix(matrix_one, dim_one, dim_mid);
	init_matrix(matrix_two, dim_mid, dim_two);
	printf("Matrix one:\n");
	print_matrix(matrix_one, dim_one, dim_mid);
	printf("Matrix two:\n");
	print_matrix(matrix_two, dim_mid, dim_two);

	for(i = 0; i < nthreads; i++)
	{
		args[i].matrix_one = matrix_one;
		args[i].matrix_two = matrix_two;
		args[i].result = result;
		args[i].dim_one = dim_one;
		args[i].dim_mid = dim_mid;
		args[i].dim_two = dim_two;
		args[i].thread_num = i;
		args[i].total_treads = nthreads;
	}

	t_full = get_full_time();
	for(i = 0; i < nthreads; i++)
	{
		if(pthread_create(threads + i, 0, matrices_mult_threaded, args + i))
		{
			fprintf(stderr, "Cannot create pthread #%d!\n", i);
			return 7;
		}	
	}
	printf("I`m here\n");
	for(i = 0; i < nthreads; i++)
	{
		if(pthread_join(threads[i], 0))
			fprintf(stderr, "Cannot wait thread #%d!\n", i);
	}

	t_full = get_full_time() - t_full;
	if(t_full == 0)
		t_full = 1;

	print_matrix(result, dim_one, dim_two);

	free(threads);
	free(args);
	free(matrix_one);
	free(matrix_two);
	free(result);

	printf("Total full time = %ld, total treads time = %ld (%ld%%), per thread = %ld\n",
			t_full, thread_total_time, (thread_total_time * 100) / t_full,
			thread_total_time / nthreads);

	return 0;
}