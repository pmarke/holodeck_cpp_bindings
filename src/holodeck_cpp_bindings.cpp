#include "holodeck_cpp_bindings.h"



namespace holodeck_bindings {

Holodeck::Holodeck() {

	// start the interpreter and keep in alive
	// py::scoped_interpreter guard{};

	holodeck_module_ = py::module::import("Holodeck");
	py::exec("from Holodeck import Holodeck;");

	// import the holodeck class
	holodeck_ = holodeck_module_.attr("Holodeck");

	// holodeck_.attr("");

	// py::print(holodeck_module_.attr("__version__"));

}

void Holodeck::make(std::string world_name, GL_VERSION gl_version = OPENGL4) {

	py::print("Hello World");
	env_ = holodeck_.attr("make")(world_name, static_cast<int>(gl_version));
	py::print("Hello World");

}

}