#include <igloo/igloo.h>
using namespace igloo;

#include "Cli.h"

using Cli = opencash::cli::Cli;

Context(iostreams)
{
  Spec(should_honor_cout_stream)
  {
    std::stringstream cout;
    const char *argv[] = {Name().c_str(), "--help"};
    Cli(cout).run(2, argv);
    Assert::That(cout.str(), Contains("USAGE:"));
  }

  Spec(should_honor_cerr_stream)
  {
    std::stringstream cerr;
    const char *argv[] = {Name().c_str(), "--nonexisting"};
    Cli(std::cout, cerr).run(2, argv);
    Assert::That(cerr.str(), StartsWith("[!] error:"));
  }
};
