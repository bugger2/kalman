#ifndef _KALMAN_H
#define _KALMAN_H

#include "model.h"

typedef struct Kalman {
	Model* system; // system to estimate
	double** K; // kalman gain matrix
	double** P; // error covariance matrix
	double** Q; // process noise covariance matrix
	double** R; // measurement noise covariance matrix
} Kalman;

// update our a priori estimation of x and increase P
void kalman_predict(Kalman* kalman);

// respond to how the measurements have impacted our estimate
void kalman_update(Kalman* kalman);

#endif
