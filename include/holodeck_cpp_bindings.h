#pragma once

#include <pybind11/embed.h>
#include <string>

namespace py = pybind11;

namespace holodeck_bindings {

	enum GL_VERSION
	{
		OPENGL4=4,
		OPENGL3 =3
	};

	class Holodeck
	{

	public:

		Holodeck();

		void make(std::string world_name, GL_VERSION gl_version );

		// set

		// reset



	private:

		py::object holodeck_module_;  // used to import Holodeck.py
		py::object holodeck_;         // Holodeck class. from Holodeck import Holodeck
		py::object env_;              // Environment object. env=Holodeck.make







	};




}