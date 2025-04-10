#pragma once

#include"ArrayTable.h"

template<class TKey, class TValue>
class ScanTable : public ArrayTable<TKey,TValue> {
public:
	bool findRecord(TKey key) {
		for (int i = 0; i < DataCount; i++) {
			if (key == ptrRec[i].key) {
				currRec = i;
				Efficiency++;
				return true;
			}
		}

		currRec = DataCount;
		return false;
	}

	void insertRecord(Record r) {
		if (isFull()) {
			throw InsertInFullTable();
		}

		if (findRecord(r.key)) 
			throw RecordAlreadyExist();

		ptrRec[currRec] = r;
		DataCount++;
	}

	void deleteRecord(TKey key) {
		if (findRecord(key)) {
			ptrRec[currRec] = ptrRec[DataCount - 1];
			DataCount--;
		}
		else return;
	}

};