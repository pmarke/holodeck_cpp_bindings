#include "holodeck_cpp_bindings.h"
#include <unistd.h>


int main(int argc, char** argv)
{


	

	holodeck_bindings::Holodeck holodeck;


	holodeck.make("UrbanCity",holodeck_bindings::OPENGL4);

	holodeck.reset();





	#ifndef USE_OPENCV

	printf("here\n");

			for(int i = 0; i < 100; i++) {
				holodeck.step(0,0,1,10);

				uint8_t*** blah = holodeck.get_primary_player_camera();
			}

		

	#else

		cv::Mat img;

		// for(int i = 0; i < 100; i++) {
			holodeck.step(0,0,1,10);

			holodeck.get_primary_player_camera(img);

			// cv::imshow("img", img);
			// cv::waitKey(0);

		// }



	#endif

	Eigen::Matrix3f rotation_matrix = holodeck.get_orientation_sensor_data();
	
	Eigen::Matrix<float,6,1> imu = holodeck.get_imu_sensor_data();

	holodeck.reset();
	holodeck.reset();

	return 0;

}