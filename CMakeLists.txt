cmake_minimum_required(VERSION 3.5)
project(holodeck_cpp_bindings)

add_compile_options(-std=c++11 -fvisibility=hidden)
set(PYBIND11_CPP_STANDARD -std=c++11)
set(PYBIND11_PYTHON_VERSION 3.5)

# If true, camera data will be returned as cv::Mat object instead
# of array pointer uint8_t***
option(USE_OPENCV "Return Camera as a cv::Mat object" ON)

add_definitions(-DBLAH)


find_package(pybind11 REQUIRED)
find_package (Eigen3 REQUIRED NO_MODULE)

set(DIRS_TO_INCLUDE 
	include
  ${EIGEN3_INCLUDE_DIR})

set(LIBS_TO_LINK pybind11::embed)

if(USE_OPENCV)
	message("Using OpenCV")
	add_definitions(-DUSE_OPENCV)
	find_package(OpenCV REQUIRED)
	set(DIRS_TO_INCLUDE ${DIRS_TO_INCLUDE} ${OpenCV_INCLUDE_DIRS})
	set(LIBS_TO_LINK ${LIBS_TO_LINK} ${OpenCV_LIBRARIES})
endif(USE_OPENCV)



include_directories(${DIRS_TO_INCLUDE})



add_executable(example 
	src/main.cpp
	src/holodeck_cpp_bindings.cpp)



target_link_libraries(example PRIVATE ${LIBS_TO_LINK})