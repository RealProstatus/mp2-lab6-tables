#include<iostream>
#include<string>

#include"ScanTable.h"
#include"SortTable.h"
#include"ArrayHashTable.h"
#include"ListHashTable.h"

using namespace std;

void testTable(Table<int, string>& table, const string& name) {
	cout << "============ Testing " << name << " ============\n";

	try {
		table.insertRecord({ 1, "one" });
		table.insertRecord({ 2, "two" });
		table.insertRecord({ 3, "three" });
		cout << "Insert OK\n";
		cout << "Efficiency: " << table.getEfficiency() << endl;
	}
	catch (InsertInFullTable e) {
		cout << "Insert error. " << e.getMessage() << endl;
	}

	cout << "Find key 2: " << (table.findRecord(2) ? "Found" : "Not found") << endl;
	cout << "Efficiency: " << table.getEfficiency() << endl;

	cout << "Find key 4: " << (table.findRecord(4) ? "Found" : "Not found") << endl;
	cout << "Efficiency: " << table.getEfficiency() << endl;

	table.deleteRecord(2);
	cout << "Efficiency: " << table.getEfficiency() << endl;

	cout << "Find key 2 after delete: " << (table.findRecord(2) ? "Found" : "Not found") << endl;

	cout << "Table content:" << endl << table << endl;
	cout << "Efficiency: " << table.getEfficiency() << endl;
	cout << endl;
}

int main() {
	ScanTable<int, std::string> scanTable(10);
	SortTable<int, std::string> sortTable(10);
	ArrayHashTable<int, std::string> arrayHashTable(10, 3);
	ListHashTable<int, std::string> listHashTable(10);

	testTable(scanTable, "ScanTable");
	testTable(sortTable, "SortTable");
	testTable(arrayHashTable, "ArrayHashTable");
	testTable(listHashTable, "ListHashTable");
}
