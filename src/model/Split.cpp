#include "opencash/model/Split.h"

namespace opencash { namespace model {

  IMPORT_ALIAS(Split);

  IMPL_COMPARATORS(Split);

  TransactionWeakPtr Split::getTransaction() const {
    return _transaction;
  }

  void Split::setTransaction(TransactionWeakPtr transaction) {
    if(_transaction.lock() == transaction.lock()) return;

    willChange("transaction");
    if(_transaction.lock()) _transaction.lock()->removeSplit(shared_from_this());
    _transaction = transaction;
    if(_transaction.lock()) _transaction.lock()->addSplit(shared_from_this());
    didChange("transaction");
  }

  AccountWeakPtr Split::getAccount() const {
    return _account;
  }

  void Split::setAccount(AccountWeakPtr account) {
    if(_account.lock() == account.lock()) return;

    willChange("account");
    if(_account.lock()) _account.lock()->removeSplit(shared_from_this());
    _account = account;
    if(_account.lock()) _account.lock()->addSplit(shared_from_this());
    didChange("account");
  }

  std::string Split::getMemo() const {
    return _memo;
  }

  void Split::setMemo(const std::string& memo) {
    willChange("memo");
    _memo = memo;
    didChange("memo");
  }

  std::string Split::getAction() const {
    return _action;
  }

  void Split::setAction(const std::string& action) {
    willChange("action");
    _action = action;
    didChange("action");
  }

  double Split::getValue() const {
    return _value;
  }

  void Split::setValue(double value) {
    willChange("value");
    _value = value;
    didChange("value");
  }

} }
