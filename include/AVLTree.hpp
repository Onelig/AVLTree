#pragma once

namespace Tree
{
	template<typename T, typename T_Height = unsigned char>
	class AVLTree
	{
	public: // Node
		class Node
		{
		public:
			T data;
		private:
			Node(T data = T(), Node* right = nullptr, Node* left = nullptr) : data(data), right(right), left(left), height(1) { }

			Node* left;
			Node* right;
			T_Height height;

			friend class AVLTree;
		};

	private:
		Node* root;
		bool isSuccessfully = true;
		unsigned short size_ = 0;

	public: // Constructors
		AVLTree() : root(nullptr) { }
		AVLTree(const T& data) : root(new Node(data)) { }
	};
}