cmake_minimum_required(VERSION 2.8)

project(lane-recg)

set(CMAKE_CXX_FLAGS_RELEASE)
find_package(OpenCV REQUIRED)
add_executable(lane-recg main.cpp)
target_link_libraries(lane-recg ${OpenCV_LIBS})
