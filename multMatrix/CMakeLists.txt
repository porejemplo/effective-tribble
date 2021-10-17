cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (multMatrix)

add_executable (multMatrix main_multMatrix.cpp multmatrix.cpp multmatrix.h)

project (mainClienteMulMatrix LANGUAGES CXX)
add_executable(mainClienteMulMatrix mainClienteMulMatrix.cpp mulmatrix_stub.h multmatrix_stub.cpp mulmatrix.h mulmatrix.cpp utils.h utils.cpp)

target_link_libraries(mainClienteMulMatrix pthread)

project (mainServidorMulMatrix LANGUAGES CXX)
add_executable(mainServidorMulMatrix mainServidorMulMatrix.cpp mulmatrix_imp.h multmatrix_imp.cpp mulmatrix.h mulmatrix.cpp utils.h utils.cpp)

target_link_libraries(mainServidorMulMatrix pthread)
