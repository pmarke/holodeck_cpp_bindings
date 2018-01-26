#include "holodeck_cpp_bindings.h"
#include <unistd.h>


int main(int argc, char** argv)
{


    
    // intantiate the holodeck object
    holodeck_bindings::Holodeck holodeck;


    // create the environment
    holodeck.make("UrbanCity",holodeck_bindings::OPENGL4);

    cv::Mat img;


    for(int i = 0; i < 100; i++) {

        // send step command (roll, pitch, altitude, yaw_rate)
        holodeck.step(0,0,1,10);

        // get camera data
        holodeck.get_primary_player_camera(img);

        // show camera data
        cv::imshow("img", img);
        cv::waitKey(1);

    }



    
    // get rotation matrix
    Eigen::Matrix3f rotation_matrix;
    holodeck.get_orientation_sensor_data(rotation_matrix);
    
    std::cout << "Printing Rotation Matrix" << std::endl << std::endl;
    for(int i= 0; i < 3; i++) {

        for(int j=0; j <3; j++) {
            std::cout << rotation_matrix(i,j) << " ";
        }

        std::cout << std::endl << std::endl;
    }



    Eigen::Matrix<float, 6,1> imu;
    holodeck.get_imu_sensor_data(imu);

    std::cout << "Printing imu Matrix" << std::endl << std::endl;
    for(int i = 0; i < 6; i++)
        std::cout << imu(i) << " ";

    // get location data
    Eigen::RowVector3f location;
    holodeck.get_location_sensor_data(location);

    std::cout << std::endl << std::endl << "Printing location information" << std::endl << std::endl;
    for(int i = 0; i < 3; i++)
        std::cout << location(i) << " "; 

    // get velocity data
    Eigen::RowVector3f velocity;
    holodeck.get_velocity_sensor_data(velocity);

    std::cout << std::endl << std::endl << "Printing velocity information" << std::endl << std::endl;
    for(int i = 0; i < 3; i++)
        std::cout << velocity(i) << " ";

    std::cout << std::endl << std::endl;   

    // reset environment
    holodeck.reset();

    return 0;

}