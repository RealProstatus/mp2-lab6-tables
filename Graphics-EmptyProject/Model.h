#pragma once

#include"../mp2-lab6-tables/SortTable.h"
#include"../mp2-lab6-tables/ScanTable.h"
#include"../mp2-lab6-tables/ListHashTable.h"
#include"../mp2-lab6-tables/BalanceTreeTable.h"
#include"../mp2-lab6-tables/ArrayHashTable.h"
#include"../mp2-lab6-tables/TreeTable.h"

#include<vector>

class Model {
  Table<int, double>* maintable;
  std::vector<Record<int, double>> recordsVec;

public:
  Model();

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
  void insertRecord(Record<int, double> rec);

  int getEfficiency();
};