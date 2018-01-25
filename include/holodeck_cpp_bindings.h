#pragma once

#include <pybind11/embed.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>
#include <stdint.h>

#include <opencv2/opencv.hpp>
// #include <pybind11/literals.h>

#include <string>

#include <Eigen/Dense>

namespace py = pybind11;

namespace holodeck_bindings {

	using namespace pybind11::literals;

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

		void reset();

		void step(float roll, float pitch, float altitude, float yaw_rate);
		// set

		// reset



	private:

		py::object holodeck_module_;  // used to import Holodeck.py
		py::object holodeck_;         // Holodeck class. from Holodeck import Holodeck
		py::object env_;              // Environment object. env=Holodeck.make


		// void unpack(std::set);




	};




}