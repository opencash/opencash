#include "Cli.h"

int main(int argc, const char** argv) {
  return opencash::cli::Cli().run(argc, argv);
}
