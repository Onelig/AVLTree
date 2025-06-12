#include <iostream>
#include <vector>
#include <set>
#include <vector>
#include <algorithm>
#include <AVLTree.hpp>

int main()
{
    Tree::AVLTree<int> obj{ 1,2,3,4 };

	std::for_each(obj.crbegin(), obj.crend(), [](auto&& vl) { std::cout << vl << " "; });

	return 0;
}