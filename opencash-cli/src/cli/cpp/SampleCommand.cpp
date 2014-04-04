#include "SampleCommand.h"
#include "definitions.h"

#include <opencash/api/Api.h>

#include <string>
#include <tclap/CmdLine.h>

namespace opencash { namespace cli {

  class ExitException {
    public:
      ExitException(int estat) : _estat(estat) {}
      int getExitStatus() const { return _estat; }

    private:
      int _estat;
  };

  SampleCommand::SampleCommand(AppContext& ctx,
      const api::Api& api)
    :
      _ctx(ctx),
      _api(api)
  {}

  int SampleCommand::run(int argc, const char **argv) {
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

    _api.createSampleFile(_outputFileName);

    return 0;
  }

  void SampleCommand::parseOptions(int argc, const char** argv) {
    try {
      TCLAP::CmdLine parser(
          "OpenCash, a free open-source accounting software.",
          ' ', VERSION);

      // output filename
      TCLAP::ValueArg<std::string> outputFileNameArg("o", "output",
          "Output filename", true, "output.opencash", "filename", parser);

      // TCLAP should rethrow any exceptions while parsing
      parser.setExceptionHandling(false);
      parser.parse(argc, argv);

      // retrieve values
      _outputFileName = outputFileNameArg.getValue();
    }
    catch (TCLAP::ArgException& e) {
      std::cerr << "error: " << e.what() << std::endl;
      throw ExitException(1);
    }
    catch (TCLAP::ExitException& e) {
      throw ExitException(e.getExitStatus());
    }
  }

}}
