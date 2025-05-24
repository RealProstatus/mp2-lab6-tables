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

// Тест удаления элементов (все три случая)
TEST(TreeTableTest, DeleteOperations) {
    TreeTable<int, std::string> table;

    // Создаем дерево:      5
    //                    /   \
    //                   3     7
    //                  / \   /
    //                 1   4 6
    table.insertRecord({ 5, "five" });
    table.insertRecord({ 3, "three" });
    table.insertRecord({ 7, "seven" });
    table.insertRecord({ 1, "one" });
    table.insertRecord({ 4, "four" });
    table.insertRecord({ 6, "six" });

    // Случай 1: Удаление листа (нет потомков)
    table.deleteRecord(1);
    EXPECT_FALSE(table.findRecord(1));

    // Случай 2: Удаление узла с одним потомком
    table.deleteRecord(7); // У 7 есть только левый потомок 6
    EXPECT_FALSE(table.findRecord(7));
    EXPECT_TRUE(table.findRecord(6)); // Проверяем, что 6 остался в дереве

    // Случай 3: Удаление узла с двумя потомками
    table.deleteRecord(3); // У 3 есть оба потомка (1 уже удален, теперь 4)
    EXPECT_FALSE(table.findRecord(3));
    EXPECT_TRUE(table.findRecord(4)); // Проверяем, что 4 остался в дереве

    // Попытка удалить несуществующий элемент
    EXPECT_NO_THROW(table.deleteRecord(10));
}

// Тест итерационных методов
TEST(TreeTableTest, IterationMethods) {
    TreeTable<int, std::string> table;

    // Создаем дерево:      5
    //                    /   \
    //                   3     7
    //                  / \   /
    //                 1   4 6
    // ожидаемый порядок обхода 1 3 4 5 6 7
    table.insertRecord({ 5, "five" });
    table.insertRecord({ 3, "three" });
    table.insertRecord({ 7, "seven" });
    table.insertRecord({ 1, "one" });
    table.insertRecord({ 4, "four" });
    table.insertRecord({ 6, "six" });

    // Проверка порядка обхода (должен быть отсортированным)
    std::vector<int> expected_order = { 1, 3, 4, 5, 6, 7 };
    std::vector<int> actual_order;

    for (table.resetIterator(); !(table.isEnd()); table.goNext()) {
        actual_order.push_back(table.getCurrentRecord().key);
    }

    EXPECT_EQ(actual_order, expected_order);
}


// Тест граничных условий
TEST(TreeTableTest, EdgeCases) {
    TreeTable<int, std::string> table;

    // Работа с пустым деревом
    EXPECT_FALSE(table.findRecord(1));
    EXPECT_NO_THROW(table.deleteRecord(1));
    EXPECT_TRUE(table.isEnd());

    // Проверка is_end после reset для пустого дерева
    table.resetIterator();
    EXPECT_TRUE(table.isEnd());
}

// Тест с последовательным удалением всех элементов
TEST(TreeTableTest, SequentialDeletion) {
    TreeTable<int, std::string> table;

    table.insertRecord({ 5, "five" });
    table.insertRecord({ 3, "three" });
    table.insertRecord({ 7, "seven" });
    table.insertRecord({ 1, "one" });
    table.insertRecord({ 4, "four" });
    table.insertRecord({ 6, "six" });

    // Удаляем все элементы в произвольном порядке
    table.deleteRecord(5);
    table.deleteRecord(1);
    table.deleteRecord(7);
    table.deleteRecord(3);
    table.deleteRecord(6);
    table.deleteRecord(4);

    EXPECT_TRUE(table.isEmpty());
}