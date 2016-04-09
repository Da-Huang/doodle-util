#ifndef UTIL_ITERATOR_ITERATOR_H_
#define UTIL_ITERATOR_ITERATOR_H_

// This class specifies abstract interfaces for iterating items.
template <typename Type>
class Iterator {
 public:
  Iterator() = default;
  Iterator(const Iterator& iterator) = delete;
  virtual ~Iterator() = default;

  // Gets next item.
  //
  // `item` cannot be nullptr. Otherwise, it crashes.
  //
  // Returns true, if it succeeds.
  virtual bool Next(Type* item) = 0;
};

#endif  // UTIL_ITERATOR_ITERATOR_H_
