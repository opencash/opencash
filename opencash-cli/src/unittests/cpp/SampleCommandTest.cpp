#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace testing;

#include "SampleCommand.h"
#include <opencash/api/Api.h>
#include <opencash/api/ApiExceptions.h>

using SampleCommand = opencash::cli::SampleCommand;
using AppContext = opencash::cli::AppContext;
using FileAlreadyExists = opencash::api::FileAlreadyExists;

class MockApi : public opencash::api::Api {
  public:
    MOCK_CONST_METHOD1(mockCreateSampleFile, void(const std::string&));

    virtual void createSampleFile(const std::string& fileName)
      const throw(FileAlreadyExists) override
    {
      mockCreateSampleFile(fileName);
    }
};

TEST(SampleCommand, shouldDelegateToApiCreateSampleFile) {
  // given
  AppContext ctx;
  MockApi mockApi;
  const std::vector<std::string> args({"sample", "-o", "sample.opencash"});

  // expect
  EXPECT_CALL(mockApi, mockCreateSampleFile("sample.opencash"));

  // when
  SampleCommand(ctx, mockApi).run(args);
}
