#pragma once

#include"HashTable.h"
#include<list>
#include<iterator>

template<class TKey, class TValue>
class ListHashTable : public HashTable<TKey, TValue> {
protected:
  std::list<Record<TKey, TValue>>* pList;
  int currList;
  std::list<Record<TKey, TValue>>::iterator currI;

public:
  ListHashTable(int size = 32) : HashTable(size) {
    pList = new std::list<Record<TKey, TValue>>[this->size];
    currList = -1;
  }

  ~ListHashTable() {
    delete[] pList;
  }

  bool isFull() {
    try {

    }
    catch (...) {

    }
  }

  bool findRecord(TKey key) {
    currList = hashFunc(key);
    bool res = false;

    for (currI = pList[currList].begin(); currI != pList[currList].end(); currI++) {
      if (currI->key == key) {
        Efficiency++;
        res = true;
        break;
      }
    }

    return res;
  }

  void insertRecord(Record<TKey, TValue> r) {
    if (isFull())
      throw InsertInFullTable();

    if (findRecord(r.key))
      throw RecordAlreadyExist();
    else {
      pList[currList].push_front(r);
      DataCount++;
      Efficiency++;
    }
  }
  
  void deleteRecord(TKey key) {
    if (findRecord(key)) {
      pList[currList].erase(currI);
      DataCount--;
      Efficiency++;
    }
    else return;
  }

};
