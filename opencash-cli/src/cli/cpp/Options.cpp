#include "Options.h"

#include <sstream>

namespace opencash { namespace cli {

  Options::Options() {
    _verbosity = 0;
  }

  const std::string Options::toString() {
    std::stringstream ss;

    ss << "{" << std::endl;
    ss << "  commandArgs = {" << std::endl;
    for (auto arg : getCommandArgs()) {
      ss << "    \"" << arg << "\"" << std::endl;
    }
    ss << "  }" << std::endl;
    ss << "  verbosity = " << getVerbosity() << std::endl;
    ss << "}" << std::endl;

    return ss.str();
  }

  const std::vector<std::string>& Options::getCommandArgs() const {
    return _commandArgs;
  }

  void Options::setCommandArgs(const std::vector<std::string>& args) {
    _commandArgs.clear();
    for (auto arg : args) {
      _commandArgs.push_back(arg);
    }
  }

  int Options::getVerbosity() const {
    return _verbosity;
  }

  void Options::setVerbosity(int verbosity) {
    _verbosity = verbosity;
  }
}}
