#include <igloo/igloo.h>
using namespace igloo;

#include "Cli.h"

using Cli = opencash::cli::Cli;

Context(kickstart_command)
{
  Spec(should_run)
  {
    std::stringstream cout;
    const char *argv[] = {Name().c_str(), "kickstart"};
    opencash::cli::Cli(cout).run(2, argv);
    Assert::That(cout.str(), Contains("Running command: kickstart"));
  }
};
