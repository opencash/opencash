#include "opencash/core/DocumentController.h"
#include "generated/Account-odb.hxx"
#include "generated/AccountsMeta-odb.hxx"
#include "generated/Transaction-odb.hxx"
#include "generated/TransactionsMeta-odb.hxx"
#include "generated/Split-odb.hxx"

#include <odb/database.hxx>
#include <odb/sqlite/database.hxx>
#include <odb/transaction.hxx>
#include <odb/schema-catalog.hxx>
#include <odb/session.hxx>

#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>

#include <memory>

namespace opencash { namespace core {

  using namespace odb::core;

  IMPORT_ALIAS(Account);
  IMPORT_ALIAS(Split);
  IMPORT_ALIAS(Transaction);

  DocumentController::DocumentController(
      const std::string & dbFilename,
      bool shouldInitialize
      ) :
    _dbFilename(dbFilename),
    _accountsMeta(new AccountsMeta()),
    _transactionsMeta(new TransactionsMeta()),
    _db(new odb::sqlite::database(dbFilename,
          SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE))
  {
    if (shouldInitialize) {
      initializeDocument();
    }
  }

  AccountsMeta* DocumentController::getAccountsMeta() const
  {
    return _accountsMeta.get();
  }

  Accounts DocumentController::retrieveAccounts() const {
    using result = odb::result<Account>;
    using query = odb::query<Account>;  

    Accounts ret;

    session s;
    transaction tx(_db->begin());
    result res(_db->query<Account>());
    
    for (result::iterator it = res.begin(); it != res.end(); ++it)
      ret.push_back(it.load());

    tx.commit();

    return ret;
  }

  Splits DocumentController::retrieveSplits() const {
    using result = odb::result<Split>;
    using query = odb::query<Split>;  

    Splits splits;

    session s;
    transaction tx(_db->begin());
    result res(_db->query<Split>());

    for(result::iterator it = res.begin(); it != res.end(); ++it)
      splits.push_back(it.load());

    tx.commit();


    return splits;
  }

  Transactions DocumentController::retrieveTransactions() const {
    using result = odb::result<Transaction>;
    using query = odb::query<Transaction>;  

    Transactions transactions;

    session s;
    transaction tx(_db->begin());
    result res(_db->query<Transaction>());

    for(result::iterator it = res.begin(); it != res.end(); ++it)
      transactions.push_back(it.load());

    tx.commit();

    return transactions;
  }

  AccountPtr DocumentController::newAccount() const
  {
    // TODO: make sure this UUID doesn't exist in DB yet
    return AccountPtr(new Account());
  }

  SplitPtr DocumentController::newSplit() const {
    return SplitPtr(new Split());
  }

  TransactionPtr DocumentController::newTransaction() const {
    return TransactionPtr(new Transaction());
  }

  void DocumentController::persistAccount(const Account & account) {
    transaction t(_db->begin());
    _db->persist(account);
    t.commit();

    updateAccountsMeta();
  }

  void DocumentController::persistSplit(const Split& split) {
    transaction t(_db->begin());
    _db->persist(split);
    t.commit();
  }

  void DocumentController::persistTransaction(const Transaction& tx) {
    transaction t(_db->begin());
    _db->persist(tx);
    t.commit();

    updateTransactionsMeta();
  }

  void DocumentController::initializeDocument()
  {
    // {
    //   transaction t(_db->begin());
    //   schema_catalog::drop_schema(*_db);
    //   t.commit();
    // }
    {
      transaction t(_db->begin());
      schema_catalog::create_schema(*_db);
      t.commit();
    }
    {
      auto acc = newAccount();
      acc->setName("Root Account");
      acc->setDescr("A pseudo account to represent the root of the account structure");
      acc->setType(Account::AccountType::Root);

      transaction t(_db->begin());
      _db->persist(acc);
      t.commit();
    }

    updateAccountsMeta();
    updateTransactionsMeta();
  }

  void DocumentController::updateAccountsMeta()
  {
    transaction t(_db->begin());
    odb::result<AccountsMeta> r(_db->query<AccountsMeta>());
    r.begin().load(*_accountsMeta);
    t.commit();
  }

  void DocumentController::updateTransactionsMeta()
  {
    transaction t(_db->begin());
    odb::result<TransactionsMeta> r(_db->query<TransactionsMeta>());
    r.begin().load(*_transactionsMeta);
    t.commit();
  }

} }
