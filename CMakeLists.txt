cmake_minimum_required(VERSION 2.8.12)
project(cpplib)

add_subdirectory(pybind11)

pybind11_add_module(cpplib
  src/main.cpp
  src/scheduler.cpp
  src/note.cpp
  src/phrase.cpp
  src/track.cpp
  src/common.cpp
  src/event.cpp)

include_directories(oscpack_1_1_0)
add_subdirectory(oscpack_1_1_0)
target_link_libraries(cpplib PRIVATE oscpack)
