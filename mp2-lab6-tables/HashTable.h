#pragma once

#include"Table.h"

template<class TKey,class TValue>
class HashTable : public Table<TKey, TValue> {
protected:
  int size;//size of array

  HashTable(int size = 32): Table() {
    this->size = size;
  }

  virtual int hashFunc(TKey key) const{
    return key % size;
  }

};
