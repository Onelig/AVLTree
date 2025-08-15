#include "AVLTree.hpp"
#include <gtest/gtest.h>
#include <set>

class AVLTree_pair : public ::testing::Test {
protected:
    Tree::AVLTree<std::pair<double,int>> obj;
};

using PairType = std::pair<double,int>;


TEST_F(AVLTree_pair, InsertANDBalance) {
    std::pair<double,int> values[] = {{1.1,1}, {2.2,2}, {3.3,3}};
    std::set<std::pair<double,int>> expected(values, values + 3);

    for (auto& v : values)
        obj.insert(v);

    ASSERT_EQ(expected, std::set<PairType>(obj.begin(), obj.end()));
}

TEST_F(AVLTree_pair, EraseANDBalance) {
    std::pair<double,int> values[] = {{1.1,1}, {2.2,2}, {3.3,3}};
    std::set<std::pair<double,int>> expected(values, values + 3);

    for (auto& v : values)
        obj.insert(v);

    obj.erase({2.2,2});
    expected.erase({2.2,2});

    ASSERT_EQ(expected, std::set<PairType>(obj.begin(), obj.end()));
}

TEST_F(AVLTree_pair, FindElement) {
    std::pair<double,int> values[] = {{1.0,1}, {2.0,2}, {3.0,3}};
    for (auto& v : values)
        obj.insert(v);

    for (auto& v : values)
        ASSERT_EQ(v, obj.find(v)->data);

    ASSERT_EQ(nullptr, obj.find({10.0,10}));
}

TEST_F(AVLTree_pair, Clear) {
    std::pair<double,int> values[] = {{1.0,1}, {2.0,2}, {3.0,3}};
    for (auto& v : values)
        obj.insert(v);

    obj.clear();
    ASSERT_EQ(0, obj.size());
}

TEST_F(AVLTree_pair, Swap) {
    Tree::AVLTree<std::pair<double,int>> obj1;
    std::pair<double,int> values1[] = {{1.0,1}, {2.0,2}};
    std::pair<double,int> values2[] = {{10.0,10}, {20.0,20}};

    for (auto& v : values1) obj.insert(v);
    for (auto& v : values2) obj1.insert(v);

    std::set<std::pair<double,int>> set1(values1, values1 + 2);
    std::set<std::pair<double,int>> set2(values2, values2 + 2);

    obj.swap(obj1);
    set1.swap(set2);

    ASSERT_EQ(set1, std::set<PairType>(obj.begin(), obj.end()));
    ASSERT_EQ(set2, std::set<PairType>(obj1.begin(), obj1.end()));
}
