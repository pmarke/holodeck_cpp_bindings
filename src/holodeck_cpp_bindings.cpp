#include "holodeck_cpp_bindings.h"



namespace holodeck_bindings {

Holodeck::Holodeck() {

    // import the py module
	holodeck_module_ = py::module::import("Holodeck");
	py::exec("from Holodeck import Holodeck;");

	// import the holodeck class
	holodeck_ = holodeck_module_.attr("Holodeck");

	

}

Holodeck::~Holodeck(){

    #ifndef USE_OPENCV
    // delete the dynamic camera array   
    deallocatePrimaryPlayerCamera();
    #endif

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


Eigen::Matrix3f Holodeck::get_orientation_sensor_data() {

    // extract data
    py::array pyData = state_.attr("get")(5);

    // return rotation matrix
    return pyData.cast<Eigen::Matrix3f>();

}

Eigen_RowVector6f Holodeck::get_imu_sensor_data() {

    // extract the data
    py::array pyData = state_.attr("get")(6);

    // return the data
    return pyData.cast<Eigen::Matrix<float, 6,1>>();


}

Eigen::RowVector3f Holodeck::get_location_sensor_data() {

    // extract the data
    py::array pyData = state_.attr("get")(9);

    // return the data
    return pyData.cast<Eigen::RowVector3f>();
}

Eigen::RowVector3f Holodeck::get_velocity_sensor_data() {

    // extract the data
    py::array pyData = state_.attr("get")(10);

    // return the data
    return pyData.cast<Eigen::RowVector3f>();
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

#ifdef USE_OPENCV

void Holodeck::get_primary_player_camera(cv::Mat& img) {

    // printf("here\n");

    py::array pyImg = state_.attr("get")(3);

    Eigen_MatrixX test;
    test(0,0,0) = 1;// = pyImg.cast<Eigen_MatrixX>;

    // py::object arrayInterface = pyImg.attr("data");

    // py::array flat = pyImg.attr("flat");

    // uint8_t test[] = flat.cast<py::array_t<uint8_t>>();

    // void* test = flat.ptr();


    // py::tuple data = arrayInterface.attr("get")("data");

    // py::int memaddr = data[0];

    // py::print(memaddr);

    // int test =  data[0].cast<int>();



    // py::print(test);
    // get camera image dimensions
    getCammeraDimensions(pyImg);


    // uint8_t tempImg[height_][width_][depth_]; 

    // uint8_t* temp =  &pyImg.attr("item")(0,0,0).cast<uint8_t>();

    // uint8_t* temImg = &pyImg;

    // unpack the image
    // for(int i = 0; i < width_; i++) {

    //     for (int j = 0; j < height_; j++) {

    //         for (int d = 0; d < depth_; d++) {

    //             tempImg[i][j][d] = pyImg.attr("item")(i,j,d).cast<uint8_t>();
                
    //         }
         
    //     }
    // }

    // convert it to cv::Mat object
    img_ = cv::Mat(height_,width_, CV_8UC4,pyImg.ptr());

    img = img_.clone();

    cv::imshow("img", img);
    cv::waitKey(0);

    // delete test;

}

#endif


#ifndef USE_OPENCV
uint8_t*** Holodeck::get_primary_player_camera()
{
    // extract the image from state_
    py::array pyImg = state_.attr("get")(3);


    allocatePrimaryPlayerCamera(pyImg);

   


    for(int i = 0; i < width_; i++) {

        for (int j = 0; j < height_; j++) {

            for (int d = 0; d < depth_; d++) {

                img_[i][j][d] = pyImg.attr("item")(i,j,d).cast<uint8_t>();
                
            }
         
        }
    }

 



    return img_;

}


void Holodeck::allocatePrimaryPlayerCamera(py::array pyImg)
{
    // if not allocated
    if (!allocated_)
    {

        getCammeraDimensions( pyImg);

        // allocate the memeory
        img_ = new uint8_t**[height_];
        for(int i = 0; i < width_; i++) {

            img_[i] = new uint8_t*[width_];

            for(int j = 0; j < height_; j++) {

                img_[i][j] = new uint8_t[depth_];
            }
        }

    }
}

void Holodeck::deallocatePrimaryPlayerCamera()
{

    // deallocate the memory if it has been allocated

    if(allocated_) {

        for(int i = 0; i < height_; i++) {

            for(int j = 0; j < width_; j++) {
                
                delete [] img_[i][j];
            }

            delete [] img_[i];

        }

        delete [] img_;
    }
}
#endif



}


