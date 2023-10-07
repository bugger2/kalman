#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

Matrix matrix_init(size_t rows, size_t columns)
{
	Matrix ret = {
		.array = (double**)malloc(rows * sizeof(double*)),
		.rows = rows,
		.columns = columns
	};

	// initialize the columns
	for(size_t i = 0; i < rows; i++)
	{
		ret.array[i] = (double*)malloc(columns * sizeof(double));
	}

	// make all entries equal to 0
	for(size_t i = 0; i < rows; i++)
	{
		for(size_t j = 0; i < columns; j++)
			ret.array[i][j] = 0;
	}

	return ret;
}

Matrix matrix_transpose(Matrix* matrix)
{
	Matrix ret = matrix_init(matrix->columns, matrix->rows);

	for(size_t i = 0; i < matrix->rows; i++)
	{
		for(size_t j = 0; j < matrix->columns; j++)
			ret.array[j][i] = matrix->array[i][j];
	}

	return ret;
}

Matrix matrix_times_matrix(Matrix* mat1, Matrix* mat2)
{
	// [m x n] * [n x p] = [m x p]. Will fail if n1 != n2.
	// Basically, because of math, the amount of columns in the left matrix must be equal to the amount of rows in the right matrix
	assert(mat1->columns == mat2->rows);

	Matrix ret = matrix_init(mat1->rows, mat2->columns);

	for(size_t i = 0; i < mat1->rows; i++)
	{
		for(size_t j = 0; j < mat2->columns; j++)
		{
			double result = 0;
			for(size_t k = 0; k < mat1->columns /* mat2->rows */; k++)
			{
				result += mat1->array[i][k] * mat2->array[k][j];
			}
			ret.array[i][j] = result;
		}
	}

	return ret;
}

Matrix matrix_multiply_scalar(Matrix* matrix, double scalar)
{
	Matrix ret = matrix_init(matrix->rows, matrix->columns);
	for(size_t i = 0; i < matrix->rows; i++)
	{
		for(size_t j = 0; j < matrix->columns; j++)
		{
			ret.array[i][j] *= scalar;
		}
	}

	return ret;
}

Matrix matrix_plus_matrix(Matrix* mat1, Matrix* mat2)
{
	// matrices must be of equal dimensions
	assert(mat1->rows == mat2->rows && mat1->columns == mat2->columns);
	
	Matrix ret = matrix_init(mat1->rows, mat1->columns);

	for(size_t i = 0; i < mat1->rows; i++)
	{
		for(size_t j = 0; j < mat2->columns; j++)
		{
			ret.array[i][j] = mat1->array[i][j] + mat2->array[i][j];
		}
	}

	return ret;
}

Matrix matrix_plus_scalar(Matrix* matrix, double scalar)
{
	Matrix ret = matrix_init(matrix->rows, matrix->columns);

	for(size_t i = 0; i < matrix->rows; i++)
	{
		for(size_t j = 0; j < matrix->columns; j++)
		{
			matrix->array[i][j] = scalar;
		}
	}

	return ret;
}

// compute the determinant of a square matrix with laplace expansion
double matrix_determinant(Matrix* matrix)
{
	// this probably doesn't make much sense on it's own, and I would be writing
	// more comments than code if I tried to explain it. I suggest reading the
	// following for a good understanding
	// https://en.wikipedia.org/wiki/Laplace_expansion

	// this only works with square matrices
	assert(matrix->rows == matrix->columns);

	double ret = 0;

	for(size_t i = 0; i < matrix->columns; i++)
	{
		Matrix temp_determ = matrix_init(matrix->rows - 1, matrix->columns - 1);
		// initialization of temp_determ
		for(size_t j = 0; j < temp_determ.rows; j++)
		{
			// used to skip over the column from the matrix passed to the function that goes unused
			int offset = 0;
			for(size_t k = 0; k < temp_determ.columns; k++)
			{
				if(k != i) {
					temp_determ.array[j][k] = matrix->array[j+1][k+offset];
				} else {
					offset = 1;
				}
			}
		}

		ret += powf(-1, i) * matrix->array[0][i] * matrix_determinant(&temp_determ);
	}

	return ret;
}

// get the inverse of a matrix
Matrix matrix_inverse(Matrix* matrix)
{
	// FIXME: this function is not finished

	// this only works with square matrices
	assert(matrix->rows == matrix->columns);

	Matrix ret = matrix_init(matrix->columns, matrix->rows);

	return ret;
}

void matrix_free(Matrix* matrix)
{
	for(size_t i = 0; i < matrix->rows; i++)
	{
		free(matrix->array[i]);
	}
	free(matrix->array);
}
