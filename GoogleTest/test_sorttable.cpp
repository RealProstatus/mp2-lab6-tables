#include"gtest.h"
#include"../mp2-lab6-tables/SortTable.h"

// Insert into empty SortTable
TEST(SortTable_Insert, IntoEmptyTable) {
    SortTable<int, std::string> st(5);
    EXPECT_NO_THROW(st.insertRecord({ 2, "two" }));
    EXPECT_EQ(st.getDataCount(), 1);
}

// Insert maintains sorted order
TEST(SortTable_Insert, MaintainsOrder) {
    SortTable<int, std::string> st(5);
    st.insertRecord({ 2, "two" });
    st.insertRecord({ 1, "one" });
    st.insertRecord({ 3, "three" });
    st.resetIterator();
    EXPECT_EQ(st.getCurrentRecord().key, 1);
    st.goNext(); EXPECT_EQ(st.getCurrentRecord().key, 2);
    st.goNext(); EXPECT_EQ(st.getCurrentRecord().key, 3);
}

// Insert duplicate throws
TEST(SortTable_Insert, DuplicateThrows) {
    SortTable<int, std::string> st(5);
    st.insertRecord({ 1, "one" });
    EXPECT_THROW(st.insertRecord({ 1, "uno" }), RecordAlreadyExist);
}

// Delete existing key shifts elements
TEST(SortTable_Delete, ExistingKey) {
    SortTable<int, std::string> st(5);
    st.insertRecord({ 1, "one" });
    st.insertRecord({ 2, "two" });
    st.deleteRecord(1);
    st.resetIterator();
    EXPECT_EQ(st.getCurrentRecord().key, 2);
    EXPECT_EQ(st.getDataCount(), 1);
}

// Delete non-existing key does nothing
TEST(SortTable_Delete, NonExistingKey) {
    SortTable<int, std::string> st(5);
    EXPECT_NO_THROW(st.deleteRecord(99));
}