cmake_minimum_required(VERSION 3.20)

project(ardilla VERSION 1.0)

# Build Type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release
        CACHE STRING "Choose the build type (Debug, Release, RelWithDebInfo)" FORCE)
endif()

# Validate build type
set(VALID_BUILD_TYPES Debug Release RelWithDebInfo MinSizeRel)
if(NOT CMAKE_BUILD_TYPE IN_LIST VALID_BUILD_TYPES)
message(FATAL_ERROR "Invalid build type : ${CMAKE_BUILD_TYPE}. Valid options are : ${VALID_BUILD_TYPES}")
endif()
message(STATUS "Configuring for build type: ${CMAKE_BUILD_TYPE}")

# Build type specific flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O2")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")

# Custom flag for trace logging
option(SQ_ENABLE_TRACE_LOGGING "Enable trace logging" OFF)
if(SQ_ENABLE_TRACE_LOGGING)
    add_definitions(-DSQ_ENABLE_TRACE_LOGGING)
endif()

# Platform and System Info
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Configuring for Linux")
    set(PlATFORM_SPECIFIC_FLAGS "-DLINUX")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Configuring for Windows")
    set(PlATFORM_SPECIFIC_FLAGS "-DWINDOWS")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Configuring for MacOS")
    set(PlATFORM_SPECIFIC_FLAGS "-DMACOS")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PLATFORM_SPECIFIC_FLAGS}")

# Compiler flags and Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(ardilla)
add_subdirectory(squirrel)
