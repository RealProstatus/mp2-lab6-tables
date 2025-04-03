#pragma once

#include<iostream>
#include"Exceptions.h"

template<class TKey, class TValue>
struct Record {
	TKey key;
	TValue val;

	friend std::ostream& operator<<(std::ostream& out, const Record& r) {
		out << "[" + key + "]: " + val;
		return out;
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

	virtual ~Table();
	virtual bool isFull() = 0;
	virtual bool findRecord(TKey key) = 0;
	virtual void insertRecord(Record r) = 0;
	virtual void deleteRecord(TKey key) = 0;

	virtual void resetIterator() = 0;
	virtual void goNext() = 0;
	virtual void isEnd() = 0;
	virtual Record getCurrentRecord() = 0;

	friend std::ostream& operator<<(std::ostream& out, Table& t) {
		for (t.resetIterator(); !(t.isEnd()); t.goNext()) {
			out << t.getCurrentRecord() << std::endl;
		}

		return out;
	}
};