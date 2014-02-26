#include "opencash/model/ManagedObject.h"

namespace opencash { namespace model {

  using Uuid = ManagedObject::Uuid;

  const Uuid & ManagedObject::getUuid() const {
    return _uuid;
  }

  void ManagedObject::setUuid(const Uuid& uuid) {
    _uuid = uuid;
  }

}}
