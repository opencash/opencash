#include <igloo/igloo.h>
using namespace igloo;

#include "Cli.h"

using Cli = opencash::cli::Cli;

Context(command_sample)
{
  Spec(should_run)
  {
    std::stringstream cout;
    const char *argv[] = {Name().c_str(), "sample"};
    Cli(cout).run(2, argv);
    Assert::That(cout.str(), Contains("Running command: sample"));
  }
};
