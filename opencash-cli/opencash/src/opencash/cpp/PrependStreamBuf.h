#ifndef __OC_CLI_PREPENDSTREAMBUF_H_
#define __OC_CLI_PREPENDSTREAMBUF_H_

#include <streambuf>

namespace opencash { namespace cli {

  class PrefixStreamBuf: public std::streambuf {
    public:
      PrefixStreamBuf(std::string prefix, std::streambuf* delegate);

    protected:
      virtual int_type overflow(int_type c);
      virtual int_type sync();

    private:
      std::string _prefix;
      std::streambuf *_delegate;
      bool _newLine;
  };

}}

#endif
