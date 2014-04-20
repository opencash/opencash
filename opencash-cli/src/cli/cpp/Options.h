#ifndef __OC_CLI_OPTIONS_H_
#define __OC_CLI_OPTIONS_H_

#include <iostream>
#include <string>
#include <vector>

namespace opencash { namespace cli {

  class Options {
    public:
      Options();
      const std::string toString();

      const std::vector<std::string>& getCommandArgs() const;
      void setCommandArgs(const std::vector<std::string>& args);

      int getVerbosity() const;
      void setVerbosity(int verbosity);

    private:
      std::vector<std::string> _commandArgs;
      int _verbosity;
  };

}}

#endif
