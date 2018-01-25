cmake_minimum_required(VERSION 3.5)
project(holodeck_cpp_bindings)

add_compile_options(-std=c++11 -fvisibility=hidden)

find_package(pybind11 REQUIRED)

find_package (Eigen3 REQUIRED NO_MODULE)

include_directories(${EIGEN3_INCLUDE_DIR})


include_directories(
  include
)



add_executable(example 
	src/main.cpp
	src/holodeck_cpp_bindings.cpp)

set(PYBIND11_CPP_STANDARD -std=c++11)
set(PYBIND11_PYTHON_VERSION 3.5)

target_link_libraries(example PRIVATE pybind11::embed )