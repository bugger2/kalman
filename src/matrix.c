#include "matrix.h"

Matrix2d matrix2d_init(int rows, int columns) {
	Matrix2d ret = {
		.array = (double**)malloc(rows * sizeof(double*)),
		.rows = rows,
		.columns = columns
	};

	// initialize the columns
	for(int i = 0; i < rows; i++) {
		ret.array[i] = (double*)malloc(columns * sizeof(double));
	}

	// make all entries equal to 0
	for(int i = 0; i < rows; i++) {
		for(int j = 0; i < columns; j++)
			ret.array[i][j] = 0;
	}

	return ret;
}

Matrix2d matrix2d_transpose(Matrix2d* matrix2d) {
	Matrix2d ret = matrix2d_init(matrix2d->columns, matrix2d->rows);

	for(int i = 0; i < matrix2d->rows; i++) {
		for(int j = 0; j < matrix2d->columns; j++)
			ret.array[j][i] = matrix2d->array[i][j];
	}

	return ret;
}
