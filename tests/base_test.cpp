#include "AVLTree.hpp"
#include <gtest/gtest.h>


TEST(AVLTreeTest, InsertElements) 
{
    Tree::AVLTree<int> tree;
    ASSERT_TRUE(tree.insert(10));
    ASSERT_TRUE(tree.insert(20));
    ASSERT_TRUE(tree.insert(5));
    ASSERT_EQ(tree.size(), 3);
    ASSERT_NE(tree.find(10), nullptr);
}


TEST(AVLTreeTest, InsertDuplicateElements) 
{
    Tree::AVLTree<int> tree;
    ASSERT_TRUE(tree.insert(10));
    ASSERT_FALSE(tree.insert(10));
    ASSERT_EQ(tree.size(), 1);
}

TEST(AVLTreeTest, FindInEmptyTree) 
{
    Tree::AVLTree<int> tree;
    ASSERT_EQ(tree.find(42), nullptr);
}


// ------------------- Erase -------------------
TEST(AVLTreeTest, EraseElements) 
{
    Tree::AVLTree<int> tree = {10, 20, 5};
    ASSERT_TRUE(tree.erase(10));
    ASSERT_EQ(tree.size(), 2);
    ASSERT_EQ(tree.find(10), nullptr);
}


TEST(AVLTreeTest, EraseNonExisting) 
{
    Tree::AVLTree<int> tree = {1, 2, 3};
    ASSERT_FALSE(tree.erase(42));
    ASSERT_EQ(tree.size(), 3);
}


TEST(AVLTreeTest, EraseAll) 
{
    Tree::AVLTree<int> tree = {1, 2, 3};
    ASSERT_TRUE(tree.erase(1));
    ASSERT_TRUE(tree.erase(2));
    ASSERT_TRUE(tree.erase(3));
    ASSERT_EQ(tree.size(), 0);
}


// ------------------- Balance -------------------
TEST(AVLTreeTest, BalanceAfterAscendingInsert) 
{
    Tree::AVLTree<int> tree;
    for(int i=1; i<=10; ++i) tree.insert(i);
    ASSERT_EQ(tree.size(), 10);
    for(int i=1; i<=10; ++i) ASSERT_NE(tree.find(i), nullptr);
}


TEST(AVLTreeTest, BalanceAfterDescendingInsert) 
{
    Tree::AVLTree<int> tree;
    for(int i=10; i>=1; --i) tree.insert(i);
    ASSERT_EQ(tree.size(), 10);
    for(int i=1; i<=10; ++i) ASSERT_NE(tree.find(i), nullptr);
}


// ------------------- Copy & Move -------------------
TEST(AVLTreeTest, CopyTree) 
{
    Tree::AVLTree<int> tree1 = {1, 2, 3};
    Tree::AVLTree<int> tree2 = tree1;
    ASSERT_TRUE(tree1 == tree2);
}


TEST(AVLTreeTest, MoveTree) {
    Tree::AVLTree<int> tree1 = {1, 2, 3};
    Tree::AVLTree<int> tree2 = std::move(tree1);
    ASSERT_EQ(tree2.size(), 3); 
}


// ------------------- Iterators & Distance -------------------
TEST(AVLTreeTest, Iterators) 
{
    Tree::AVLTree<int> tree = {2, 1, 3};
    std::vector<int> result;
    for(auto it = tree.begin(); it != tree.end(); ++it) result.push_back(*it);
    ASSERT_EQ(result, (std::vector<int>{1,2,3}));

    result.clear();
    for(auto it = tree.rbegin(); it != tree.rend(); ++it) result.push_back(*it);
    ASSERT_EQ(result, (std::vector<int>{3,2,1}));
}


TEST(AVLTreeTest, ConstIterators) 
{
    const Tree::AVLTree<int> tree = {5,3,7};
    std::vector<int> result;
    for(auto it = tree.cbegin(); it != tree.cend(); ++it) result.push_back(*it);
    ASSERT_EQ(result, (std::vector<int>{3,5,7}));
}


TEST(AVLTreeTest, DistanceAndLCA) 
{
    Tree::AVLTree<int> tree = {10,5,15,3,7};
    ASSERT_EQ(tree.distance(3,7), 2);
    ASSERT_EQ(tree.distance(3,15), 4);
    ASSERT_EQ(tree.distance(5,5), 0);
}