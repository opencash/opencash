#ifndef __OC_CLI_APPCONTEXT_H_
#define __OC_CLI_APPCONTEXT_H_

#include "Options.h"

#include <iostream>

namespace opencash { namespace cli {

  class AppContext {
    public:
      AppContext(std::ostream& cout_ = std::cout);
      Options& getOptions();

    public:
      // safe because ostream reference can't be changed once assigned
      std::ostream& cout;

    private:
      Options _options;
  };

}}

#endif
