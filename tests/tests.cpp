#include <AVLTree.hpp>
#include <gtest/gtest.h>
#include <random>
#include <vector>

std::random_device rd;
std::mt19937 mt19937(rd());
std::uniform_real_distribution<double> urd;
std::uniform_int_distribution<int> uid;

class AVLTreeTest_int : public ::testing::TestWithParam<int> 
{
protected:
    Tree::AVLTree<int> obj;

public:
    static std::vector<int> vec;
};

std::vector<int> AVLTreeTest_int::vec(200);


TEST_P(AVLTreeTest_int, InsertANDBalance)
{
    int param = GetParam();
    std::set<int> set;

    for (size_t i = 0; i < param; i++)
    {
        int temp = uid(mt19937);
        obj.insert(temp);
        set.insert(temp);
    }
    EXPECT_EQ(set, std::set<int>(obj.begin(), obj.end()));
}

TEST_P(AVLTreeTest_int, EraseANDBalance)
{
    int param = GetParam();
    std::set<int> set;
    //std::cout << "Set: { ";
    std::vector<int> some_elemets;
    for (size_t i = 0; i < param; i++)
    {
        int temp = uid(mt19937) & 100000;
        obj.insert(temp);
        set.insert(temp);

        if (!(i % 2))
            some_elemets.push_back(temp);
    }

    for (const int& element : some_elemets)
    {
        obj.erase(element);
        set.erase(element);
    }

    EXPECT_EQ(set, std::set<int>(obj.begin(), obj.end()));
}

TEST_P(AVLTreeTest_int, FindElement)
{
    int param = GetParam();
    std::set<int> set;
    std::vector<int> vec(param);
    for (size_t i = 0; i < param; i++)
    {
        int temp = uid(mt19937);
        obj.insert(temp);
        set.insert(temp);
        vec[i] = temp;
    }
    
    for (size_t i = 0; i < param; i++)
    {
        EXPECT_EQ(*set.find(vec[i]), obj.find(vec[i])->data);
    }
}

TEST_P(AVLTreeTest_int, Clear)
{
    int param = GetParam();
    std::set<int> set;
    for (size_t i = 0; i < param; i++)
    {
        int temp = uid(mt19937);
        obj.insert(temp);
        set.insert(temp);
    }
    
    set.clear();
    obj.clear();

    EXPECT_EQ(set.size(), obj.size());
}

TEST_P(AVLTreeTest_int, Swap)
{
    int param = GetParam();
    std::set<int> set;
    std::set<int> set1;

    Tree::AVLTree<int> obj1;
    for (int i = 0; i < param; i++)
    {
        int temp = uid(mt19937);
        obj.insert(temp);
        obj1.insert(temp + i * i);
        set.insert(temp);
        set1.insert(temp + i * i);
    }

    set.swap(set1);
    obj.swap(obj1);

    EXPECT_EQ(set, std::set<int>(obj.begin(), obj.end()));
    EXPECT_EQ(set1, std::set<int>(obj1.begin(), obj1.end()));
}

TEST_P(AVLTreeTest_int, Distance)
{
    int param = GetParam() % 1000;
    std::set<int> set, set2;
    for (size_t i = 0; i < param; i++)
    {
        int temp = uid(mt19937);
        obj.insert(temp);
        set.insert(temp);
        set2.insert(temp);
        set2.insert(uid(mt19937));
    }
    if (!set.empty())
    {
        std::set<int>::iterator last = --set2.end();
        for (std::set<int>::iterator i = set2.begin(); i != last; ++i)
        {
            for (std::set<int>::iterator j = ++i; j != set2.end(); ++j)
            {
                if (set.find(*i) == set.end() || set.find(*j) == set.end())
                {
                    EXPECT_EQ(0, obj.distance(*i, *j));
                }
                else
                {
                    EXPECT_EQ(std::distance(set.find(*i), set.find(*j)), obj.distance(*i, *j));
                }
            }
            --i;
        }
    }
}

INSTANTIATE_TEST_SUITE_P(RandomInt, AVLTreeTest_int, ::testing::ValuesIn(AVLTreeTest_int::vec.begin(), AVLTreeTest_int::vec.end()));


class AVLTreeTest_pair : public ::testing::TestWithParam<int>
{
protected:
    Tree::AVLTree<std::pair<double, int>> obj;

public:
    static std::vector<int> vec;
};

std::vector<int> AVLTreeTest_pair::vec(100);

TEST_P(AVLTreeTest_pair, InsertANDBalance)
{
    int param = GetParam();
    std::set<std::pair<double, int>> set;
    for (size_t i = 0; i < param; i++)
    {
        int temp = uid(mt19937);
        double temp_d = urd(mt19937) * 100;
        obj.insert(std::pair{temp_d, temp});
        set.insert(std::pair{ temp_d, temp });
    }

    std::set<std::pair<double, int>> b(obj.begin(), obj.end());
    EXPECT_EQ(set, b);
}

TEST_P(AVLTreeTest_pair, EraseANDBalance)
{
    int param = GetParam();
    std::set<std::pair<double, int>> set;
    //std::cout << "Set: { ";
    std::vector<std::pair<double, int>> some_elemets;
    for (size_t i = 0; i < param; i++)
    {
        int temp = uid(mt19937);
        double temp_d = urd(mt19937) * 100;
        obj.insert(std::pair{ temp_d, temp });
        set.insert(std::pair{ temp_d, temp });

        if (!(i % 2))
            some_elemets.push_back(std::pair<double, int>(temp_d, temp));
    }

    for (const std::pair<double, int>& element : some_elemets)
    {
        obj.erase(element);
        set.erase(element);
    }

    std::set<std::pair<double, int>> b(obj.begin(), obj.end());
    EXPECT_EQ(set, b);
}

TEST_P(AVLTreeTest_pair, FindElement)
{
    int param = GetParam();
    std::set<std::pair<double, int>> set;
    std::vector<std::pair<double, int>> vec(param);
    for (size_t i = 0; i < param; i++)
    {
        int temp = uid(mt19937);
        double temp_d = urd(mt19937) * 10;
        obj.insert(std::pair{ temp_d, temp });
        set.insert(std::pair{ temp_d, temp });
        vec[i] = std::pair<double, int>(temp_d, temp);
    }

    for (size_t i = 0; i < param; i++)
    {
        EXPECT_EQ(*set.find(vec[i]), obj.find(vec[i])->data);
    }
}

TEST_P(AVLTreeTest_pair, Clear)
{
    int param = GetParam();
    std::set<std::pair<double, int>> set;
    for (size_t i = 0; i < param; i++)
    {
        int temp = uid(mt19937);
        double temp_d = urd(mt19937) * 10;
        obj.insert(std::pair{ temp_d, temp });
        set.insert(std::pair{ temp_d, temp });
    }

    set.clear();
    obj.clear();

    EXPECT_EQ(set.size(), obj.size());
}

TEST_P(AVLTreeTest_pair, Swap)
{
    int param = GetParam();
    std::set<std::pair<double, int>> set;
    std::set<std::pair<double, int>> set1;

    Tree::AVLTree<std::pair<double, int>> obj1;
    for (size_t i = 0; i < param; i++)
    {
        int temp = uid(mt19937);
        double temp_d = urd(mt19937) * 10;
        obj.insert(std::pair{ temp_d, temp });
        obj1.insert(std::pair{ temp_d + i * i, temp });
        set.insert(std::pair{ temp_d, temp });
        set1.insert(std::pair{ temp_d + i * i, temp });
    }
    set.swap(set1);
    obj.swap(obj1);

    std::set<std::pair<double, int>> b1(obj.begin(), obj.end());
    std::set<std::pair<double, int>> b2(obj1.begin(), obj1.end());

    EXPECT_EQ(set, b1);
    EXPECT_EQ(set1, b2);
}

TEST_P(AVLTreeTest_pair, Distance)
{
    int param = GetParam() % 1000;
    std::set<std::pair<double, int>> set;
    std::set<std::pair<double, int>> set2;
    
    for (size_t i = 0; i < param; i++)
    {
        int temp = uid(mt19937);
        double temp_d = urd(mt19937) * 10; 
        obj.insert(std::pair{ temp_d, temp });
        set.insert(std::pair{ temp_d, temp });
        set2.insert(std::pair{ temp_d, temp });
        set2.insert(std::pair{ urd(mt19937) * 10, uid(mt19937) });
    }
    if (!set.empty())
    {
        std::set<std::pair<double, int>>::iterator last = --set2.end();
        for (std::set<std::pair<double, int>>::iterator i = set2.begin(); i != last; ++i)
        {
            for (std::set<std::pair<double, int>>::iterator j = ++i; j != set2.end(); ++j)
            {
                if (set.find(*i) == set.end() || set.find(*j) == set.end())
                {
                    EXPECT_EQ(0, obj.distance(*i, *j));
                }
                else
                {
                    EXPECT_EQ(std::distance(set.find(*i), set.find(*j)), obj.distance(*i, *j));
                }
            }
            --i;
        }
    }

}

//INSTANTIATE_TEST_SUITE_P(RandomPair, AVLTreeTest_pair, ::testing::ValuesIn(AVLTreeTest_pair::vec.begin(), AVLTreeTest_pair::vec.end()));
INSTANTIATE_TEST_SUITE_P(RandomPair, AVLTreeTest_pair, ::testing::ValuesIn(AVLTreeTest_pair::vec.begin(), AVLTreeTest_pair::vec.end()));
int main(int argc, char** argv) 
{
    for (int& param : AVLTreeTest_int::vec)
    {
        param = uid(mt19937) % 9898;
    } 
    
    for (int& param : AVLTreeTest_pair::vec)
    {
        param = uid(mt19937) % 9898;
    }

    ::testing::InitGoogleTest(&argc, argv);
    int p = RUN_ALL_TESTS();
    system("pause");
    return p;
}