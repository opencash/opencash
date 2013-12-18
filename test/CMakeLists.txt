set(GTEST_LIBS gtest gtest_main)
set(GMOCK_LIBS gmock gmock_main)

include_directories(
  ${GTEST_INCLUDE_DIRS}
  ${GMOCK_INCLUDE_DIRS}
)

link_directories(
  ${GTEST_LIBS_DIR}
  ${GMOCK_LIBS_DIR}
)

#
# Account
#

add_executable(TestAccount
  TestAccount.cpp
)
target_link_libraries(TestAccount
  ${GTEST_LIBS}
  ${GMOCK_LIBS}
  ${OC_LIB_NAME}
)
add_test(TestAccount TestAccount)

#
# DocumentController
#

add_executable(TestDocumentController
  TestDocumentController.cpp
)
target_link_libraries(TestDocumentController
  ${GTEST_LIBS}
  ${GMOCK_LIBS}
  ${OC_LIB_NAME}
)
add_test(TestDocumentController TestDocumentController)
