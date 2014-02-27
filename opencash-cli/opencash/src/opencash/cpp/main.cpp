#include "Cli.h"

int main(int argc, const char** argv) {
  opencash::cli::Cli cli;
  return cli.run(argc, argv);
}
