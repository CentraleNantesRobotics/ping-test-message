cmake_minimum_required(VERSION 3.1)
project(ping_test)
set(CMAKE_CXX_STANDARD 11)

include_directories(lib/ping-cpp/src/message lib/device)
# compile the test
add_executable(ping_test
  lib/device/ping-port-linux.cpp
  lib/device/ping-time-linux.cpp
  lib/device/ping-device.cpp
  src/main.cpp
)
