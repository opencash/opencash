cmake_minimum_required(VERSION 2.8.8)
project(poco_builder C CXX)
include(ExternalProject)

if(OC_STATIC)
  set(BUILD_TARGET my_static)
else()
  set(BUILD_TARGET my_shared)
endif()

if(OC_DEBUG)
  set(BUILD_TARGET ${BUILD_TARGET}_debug)
else()
  set(BUILD_TARGET ${BUILD_TARGET}_release)
endif()

if(OC_PLATFORM_IOS_DEVICE)
  set(CONFIGURE_ARGS --config=iPhone-clang)
elseif(OC_PLATFORM_IOS_SIMULATOR)
  set(CONFIGURE_ARGS --config=iPhoneSimulator-clang)
elseif(OC_PLATFORM_ANDROID)
  set(CONFIGURE_ARGS --config=Android)
endif()

ExternalProject_Add(poco
  URL http://pocoproject.org/releases/poco-1.4.6/poco-1.4.6p2.tar.gz
  URL_MD5 33f6a0b7e7fd6b86a1028b1e7fa78b84
  SOURCE_DIR ${PROJECT_BINARY_DIR}/src/poco

  PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
  INSTALL_DIR ${OC_INSTALL_DIR}
  UPDATE_COMMAND ""
  BUILD_IN_SOURCE 1

  # Unfortunately the poco Makefile isn't as flexible as we'd like, so we copy
  # our own Makefile extensions to the source dir
  PATCH_COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/Makefile-custom" <SOURCE_DIR>/Makefile-custom

  CONFIGURE_COMMAND <SOURCE_DIR>/configure --no-tests --no-samples
    --prefix=<INSTALL_DIR> ${CONFIGURE_ARGS}

  # Source our custom Makefile before building
  BUILD_COMMAND make -f Makefile -f Makefile-custom -j4 ${BUILD_TARGET}

  # Source our custom Makefile before installing
  INSTALL_COMMAND make -f Makefile -f Makefile-custom my_install

  # Wrap download, configure and build steps in a script to log output
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON
  LOG_INSTALL ON
)
