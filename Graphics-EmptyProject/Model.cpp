#include "Model.h"
#include <stdexcept>

Model::Model() : maintable(nullptr), currentType(TableType::Scan) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

Model::~Model() {
    delete maintable;
}

void Model::initSortTable(int size) {
    delete maintable;
    maintable = new SortTable<int, double>(size);
    currentType = TableType::Sort;
}

void Model::initScanTable(int size) {
    delete maintable;
    maintable = new ScanTable<int, double>(size);
    currentType = TableType::Scan;
}

void Model::initListHashTable(int size) {
    delete maintable;
    maintable = new ListHashTable<int, double>(size);
    currentType = TableType::ListHash;
}

void Model::initArrayHashTable(int size) {
    delete maintable;
    maintable = new ArrayHashTable<int, double>(size);
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
    case TableType::Scan:       initScanTable(recordsVec.size());        break;
    case TableType::Sort:       initSortTable(recordsVec.size());        break;
    case TableType::ListHash:   initListHashTable(recordsVec.size());    break;
    case TableType::ArrayHash:  initArrayHashTable(recordsVec.size());   break;
    case TableType::Tree:       initTreeTable();                         break;
    case TableType::AVL:        initAVLTreeTable();                      break;
    }
    recordsVec.clear();
}

void Model::generateRecords(int amount, int maxKey) {
    recordsVec.clear();
    if (!maintable)
        return;

    std::unordered_set<int> usedKeys;
    int inserted = 0;

    while (inserted < amount) {
        int key = std::rand() % (maxKey + 1);
        if (usedKeys.find(key) != usedKeys.end())
            continue; // такой ключ уже есть, пропускаем

        double val = static_cast<double>(std::rand()) / RAND_MAX;
        Record<int, double> rec{ key, val };
        maintable->insertRecord(rec);
        recordsVec.push_back(rec);
        usedKeys.insert(key);
        ++inserted;
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

const std::vector<Record<int, double>>& Model::getRecordsVec() const {
    return recordsVec;
}

std::vector<Record<int, double>> Model::getAllRecords() {
    std::vector<Record<int, double>> result;
    if (!maintable)
        return result;

    maintable->resetIterator();
    while (!maintable->isEnd()) {
        result.push_back(maintable->getCurrentRecord());
        maintable->goNext();
    }
    return result;
}

std::string Model::getTreeAsString() {
    if (!maintable) return "";

    if (auto t = dynamic_cast<TreeTable<int, double>*>(maintable)) {
        return t->getTreeAsString();
    }
    if (auto a = dynamic_cast<AVLTreeTable<int, double>*>(maintable)) {
        return a->getTreeAsString();
    }
    return "";
}

