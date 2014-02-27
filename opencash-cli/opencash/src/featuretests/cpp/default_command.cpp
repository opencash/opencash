#include <igloo/igloo.h>
using namespace igloo;

#include "Cli.h"
#include "definitions.h"

Context(default_command)
{
  Spec(should_print_version)
  {
    std::stringstream cout;
    opencash::cli::Cli cli(cout);
    const char *argv[] = {Name().c_str(), "--version"};
    cli.run(2, argv);
    Assert::That(cout.str(), Contains("version: " VERSION));
  }
};
