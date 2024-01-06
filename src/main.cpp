#include "KalmanFilter.hpp"

int main(void) {
    InputVector u;
    u.setZero();

    OutputVector y;
    y.setZero();
    
    KalmanFilter filter;

    filter.predict(u);
    filter.update(y, u);

    return 0;
}
