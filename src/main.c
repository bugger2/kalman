#include "../include/matrix.h"

typedef struct Kalman_Filter
{
    Matrix A; // states x states; system matrix
    Matrix xhat; // states x 1; system estimate vector
    Matrix B; // states x inputs; input matrix
    // u (input vector) is left out because that is determined by a seperate controller, like PID or LQR
    Matrix C; // outputs x outputs; outputs matrix
    Matrix D; // outputs x inputs; feedthrough matrix
    Matrix P; // states x states; error covariance matrix
    Matrix K; // states x outputs; kalman gain
    Matrix Q; // states x states; process noise covariance matrix
    Matrix R; // outputs x outputs; measurement noise covariance matrix
} Kalman_Filter;

// predict our state into the future based solely on our model
void predict(Kalman_Filter* filter, Matrix* u)
{
    // x_future = Ax + Bu
    Matrix Ax = *matrix_times_matrix(&filter->A, &filter->xhat);
    Matrix Bu = *matrix_times_matrix(&filter->B, u);
    filter->xhat = *matrix_plus_matrix(&Ax, &Bu);
    matrix_free(&Ax);
    matrix_free(&Bu);

    // P_priori_future = APA^T + Q
    Matrix AP = *matrix_times_matrix(&filter->A, &filter->P);
    Matrix A_transpose = *matrix_transpose(&filter->A);
    Matrix APAt = *matrix_times_matrix(&AP, &A_transpose);
    filter->P = *matrix_plus_matrix(&APAt, &filter->Q);
    matrix_free(&AP);
    matrix_free(&APAt);
    matrix_free(&A_transpose);
}

// update our prediction by incorporating measurements
void update(Kalman_Filter* filter, Matrix* y, Matrix* u)
{
    // K_future = P_priori_future * C^T * (C * P_priori_future * C^T + R)^-1
    Matrix CPCtPlusR = matrix_plus_matrix(matrix_times_matrix(
															  matrix_times_matrix(&filter->C, &filter->P),
															  matrix_transpose(&filter->C)),
                                          &filter->R);
    Matrix PCt = matrix_times_matrix(&filter->P, matrix_transpose(&filter->C));
    
    filter->K = *matrix_times_matrix(PCt, matrix_inverse(CPCtPlusR));
    
    matrix_free(CPCtPlusR);
    matrix_free(PCt);

    // x_posteriori_future = x_priori_future + K_future * (y - C * x_priori_future - D * u_future)
	Matrix* outputError = matrix_minus_matrix(y, matrix_minus_matrix(
																	 matrix_times_matrix(&filter->C, &filter->xhat),
																	 matrix_times_matrix(&filter->D, u)
																	 ));
	filter->xhat = matrix_plus_matrix(filter->xhat, matrix_times_matrix(filter->K, outputError));
    matrix_free(outputError);

    // P_posteriori_future = (I - K_future * C) * P_priori_future
    // FIXME I'm pretty sure the dimensionality of KC as the matrix library is written now does not produce a square matrix
    Matrix* temp = matrix_minus_matrix(matrix_identity(filter->A.rows), matrix_times_matrix(&filter->K, &filter->C));
    filter->P = matrix_times_matrix(temp, &filter->P);
    matrix_free(temp);
}

int main(void)
{
    
    
    return 0;
}
