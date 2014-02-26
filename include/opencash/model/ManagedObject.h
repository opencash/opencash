#ifndef __OC_MODEL_MANAGEDOBJECT_H_
#define __OC_MODEL_MANAGEDOBJECT_H_

#include "opencash/model/ObservableModel.h"

#include <odb/core.hxx>

namespace opencash { namespace controller {
  class ManagedObjectContext;
}}

namespace opencash { namespace model {

  #pragma db object abstract
  class ManagedObject : public ObservableModel {
    public:
      using Uuid = std::string;

    public:
      const Uuid & getUuid() const;

    private:
      friend class ::opencash::controller::ManagedObjectContext;
      friend class ::odb::access;

      void setUuid(const Uuid& uuid);

    private:
      #pragma db id set(setUuid)
      Uuid _uuid;
  };

}}

#endif
