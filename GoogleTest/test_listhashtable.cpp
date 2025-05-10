#include"gtest.h"
#include"../mp2-lab6-tables/ListHashTable.h"

// Insert into empty ListHashTable
TEST(ListHashTable_Insert, IntoEmptyTable) {
    ListHashTable<int, std::string> ht(3);
    EXPECT_NO_THROW(ht.insertRecord({ 1, "one" }));
    EXPECT_EQ(ht.getDataCount(), 1);
}

// Collision handling: two keys in same bucket
TEST(ListHashTable_Insert, HandlesCollision) {
    ListHashTable<int, std::string> ht(3);
    ht.insertRecord({ 1, "one" });
    EXPECT_NO_THROW(ht.insertRecord({ 4, "four" }));  // 1%3 == 4%3
    EXPECT_EQ(ht.getDataCount(), 2);
}

// Insert duplicate throws
TEST(ListHashTable_Insert, DuplicateThrows) {
    ListHashTable<int, std::string> ht(3);
    ht.insertRecord({ 1, "one" });
    EXPECT_THROW(ht.insertRecord({ 1, "uno" }), RecordAlreadyExist);
}

// Find existing
TEST(ListHashTable_Find, ExistingKey) {
    ListHashTable<int, std::string> ht(3);
    ht.insertRecord({ 2, "two" });
    EXPECT_TRUE(ht.findRecord(2));
    EXPECT_EQ(ht.getCurrentRecord().val, "two");
}

// Find non-existing
TEST(ListHashTable_Find, NonExistingKey) {
    ListHashTable<int, std::string> ht(3);
    EXPECT_FALSE(ht.findRecord(5));
}

// Delete existing
TEST(ListHashTable_Delete, ExistingKey) {
    ListHashTable<int, std::string> ht(3);
    ht.insertRecord({ 2, "two" });
    EXPECT_NO_THROW(ht.deleteRecord(2));
    EXPECT_FALSE(ht.findRecord(2));
}

// Delete non-existing does nothing
TEST(ListHashTable_Delete, NonExistingKey) {
    ListHashTable<int, std::string> ht(3);
    EXPECT_NO_THROW(ht.deleteRecord(7));
}