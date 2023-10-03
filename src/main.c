#include "matrix.h"

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
	Matrix Ax = matrix_times_matrix(&filter->A, &filter->xhat);
	Matrix Bu = matrix_times_matrix(&filter->B, u);
	filter->xhat = matrix_plus_matrix(&Ax, &Bu);
	matrix_free(&Ax);
	matrix_free(&Bu);

	// P_priori_future = APA^T + Q
	Matrix AP = matrix_times_matrix(&filter->A, &filter->P);
	Matrix A_tranpose = matrix_transpose(&filter->A);
	Matrix APAT = matrix_times_matrix(&AP, &A_tranpose);
	filter->P = matrix_plus_matrix(&APAT, &filter->Q);
	matrix_free(&AP);
	matrix_free(&APAT);
}

// update our prediction by incorporating measurements
void update(Kalman_Filter* filter, Matrix* y, Matrix* u)
{
	// K_future = P_priori_future * C^T * (C * P_priori_future * C^T + R)^-1

	// x_posteriori_future = x_priori_future + K_future * (y - C * x_priori_future - D * u_future)

	// P_posteriori_future = (I - K_future * C) * P_priori_future
}

int main(void)
{
	
	
	return 0;
}
