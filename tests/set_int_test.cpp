#include "AVLTree.hpp"
#include <gtest/gtest.h>
#include <set>

class AVLTree_int : public ::testing::Test 
{
protected:
    Tree::AVLTree<int> obj;
};


TEST_F(AVLTree_int, InsertANDBalance) 
{
    int values[] = {10, 5, 20, 3, 7, 15, 30};
    std::set<int> expected(values, values + 7);

    for (int v : values)
        obj.insert(v);

    ASSERT_EQ(expected, std::set<int>(obj.begin(), obj.end()));
}


TEST_F(AVLTree_int, EraseANDBalance) 
{
    int values[] = {10, 5, 20, 3, 7};
    std::set<int> expected(values, values + 5);

    for (int v : values)
        obj.insert(v);

    int to_erase[] = {5, 10};
    for (int v : to_erase) {
        obj.erase(v);
        expected.erase(v);
    }

    ASSERT_EQ(expected, std::set<int>(obj.begin(), obj.end()));
}


TEST_F(AVLTree_int, FindElement) 
{
    int values[] = {1, 2, 3, 4};
    for (int v : values)
        obj.insert(v);

    for (int v : values)
        ASSERT_EQ(v, obj.find(v)->data);

    ASSERT_EQ(nullptr, obj.find(10));
}


TEST_F(AVLTree_int, Clear) 
{
    int values[] = {1, 2, 3};
    for (int v : values)
        obj.insert(v);

    obj.clear();
    ASSERT_EQ(0, obj.size());
}


TEST_F(AVLTree_int, Swap)
 {
    Tree::AVLTree<int> obj1;
    int values1[] = {1, 2, 3};
    int values2[] = {10, 20, 30};

    for (int v : values1) obj.insert(v);
    for (int v : values2) obj1.insert(v);

    std::set<int> set1(values1, values1 + 3);
    std::set<int> set2(values2, values2 + 3);

    obj.swap(obj1);
    set1.swap(set2);

    ASSERT_EQ(set1, std::set<int>(obj.begin(), obj.end()));
    ASSERT_EQ(set2, std::set<int>(obj1.begin(), obj1.end()));
}
