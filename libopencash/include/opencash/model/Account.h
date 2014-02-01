#ifndef __OC_MODEL_ACCOUNT_H_
#define __OC_MODEL_ACCOUNT_H_

#include "opencash/model/definitions.h"
#include "opencash/model/ObservableModel.h"

#include <Poco/UUID.h>
#include <odb/core.hxx>
#include <string>
#include <memory>

namespace opencash { namespace model {

  class Split;
  IMPORT_ALIAS(Split);

  #pragma db object session table("accounts") pointer(std::shared_ptr)
  class Account :
    public ::std::enable_shared_from_this<Account>,
    public ObservableModel
  {
    friend class odb::access;

    public:
      CREATE_ALIAS(Account);

      enum class AccountType {
        None,
        Root,
        Asset,
        Liability,
        Expense,
        Income,
        Equity,
      };

    public:
      Account(const std::string & uuid);

      DECL_COMPARATORS(Account);

      std::string getUuid() const;

      std::string getName() const;
      void setName(std::string name);

      std::string getDescr() const;
      void setDescr(std::string descr);

      AccountType getType() const;
      void setType(AccountType type);

      AccountPtr getParent() const;
      void setParent(AccountPtr parent);

	  void removeParent();

      const WeakAccounts & getChildren() const;

      void addSplit(SplitPtr split);
      void removeSplit(SplitPtr split);
      const Splits& getSplits() const;
    private:
      Account();
	  void unregisterFromCurrentParent();
	  void registerWithParent(AccountPtr parent);

      #pragma db id
      std::string _uuid;

      #pragma db set(setName)
      std::string _name;

      #pragma db set(setDescr)
      std::string _descr;

      #pragma db set(setType)
      AccountType _type;

      #pragma db set(setParent)
      AccountPtr _parent;

      #pragma db value_not_null inverse(_parent)
      WeakAccounts _children;

      #pragma db value_not_null inverse(_account)
      Splits _splits;
  };

} }

//odb manual pg. 119
#ifdef ODB_COMPILER
#include "opencash/model/Split.h"
#endif

#endif
