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

		//
		// Private Methods
		//

		// R || Insert Element + Balance
		Node* insert_(Node* root, const T& data);

	public: // Constructors
		AVLTree() : root(nullptr) { }
		AVLTree(const T& data) : root(new Node(data)) { }

	public: // Methods
		bool insert(const T& data);

	};

	//
	// Private Methods
	//
	
	// R || Insert Element + Balance
	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::Node AVLTree<T, T_Height>::insert_(Node* root, const T& data)
	{
		if (root == nullptr)
		{
			return new Node(data);
		}
		else if (data < root->data)
		{
			root->left = insert_(root->left, data);
		}
		else if (data > root->data)
		{
			root->right = insert_(root->right, data);
		}
		else if (root->data == data)
		{
			isSuccessfully = false;
			return root;
		}

		return isSuccessfully ? balance(root) : root;
	}

	//
	// Public Methods
	//

	template<typename T, typename T_Height>
	inline bool AVLTree<T, T_Height>::insert(const T& data)
	{
		isSuccessfully = true;
		root = insert_(root, data);
		size_ += isSuccessfully;
		return isSuccessfully;
	}
}