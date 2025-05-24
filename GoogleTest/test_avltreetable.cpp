#include"gtest.h"
#include"../mp2-lab6-tables/BalanceTreeTable.h"

static std::vector<int> collectKeys(AVLTreeTable<int, std::string>& avl) {
    std::vector<int> out;
    for (avl.resetIterator(); !avl.isEnd(); avl.goNext()) {
        out.push_back(avl.getCurrentRecord().key);
    }
    return out;
}

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

// Right-Right (RR) ротация: 10,20,30 → in-order 10,20,30
TEST(AVL_Balance, RightRightRotation) {
    AVLTreeTable<int, std::string> avl;
    avl.insertRecord({ 10,"10" });
    avl.insertRecord({ 20,"20" });
    avl.insertRecord({ 30,"30" });  // RR
    EXPECT_EQ(collectKeys(avl), std::vector<int>({ 10,20,30 }));
}

// Left-Left (LL) ротация: 30,20,10 → in-order 10,20,30
TEST(AVL_Balance, LeftLeftRotation) {
    AVLTreeTable<int, std::string> avl;
    avl.insertRecord({ 30,"30" });
    avl.insertRecord({ 20,"20" });
    avl.insertRecord({ 10,"10" });  // LL
    EXPECT_EQ(collectKeys(avl), std::vector<int>({ 10,20,30 }));
}

// Left-Right (LR) ротация: 30,10,20 → in-order 10,20,30
TEST(AVL_Balance, LeftRightRotation) {
    AVLTreeTable<int, std::string> avl;
    avl.insertRecord({ 30,"30" });
    avl.insertRecord({ 10,"10" });
    avl.insertRecord({ 20,"20" });  // LR
    EXPECT_EQ(collectKeys(avl), std::vector<int>({ 10,20,30 }));
}

// Right-Left (RL) ротация: 10,30,20 → in-order 10,20,30
TEST(AVL_Balance, RightLeftRotation) {
    AVLTreeTable<int, std::string> avl;
    avl.insertRecord({ 10,"10" });
    avl.insertRecord({ 30,"30" });
    avl.insertRecord({ 20,"20" });  // RL
    EXPECT_EQ(collectKeys(avl), std::vector<int>({ 10,20,30 }));
}

// Удаление из пустого дерева бросает
TEST(AVL_Delete, EmptyTreeThrows) {
    AVLTreeTable<int, std::string> avl;
    EXPECT_THROW(avl.deleteRecord(1), DeleteFromEmptyTable);
}

// Удаление листа корректно
TEST(AVL_Delete, RemoveLeaf) {
    AVLTreeTable<int, std::string> avl;
    for (int k : {20, 10, 30}) avl.insertRecord({ k,std::to_string(k) });
    EXPECT_NO_THROW(avl.deleteRecord(10));  // 10 — лист
    EXPECT_EQ(avl.getDataCount(), 2);
    EXPECT_EQ(collectKeys(avl), std::vector<int>({ 20,30 }));
}

// Удаление узла с одним ребёнком корректно
TEST(AVL_Delete, RemoveNodeWithOneChild) {
    AVLTreeTable<int, std::string> avl;
    // Построим цепочку: 20 → 10 → 5
    for (int k : {20, 10, 5}) avl.insertRecord({ k,std::to_string(k) });
    EXPECT_NO_THROW(avl.deleteRecord(10));  // 10 имеет единственного ребёнка 5
    EXPECT_EQ(avl.getDataCount(), 2);
    // После удаления должно остаться {5,20} in-order
    EXPECT_EQ(collectKeys(avl), std::vector<int>({ 5,20 }));
}

// Удаление узла с двумя детьми корректно и ребалансировка
TEST(AVL_Delete, RemoveNodeWithTwoChildrenRebalance) {
    AVLTreeTable<int, std::string> avl;
    for (int k : {40, 20, 60, 10, 30, 50, 70}) avl.insertRecord({ k,std::to_string(k) });
    // Удаляем корень 40, у которого двое детей
    EXPECT_NO_THROW(avl.deleteRecord(40));
    EXPECT_EQ(avl.getDataCount(), 6);
    // in-order после удаления — все кроме 40
    std::vector<int> expected = { 10,20,30,50,60,70 };
    EXPECT_EQ(collectKeys(avl), expected);
}

// После серии вставок/удалений дерево остаётся сбалансированным
TEST(AVL_Stress, BalanceAfterManyOps) {
    AVLTreeTable<int, std::string> avl;
    // Вставим 1..100
    for (int i = 1; i <= 100; i++) avl.insertRecord({ i,std::to_string(i) });
    // Удалим все чётные
    for (int i = 2; i <= 100; i += 2) avl.deleteRecord(i);
    // Проверим count и in-order = все нечётные
    EXPECT_EQ(avl.getDataCount(), 50);
    auto out = collectKeys(avl);
    std::vector<int> expected;
    for (int i = 1; i <= 100; i += 2) expected.push_back(i);
    EXPECT_EQ(out, expected);
    // Проверим эффективность не нулевая 
    EXPECT_GT(avl.getEfficiency(), 0);
}

TEST(AVLTree_log, LogDifficultTest) {
    AVLTreeTable<int, std::string> avl;
    for (int i = 1; i <= 100; i++) avl.insertRecord({ i,std::to_string(i) });

    EXPECT_TRUE(avl.findRecord(75));
    avl.getEfficiency();
    EXPECT_TRUE(avl.getEfficiency() <= 7);
}