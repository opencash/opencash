#ifndef __OC_CORE_DOCUMENTCONTROLLER_H_
#define __OC_CORE_DOCUMENTCONTROLLER_H_

#include "definitions.h"

#include <odb/database.hxx>
#include <odb/session.hxx>
#include <string>
#include <memory>

namespace opencash { namespace core {
  class Account;
  class Split;
  class Transaction;

  class AccountsMeta;
  class TransactionsMeta;

  class DocumentController {
    public: // public using aliases
      IMPORT_ALIAS(Account);
      IMPORT_ALIAS(Split);
      IMPORT_ALIAS(Transaction);

    public: // general methods
      DocumentController(const std::string & dbFilename,
          bool shouldInitialize = false);

    public: // related to Accounts
      AccountsMeta* getAccountsMeta() const;
      
      Accounts retrieveAccounts() const;
      Splits retrieveSplits() const;
      Transactions retrieveTransactions() const;

      AccountPtr newAccount() const;
      SplitPtr newSplit() const;
      TransactionPtr newTransaction() const;
      
      void persistAccount(const Account& account);
      void persistSplit(const Split& split);
      void persistTransaction(const Transaction& transaction);

    private: // private methods
      void initializeDocument();
      void updateAccountsMeta();
      void updateTransactionsMeta();

    private: // private members
      const std::string _dbFilename;
      std::unique_ptr<AccountsMeta> _accountsMeta;
      std::unique_ptr<TransactionsMeta> _transactionsMeta;
      std::unique_ptr<odb::database> _db;
  };

}}

#endif
