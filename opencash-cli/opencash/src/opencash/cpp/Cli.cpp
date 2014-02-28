#include "Cli.h"
#include "definitions.h"

#include <tclap/CmdLine.h>

namespace opencash { namespace cli {

  class ExitException {
    public:
      ExitException(int estat) : _estat(estat) {}
      int getExitStatus() const { return _estat; }

    private:
      int _estat;
  };

  Cli::Cli(std::ostream& cout, std::ostream& cerr) : _ctx(cout, cerr) {}

  int Cli::run(int argc, const char **argv) {
    std::ostream& cout(_ctx.cout);
    Options& options(_ctx.getOptions());

    try {
      parseOptions(argc, argv);
    }
    catch (ExitException& e) {
      return e.getExitStatus();
    }

    if (options.getVerbosity() >= 2) {
      cout << "Command line options:" << std::endl;
      cout << options.toString() << std::endl;
    }

    cout << "Hello World! Printed on cout" << std::endl;
    cout << "Running command: " << options.getCommand() << std::endl;

    return 0;
  }

  void Cli::parseOptions(int argc, const char** argv) {
    // TCLAP prints to standard io so we need to hijack these streams
    hijackStdIo();

    try {
      TCLAP::CmdLine parser("OpenCash, a free open-source accounting software.",
          ' ', VERSION);

      // verbosity

      TCLAP::MultiSwitchArg verboseArg("v", "verbose",
          "Increase verbosity (1 = INFO, 2 = FINE, 3 = FINEST)", parser);

      // command

      std::vector<std::string> commands;
      commands.push_back("kickstart");
      TCLAP::ValuesConstraint<std::string> availCommands(commands);

      TCLAP::UnlabeledValueArg<std::string> commandArg("command",
          "OpenCash command to run", true, "none", &availCommands, parser);

      // TCLAP should rethrow any exceptions while parsing
      parser.setExceptionHandling(false);
      parser.parse(argc, argv);

      // retrieve values
      Options& options(_ctx.getOptions());
      options.setCommand(commandArg.getValue());
      options.setVerbosity(verboseArg.getValue());
    }
    catch (TCLAP::ArgException& e) {
      std::cerr << "error: " << e.what() << std::endl;
      restoreStdIo();
      throw ExitException(1);
    }
    catch (TCLAP::ExitException& e) {
      restoreStdIo();
      throw ExitException(e.getExitStatus());
    }

    restoreStdIo();
  }

  void Cli::hijackStdIo() {
    _ioBackups.cout = std::cout.rdbuf();
    std::cout.rdbuf(_ctx.cout.rdbuf());

    _ioBackups.cerr = std::cerr.rdbuf();
    std::cerr.rdbuf(_ctx.cerr.rdbuf());
  }

  void Cli::restoreStdIo() {
    std::cout.rdbuf(_ioBackups.cout);
    std::cerr.rdbuf(_ioBackups.cerr);
  }

}}
