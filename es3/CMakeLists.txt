cmake_minimum_required(VERSION 3.19)

project(esercitazione3-23-24)

set(CMAKE_CXX_FLAGS "-Wall -fdiagnostics-color=always -std=c++2b -pthread -g -march=native -fPIC")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/)

set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})

add_library(uwimg++ SHARED
            src/utils.cpp
            src/utils.h
            src/image.h
            src/load_image.cpp
            src/stb_image.h
            src/stb_image_write.h
            src/process_image.cpp
            src/filter_image.cpp
            src/edge_detection.cpp
            )

link_libraries(uwimg++ m stdc++)

add_executable (test_canny src/test/test2.cpp)
target_link_libraries (test_canny ${Boost_LIBRARIES})
