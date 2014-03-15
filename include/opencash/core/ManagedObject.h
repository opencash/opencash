#ifndef __OC_CORE_MANAGEDOBJECT_H_
#define __OC_CORE_MANAGEDOBJECT_H_

#include "ObservableModel.h"

#include <odb/core.hxx>

namespace opencash { namespace core {
  class ManagedObjectContext;

  #pragma db object abstract
  class ManagedObject : public ObservableModel {
    public:
      using Uuid = std::string;

    public:
      const Uuid & getUuid() const;

    private:
      friend class ManagedObjectContext;
      friend class ::odb::access;

      void setUuid(const Uuid& uuid);

    private:
      #pragma db id set(setUuid)
      Uuid _uuid;
  };

}}

#endif
