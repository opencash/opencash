#ifndef __OC_CLI_OPTIONS_H_
#define __OC_CLI_OPTIONS_H_

#include <iostream>
#include <string>

namespace opencash { namespace cli {

  class Options {
    public:
      const std::string toString();

      const std::string& getCommand() const;
      void setCommand(std::string command);

      int getVerbosity() const;
      void setVerbosity(int verbosity);

    private:
      std::string _command;
      int _verbosity;
  };

}}

#endif
