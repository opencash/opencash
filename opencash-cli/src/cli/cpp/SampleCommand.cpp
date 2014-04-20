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
  { }

  SampleCommand::~SampleCommand() { }

  int SampleCommand::run(const std::vector<std::string>& args) {
    std::ostream& cout(_ctx.cout);

    try {
      parseOptions(args);
    }
    catch (ExitException& e) {
      return e.getExitStatus();
    }

    cout << "Creating sample at '" << _outputFileName << "'" << std::endl;
    _api.createSampleFile(_outputFileName);
    return 0;
  }

  void SampleCommand::parseOptions(const std::vector<std::string>& args) {
    try {
      TCLAP::CmdLine parser(
          "OpenCash, a free open-source accounting software.",
          ' ', VERSION);

      // output filename
      TCLAP::ValueArg<std::string> outputFileNameArg("o", "output",
          "Output filename", true, "output.opencash", "filename", parser);

      // TCLAP should rethrow any exceptions while parsing
      parser.setExceptionHandling(false);

      // parse (needs copy because it modifies the vector)
      std::vector<std::string> argsCopy(args);
      parser.parse(argsCopy);

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
