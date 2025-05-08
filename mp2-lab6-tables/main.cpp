#include <iostream>
#include <unordered_set>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include<string>

#include"ScanTable.h"
#include"SortTable.h"
#include"ArrayHashTable.h"
#include"ListHashTable.h"
#include"TreeTable.h"

using namespace std;

double getRandomDouble(double min = 0.0, double max = 1000.0) {
	static mt19937 rng(static_cast<unsigned int>(time(nullptr)));
	uniform_real_distribution<double> dist(min, max);
	return dist(rng);
}

inline void testTable(Table<int, double>& table, const string& name) {
    cout << "============ Testing " << name << " ============\n";

    //generating and inserting 100 unique records
    for (int key = 1; key <= 100; key++) {
        Record<int, double> rec{ key, getRandomDouble() };
        try {
            table.insertRecord(rec);
        }
        catch (...) {
            cout << "Insert error on key: " << key << endl;
        }
    }

    cout << "Efficiency after 100 insertions: " << table.getEfficiency() << endl;

    //deleting keys 1-10
    for (int key = 1; key <= 10; key++) {
        table.deleteRecord(key);
    }

    cout << "Efficiency after deleting keys 1-10: " << table.getEfficiency() << endl;

    //search for a deleted key (1)
    bool found = table.findRecord(1);
    cout << "Find deleted key 1: " << (found ? "Found" : "Not found") << endl;
    cout << "Efficiency after searching deleted key: " << table.getEfficiency() << endl;

    //search for an existing key (50)
    found = table.findRecord(50);
    cout << "Find existing key 50: " << (found ? "Found" : "Not found") << endl;
    cout << "Efficiency after searching existing key: " << table.getEfficiency() << endl;
    cout << "===============================================\n\n";
}

int main() {
	ScanTable<int, double> scanTable(100);
	SortTable<int, double> sortTable(100);
	ArrayHashTable<int, double> arrayHashTable(100, 3);
	ListHashTable<int, double> listHashTable(100);
    TreeTable<int, double> treetable;

	testTable(scanTable, "ScanTable");
	testTable(sortTable, "SortTable");
	testTable(arrayHashTable, "ArrayHashTable");
	testTable(listHashTable, "ListHashTable");
    testTable(treetable, "TreeTable");
}
