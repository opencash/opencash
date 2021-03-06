#include "PrefixedStreamBuf.h"

namespace opencash { namespace cli {

  using int_type = std::streambuf::int_type;

  PrefixedStreamBuf::PrefixedStreamBuf(std::string prefix, std::streambuf *delegate)
    :
      _prefix(prefix),
      _delegate(delegate),
      _newLine(true)
  { }

  int_type PrefixedStreamBuf::overflow(int_type c) {
    if (_newLine && c != traits_type::eof()) {
      _newLine = false;
      _delegate->sputn(_prefix.c_str(), _prefix.length());
    }

    if (c == '\n') {
      _newLine = true;
    }

    return _delegate->sputc(c);
  }

  int_type PrefixedStreamBuf::sync() {
    return _delegate->pubsync();
  }

}}
