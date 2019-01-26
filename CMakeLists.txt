cmake_minimum_required(VERSION 2.8.12)
project(cpplib)

add_subdirectory(pybind11)
include_directories(oscpack_1_1_0)
add_library(oscpack
  oscpack_1_1_0/ip/posix/UdpSocket.cpp
  oscpack_1_1_0/ip/posix/NetworkingUtils.cpp
  oscpack_1_1_0/ip/IpEndpointName.cpp
  oscpack_1_1_0/osc/OscOutboundPacketStream.cpp
  oscpack_1_1_0/osc/OscPrintReceivedElements.cpp
  oscpack_1_1_0/osc/OscReceivedElements.cpp
  oscpack_1_1_0/osc/OscTypes.cpp)

pybind11_add_module(cpplib
  src/main.cpp
  src/scheduler.cpp
  src/note.cpp
  src/phrase.cpp
  src/track.cpp
  src/common.cpp)

target_link_libraries(cpplib PRIVATE oscpack)
