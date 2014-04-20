#include <igloo/igloo.h>
using namespace igloo;

#include "Cli.h"
#include <Poco/File.h>

using Cli = opencash::cli::Cli;

Context(command_sample)
{
  void SetUp() {
    Poco::File f("test.opencash");
    if (f.exists()) f.remove();
  }

  Spec(should_run)
  {
    std::stringstream cout;
    const char *argv[] = {Name().c_str(), "sample", "-o", "test.opencash"};
    Cli(cout).run(4, argv);
    Assert::That(cout.str(), Contains("Creating sample at 'test.opencash'"));
  }
};
