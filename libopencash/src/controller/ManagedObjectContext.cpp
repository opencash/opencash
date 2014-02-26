#include "opencash/controller/ManagedObjectContext.h"
#include "opencash/model/Account.h"
#include "opencash/model/Split.h"

#include <poco/UUID.h>
#include <poco/UUIDGenerator.h>

namespace opencash { namespace controller {

  IMPORT_ALIAS(Account);
  IMPORT_ALIAS(Split);

  using Uuid = model::ManagedObject::Uuid;

  AccountPtr ManagedObjectContext::createAccount() const {
    AccountPtr account(new Account);
    account->setUuid(generateUuid());
    return account;
  }

  SplitPtr ManagedObjectContext::createSplit() const {
    SplitPtr split(new Split);
    split->setUuid(generateUuid());
    return split;
  }

  Uuid ManagedObjectContext::generateUuid() const {
    return Poco::UUIDGenerator::defaultGenerator().createOne().toString();
  }

} }
