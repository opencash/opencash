#ifndef __OC_CLI_CLI_H_
#define __OC_CLI_CLI_H_

#include "AppContext.h"
#include "SampleCommand.h"
#include <opencash/api/Api.h>

#include <iostream>

namespace opencash { namespace cli {

  class Cli {
    public:
      Cli(std::ostream& cout = std::cout, std::ostream& cerr = std::cerr);
      virtual ~Cli();
      int run(int argc, const char** argv);

    protected:
      virtual SampleCommand& getSampleCommand();

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
      opencash::api::Api _api;
      SampleCommand _sampleCommand;
  };

}}

#endif
