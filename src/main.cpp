#include "holodeck_cpp_bindings.h"
#include <unistd.h>


int main(int argc, char** argv)
{

	py::scoped_interpreter guard{};


	holodeck_bindings::Holodeck holodeck;


	holodeck.make("UrbanCity",holodeck_bindings::OPENGL4);

	holodeck.reset();

	int milliseconds = 100;

	for(int i = 0; i < 300; i++) {
		holodeck.step(0,0,1,10);

		// usleep(milliseconds * 1000); // takes microseconds
	}
	

	return 0;

}