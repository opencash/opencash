#include "opencash/model/Transaction.h"
#include "opencash/model/Split.h"

namespace opencash { namespace model {

  IMPORT_ALIAS(Transaction);

  IMPL_COMPARATORS(Transaction);

  std::string Transaction::getDescription() const {
  	return _description;
  }

  void Transaction::setDescription(const std::string& description) {
    willChange("description");
  	_description = description;
    didChange("description");
  }

  void Transaction::addSplit(SplitPtr split) {
    auto it = std::find(_splits.begin(), _splits.end(), split);
    if(it == _splits.end()) {
      size_t index = _splits.size();

      willChangeAtIndex("splits", index, ChangeType::Insertion);
      _splits.push_back(split);
      didChangeAtIndex("splits", index, ChangeType::Insertion);

      split->setTransaction(shared_from_this());
    }
  }

  void Transaction::removeSplit(SplitPtr split) {
    auto it = std::find(_splits.begin(), _splits.end(), split);
    if(it != _splits.end()) {
      size_t index = std::distance(_splits.begin(), it);

      willChangeAtIndex("splits", index, ChangeType::Removal);
      _splits.erase(it);
      didChangeAtIndex("splits", index, ChangeType::Removal);

      if(split)
        split->setTransaction(TransactionPtr());
    }
  }

  const Splits& Transaction::getSplits() const {
    return _splits;
  }

} }
