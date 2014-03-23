#include "Options.h"

#include <sstream>

namespace opencash { namespace cli {

  Options::Options() {
    _command = "";
    _verbosity = 0;
  }

  const std::string Options::toString() {
    std::stringstream ss;

    ss << "{" << std::endl;
    ss << "command = \"" << getCommand() << "\"" << std::endl;
    ss << "verbosity = " << getVerbosity() << std::endl;
    ss << "}" << std::endl;

    return ss.str();
  }

  const std::string& Options::getCommand() const {
    return _command;
  }

  void Options::setCommand(std::string command) {
    _command = command;
  }

  int Options::getVerbosity() const {
    return _verbosity;
  }

  void Options::setVerbosity(int verbosity) {
    _verbosity = verbosity;
  }
}}
