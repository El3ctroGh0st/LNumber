cmake_minimum_required(VERSION 3.8)
project(codewars)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.7.0\\5.7\\mingw53_32\\include")

find_package(Qt5Widgets REQUIRED)

set(SOURCE_FILES main.cpp LNumber.cpp LNumber.hpp)
add_executable(codewars ${SOURCE_FILES})

target_link_libraries(codewars Qt5::Widgets)