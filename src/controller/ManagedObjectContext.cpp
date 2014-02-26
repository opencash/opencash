#include "opencash/controller/ManagedObjectContext.h"
#include "opencash/model/Account.h"
#include "opencash/model/Split.h"

#include <poco/UUID.h>
#include <poco/UUIDGenerator.h>

namespace opencash { namespace controller {

  IMPORT_ALIAS(Account);
  IMPORT_ALIAS(Split);
  using Uuid = ManagedObjectContext::Uuid;

  // public

  AccountPtr ManagedObjectContext::createAccount() {
    AccountPtr account(new Account);
    assignUuid(*account);
    return account;
  }

  SplitPtr ManagedObjectContext::createSplit() {
    SplitPtr split(new Split);
    assignUuid(*split);
    return split;
  }

  bool ManagedObjectContext::hasUuid(const Uuid & uuid) const {
    return _uuids.find(uuid) != _uuids.end();
  }

  // protected

  void ManagedObjectContext::assignUuid(ManagedObject & mobj) {
    Uuid uuid(generateUuid());
    mobj.setUuid(uuid);
    _uuids.insert(uuid);
  }

  Uuid ManagedObjectContext::generateUuid() const {
    return Poco::UUIDGenerator::defaultGenerator().createOne().toString();
  }

} }
