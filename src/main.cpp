// Copyright[2019] <marshi(masashi yoshikawa)>
#include <pybind11/pybind11.h>

#include "./scheduler.h"
#include "./note.h"
#include "./phrase.h"
#include "./track.h"
#include "./common.h"

namespace py = pybind11;

PYBIND11_MODULE(cpplib, m) {
  py::class_<Common>(m, "Common")
        .def_static("get", &Common::get, py::return_value_policy::reference)
        .def("get_next_bus_id", &Common::get_next_bus_id)
        .def("get_next_synth_id", &Common::get_next_synth_id)
        .def("increment_next_bus_id", &Common::increment_next_bus_id)
        .def("increment_next_synth_id", &Common::increment_next_synth_id)
        .def("get_transmit_socket", &Common::get_transmit_socket);
}
