#ifndef __OC_CLI_APPCONTEXT_H_
#define __OC_CLI_APPCONTEXT_H_

#include "Options.h"
#include "PrefixedStreamBuf.h"

#include <iostream>

namespace opencash { namespace cli {

  class AppContext {
    public:
      AppContext(std::ostream& cout = std::cout,
          std::ostream& cerr = std::cerr);
      Options& getOptions();

    public:
      // safe because ostream reference can't be changed once assigned
      std::ostream& cout;
      std::ostream& cerr;
      std::ostream& error;

    private:
      Options _options;
      PrefixedStreamBuf errorPrefixedBuf;
  };

}}

#endif
