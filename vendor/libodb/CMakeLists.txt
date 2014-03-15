cmake_minimum_required(VERSION 2.8.7)
project(libodb_builder C CXX)
include(ExternalProject)

if(OC_STATIC)
  set(CONFIGURE_ARGS --enable-static --disable-shared)
else()
  set(CONFIGURE_ARGS --enable-shared --disable-static)
endif()

if(OC_PLATFORM_IOS_DEVICE)
  set(CONFIGURE_ARGS ${CONFIGURE_ARGS} --host=armv7 --build=x86_64)
elseif(OC_PLATFORM_IOS_SIMULATOR)
  set(CONFIGURE_ARGS ${CONFIGURE_ARGS} --host=i386 --build=x86_64)
elseif(OC_PLATFORM_ANDROID)
  set(CONFIGURE_ARGS ${CONFIGURE_ARGS} --host=arm-linux-androideabi --build=x86_64)
endif()

ExternalProject_Add(libodb
  URL http://www.codesynthesis.com/download/odb/2.3/libodb-2.3.0.tar.gz
  URL_MD5 85cc1c357d8791b684f41c4c8801be55
  #URL_HASH SHA1=8ac9a09a6a86e73951289ee79c022661caea7f96
  SOURCE_DIR ${PROJECT_BINARY_DIR}/src/libodb

  PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
  INSTALL_DIR ${OC_INSTALL_DIR}
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  BUILD_IN_SOURCE 1

  CONFIGURE_COMMAND <SOURCE_DIR>/configure
    --prefix=<INSTALL_DIR>
    --disable-threads
    CXX=${CMAKE_CXX_COMPILER}
    CXXFLAGS=${CMAKE_CXX_FLAGS}
    ${CONFIGURE_ARGS}

  BUILD_COMMAND make -j4 all

  # Wrap download, configure and build steps in a script to log output
  LOG_DOWNLOAD ${OC_QUIET_EXTERNALPROJECT}
  LOG_CONFIGURE ${OC_QUIET_EXTERNALPROJECT}
  LOG_BUILD ${OC_QUIET_EXTERNALPROJECT}
  LOG_INSTALL ${OC_QUIET_EXTERNALPROJECT}
)
