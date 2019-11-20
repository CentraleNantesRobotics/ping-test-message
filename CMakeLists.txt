cmake_minimum_required(VERSION 3.1)
project(ping_test)
set(CMAKE_CXX_STANDARD 11)

# compile the test
add_executable(ping_test
  src/main.cpp
)
target_include_directories(ping_test PUBLIC lib)
