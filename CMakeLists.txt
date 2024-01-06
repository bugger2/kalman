cmake_minimum_required(VERSION 3.9)
project(kalman)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(${PROJECT_NAME} src/main.cpp src/KalmanFilter.cpp)
target_link_libraries(${PROJECT_NAME} Eigen3::Eigen)
