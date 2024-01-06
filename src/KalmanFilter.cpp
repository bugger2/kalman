#include "Eigen/Core"
#include "Eigen/LU"

#include "KalmanFilter.hpp"

using namespace Eigen;

KalmanFilter::KalmanFilter() {
    this->A.setZero();
    this->B.setZero();
    this->C.setZero();
    this->D.setZero();
    this->Q.setZero();
    this->R.setZero();
    this->K.setZero();
    this->P.setZero();
    this->xhat.setZero();
}

KalmanFilter::~KalmanFilter() {

}

void KalmanFilter::predict(Vector<double, INPUTS>& u) {
    // x_future = Ax + Bu
    this->xhat = this->A * this->xhat + this->B * u;

    // P_priori_future = APA^T + Q
    this->P = this->A * this->P * A.transpose() + this->Q;
}

void KalmanFilter::update(OutputVector& y, InputVector& u) {
    // K_future = P_priori_future * C^T * (C * P_priori_future * C^T + R)^-1
    this->K = this->P * this->C.transpose() * (this->C * this->P * this->C.transpose() + this->R).inverse();

    // x_posteriori_future = x_priori_future + K_future * (y - C * x_priori_future - D * u_future)
    this->xhat = this->xhat + this->K * (y - this->C * this->xhat - this->D * u);

    // P_posteriori_future = (I - K_future * C) * P_priori_future
    this->P = (Matrix<double, STATES, OUTPUTS>::Identity() - this->K * this->C) * this->P;
}
