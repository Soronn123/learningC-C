cmake_minimum_required(VERSION 3.5)

project(Convert_jpg_to_png VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(PROJECT_SOURCES
        main.cpp
        convert.h
        FileCreater.h
        FileCreater.cpp
)

add_executable(Convert_jpg_to_png WIN32 ${PROJECT_SOURCES})

target_link_libraries(Convert_jpg_to_png PRIVATE ${OpenCV_LIBS})



