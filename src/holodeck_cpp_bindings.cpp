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

	
	env_ = holodeck_.attr("make")(world_name, static_cast<int>(gl_version));
	
// 	py::object scope = py::module::import("__main__").attr("__dict__");

// 	py::exec(R"(
// from Holodeck.Sensors import Sensors
// import numpy as np
// env = Holodeck.make("UrbanCity")
// for i in range(10):
//     env.reset()

//     # This command tells the UAV to not roll or pitch, but to constantly yaw left at 10m altitude.
//     command = np.array([0, 0, 1, 10])
//     for _ in range(300):
//         state, reward, terminal, _ = env.step(command)

//         # To access specific sensor data:
//         pixels = state[Sensors.PRIMARY_PLAYER_CAMERA]
//         velocity = state[Sensors.VELOCITY_SENSOR]
//         # For a full list of sensors the UAV has, view the README

// 		)", scope);


		// )); "import numpy as np;"
		// "env_ = Holodeck.make('UrbanCity');"
		// );

}

void Holodeck::reset() {

	env_.attr("reset")();

}

void Holodeck::step(float roll, float pitch, float altitude, float yaw_rate) {

	

    Eigen::RowVector4f command(roll,pitch,altitude,yaw_rate);

	py::tuple result_py = env_.attr("step")(command);

    py::dict state = result_py[0];

    float reward = result_py[1].cast<float>();

    bool terminal = result_py[2].cast<bool>();


    int i = 1;
    for (auto list : state) {

        switch(i)
        {
            case 1:
            {
                reward = list.second;
                py::print(list);
                break;
            }
            default :
            {
                break;
            }
        }
         i++;

    }

    // py::print(state[]);
    // py::print(reward);

    // for(auto item : object)

    // std::tuple<int> data = env_.attr("step")(v);
    // = result_py;

	// py::object result_py = step(command);

	// step(command);

}

}