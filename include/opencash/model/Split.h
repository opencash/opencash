#ifndef __OC_MODEL_SPLIT_H_
#define __OC_MODEL_SPLIT_H_

#include "opencash/model/definitions.h"
#include "opencash/model/Transaction.h"
#include "opencash/model/Account.h"

#include <Poco/UUID.h>
#include <odb/core.hxx>
#include <string>
#include <memory>

namespace opencash { namespace model {

  IMPORT_ALIAS(Transaction);
  IMPORT_ALIAS(Account);

  #pragma db object session table("splits") pointer(std::shared_ptr)
  class Split :
    public ::std::enable_shared_from_this<Split>,
    public ManagedObject
  {
    friend class odb::access;

    public:
      CREATE_ALIAS(Split);

      DECL_COMPARATORS(Split);

      TransactionWeakPtr getTransaction() const;
      void setTransaction(TransactionWeakPtr transaction);

      AccountWeakPtr getAccount() const;
      void setAccount(AccountWeakPtr account);

      std::string getMemo() const;
      void setMemo(const std::string& memo);

      std::string getAction() const;
      void setAction(const std::string& action);

      double getValue() const;
      void setValue(double value);

    private:
      #pragma db not_null
      TransactionWeakPtr _transaction; //pg. 112

      #pragma db not_null
      AccountWeakPtr _account; //pg. 112

      #pragma db set(setMemo)
      std::string _memo;

      #pragma db set(setAction)
      std::string _action;

      #pragma db not_null set(setValue)
      double _value;
  };

} }

#endif
