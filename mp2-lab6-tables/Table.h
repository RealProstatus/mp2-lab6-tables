#pragma once

#include<iostream>
#include"Exceptions.h"

template<class TKey, class TValue>
struct Record {
	TKey key;
	TValue val;

	friend std::ostream& operator<<(std::ostream& out, const Record& r) {
		out << "[" << key << "]: " << val;
		return out;
	}

	bool operator==(const Record<TKey,TValue> r) {
		return this->key == r->key;
	}
};

template<class TKey, class TValue>
class Table {
protected:
	int DataCount;
	int Efficiency;
public:
	Table() {
		DataCount = Efficiency = 0;
	}

	int getDataCount() const {
		return DataCount;
	}
	int getEfficiency() const {
		return Efficiency;
	}
	bool isEmpty() const {
		return DataCount == 0;
	}

	virtual ~Table() = default;
	virtual bool isFull() = 0;
	virtual bool findRecord(TKey key) = 0;
	virtual void insertRecord(Record<TKey,TValue> r) = 0;
	virtual void deleteRecord(TKey key) = 0;

	virtual void resetIterator() = 0;
	virtual void goNext() = 0;
	virtual bool isEnd() = 0;
	virtual Record<TKey,TValue> getCurrentRecord() = 0;

	friend std::ostream& operator<<(std::ostream& out, Table<TKey,TValue>& t) {
		for (t.resetIterator(); !(t.isEnd()); t.goNext()) {
			out << t.getCurrentRecord() << std::endl;
		}

		return out;
	}

};