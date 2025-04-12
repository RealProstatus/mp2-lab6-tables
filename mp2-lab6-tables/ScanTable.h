#pragma once

#include"ArrayTable.h"

template<class TKey, class TValue>
class ScanTable : public ArrayTable<TKey,TValue> {
public:
	ScanTable(int size = 32): ArrayTable<TKey,TValue>(size) { }

	bool findRecord(TKey key) {
		for (int i = 0; i < this->DataCount; i++) {
			if (key == this->ptrRec[i].key) {
				this->currRec = i;
				this->Efficiency++;
				return true;
			}
		}

		this->currRec = this->DataCount;
		return false;
	}

	void insertRecord(Record<TKey, TValue> r) {
		if (this->isFull()) {
			throw InsertInFullTable();
		}

		if (findRecord(r.key)) 
			throw RecordAlreadyExist();

		this->ptrRec[this->currRec] = r;
		this->DataCount++;
	}

	void deleteRecord(TKey key) {
		if (findRecord(key)) {
			this->ptrRec[this->currRec] = this->ptrRec[this->DataCount - 1];
			this->DataCount--;
		}
		else return;
	}

};