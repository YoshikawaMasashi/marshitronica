// Copyright[2019] <marshi(masashi yoshikawa)>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

#include "./scheduler.h"
#include "./note.h"
#include "./event.h"
#include "./phrase.h"
#include "./track.h"
#include "./common.h"

namespace py = pybind11;

PYBIND11_MODULE(cpplib, m) {
  py::class_<Common>(m, "Common")
    .def_static("get", &Common::get, py::return_value_policy::reference)
    .def_static("pitch_to_freq", &Common::pitch_to_freq)
    .def("get_next_bus_id", &Common::get_next_bus_id)
    .def("get_next_synth_id", &Common::get_next_synth_id)
    .def("increment_next_bus_id", &Common::increment_next_bus_id)
    .def("increment_next_synth_id", &Common::increment_next_synth_id)
    .def("get_transmit_socket", &Common::get_transmit_socket);

  py::class_<Scheduler>(m, "Scheduler")
    .def(py::init<>())
    .def("schedule", &Scheduler::schedule)
    .def("start", &Scheduler::start)
    .def("stop", &Scheduler::stop)
    .def("add_task", &Scheduler::add_task)
    .def("now_seconds", &Scheduler::now_seconds)
    .def("now_beats", &Scheduler::now_beats)
    .def("seconds_to_beats", &Scheduler::seconds_to_beats)
    .def("beats_to_seconds", &Scheduler::beats_to_seconds);

  py::class_<Event, std::shared_ptr<Event>>(m, "Event")
    .def("add_osc_message", &Event::add_osc_message)
    .def("get_length", &Event::get_length);

  py::class_<Note, Event, std::shared_ptr<Note>>(m, "Note")
    .def(py::init<double, double, double>())
    .def("add_osc_message", &Note::add_osc_message)
    .def("get_length", &Note::get_length)
    .def("get_pitch", &Note::get_pitch)
    .def("get_duration", &Note::get_duration)
    .def("get_amp", &Note::get_amp);

  py::class_<Phrase>(m, "Phrase")
    .def(py::init<>())
    .def("add_event", &Phrase::add_event)
    .def("get_length", &Phrase::get_length)
    .def("get_events_in_range", &Phrase::get_events_in_range);

  py::class_<Track>(m, "Track")
    .def(py::init<>())
    .def("set_phrase", &Track::set_phrase)
    .def("set_scheduler", &Track::set_scheduler)
    .def("now_repeats", &Track::now_repeats)
    .def("now_beats", &Track::now_beats)
    .def("next_scheduler_beats", &Track::next_scheduler_beats)
    .def("next_scheduler_beats_of_beats", &Track::next_scheduler_beats_of_beats)
    .def("play", &Track::play);
}
