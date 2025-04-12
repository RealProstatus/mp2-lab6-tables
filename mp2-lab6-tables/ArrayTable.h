#pragma once

#include"Table.h"

template<class TKey, class TValue>
class ArrayTable : public Table<TKey,TValue> {
protected:
	int size;
	Record<TKey, TValue>* ptrRec;

	int currRec;
public:
	ArrayTable(int size = 32) : Table<TKey,TValue>() {
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
		this->DataCount = t.DataCount;
		this->Efficiency = t.Efficiency;
	}

	~ArrayTable() {
		delete[] ptrRec;
	}

	bool isFull() {
		return this->DataCount == size;
	}

	Record<TKey,TValue> getCurrentRecord() {
		if (currRec >= 0 && currRec < this->DataCount)
			return ptrRec[currRec];
		else throw OutOfRange();
	}

	void resetIterator() override {
		currRec = 0;
	}

	void goNext() override {
		currRec++;
	}

	bool isEnd() override {
		return currRec == this->DataCount;
	}

};