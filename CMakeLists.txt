cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(serdepp)

add_library(serdepp INTERFACE)
target_include_directories(serdepp INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/")

if(DEFINED BUILD_TESTS)
    add_executable(test "test/test.cpp")
    target_link_libraries(test PRIVATE serdepp)
endif()

