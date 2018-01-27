#pragma once

// includes for pybind
#include <pybind11/embed.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>


#include <opencv2/opencv.hpp>

#include <Eigen/Dense>

// standard libraries
#include <stdint.h>
#include <iostream>
#include <string>



namespace py = pybind11;


namespace holodeck_bindings {

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

    class Holodeck
    {

    public:

        Holodeck();

        // make the world
        void make(std::string world_name, GL_VERSION gl_version );

        // reset the world and update the state variable
        void reset();

        // take a step in the world
        void step(float roll, float pitch, float altitude, float yaw_rate);
        
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

        py::scoped_interpreter guard{};// start the py interpreter
        py::object holodeck_module_;   // used to import Holodeck.py
        py::object holodeck_;          // Holodeck class. from Holodeck import Holodeck
        py::object env_;               // Environment object. env=Holodeck.make
        py::dict state_;               // get the state of the copter

        // allocates memory for the primary player camera image
        void allocatePrimaryPlayerCamera(py::array pyImg);

        // deallocates memory for the primary player camera image
        void deallocatePrimaryPlayerCamera();

        void getCammeraDimensions(py::array pyImg);


        // primary player camera data
        int height_;
        int width_;
        int depth_;
        bool allocated_ = false;

        
        






    };




}