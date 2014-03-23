#include <igloo/igloo.h>
using namespace igloo;

#include "Cli.h"
#include "definitions.h"

using Cli = opencash::cli::Cli;

Context(no_command)
{
  Spec(should_print_version)
  {
    std::stringstream cout;
    const char *argv[] = {Name().c_str(), "--version"};
    Cli(cout).run(2, argv);
    Assert::That(cout.str(), Contains("version: " VERSION));
  }
};
