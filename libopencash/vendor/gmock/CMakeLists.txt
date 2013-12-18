cmake_minimum_required(VERSION 2.8.7)
project(gmock_builder C CXX)
include(ExternalProject)

ExternalProject_Add(googlemock
  URL https://googlemock.googlecode.com/files/gmock-1.7.0.zip
  URL_MD5 073b984d8798ea1594f5e44d85b20d66
  SOURCE_DIR ${PROJECT_BINARY_DIR}/src/googlemock

  CMAKE_ARGS
      -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
      -Dgtest_force_shared_crt=ON
      -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
      -DCMAKE_AR=${CMAKE_AR}
      -DCMAKE_RANLIB=${CMAKE_RANLIB}
      -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
      -DCMAKE_CXX_FLAGS_DEBUG=${CMAKE_CXX_FLAGS_DEBUG}
      -DCMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}
  PREFIX "${CMAKE_CURRENT_BINARY_DIR}"

  # Disable install step
  INSTALL_COMMAND ""

  # Wrap download, configure and build steps in a script to log output
  LOG_DOWNLOAD ${OC_QUIET_EXTERNALPROJECT}
  LOG_CONFIGURE ${OC_QUIET_EXTERNALPROJECT}
  LOG_BUILD ${OC_QUIET_EXTERNALPROJECT}
  LOG_INSTALL ${OC_QUIET_EXTERNALPROJECT}
)

# Specify include dir
ExternalProject_Get_Property(googlemock source_dir)
set(GMOCK_INCLUDE_DIRS ${source_dir}/include PARENT_SCOPE)

# Specify link libraries
ExternalProject_Get_Property(googlemock binary_dir)
set(GMOCK_LIBS_DIR ${binary_dir} PARENT_SCOPE)
