cmake_minimum_required(VERSION 2.8.12)
project(cpplib)

add_subdirectory(pybind11)
include_directories(oscpack_1_1_0)

pybind11_add_module(cpplib
  src/main.cpp
  src/scheduler.cpp
  src/note.cpp
  src/phrase.cpp)
