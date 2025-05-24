#pragma once

#include"HashTable.h"
#include<list>
#include<iterator>

template<class TKey, class TValue>
class ListHashTable : public HashTable<TKey, TValue> {
protected:
  std::list<Record<TKey, TValue>>* pList;
  int currList;
  typename std::list<Record<TKey, TValue>>::iterator currI;

public:
  ListHashTable(int size = 32) : HashTable<TKey,TValue>(size) {
    pList = new std::list<Record<TKey, TValue>>[this->size];
    currList = -1;
  }

  ~ListHashTable() {
    delete[] pList;
  }

  bool isFull() {
    return false;
  }

  bool findRecord(TKey key) {
    currList = this->hashFunc(key);
    bool res = false;

    for (currI = pList[currList].begin(); currI != pList[currList].end(); currI++) {
      this->Efficiency++;
      if (currI->key == key) {
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
      this->DataCount++;
      this->Efficiency++;
    }
  }
  
  void deleteRecord(TKey key) {
    if (findRecord(key)) {
      pList[currList].erase(currI);
      this->DataCount--;
      this->Efficiency++;
    }
    else return;
  }

  void resetIterator() override {
      for (currList = 0; currList < this->size; currList++) {
          if (!pList[currList].empty()) {
              currI = pList[currList].begin();
              return;
          }
      }
      currList = this->size;
  }

  void goNext() override {
      ++currI;
      // Если текущий список закончился, ищем следующий непустой список
      while (currList < this->size && currI == pList[currList].end()) {
          ++currList;
          if (currList < this->size) {
              currI = pList[currList].begin();
          }
      }
  }

  bool isEnd() override {
      return currList >= this->size;
  }

  Record<TKey, TValue> getCurrentRecord() override {
      if (currList < this->size && currI != pList[currList].end())
          return *currI;
      else
          throw OutOfRange();
  }

};
