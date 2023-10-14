cmake_minimum_required(VERSION 3.0)
project(3D_model)

add_executable(${PROJECT_NAME} Tree/main.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)