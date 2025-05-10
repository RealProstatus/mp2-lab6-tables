#include"gtest.h"
#include"../mp2-lab6-tables/ArrayHashTable.h"

// Insert into empty ArrayHashTable
TEST(ArrayHashTable_Insert, IntoEmptyTable) {
    ArrayHashTable<int, std::string> ht(5, 2);
    EXPECT_NO_THROW(ht.insertRecord({ 1, "one" }));
    EXPECT_EQ(ht.getDataCount(), 1);
}

// Probe handles wrap-around
TEST(ArrayHashTable_Insert, ProbeWrapAround) {
    ArrayHashTable<int, std::string> ht(5, 2);
    ht.insertRecord({ 1, "one" });
    EXPECT_NO_THROW(ht.insertRecord({ 6, "six" }));  // 6%5==1, then +2
    EXPECT_EQ(ht.getDataCount(), 2);
}

// Insert duplicate throws
TEST(ArrayHashTable_Insert, DuplicateThrows) {
    ArrayHashTable<int, std::string> ht(5, 2);
    ht.insertRecord({ 2, "two" });
    EXPECT_THROW(ht.insertRecord({ 2, "dos" }), RecordAlreadyExist);
}

// Delete existing marks as deleted
TEST(ArrayHashTable_Delete, ExistingKey) {
    ArrayHashTable<int, std::string> ht(5, 2);
    ht.insertRecord({ 3, "three" });
    EXPECT_NO_THROW(ht.deleteRecord(3));
    EXPECT_FALSE(ht.findRecord(3));
}

// Delete non-existing does nothing
TEST(ArrayHashTable_Delete, NonExistingKey) {
    ArrayHashTable<int, std::string> ht(5, 2);
    EXPECT_NO_THROW(ht.deleteRecord(8));
}