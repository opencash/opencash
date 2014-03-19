#include "AppContext.h"

namespace opencash { namespace cli {

  AppContext::AppContext(std::ostream& cout, std::ostream& cerr) :
    cout(cout),
    cerr(cerr),
    error(cerr),
    errorPrefixedBuf("[!] ", cerr.rdbuf())
  {
    error.rdbuf(&errorPrefixedBuf);
  }

  Options& AppContext::getOptions() {
    return _options;
  }

}}
