#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace testing;

#include "Cli.h"
#include "SampleCommand.h"

#include <opencash/api/Api.h>

using AppContext = opencash::cli::AppContext;
using Api = opencash::api::Api;

AppContext appContext;
Api api;

class MockSampleCommand : public opencash::cli::SampleCommand {
  public:
    MockSampleCommand() : SampleCommand(appContext, api) { }
    MOCK_METHOD1(run, int(const std::vector<std::string>&));
};

TEST(Cli, sampleShouldDelegateToSampleCommand) {
  // given
  static MockSampleCommand sampleCommand; // must be static for inner return

  class PartialMockCli : public opencash::cli::Cli {
    protected:
      virtual opencash::cli::SampleCommand& getSampleCommand() override {
        return sampleCommand;
      }
  };

  const int argc = 4;
  const char *argv[] = {"opencash", "sample", "-o", "sample.opencash"};

  // expect
  EXPECT_CALL(sampleCommand, run(ElementsAre("sample", "-o", "sample.opencash")));

  // when
  PartialMockCli().run(argc, argv);
}
