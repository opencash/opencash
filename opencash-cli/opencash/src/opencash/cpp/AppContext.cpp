#include "AppContext.h"

namespace opencash { namespace cli {

  AppContext::AppContext(std::ostream& cout, std::ostream& cerr) :
    cout(cout),
    cerr(cerr),
    error(cerr),
    errorPrefixBuf("[!] ", cerr.rdbuf())
  {
    error.rdbuf(&errorPrefixBuf);
  }

  Options& AppContext::getOptions() {
    return _options;
  }

}}
