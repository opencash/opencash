#include "opencash/core/ObservableModel.h"

namespace opencash { namespace core {

  void ObservableModel::willChange(std::string key)
  {
    willChangeEvent.notify(this, EventArgs(key));
  }

  void ObservableModel::didChange(std::string key)
  {
    didChangeEvent.notify(this, EventArgs(key));
  }

  void ObservableModel::willChangeAtIndex(std::string key, size_t index,
      ChangeType change)
  {
    willChangeAtIndexEvent.notify(this, EventArgs(key, index, change));
  }

  void ObservableModel::didChangeAtIndex(std::string key, size_t index,
      ChangeType change)
  {
    didChangeAtIndexEvent.notify(this, EventArgs(key, index, change));
  }

}}
