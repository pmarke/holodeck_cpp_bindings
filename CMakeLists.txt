cmake_minimum_required(VERSION 3.0)
project(holodeck_cpp_bindings)



set(CMAKE_CXX_STANDARD 11)
add_compile_options(-fvisibility=hidden)


set(PYBIND11_CPP_STANDARD -std=c++11)
set(PYBIND11_PYTHON_VERSION 3.5)


set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 0)


# Define the installation diretories and paths
set(INSTALL_LIB_DIR     lib                          CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR     bin                          CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include/                     CACHE PATH "Installation directory for header files")
set(INSTALL_CMAKE_DIR   lib/cmake/holodeck_cpp_bindings  CACHE PATH "Installation directory for CMake Config files")


# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()


###############################

#     Add in dependencies     #

###############################


find_package(pybind11 REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(include ${EIGEN3_INCLUDE_DIR} ${OpenCV_INCLUDE_DIRS})

##############################

#  Create a shared library   #

##############################

add_library(${PROJECT_NAME} SHARED src/holodeck.cpp)
# pybind11_add_module(${PROJECT_NAME} SHARED src/holodeck_cpp_bindings.cpp)

# message(${PROJECT_SOURCE_DIR})
message("${OpenCV_INCLUDE_DIRS}")
message("${EIGEN3_INCLUDE_DIR}")
message("${pybind11_INCLUDE_DIR}")
message("${pybind11_INCLUDE_DIRS}")
message("${PYTHON_INCLUDE_DIRS}")

target_include_directories( ${PROJECT_NAME} PUBLIC 
			$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
			$<BUILD_INTERFACE:${EIGEN3_INCLUDE_DIR}>
			$<BUILD_INTERFACE:${pybind11_INCLUDE_DIR}>
			$<BUILD_INTERFACE:${PYTHON_INCLUDE_DIRS}>
			$<INSTALL_INTERFACE:${INSTALL_INCLUDE_DIR}>
			$<INSTALL_INTERFACE:${EIGEN3_INCLUDE_DIR}>
			$<INSTALL_INTERFACE:${pybind11_INCLUDE_DIR}>
			$<INSTALL_INTERFACE:${PYTHON_INCLUDE_DIRS}>)

target_link_libraries(${PROJECT_NAME} PRIVATE pybind11::embed)
target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBRARIES} ${PYTHON_LIBRARIES})

# ##############################

# #    Install the library     #

# ##############################

# Project paths
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )


# install library
# The EXPORT tells CMake that we want to generate a .cmake
# file that other projects can find using `find_package`
install(
	TARGETS ${PROJECT_NAME}
    EXPORT  ${PROJECT_NAME}
    RUNTIME DESTINATION "${INSTALL_LIB_DIR}"   # For windows
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}")

# message(${INSTALL_CMAKE_DIR})

# Actually place the `find_package` instructions on the user's system
install(EXPORT ${PROJECT_NAME} DESTINATION "${INSTALL_CMAKE_DIR}")


# # Similiar to the `install(EXPORT ...)` command above, but this creates
# # the package.cmake file that exports all the neccessary CMake info
# # for use of librransac out of the build tree.
export(EXPORT ${PROJECT_NAME})


# install headers
install(DIRECTORY include/${PROJECT_NAME} DESTINATION "${INSTALL_INCLUDE_DIR}")

message("Module path ${CMAKE_MODULE_PATH}")

# # Add `make uninstall` target
configure_file(
    "${CMAKE_MODULE_PATH}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)


##############################

# CMake Package Installation #

##############################

set(PROJECTS ${PROJECT_NAME} )

# Create the Holodeck_cpp_bindingsConfig.cmake and FooBarConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include" )

message("${CONF_INCLUDE_DIRS}")

configure_file("${CMAKE_MODULE_PATH}/holodeck_cpp_bindings-config.cmake.in"
  "${PROJECT_BINARY_DIR}/holodeck_cpp_bindings-config.cmake" @ONLY)

# ... for the install tree
set(CONF_INCLUDE_DIRS "\${HOLODECK_CPP_BINDINGS_CMAKE_DIR}/${REL_INCLUDE_DIR}")

message("install include dir ${CONF_INCLUDE_DIRS}")
configure_file("${CMAKE_MODULE_PATH}/holodeck_cpp_bindings-config.cmake.in"
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/holodeck_cpp_bindings-config.cmake" @ONLY)

# ... for both
configure_file("${CMAKE_MODULE_PATH}/holodeck_cpp_bindings-config-version.cmake.in"
  "${PROJECT_BINARY_DIR}/holodeck_cpp_bindings-config-version.cmake" @ONLY)
 
# Install the FooBarConfig.cmake and FooBarConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/holodeck_cpp_bindings-config.cmake"
  "${PROJECT_BINARY_DIR}/holodeck_cpp_bindings-config-version.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" )
 
# Install the export set for use with the install-tree
# install(EXPORT FooBarTargets DESTINATION
#   "${INSTALL_CMAKE_DIR}" COMPONENT dev)



