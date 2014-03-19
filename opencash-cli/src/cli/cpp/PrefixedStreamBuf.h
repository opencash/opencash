#ifndef __OC_CLI_PREFIXEDSTREAMBUF_H_
#define __OC_CLI_PREFIXEDSTREAMBUF_H_

#include <streambuf>

namespace opencash { namespace cli {

  class PrefixedStreamBuf : public std::streambuf {
    public:
      PrefixedStreamBuf(std::string prefix, std::streambuf* delegate);

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
