if (WIN32)
    set(CMAKE_VER 3.20)
else()
    set(CMAKE_VER 3.10)
endif()

cmake_minimum_required(VERSION ${CMAKE_VER})

set(ADDITIONAL_LIBS "")
if(WIN32)
    set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang++.exe")
    set(CMAKE_C_COMPILER "C:/Program Files/LLVM/bin/clang.exe")
    set(PROJECT_NAME ${PROJECT}-${BUILD_TYPE})
    set(ADDITIONAL_LIBS winmm.lib Version.lib Setupapi.lib)
else()
    set(PROJECT_NAME ${PROJECT}-${BUILD_TYPE}.exe)
    set(ADDITIONAL_LIBS -ldl)
endif()

project(${PROJECT_NAME})

if(BUILD_TYPE STREQUAL "dbg")
    set(CMAKE_BUILD_TYPE  "Debug")
elseif(BUILD_TYPE STREQUAL "rel")
    set(CMAKE_BUILD_TYPE  "Release")
endif()


set(PROJECT_ROOT ${CMAKE_SOURCE_DIR}/Sources)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-pragma-pack -Wno-deprecated-declarations")

include_directories(${PROJECT_ROOT})
file(GLOB_RECURSE PROJECT_SOURCES  ${PROJECT_ROOT}/*.cpp)
file(GLOB_RECURSE PROJECT_C_SOURCES ${PROJECT_ROOT}/*.c)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_C_SOURCES})

target_link_libraries(${PROJECT_NAME} ${ADDITIONAL_LIBS})



