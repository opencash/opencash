#ifndef __OC_CORE_ACCOUNTSMETA_H_
#define __OC_CORE_ACCOUNTSMETA_H_

#include "ObservableModel.h"
#include "Account.h"

#include <odb/core.hxx>

namespace opencash { namespace core {

  #pragma db view object(Account)
  class AccountsMeta : public ObservableModel {
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

#endif
