#ifndef __DEFINITIONS_H_
#define __DEFINITIONS_H_

#include <memory>
#include <vector>

#define CREATE_ALIAS(x) \
  using x##Ptr = std::shared_ptr<opencash::model::x>; \
  using x##WeakPtr = std::weak_ptr<opencash::model::x>; \
  using x##s = std::vector<x##Ptr>; \
  using Weak##x##s = std::vector<x##WeakPtr>;

#define IMPORT_ALIAS(x) \
  using x = opencash::model::x; \
  CREATE_ALIAS(x)

#define DECL_COMPARATORS(x) \
  bool operator==(const x& rhs) const; \
  bool operator!=(const x& rhs) const;

#define IMPL_COMPARATORS(x) \
  bool x::operator==(const x& rhs) const { \
    return this == &rhs; \
  } \
  bool x::operator!=(const x& rhs) const { \
    return !(*this == rhs); \
  }

#endif
