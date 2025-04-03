#pragma once

#include"Table.h"

template<class TKey,class TValue>
class HashTable : public Table<TKey, TValue> {
protected:
  int size;//size of array

  virtual int hashFunc(TKey key) const{
    return key % size;
  }

};
