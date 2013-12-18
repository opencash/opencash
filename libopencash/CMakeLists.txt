cmake_minimum_required(VERSION 2.8.7)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(OC_LIB_NAME opencash)
set(OC_PROJECT_NAME "lib${OC_LIB_NAME}")

option(OC_VERBOSE "Print verbose build progress (default: off)." OFF)
option(OC_DEBUG "Build a debug version of ${OC_PROJECT_NAME} and its dependencies (default: build a release version)." OFF)
option(OC_STATIC "Build a static version of ${OC_PROJECT_NAME} and its dependencies (default: enabled)." ON)
option(OC_TESTS "Build all of ${OC_PROJECT_NAME}'s unit tests (default: OFF)." OFF)
set(OC_PLATFORM "host" CACHE STRING "Build ${OC_PROJECT_NAME} for a particular platform. Options are 'host', 'ios-device', 'ios-simulator' or 'android' (default: host).")

if(OC_VERBOSE)
  set(OC_QUIET_EXTERNALPROJECT OFF)
else()
  set(OC_QUIET_EXTERNALPROJECT ON)
endif()

if(OC_DEBUG)
  set(CMAKE_BUILD_TYPE "Debug")
else()
  set(CMAKE_BUILD_TYPE "Release")
endif(OC_DEBUG)

if(OC_PLATFORM STREQUAL "host")
  set(OC_PLATFORM_HOST ON)
elseif(OC_PLATFORM STREQUAL "ios-device")
  set(OC_PLATFORM_IOS_DEVICE ON)
elseif(OC_PLATFORM STREQUAL "ios-simulator")
  set(OC_PLATFORM_IOS_SIMULATOR ON)
elseif(OC_PLATFORM STREQUAL "android")
  set(OC_PLATFORM_ANDROID ON)
else()
  message(FATAL_ERROR "OC_PLATFORM set to invalid value: '${OC_PLATFORM}'")
endif()

if(NOT OC_PLATFORM_HOST)
  if(NOT OC_STATIC)
    set(OC_STATIC ON)
    message(WARNING "Setting OC_STATIC to ON for OC_PLATFORM '${OC_PLATFORM}'")
  endif()
endif()

if(OC_PLATFORM_IOS_DEVICE OR OC_PLATFORM_IOS_SIMULATOR)
  if(OC_TESTS)
    set(OC_TESTS OFF)
    message(WARNING "Setting OC_TESTS to OFF for OC_PLATFORM '${OC_PLATFORM}'")
  endif()
endif()

if(OC_STATIC)
  set(BUILD_SHARED_LIBS OFF)
else()
  set(BUILD_SHARED_LIBS ON)
endif(OC_STATIC)

if(OC_PLATFORM_IOS_DEVICE OR OC_PLATFORM_IOS_SIMULATOR)
  if(OC_PLATFORM_IOS_DEVICE)
    set(IOS_PLATFORM "OS")
  else()
    set(IOS_PLATFORM "SIMULATOR")
  endif()
  # Must be included before project declaration
  include(ios-toolchain)
endif()

if(OC_PLATFORM_ANDROID)
  set(ANDROID_COMPILER_IS_CLANG 1)
  set(LIBRARY_OUTPUT_PATH_ROOT ${CMAKE_BINARY_DIR}/out CACHE PATH "root for library output" FORCE)
  # Must be included before project declaration
  include(android-toolchain)
endif()

# Project must be declared before adjustments to CMAKE_CXX_FLAGS
project(${OC_PROJECT_NAME} C CXX)

# -Wno-unknown-pragmas needed due to libodb custom #pragma db
set(OC_C_ADDITIONAL_FLAGS "-Wall -Wno-unknown-pragmas")
set(OC_CXX_ADDITIONAL_FLAGS "-Wall -std=c++11 -Wno-unknown-pragmas")

# Compiler-specific C++11 activation.
#if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
#  execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
#  if(NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
#    message(FATAL_ERROR "${PROJECT_NAME} requires g++ 4.7 or greater.")
#  endif()
#elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
#  set(OC_CXX_ADDITIONAL_FLAGS "${OC_CXX_ADDITIONAL_FLAGS} -stdlib=libc++")
#elseif((OC_PLATFORM_IOS_DEVICE OR OC_PLATFORM_IOS_SIMULATOR) AND "${CMAKE_CXX_COMPILER_ID}" MATCHES "g\\+\\+")
#  # empty
#else()
#  message(FATAL_ERROR "Your C++ compiler does not support C++11 (CXX_COMPILER_ID='${CMAKE_CXX_COMPILER_ID}').")
#endif()

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
  execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
  if(NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
    message(FATAL_ERROR "${PROJECT_NAME} requires g++ 4.7 or greater.")
  endif()
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OC_C_ADDITIONAL_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OC_CXX_ADDITIONAL_FLAGS}")

if(OC_DEBUG)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG} -v -g -O0")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -v -g -O0")
else()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE} -g0")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -g0")
endif(OC_DEBUG)

set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "")
set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELEASE "")

set(OC_INSTALL_DIR ${CMAKE_BINARY_DIR}/out)
set(OC_INSTALL_INCLUDE_DIR ${OC_INSTALL_DIR}/include)
set(OC_INSTALL_LIB_DIR ${OC_INSTALL_DIR}/lib)

message(STATUS "OC_VERBOSE: ${OC_VERBOSE}")
message(STATUS "OC_DEBUG: ${OC_DEBUG}")
message(STATUS "OC_STATIC: ${OC_STATIC}")
message(STATUS "OC_TESTS: ${OC_TESTS}")
message(STATUS "OC_PLATFORM: ${OC_PLATFORM}")

if(OC_VERBOSE)
  message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
  message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
endif()

include_directories(
  ./include/
  ${OC_INSTALL_INCLUDE_DIR}
)

link_directories(
  ${OC_INSTALL_LIB_DIR}
)

add_subdirectory(vendor/poco)
add_subdirectory(vendor/libodb)
add_subdirectory(vendor/libodb-sqlite)
add_subdirectory(src)

if(OC_TESTS)
  enable_testing()
  add_subdirectory(vendor/gtest)
  add_subdirectory(vendor/gmock)
  add_subdirectory(test)
endif()
