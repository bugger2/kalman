#ifndef KALMAN_FILTER_HPP
#define KALMAN_FILTER_HPP

#include "Eigen/Core"

#define STATES 2
#define INPUTS 1
#define OUTPUTS 2

#define StateMatrix Eigen::Matrix<double, STATES, STATES>
#define StateVector Eigen::Vector<double, STATES>
#define OutputMatrix Eigen::Matrix<double, OUTPUTS, OUTPUTS>
#define OutputVector Eigen::Vector<double, OUTPUTS>
#define InputMatrix Eigen::Matrix<double, STATES, INPUTS>
#define InputVector Eigen::Vector<double, INPUTS>

class KalmanFilter {
public:
    KalmanFilter();
    ~KalmanFilter();
    
    StateMatrix A; // states x states; system matrix
    StateVector xhat; // states x 1; system estimate vector
    InputMatrix B; // states x inputs; input matrix
    // u (input vector) is left out because that is determined by a seperate controller, like PID or LQR
    OutputMatrix C; // outputs x outputs; outputs matrix
    Eigen::Matrix<double, OUTPUTS, INPUTS> D; // outputs x inputs; feedthrough matrix
    Eigen::Matrix<double, STATES, STATES> P; // states x states; error covariance matrix
    Eigen::Matrix<double, STATES, OUTPUTS> K; // states x outputs; kalman gain
    Eigen::Matrix<double, STATES, STATES> Q; // states x states; process noise covariance matrix
    Eigen::Matrix<double, OUTPUTS, OUTPUTS> R; // outputs x outputs; measurement noise covariance matrix

    void predict(InputVector& u);
    void update(OutputVector& y, InputVector& u);
};

#endif
