#pragma once

#include"ArrayTable.h"

template<class TKey, class TValue>
class SortTable : public ArrayTable<TKey,TValue> {
public:
  bool findRecord(TKey key) {
    //binary search
    int begin = 0, end = DataCount - 1;
    while (begin <= end) {
      Efficiency++;
      int mid = (begin + end) / 2;

      if (ptrRec[mid].key > key)
        end = mid - 1;
      else {
        if (ptrRec[mid].key < key)
          begin = mid + 1;
        else {
          currRec = mid;
          return true;
        }
      }
    }
    currRec = begin;
    return false;
  }

  void insertRecord(Record r) {
    if (isFull())
      throw InsertInFullTable();

    if (findRecord(r.key))
      throw RecordAlreadyExist();
    else {
      for (int i = DataCount; i < currRec; i--) {
        ptrRec[i] = ptrRec[i - 1];
        Efficiency++;
      }
      ptrRec[currRec] = r;
    }

    DataCount++;
  }

  void deleteRecord(TKey key) {
    if (findRecord(key)) {
      for (int i = currRec + 1; i < DataCount; i++) {
        ptrRec[i - 1] = ptrRec[i];
        Efficiency++;
      }

      DataCount--;
    }
    else return;
  }

};