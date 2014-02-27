#include "AppContext.h"

namespace opencash { namespace cli {

  AppContext::AppContext(std::ostream& cout_) : cout(cout_) {}

  Options& AppContext::getOptions() {
    return _options;
  }

}}
