#pragma once

#include "../mp2-lab6-tables/SortTable.h"
#include "../mp2-lab6-tables/ScanTable.h"
#include "../mp2-lab6-tables/ListHashTable.h"
#include "../mp2-lab6-tables/BalanceTreeTable.h"
#include "../mp2-lab6-tables/ArrayHashTable.h"
#include "../mp2-lab6-tables/TreeTable.h"

#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <ctime>

class Model {
    enum class TableType { Scan, Sort, ListHash, ArrayHash, Tree, AVL };
    Table<int, double>* maintable;
    TableType currentType;
    std::vector<Record<int, double>> recordsVec;

public:
    Model();
    ~Model();

    void initSortTable(int size);
    void initScanTable(int size);
    void initListHashTable(int size);
    void initArrayHashTable(int size);
    void initTreeTable();
    void initAVLTreeTable();

    void generateRecords(int amount, int maxKey);
    void deleteAllrecords();

    bool findRecord(int key);
    void deleteRecord(int key);
    void insertRecord(const Record<int, double>& rec);

    int getEfficiency();

    void resetIterator();
    bool isEnd();
    void goNext();
    Record<int, double> getCurrentRecord();

    const std::vector<Record<int, double>>& getRecordsVec() const;
};