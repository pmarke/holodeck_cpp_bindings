cmake_minimum_required(VERSION 2.8.3)
project(holodeck_cpp_bindings)

add_compile_options(-std=c++11 -fvisibility=hidden)

find_package(pybind11 REQUIRED)


include_directories(
  include
)



add_executable(example 
	src/main.cpp
	src/holodeck_cpp_bindings.cpp)

set(PYBIND11_CPP_STANDARD -std=c++11)
set(PYBIND11_PYTHON_VERSION 3.5)

target_link_libraries(example PRIVATE pybind11::embed)