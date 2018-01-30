#pragma once

// standard libraries
#include <stdint.h>
#include <iostream>
#include <string>
#include <memory>

#include <opencv2/opencv.hpp>
#include <Eigen/Dense>

// redefinition of PYBIND11_EXPORT from the pybind source code.
// We do this so that we don't have to pop the pimpl and include
// private pybind11 implementation details.
#define PYBIND11_EXPORT __attribute__ ((visibility("default")))

namespace holodeck {

    typedef Eigen::Matrix<float, 6,1> Eigen_RowVector6f;


    enum GL_VERSION
    {
        OPENGL4=4,
        OPENGL3 =3
    };

    // The sensor information that you can retrieve
    enum Sensor
    {
        TERMINAL = 1,
        REWARD = 2,
        PRIMARY_PLAYER_CAMERA = 3,   // default is 512 x 512 RGBA
        CAMERA_SENSOR_ARRAY_2D = 4,  // default is 512 x 512 RGBA
        ORIENTATION_SENSOR = 5,
        IMU_SENSOR = 6,
        JOINT_ROTATION_SENSOR = 7,
        RELATIVE_SKELETAL_POSITION_SENSOR = 8,
        LOCATION_SENSOR = 9,
        VELOCITY_SENSOR = 10

    };

    class PYBIND11_EXPORT Holodeck
    {

    public:

        Holodeck();

        // make the world
        void make(std::string world_name, GL_VERSION gl_version );

        // reset the world and update the state variable
        void reset();

        // take a step in the world
        void step(float roll, float pitch, float yaw_rate, float altitude);
        
        // return the orientation sensor data
        void get_orientation_sensor_data(Eigen::Ref<Eigen::Matrix3f> m);

        // return the imu sensor data
        void get_imu_sensor_data(Eigen::Ref<Eigen_RowVector6f> v);

        // return the location sensor data
        void get_location_sensor_data(Eigen::Ref<Eigen::RowVector3f> v);

        // return the velocity sensor data
        void get_velocity_sensor_data(Eigen::Ref<Eigen::RowVector3f> v);

        // returns the primary player camera data
        void get_primary_player_camera(cv::Mat& img);

    private:
        // Forward declaration
        class Impl;
        // Smart pointer to the implementation, along with custom deleter
        std::unique_ptr<Impl, void (*)(Impl *)> impl_;
    };
}