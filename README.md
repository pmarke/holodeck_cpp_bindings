# holodeck_cpp_bindings

This library offers c++ bindings for the [Holodeck](https://github.com/BYU-PCCL/HolodeckPythonBinding) so that users who want to use the Holodeck can do so through c++. 

#### Build Dependencies
To build the library, you will need to install [pybind11](https://github.com/pybind/pybind11).

#### Install
Clone the repository and navigate to its directory. Create a build folder
```bash
$ mkdir
```

Navigate to the build folder, create the cmake files and install.
```bash
$ cd build
$ cmake ..
$ sudo make install
```

You can also remove the library at any time by
```bash
$ sudo make uninstall
```

#### Using the library
To add the library to your project you will need to know the following. 

* project name: holodeck_cpp_bindings
* DIR VAR: HOLODECK_CPP_BINDINGS_INCLUDE_DIRS
* LIB VAR: HOLODECK_CPP_BINDINGS_LIBRARIES

An example CMakeLists.txt is shown below

```
cmake_minimum_required(VERSION 3.0)
project(test)

set(CMAKE_CXX_STANDARD 11)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(holodeck_cpp_bindings REQUIRED)



include_directories(
	${EIGEN3_INCLUDE_DIR}
	${OpenCV_INCLUDE_DIRS}
	${HOLODECK_CPP_BINDINGS_INCLUDE_DIRS})



add_executable(example src/main.cpp)

target_link_libraries(example
	${OpenCV_LIBRARIES}
	${HOLODECK_CPP_BINDINGS_LIBRARIES})
```

