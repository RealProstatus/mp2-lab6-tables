#include"gtest.h"
#include"../mp2-lab6-tables/TreeTable.h"

// Insert into empty TreeTable
TEST(TreeTable_Insert, IntoEmptyTree) {
    TreeTable<int, std::string> tt;
    EXPECT_NO_THROW(tt.insertRecord({ 5, "five" }));
    EXPECT_EQ(tt.getDataCount(), 1);
}

// Insert duplicate throws
TEST(TreeTable_Insert, DuplicateThrows) {
    TreeTable<int, std::string> tt;
    tt.insertRecord({ 5, "five" });
    EXPECT_THROW(tt.insertRecord({ 5, "cinco" }), RecordAlreadyExist);
}

// Find existing
TEST(TreeTable_Find, ExistingKey) {
    TreeTable<int, std::string> tt;
    tt.insertRecord({ 7, "seven" });
    EXPECT_TRUE(tt.findRecord(7));
}

// Find non-existing
TEST(TreeTable_Find, NonExistingKey) {
    TreeTable<int, std::string> tt;
    EXPECT_FALSE(tt.findRecord(10));
}

// In-order traversal ascending
TEST(TreeTable_Iterator, InOrderTraversal) {
    TreeTable<int, std::string> tt;
    std::vector<int> keys = { 5,2,8,1,3 };
    for (int k : keys) tt.insertRecord({ k, std::to_string(k) });
    std::vector<int> out;
    for (tt.resetIterator(); !tt.isEnd(); tt.goNext()) {
        out.push_back(tt.getCurrentRecord().key);
    }
    EXPECT_EQ(out, (std::vector<int>{1, 2, 3, 5, 8}));
}