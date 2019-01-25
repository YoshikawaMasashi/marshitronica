// Copyright[2019] <marshi(masashi yoshikawa)>
#include <pybind11/pybind11.h>

#include "./scheduler.h"
#include "./note.h"
#include "./phrase.h"
#include "./track.h"
#include "./common.h"

int add(int i, int j) {
    return i + j;
}

namespace py = pybind11;

PYBIND11_MODULE(cpplib, m) {
  py::class_<Common>(m, "Common")
        .def("get", &Common::get);
}
