#ifndef MATRICES_H
#define MATRICES_H

void init_matrix(double* matrix, int dim_one, int dim_two);
void print_matrix(double* matrix, int dim_one, int dim_two);
void matrices_mult(double* matrix_one, double* matrix_two, double* result,
						int dim_one, int dim_mid, int dim_two,
						int thread_num, int total_treads);

#endif