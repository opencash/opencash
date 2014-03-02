#ifndef __OC_CLI_CLI_H_
#define __OC_CLI_CLI_H_

#include "AppContext.h"

#include <iostream>

namespace opencash { namespace cli {

  class Cli {
    public:
      Cli(std::ostream& cout = std::cout, std::ostream& cerr = std::cerr);
      int run(int argc, const char** argv);

    private:
      void parseOptions(int argc, const char** argv);
      void hijackStdIo();
      void restoreStdIo();

    private:
      class IoBackups {
        public:
          std::streambuf* cout;
          std::streambuf* cerr;
      };

    private:
      AppContext _ctx;
      IoBackups _ioBackups;
  };

}}

#endif
