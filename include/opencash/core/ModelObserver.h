#ifndef __OC_CORE_MODELOBSERVER_H_
#define __OC_CORE_MODELOBSERVER_H_

#include "ObservableModel.h"

#include <string>

namespace opencash { namespace core {

  class ModelObserver {
    using ChangeType = ObservableModel::ChangeType;
    using EventArgs = ObservableModel::EventArgs;

    public:
      ModelObserver(ObservableModel & model);
      virtual ~ModelObserver();

    protected:
      ObservableModel & getModel() const;

      virtual void willChange(const std::string & key) = 0;
      virtual void didChange(const std::string & key) = 0;

      virtual void willChangeAtIndex(const std::string & key,
          const size_t & index, const ChangeType & change) = 0;

      virtual void didChangeAtIndex(const std::string & key,
          const size_t & index, const ChangeType & change) = 0;

    private:
      ObservableModel & _model;

      void willChange(const EventArgs & args);
      void didChange(const EventArgs & args);
      void willChangeAtIndex(const EventArgs & args);
      void didChangeAtIndex(const EventArgs & args);
  };

}}

#endif
