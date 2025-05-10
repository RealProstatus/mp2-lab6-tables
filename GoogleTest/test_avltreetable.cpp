#include"gtest.h"
#include"../mp2-lab6-tables/BalanceTreeTable.h"

// Insert into empty AVLTreeTable
TEST(AVLTree_Insert, IntoEmptyTree) {
    AVLTreeTable<int, std::string> avl;
    EXPECT_NO_THROW(avl.insertRecord({ 10, "ten" }));
    EXPECT_EQ(avl.getDataCount(), 1);
}

// Insert duplicate throws
TEST(AVLTree_Insert, DuplicateThrows) {
    AVLTreeTable<int, std::string> avl;
    avl.insertRecord({ 10, "ten" });
    EXPECT_THROW(avl.insertRecord({ 10, "dix" }), RecordAlreadyExist);
}

// Balance on multiple inserts (RR case)
TEST(AVLTree_Balance, RightRightRotation) {
    AVLTreeTable<int, std::string> avl;
    avl.insertRecord({ 10, "10" });
    avl.insertRecord({ 20, "20" });
    avl.insertRecord({ 30, "30" });  // should trigger RR rotation
    std::vector<int> out;
    for (avl.resetIterator(); !avl.isEnd(); avl.goNext()) out.push_back(avl.getCurrentRecord().key);
    EXPECT_EQ(out, (std::vector<int>{10, 20, 30}));
}

// Delete from empty throws
TEST(AVLTree_Delete, EmptyThrows) {
    AVLTreeTable<int, std::string> avl;
    EXPECT_THROW(avl.deleteRecord(1), DeleteFromEmptyTable);
}

// Delete existing and re-balance
TEST(AVLTree_Delete, ExistingKeyRebalance) {
    AVLTreeTable<int, std::string> avl;
    for (int k : {10, 20, 30, 40, 50, 25}) avl.insertRecord({ k, std::to_string(k) });
    EXPECT_NO_THROW(avl.deleteRecord(30));
    std::vector<int> out;
    for (avl.resetIterator(); !avl.isEnd(); avl.goNext()) out.push_back(avl.getCurrentRecord().key);
    EXPECT_EQ(out.size(), 5);
}