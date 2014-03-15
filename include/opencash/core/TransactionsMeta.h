#ifndef __OC_CORE_TRANSACTIONSMETA_H_
#define __OC_CORE_TRANSACTIONSMETA_H_

#include "ObservableModel.h"
#include "Transaction.h"

#include <odb/core.hxx>

namespace opencash { namespace core {

  #pragma db view object(Transaction)
  class TransactionsMeta : public ObservableModel {
    friend class odb::access;

    public:
      std::size_t getCount() const;

    private:
      void setCount(std::size_t count);

    private:
      #pragma db column("count(*)") set(setCount)
      std::size_t _count;
  };

}}

#endif //__OC_CORE_TRANSACTIONSMETA_H_
