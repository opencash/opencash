#include <igloo/igloo.h>
using namespace igloo;

#include "Cli.h"

Context(kickstart_command)
{
  Spec(should_run)
  {
    std::stringstream cout;
    opencash::cli::Cli cli(cout);
    const char *argv[] = {Name().c_str(), "kickstart"};
    cli.run(2, argv);
    Assert::That(cout.str(), Contains("Running command: kickstart"));
  }
};
