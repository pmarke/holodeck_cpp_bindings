#include "holodeck_cpp_bindings.h"



int main(int argc, char** argv)
{

	py::scoped_interpreter guard{};


	holodeck_bindings::Holodeck holodeck;

	// py::object test = py::module::import("test");

	holodeck.make("UrbanCity",holodeck_bindings::OPENGL4);

	return 0;

}