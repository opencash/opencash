#ifndef __OC_CLI_SAMPLECOMMAND_H_
#define __OC_CLI_SAMPLECOMMAND_H_

#include "AppContext.h"

namespace opencash { namespace api {
  class Api;
}}

namespace opencash { namespace cli {

  class SampleCommand {
    public:
      SampleCommand(AppContext& ctx, const api::Api& api);
      virtual ~SampleCommand();
      virtual int run(const std::vector<std::string>& args);

    private:
      void parseOptions(const std::vector<std::string>& args);

    private:
      AppContext& _ctx;
      const api::Api& _api;
      std::string _outputFileName;
  };

}}

#endif
