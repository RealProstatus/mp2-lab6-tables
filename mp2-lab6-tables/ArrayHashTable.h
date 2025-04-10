#pragma once

#include"HashTable.h"

template<class TKey, class TValue>
class ArrayHashTable : public HashTable<TKey, TValue> {
protected:
  int step;                         //step of secondary hashing
  int currRec;                      //index of current record
  
  Record<TKey, TValue>* ptrRec;

  Record<TKey, TValue> free, del;   //designation of an empty and deleted record
public:
  ArrayHashTable(int size = 32, int step = 5) {
    //TODO feature: добавить проверку взаимной простоты размера и шага

    free.key = -1;
    del.key = -2;

    this->size = size;
    this->step = step;

    ptrRec = new Record<TKey, TValue>[size];
    for (int i = 0; i < size; i++) {
      ptrRec[i] = free;
    }
  }

  bool isFull() {
    return DataCount == size;
  }

  bool findRecord(TKey key) {
    currRec = hashFunc(key);

    int tmp = -1;
    for (int i = 0; i < size; i++) {
      Efficiency++;

      if (ptrRec[currRec] == free)
        break;
      else
        if (ptrRec[currRec] == del && tmp == -1)
          tmp = currRec;
        else
          if (ptrRec[currRec].key == key)
            return true;
      currRec = (currRec + step) % size;
    }

    if (tmp != -1)
      currRec = tmp;
    return false;
  }

  bool insertRecord(Record<TKey, TValue> r) {
    if (isFull())
      throw InsertInFullTable();

    if (findRecord(r.key))
      throw RecordAlreadyExist();
    else {
      ptrRec[currRec] = r;
      DataCount++;
      Efficiency++;
      return true;
    }
  }

  void deleteRecord(TKey key) {
    if (findRecord(key)) {
      DataCount--;
      Efficiency++;
      ptrRec[currRec] = del;
    }
    else return;
  }

  void resetIterator() override {
    currRec = 0;
    while ((ptrRec[currRec] == free || ptrRec[currRec] == del)
      && currRec < size)
      currRec++;
  }

  void goNext() override {
    curr++;
    while ((ptrRec[currRec] == free || ptrRec[currRec] == del)
      && currRec < size)
      currRec++;
  }

  bool isEnd() override {
    return currRec == size;
  }

  Record<TKey, TValue> getCurrentRecord() {
    return ptrRec[currRec];
  }

  ~ArrayHashTable() {
    delete[] ptrRec;
  }

};
