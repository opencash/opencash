cmake_minimum_required(VERSION 2.8.7)
project(libodb-sqlite_builder C CXX)
include(ExternalProject)

if(OC_STATIC)
  set(CONFIGURE_ARGS --enable-static --disable-shared)
else()
  set(CONFIGURE_ARGS --enable-shared --disable-static)
endif()

if(OC_PLATFORM_IOS_DEVICE)
  set(CONFIGURE_ARGS ${CONFIGURE_ARGS} --host=armv7 --build=x86_64 --disable-threads)
elseif(OC_PLATFORM_IOS_SIMULATOR)
  set(CONFIGURE_ARGS ${CONFIGURE_ARGS} --host=i386 --build=x86_64 --disable-threads)
elseif(OC_PLATFORM_ANDROID)
  set(CONFIGURE_ARGS ${CONFIGURE_ARGS} --host=arm-linux-androideabi --build=x86_64 --disable-threads)
endif()

ExternalProject_Add(libodb-sqlite
  URL http://www.codesynthesis.com/download/odb/2.3/libodb-sqlite-2.3.0.tar.gz
  URL_HASH SHA1=2643d3c2c3f273f3fb223759e4ad10635cc91ce8
  SOURCE_DIR ${PROJECT_BINARY_DIR}/src/libodb-sqlite

  PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
  INSTALL_DIR ${OC_INSTALL_DIR}
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  BUILD_IN_SOURCE 1

  CONFIGURE_COMMAND <SOURCE_DIR>/configure
    --prefix=<INSTALL_DIR>
    CXX=${CMAKE_CXX_COMPILER}
    CXXFLAGS=${CMAKE_CXX_FLAGS}
    LDFLAGS=-L${OC_INSTALL_LIB_DIR}
    CPPFLAGS=-I${OC_INSTALL_INCLUDE_DIR}
    ${CONFIGURE_ARGS}

  BUILD_COMMAND make -j4 all

  # Wrap download, configure and build steps in a script to log output
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON
  LOG_INSTALL ON
)

if(OC_PLATFORM_ANDROID)
  # Android does not provide libsqlite3 for the NDK
  ExternalProject_Add(libsqlite3
    URL http://www.sqlite.org/2013/sqlite-autoconf-3080200.tar.gz
    URL_HASH SHA1=6033ef603ce221d367c665477514d972ef1dc90e
    SOURCE_DIR ${PROJECT_BINARY_DIR}/src/libsqlite3

    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
    INSTALL_DIR ${OC_INSTALL_DIR}
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    BUILD_IN_SOURCE 1

    CONFIGURE_COMMAND <SOURCE_DIR>/configure
      --prefix=<INSTALL_DIR>
      CC=${CMAKE_C_COMPILER}
      CFLAGS=${CMAKE_C_FLAGS}\ -DSQLITE_ENABLE_UNLOCK_NOTIFY=1
      --disable-shared
      --host=arm-linux-androideabi
      ${CONFIGURE_ARGS}

    BUILD_COMMAND make -j4 all

    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
    LOG_INSTALL ON
  )

  add_dependencies(libodb-sqlite libsqlite3)
endif()
