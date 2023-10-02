#ifndef _MATRIX_H
#define _MATRIX_H

typedef struct
{
	double** array;
	size_t rows;
	size_t columns;
} Matrix;

/* Matrix Functions */

// initialize a 2d matrix of rows x columns
Matrix matrix_init(size_t rows, size_t columns);

// create a 2d matrix which is the transpose of matrix
Matrix matrix_transpose(Matrix* matrix);

// find the dot product of two matrices
Matrix matrix_times_matrix(Matrix* mat1, Matrix* mat2);

// find the dot product of a matrix and a scalar
Matrix matrix_times_scalar(Matrix* matrix, double scalar);

// get the sum of two matrices
Matrix matrix_add_matrix(Matrix* mat1, Matrix* mat2);

// get the sum of a matrix and a scalar value
Matrix matrix_add_scalar(Matrix* matrix, double scalar);

void matrix_free(Matrix* matrix);

#endif
