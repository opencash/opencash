#ifndef __OC_CONTROLLER_DOCUMENTCONTROLLER_H_
#define __OC_CONTROLLER_DOCUMENTCONTROLLER_H_

#include "opencash/model/definitions.h"

#include <odb/database.hxx>
#include <odb/session.hxx>
#include <string>
#include <memory>

namespace opencash { namespace model {
  class Account;
  class Split;
  class Transaction;

  class AccountsMeta;
  class TransactionsMeta;
}}

namespace opencash { namespace controller {

  class DocumentController {
    public: // public using aliases
      IMPORT_ALIAS(Account);
      IMPORT_ALIAS(Split);
      IMPORT_ALIAS(Transaction);

    public: // general methods
      DocumentController(const std::string & dbFilename,
          bool shouldInitialize = false);

    public: // related to Accounts
      model::AccountsMeta * getAccountsMeta() const;
      
      Accounts retrieveAccounts() const;
      Splits retrieveSplits() const;
      Transactions retrieveTransactions() const;

      AccountPtr newAccount() const;
      SplitPtr newSplit() const;
      TransactionPtr newTransaction() const;
      
      void persistAccount(const model::Account& account);
      void persistSplit(const model::Split& split);
      void persistTransaction(const model::Transaction& transaction);

    private: // private methods
      void initializeDocument();
      void updateAccountsMeta();
      void updateTransactionsMeta();

    private: // private members
      const std::string _dbFilename;
      std::unique_ptr<model::AccountsMeta> _accountsMeta;
      std::unique_ptr<model::TransactionsMeta> _transactionsMeta;
      std::unique_ptr<odb::database> _db;
  };

}}

#endif
