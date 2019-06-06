cmake_minimum_required(VERSION 3.13)

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})
set(snowflake_VERSION "0.1.0")
set(PACKAGE_VERSION ${snowflake_VERSION})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/output")

message(STATUS "Configuring ${CMAKE_PROJECT_NAME} ${snowflake_VERSION}")

project(snowflake)

set(CMAKE_CXX_STANDARD 11)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src snowflake_src)

find_package(LibEvent REQUIRED)

include_directories(${LIBEVENT_INCLUDE_DIR})
link_directories(${LIBEVENT_LIB_DIR})
link_libraries("${LIBEVENT_A_LIB}")

add_executable(snowflake ${snowflake_src})