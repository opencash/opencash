#ifndef __OC_CONTROLLER_MANAGEDOBJECTCONTAINER_H_
#define __OC_CONTROLLER_MANAGEDOBJECTCONTAINER_H_

#include "opencash/model/ManagedObject.h"
#include "opencash/model/definitions.h"

#include <set>

namespace opencash { namespace model {
  class Account;
  class Split;
}}

namespace opencash { namespace controller {

  class ManagedObjectContext {
    public:
      IMPORT_ALIAS(Account);
      IMPORT_ALIAS(Split);
      using ManagedObject = model::ManagedObject;
      using Uuid = ManagedObject::Uuid;

    public:
      AccountPtr createAccount();
      SplitPtr createSplit();
      bool hasUuid(const Uuid & uuid) const;

    protected:
      void assignUuid(ManagedObject & mobj);
      Uuid generateUuid() const;

    private:
      std::set<Uuid> _uuids;
  };

}}

#endif
