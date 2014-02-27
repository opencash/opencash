#ifndef __OC_CLI_CLI_H_
#define __OC_CLI_CLI_H_

#include "AppContext.h"

#include <iostream>

namespace opencash { namespace cli {

  class Cli {
    public:
      Cli(std::ostream& cout = std::cout);
      int run(int argc, const char** argv);

    private:
      void parseOptions(int argc, const char **argv);

    private:
      AppContext _ctx;
  };

}}

#endif
