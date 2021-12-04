if (WIN32)
    set(CMAKE_VER 3.20)
else()
    set(CMAKE_VER 3.10)
endif()

cmake_minimum_required(VERSION ${CMAKE_VER})

set(ADDITIONAL_LIBS "")
set(PROJECT_NAME Application)
if(WIN32)
    set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang++.exe")
    set(CMAKE_C_COMPILER "C:/Program Files/LLVM/bin/clang.exe")
    set(ADDITIONAL_LIBS winmm.lib Version.lib Setupapi.lib)
else()
    set(ADDITIONAL_LIBS -ldl)
endif()
project(${PROJECT_NAME})


set(PARENT_DIR ${CMAKE_SOURCE_DIR}/..)
set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_ROOT ${ROOT_DIR}/Projects/${PROJECT}/Sources)
set(COMMON_ROOT ${ROOT_DIR}/Common/Sources)

add_subdirectory(${ROOT_DIR}/Common)
add_subdirectory(${ROOT_DIR}/${PROJECT})
if(WIN32)
    set (BuildDir "${PARENT_DIR}/Builds")
    add_library(SDL2 STATIC IMPORTED)
    set_target_properties(SDL2 PROPERTIES
        IMPORTED_LOCATION_RELEASE "${BuildDir}/win/libSDL2.a"
        IMPORTED_LOCATION_DEBUG "${BuildDir}/win/libSDL2.a"
        LINKER_LANGUAGE CXX)
    add_library(SDL2_MIXER STATIC IMPORTED)
    set_target_properties(SDL2_MIXER PROPERTIES
        IMPORTED_LOCATION_RELEASE "${BuildDir}/win/libSDL2_mixer.a"
        IMPORTED_LOCATION_DEBUG "${BuildDir}/win/libSDL2_mixer.a"
        LINKER_LANGUAGE CXX)
else()
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    find_package(SDL2_MIXER REQUIRED)
    include_directories(${SDL2_MIXER_INCLUDE_DIRS})
endif()


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-pragma-pack -Wno-deprecated-declarations")


if(BUILD_TYPE STREQUAL "dbg")
    set(CMAKE_BUILD_TYPE "Debug")
elseif(BUILD_TYPE STREQUAL "rel")
    set(CMAKE_BUILD_TYPE  "Release")
endif()


add_executable(${PROJECT_NAME} )
target_link_libraries(${PROJECT_NAME} SDL2 SDL2_MIXER Engine Game ${ADDITIONAL_LIBS})
