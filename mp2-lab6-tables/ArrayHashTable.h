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
  ArrayHashTable(int size = 32, int step = 3): HashTable<TKey,TValue>(size) {
    //TODO feature: добавить проверку взаимной простоты размера и шага
    currRec = -1;
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
    return this->DataCount == this->size;
  }

  bool findRecord(TKey key) {
    currRec = this->hashFunc(key);

    int tmp = -1;
    for (int i = 0; i < this->size; i++) {
      this->Efficiency++;

      if (this->ptrRec[this->currRec] == free)
        break;
      else
        if (this->ptrRec[this->currRec] == del && tmp == -1)
          tmp = this->currRec;
        else
          if (this->ptrRec[this->currRec].key == key)
            return true;
      this->currRec = (this->currRec + step) % this->size;
    }

    if (tmp != -1)
        this->currRec = tmp;
    return false;
  }

  void insertRecord(Record<TKey, TValue> r) {
    if (isFull())
      throw InsertInFullTable();

    if (findRecord(r.key))
      throw RecordAlreadyExist();
    else {
      this->ptrRec[this->currRec] = r;
      this->DataCount++;
      this->Efficiency++;
    }
  }

  void deleteRecord(TKey key) {
    if (findRecord(key)) {
      this->DataCount--;
      this->Efficiency++;
      this->ptrRec[this->currRec] = del;
    }
    else return;
  }

  void resetIterator() override {
    this->currRec = 0;
    while ((this->ptrRec[this->currRec] == free || this->ptrRec[this->currRec] == del)
      && this->currRec < this->size)
      this->currRec++;
  }

  void goNext() override {
    this->currRec++;
    while ((this->ptrRec[this->currRec] == free || this->ptrRec[this->currRec] == del)
      && this->currRec < this->size)
      this->currRec++;
  }

  bool isEnd() override {
    return this->currRec == this->size;
  }

  Record<TKey, TValue> getCurrentRecord() {
    return this->ptrRec[this->currRec];
  }

  ~ArrayHashTable() {
    delete[] this->ptrRec;
  }

};
