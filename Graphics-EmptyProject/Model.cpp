#include "Model.h"
#include <stdexcept>

Model::Model() : maintable(nullptr), currentType(TableType::Scan) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

Model::~Model() {
    delete maintable;
}

void Model::initSortTable() {
    delete maintable;
    maintable = new SortTable<int, double>();
    currentType = TableType::Sort;
}

void Model::initScanTable() {
    delete maintable;
    maintable = new ScanTable<int, double>();
    currentType = TableType::Scan;
}

void Model::initListHashTable() {
    delete maintable;
    maintable = new ListHashTable<int, double>();
    currentType = TableType::ListHash;
}

void Model::initArrayHashTable() {
    delete maintable;
    maintable = new ArrayHashTable<int, double>();
    currentType = TableType::ArrayHash;
}

void Model::initTreeTable() {
    delete maintable;
    maintable = new TreeTable<int, double>();
    currentType = TableType::Tree;
}

void Model::initAVLTreeTable() {
    delete maintable;
    maintable = new AVLTreeTable<int, double>();
    currentType = TableType::AVL;
}

void Model::deleteAllrecords() {
    switch (currentType) {
    case TableType::Scan:       initScanTable();    break;
    case TableType::Sort:       initSortTable();    break;
    case TableType::ListHash:   initListHashTable(); break;
    case TableType::ArrayHash:  initArrayHashTable(); break;
    case TableType::Tree:       initTreeTable();    break;
    case TableType::AVL:        initAVLTreeTable(); break;
    }
    recordsVec.clear();
}

void Model::generateRecords(int amount, int maxKey) {
    recordsVec.clear();
    int inserted = 0;
    while (inserted < amount) {
        int key = std::rand() % (maxKey + 1);
        double val = static_cast<double>(std::rand()) / RAND_MAX;
        Record<int, double> rec{ key, val };
        try {
            maintable->insertRecord(rec);
            recordsVec.push_back(rec);
            ++inserted;
        }
        catch (...) {
            // duplicate key, skip
        }
    }
}

bool Model::findRecord(int key) {
    return maintable->findRecord(key);
}

void Model::deleteRecord(int key) {
    maintable->deleteRecord(key);
}

void Model::insertRecord(const Record<int, double>& rec) {
    maintable->insertRecord(rec);
    recordsVec.push_back(rec);
}

int Model::getEfficiency() {
    return maintable->getEfficiency();
}

void Model::resetIterator() {
    maintable->resetIterator();
}

bool Model::isEnd() {
    return maintable->isEnd();
}

void Model::goNext() {
    maintable->goNext();
}

Record<int, double> Model::getCurrentRecord() {
    return maintable->getCurrentRecord();
}
