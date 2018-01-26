#include "holodeck_cpp_bindings.h"



namespace holodeck_bindings {

Holodeck::Holodeck() {

    // import the py module
    holodeck_module_ = py::module::import("Holodeck");
    py::exec("from Holodeck import Holodeck;");

    // import the holodeck class
    holodeck_ = holodeck_module_.attr("Holodeck");

    

}


void Holodeck::make(std::string world_name, GL_VERSION gl_version = OPENGL4) {

    // Create the world
    env_ = holodeck_.attr("make")(world_name, static_cast<int>(gl_version));
    
}


void Holodeck::reset() {

    // reset the environment and returns [state, terminal, reward, and info]
    py::tuple result_py = env_.attr("reset")();

    // extract the state
    state_ = result_py[0];

}

void Holodeck::step(float roll, float pitch, float altitude, float yaw_rate) {

    // pack commands up
    Eigen::RowVector4f command(roll,pitch,altitude,yaw_rate);

    // send the commands to the simulator and get states
    py::tuple result_py = env_.attr("step")(command);

    // extract state information
    state_ = result_py[0];

}

void Holodeck::get_orientation_sensor_data(Eigen::Ref< Eigen::Matrix3f> m) {

    // extract data
    py::array pyData = state_.attr("get")(5);

    // return pointer of data
    m = pyData.cast<py::EigenDRef<Eigen::Matrix3f>>();
    
}

void Holodeck::get_imu_sensor_data(Eigen::Ref<Eigen_RowVector6f> v) {

    // extract the data
    py::array pyData = state_.attr("get")(6);

    // return the data
    v = pyData.cast<py::EigenDRef<Eigen::Matrix<float, 6,1>>>();


}

void Holodeck::get_location_sensor_data(Eigen::Ref<Eigen::RowVector3f> v) {

    // extract the data
    py::array pyData = state_.attr("get")(9);

    // return the data
    v = pyData.cast<py::EigenDRef<Eigen::Matrix<float,3,1>>>();
}

void Holodeck::get_velocity_sensor_data(Eigen::Ref<Eigen::RowVector3f> v) {

    // extract the data
    py::array pyData = state_.attr("get")(10);

    // return the data
    v = pyData.cast<py::EigenDRef<Eigen::Matrix<float,3,1>>>();
}

void Holodeck::getCammeraDimensions(py::array pyImg) {

    if(!allocated_) {
        // get the shape of the image
        py::tuple shape = pyImg.attr("shape");

        // extract the dimensions
        width_ = shape[0].cast<int>();
        height_ = shape[1].cast<int>();
        depth_ = shape[2].cast<int>();

        allocated_ = true;
    }


}


void Holodeck::get_primary_player_camera(cv::Mat& img) {

    // get camera data
    py::array pyImg = state_.attr("get")(3);
    
    // get dimensions of image
    getCammeraDimensions(pyImg);
    
    // convert numpy ndarray to cv::Mat object
    img = cv::Mat(height_,width_, CV_8UC4,pyImg.mutable_data());

}



}


