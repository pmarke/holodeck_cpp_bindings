#include "holodeck_cpp_bindings/holodeck.h"

// includes for pybind
#include <pybind11/embed.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>

namespace py = pybind11;

namespace holodeck {

class Holodeck::Impl
{
public:
    Impl() {
        // import the py module
        holodeck_module_ = py::module::import("Holodeck");
        py::exec("from Holodeck import Holodeck;");

        // import the holodeck class
        holodeck_ = holodeck_module_.attr("Holodeck");
    }

    // make the world
    void make(std::string world_name, GL_VERSION gl_version) {
        // Create the world
        env_ = holodeck_.attr("make")(world_name, static_cast<int>(gl_version));
    }

    // reset the world and update the state variable
    void reset() {
        // reset the environment and returns [state, terminal, reward, and info]
        py::tuple result_py = env_.attr("reset")();

        // extract the state
        state_ = result_py[0];
    }

    // take a step in the world
    void step(float roll, float pitch, float altitude, float yaw_rate) {
        // pack commands up
        Eigen::RowVector4f command(roll,pitch,altitude,yaw_rate);

        // send the commands to the simulator and get states
        py::tuple result_py = env_.attr("step")(command);

        // extract state information
        state_ = result_py[0];
    }
    
    // return the orientation sensor data
    void get_orientation_sensor_data(Eigen::Ref<Eigen::Matrix3f> m) {
        // extract data
        py::array pyData = state_.attr("get")(5);

        // return pointer of data
        m = pyData.cast<py::EigenDRef<Eigen::Matrix3f>>();
    }

    // return the imu sensor data
    void get_imu_sensor_data(Eigen::Ref<Eigen_RowVector6f> v) {
        // extract the data
        py::array pyData = state_.attr("get")(6);

        // return the data
        v = pyData.cast<py::EigenDRef<Eigen::Matrix<float, 6,1>>>();
    }

    // return the location sensor data
    void get_location_sensor_data(Eigen::Ref<Eigen::RowVector3f> v) {
        // extract the data
        py::array pyData = state_.attr("get")(9);

        // return the data
        v = pyData.cast<py::EigenDRef<Eigen::Matrix<float,3,1>>>();
    }

    // return the velocity sensor data
    void get_velocity_sensor_data(Eigen::Ref<Eigen::RowVector3f> v) {
        // extract the data
        py::array pyData = state_.attr("get")(10);

        // return the data
        v = pyData.cast<py::EigenDRef<Eigen::Matrix<float,3,1>>>();
    }

    // returns the primary player camera data
    void get_primary_player_camera(cv::Mat& img) {
        // get camera data
        py::array pyImg = state_.attr("get")(3);
        
        // get dimensions of image
        get_camera_dimensions(pyImg);
        
        // convert numpy ndarray to cv::Mat object
        img = cv::Mat(height_,width_, CV_8UC4,pyImg.mutable_data());
    }
    
private:
    py::scoped_interpreter guard{};// start the py interpreter
    py::object holodeck_module_;   // used to import Holodeck.py
    py::object holodeck_;          // Holodeck class. from Holodeck import Holodeck
    py::object env_;               // Environment object. env=Holodeck.make
    py::dict state_;               // get the state of the copter

    // primary player camera data
    int height_;
    int width_;
    int depth_;
    bool allocated_ = false;

    void get_camera_dimensions(py::array pyImg) {
        if (!allocated_) {
            // get the shape of the image
            py::tuple shape = pyImg.attr("shape");

            // extract the dimensions
            width_ = shape[0].cast<int>();
            height_ = shape[1].cast<int>();
            depth_ = shape[2].cast<int>();

            allocated_ = true;
        }
    }
};

Holodeck::Holodeck() 
: impl_(new Impl, [](Impl *impl) { delete impl; })
{}

void Holodeck::make(std::string world_name, GL_VERSION gl_version) {
    impl_->make(world_name, gl_version);
}

void Holodeck::reset() {
    impl_->reset();
}

void Holodeck::step(float roll, float pitch, float altitude, float yaw_rate) {
    impl_->step(roll, pitch, altitude, yaw_rate);
}

void Holodeck::get_orientation_sensor_data(Eigen::Ref< Eigen::Matrix3f> m) {
    impl_->get_orientation_sensor_data(m);    
}

void Holodeck::get_imu_sensor_data(Eigen::Ref<Eigen_RowVector6f> v) {
    impl_->get_imu_sensor_data(v);
}

void Holodeck::get_location_sensor_data(Eigen::Ref<Eigen::RowVector3f> v) {
    impl_->get_location_sensor_data(v);
}

void Holodeck::get_velocity_sensor_data(Eigen::Ref<Eigen::RowVector3f> v) {
    impl_->get_velocity_sensor_data(v);
}

void Holodeck::get_primary_player_camera(cv::Mat& img) {
    impl_->get_primary_player_camera(img);
}

}