#pragma once

#include"Table.h"

template<class TKey, class TValue>
class ArrayTable : public Table<TKey,TValue> {
protected:
	int size;
	Record<TKey, TValue>* ptrRec;

	int currRec;
public:
	ArrayTable(int size = 32) : Table() {
		if (size >= 0) {
			this->size = size;
			ptrRec = new Record<TKey, TValue>[size];
			currRec = -1;
		}
		else throw InvalidConstructorArgument();
	}

	ArrayTable(const ArrayTable<TKey, TValue>& t) : Table() {
		size = t.size;
		currRec = t.currRec;
		ptrRec = new Record<TKey, TValue>[size];
		for (int i = 0; i < size; i++) {
			ptrRec[i] = t.ptrRec[i];
		}
		DataCount = t.DataCount;
		Efficiency = t.Efficiency;
	}

	~ArrayTable() {
		delete ptrRec;
	}

	bool isFull() {
		return DataCount == size;
	}

	Record getCurrentRecord() {
		if (currRec >= 0 && currRec < DataCount)
			return ptrRec[currRec];
		else throw OutOfRange();
	}

	void reset() {
		currRec = 0;
	}

	void goNext() {
		currRec++;
	}

	bool isEnd() {
		return currRec == DataCount;
	}

};