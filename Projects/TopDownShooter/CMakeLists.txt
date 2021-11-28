cmake_minimum_required(VERSION 3.10)

project(Game)


set(COMMON_FOLDER "${CMAKE_SOURCE_DIR}/Common/Sources")
set(PROJECT_FOLDER "${CMAKE_SOURCE_DIR}/${PROJECT}/Sources")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-pragma-pack -Wno-deprecated-declarations")
if(BUILD_TYPE STREQUAL "dbg")
    set(CMAKE_BUILD_TYPE  "Debug")
elseif(BUILD_TYPE STREQUAL "rel")
    set(CMAKE_BUILD_TYPE  "Release")
endif()


file(GLOB_RECURSE ENGINE_SOURCES ${PROJECT_FOLDER}/*.cpp)
file(GLOB_RECURSE ENGINE_C_SOURCES ${PROJECT_FOLDER}/*.c)

include_directories(${COMMON_FOLDER})
include_directories(${PROJECT_FOLDER})
add_library(Game OBJECT ${ENGINE_SOURCES} ${ENGINE_C_SOURCES})


