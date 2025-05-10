#pragma once

#include"ArrayTable.h"

template<class TKey, class TValue>
class SortTable : public ArrayTable<TKey,TValue> {
public:
  SortTable(int size = 32): ArrayTable<TKey,TValue>(size) { }

  bool findRecord(TKey key) {
    //binary search
    int begin = 0, end = this->DataCount - 1;
    while (begin <= end) {
      this->Efficiency++;
      int mid = (begin + end) / 2;

      if (this->ptrRec[mid].key > key)
        end = mid - 1;
      else {
        if (this->ptrRec[mid].key < key)
          begin = mid + 1;
        else {
          this->currRec = mid;
          return true;
        }
      }
    }
    this->currRec = begin;
    return false;
  }

  void insertRecord(Record<TKey, TValue> r) {
    if (this->isFull())
      throw InsertInFullTable();

    if (findRecord(r.key))
      throw RecordAlreadyExist();
    else {
      for (int i = this->DataCount; i > this->currRec; i--) {
        this->ptrRec[i] = this->ptrRec[i - 1];
        this->Efficiency++;
      }
      this->ptrRec[this->currRec] = r;
      this->Efficiency++;
    }

    this->DataCount++;
  }

  void deleteRecord(TKey key) {
    if (findRecord(key)) {
      for (int i = this->currRec + 1; i < this->DataCount; i++) {
        this->ptrRec[i - 1] = this->ptrRec[i];
        this->Efficiency++;
      }

      this->DataCount--;
      this->Efficiency++;
    }
    else return;
  }

};