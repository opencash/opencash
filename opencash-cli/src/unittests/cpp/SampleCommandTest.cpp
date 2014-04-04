#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace testing;

#include "SampleCommand.h"
#include <opencash/api/Api.h>

using SampleCommand = opencash::cli::SampleCommand;
using AppContext = opencash::cli::AppContext;

class MockApi : public opencash::api::Api {
  public:
    MOCK_CONST_METHOD1(createSampleFile, void(const std::string& outputFileName));
};

TEST(SampleCommand, shouldDelegateToApi) {
  // given
  AppContext ctx;
  MockApi mockApi;
  const char *argv[] = {"sample", "-o", "sample.opencash"};

  // expect
  EXPECT_CALL(mockApi, createSampleFile("sample.opencash"));

  // when
  SampleCommand(ctx, mockApi).run(3, argv);
}
