#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdlib.h>

typedef struct Matrix2d {
	double** array;
	int rows;
	int columns;
} Matrix2d;

// initialize a 2d matrix of rows x columns
Matrix2d matrix2d_init(int rows, int columns);

// create a 2d matrix which is the transpose of matrix2d
Matrix2d matrix2d_transpose(Matrix2d* matrix2d);

#endif
