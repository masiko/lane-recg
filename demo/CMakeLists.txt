cmake_minimum_required(VERSION 2.8)

project(video-cap)

set(CMAKE_CXX_FLAGS_RELEASE)
find_package(OpenCV REQUIRED)
add_executable(Side-Recog main.cpp)
target_link_libraries(Side-Recog ${OpenCV_LIBS})
