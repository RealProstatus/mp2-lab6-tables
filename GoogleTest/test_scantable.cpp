#include"gtest.h"
#include"../mp2-lab6-tables/ScanTable.h"

TEST(ScanTable_Insert, IntoEmptyTable) {
    ScanTable<int, std::string> st(5);
    EXPECT_TRUE(st.isEmpty());
    Record<int, std::string> r{ 1, "one" };
    EXPECT_NO_THROW(st.insertRecord(r));
    EXPECT_FALSE(st.isEmpty());
    EXPECT_EQ(st.getDataCount(), 1);
}

// Insert into non-empty ScanTable
TEST(ScanTable_Insert, IntoNonEmptyTable) {
    ScanTable<int, std::string> st(5);
    st.insertRecord({ 1, "one" });
    EXPECT_NO_THROW(st.insertRecord({ 2, "two" }));
    EXPECT_EQ(st.getDataCount(), 2);
}

// Insert duplicate throws
TEST(ScanTable_Insert, DuplicateThrows) {
    ScanTable<int, std::string> st(5);
    st.insertRecord({ 1, "one" });
    EXPECT_THROW(st.insertRecord({ 1, "uno" }), RecordAlreadyExist);
}

// Find existing key
TEST(ScanTable_Find, ExistingKey) {
    ScanTable<int, std::string> st(5);
    st.insertRecord({ 1, "one" });
    EXPECT_TRUE(st.findRecord(1));
    EXPECT_EQ(st.getCurrentRecord().val, "one");
}

// Find non-existing key
TEST(ScanTable_Find, NonExistingKey) {
    ScanTable<int, std::string> st(5);
    EXPECT_FALSE(st.findRecord(42));
}

// Delete existing key
TEST(ScanTable_Delete, ExistingKey) {
    ScanTable<int, std::string> st(5);
    st.insertRecord({ 1, "one" });
    EXPECT_NO_THROW(st.deleteRecord(1));
    EXPECT_EQ(st.getDataCount(), 0);
    EXPECT_FALSE(st.findRecord(1));
}

// Delete non-existing key
TEST(ScanTable_Delete, NonExistingKey) {
    ScanTable<int, std::string> st(5);
    EXPECT_NO_THROW(st.deleteRecord(2));
}