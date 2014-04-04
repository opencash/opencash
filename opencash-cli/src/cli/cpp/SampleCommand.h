#ifndef __OC_CLI_SAMPLECOMMAND_H_
#define __OC_CLI_SAMPLECOMMAND_H_

#include "AppContext.h"

namespace opencash { namespace api {
  class Api;
}}

namespace opencash { namespace cli {

  class SampleCommand {
    public:
      SampleCommand(
          AppContext& ctx,
          const api::Api& api);
      int run(int argc, const char** argv);

    private:
      void parseOptions(int argc, const char** argv);

    private:
      AppContext& _ctx;
      const api::Api& _api;
      std::string _outputFileName;
  };

}}

#endif
