cmake_minimum_required(VERSION 3.10)

project(Engine)

set(LIB_FOLDER "${CMAKE_SOURCE_DIR}/Common/Sources")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-pragma-pack -Wno-deprecated-declarations")
if(BUILD_TYPE STREQUAL "dbg")
    set(CMAKE_BUILD_TYPE  "Debug")
elseif(BUILD_TYPE STREQUAL "rel")
    set(CMAKE_BUILD_TYPE  "Release")
endif()


file(GLOB_RECURSE ENGINE_SOURCES ${LIB_FOLDER}/*.cpp)
file(GLOB_RECURSE ENGINE_C_SOURCES ${LIB_FOLDER}/*.c)
file(GLOB_RECURSE ENGINE_STATIC_LIBS ${LIB_FOLDER}/*.lib)

include_directories(${LIB_FOLDER})
include_directories(${LIB_FOLDER}/Systems)
add_library(Engine OBJECT ${ENGINE_SOURCES} ${ENGINE_C_SOURCES})
target_link_libraries(Engine ${ENGINE_STATIC_LIBS})
