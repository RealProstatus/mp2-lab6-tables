#pragma once

#include "../mp2-lab6-tables/SortTable.h"
#include "../mp2-lab6-tables/ScanTable.h"
#include "../mp2-lab6-tables/ListHashTable.h"
#include "../mp2-lab6-tables/BalanceTreeTable.h"
#include "../mp2-lab6-tables/ArrayHashTable.h"
#include "../mp2-lab6-tables/TreeTable.h"

#include <vector>
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

    void initSortTable();
    void initScanTable();
    void initListHashTable();
    void initArrayHashTable();
    void initTreeTable();
    void initAVLTreeTable();

    void generateRecords(int amount, int maxKey);
    void deleteAllrecords();

    bool findRecord(int key);
    void deleteRecord(int key);
    void insertRecord(const Record<int, double>& rec);

    int getEfficiency();

    // Iteration
    void resetIterator();
    bool isEnd();
    void goNext();
    Record<int, double> getCurrentRecord();
};