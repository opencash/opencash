#ifndef __OC_MODEL_TRANSACTION_H_
#define __OC_MODEL_TRANSACTION_H_

#include "opencash/model/definitions.h"
#include "opencash/model/ObservableModel.h"

#include <Poco/UUID.h>
#include <odb/core.hxx>
#include <string>
#include <memory>

namespace opencash { namespace model {

  class Split;
  IMPORT_ALIAS(Split);

  #pragma db object session table("transactions") pointer(std::shared_ptr)
  class Transaction :
    public ::std::enable_shared_from_this<Transaction>,
    public ObservableModel {
    friend class odb::access;

    public:
      CREATE_ALIAS(Transaction);

      Transaction(const std::string& uuid);

      DECL_COMPARATORS(Transaction);

      std::string getUuid() const;

      std::string getDescription() const;
      void setDescription(const std::string& description);

      void addSplit(SplitPtr split);
      void removeSplit(SplitPtr split);
      const Splits& getSplits() const;
    private:
      Transaction();
      
      #pragma db id
      std::string _uuid;

      #pragma db set(setDescription)
      std::string _description;

      #pragma db value_not_null inverse(_transaction)
      Splits _splits;
  };

} }

//odb manual pg. 119
#ifdef ODB_COMPILER
#include "opencash/model/Split.h"
#endif

#endif
