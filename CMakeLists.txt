#=============================================================================
#
# CMake configuration file for the twisted project
#
#=============================================================================


cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(twisted LANGUAGES CXX)


# Prevent in-source build
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message( FATAL_ERROR  "In-source build is not possible and not recommended. Choose an empty directory for build output.")
endif(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})

# Languages requirements
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)


# Version informations
set(twisted_VERSION_MAJOR   "0")
set(twisted_VERSION_MINOR   "1")
set(twisted_VERSION_PATCH   "0")
set(twisted_VERSION
  "${twisted_VERSION_MAJOR}.${twisted_VERSION_MINOR}.${twisted_VERSION_PATCH}")

# Cmake scripts
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Twisted options
option(TWISTED_BUILD_TESTS "Tests building." ON)

# For Windows (exposing public API)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Creating the library
#add_library(twisted SHARED "")
add_subdirectory(src/twisted)

#target_link_libraries(twisted mathutils)

# Adding tests
message(STATUS "Building twisted test : ${TWISTED_BUILD_TESTS}")
if (TWISTED_BUILD_TESTS)
    add_subdirectory(tests)
endif()
