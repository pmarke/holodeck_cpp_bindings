cmake_minimum_required(VERSION 3.5)
project(holodeck_cpp_bindings)

add_compile_options(-std=c++11 -fvisibility=hidden)
set(PYBIND11_CPP_STANDARD -std=c++11)
set(PYBIND11_PYTHON_VERSION 3.5)




find_package(pybind11 REQUIRED)
find_package (Eigen3 REQUIRED NO_MODULE)
find_package(OpenCV REQUIRED)


include_directories(
	include
	${EIGEN3_INCLUDE_DIR}
	${OpenCV_INCLUDE_DIRS})



add_executable(example 
	src/main.cpp
	src/holodeck_cpp_bindings.cpp)



target_link_libraries(example PRIVATE 
	pybind11::embed
	${OpenCV_LIBRARIES})