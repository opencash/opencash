#include "opencash/core/ManagedObject.h"

namespace opencash { namespace core {

  using Uuid = ManagedObject::Uuid;

  const Uuid & ManagedObject::getUuid() const {
    return _uuid;
  }

  void ManagedObject::setUuid(const Uuid& uuid) {
    _uuid = uuid;
  }

}}
