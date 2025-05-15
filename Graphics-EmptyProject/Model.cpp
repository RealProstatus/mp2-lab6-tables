#include"Model.h"

Model::Model() {
  maintable = nullptr;
}

void Model::initSortTable() {
  maintable = new SortTable<int, double>();
}
void Model::initScanTable() {
  maintable = new ScanTable<int, double>();
}
void Model::initListHashTable() {
  maintable = new ListHashTable<int, double>();
}
void Model::initArrayHashTable() {
  maintable = new ArrayHashTable<int, double>();
}
void Model::initTreeTable() {
  maintable = new TreeTable<int, double>();
}
void Model::initAVLTreeTable() {
  maintable = new AVLTreeTable<int, double>();
}

void Model::generateRecords(int amount, int maxKey);
void Model::deleteAllrecords();

bool Model::findRecord(int key);
void Model::deleteRecord(int key);
void Model::insertRecord(Record<int, double> rec);

int Model::getEfficiency();