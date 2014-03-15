#include "opencash/core/TransactionsMeta.h"

#include <sstream>
#include <iostream>

namespace opencash { namespace core {

  std::size_t TransactionsMeta::getCount() const
  {
    return _count;
  }

  void TransactionsMeta::setCount(std::size_t count)
  {
    willChange("count");
    _count = count;
    didChange("count");
  }

}}
