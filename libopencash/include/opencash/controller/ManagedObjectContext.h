#ifndef __OC_CONTROLLER_MANAGEDOBJECTCONTAINER_H_
#define __OC_CONTROLLER_MANAGEDOBJECTCONTAINER_H_

#include "opencash/model/ManagedObject.h"
#include "opencash/model/definitions.h"

namespace opencash { namespace model {
  class Account;
  class Split;
}}

namespace opencash { namespace controller {

  class ManagedObjectContext {
    public:
      IMPORT_ALIAS(Account);
      IMPORT_ALIAS(Split);

    public:
      AccountPtr createAccount() const;
      SplitPtr createSplit() const;

    protected:
      model::ManagedObject::Uuid generateUuid() const;
  };

}}

#endif
