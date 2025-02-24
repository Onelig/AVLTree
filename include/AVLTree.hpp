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

		unsigned char abs(signed char element) const;

		// Balancing

		// Single Left Rotation
		void SingleLeftRotation(Node*& root);

		// Double Left Roration
		void DoubleLeftRotation(Node*& root);

		// Single Right Rotation
		void SingleRightRotation(Node*& root);

		// Double Right Roration
		void DoubleRightRotation(Node*& root);


		// Get The Correct Height
		T_Height height(Node* root) const;

		// Update Height
		void update(Node* root);

		// Get Balance Factor
		signed char balance_factor(Node* root) const;

		// Balance Root + Update Height
		Node* balance(Node* root);

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
	
	// Balancing

	// Single Left Rotation
	template<typename T, typename T_Height>
	void AVLTree<T, T_Height>::SingleLeftRotation(Node*& root)
	{
		Node* root_copy = root;
		root = root->right;
		root_copy->right = root->left;
		root->left = root_copy;

		update(root->left);
		update(root);
	}

	// Double Left Roration
	template<typename T, typename T_Height>
	void AVLTree<T, T_Height>::DoubleLeftRotation(Node*& root)
	{
		Node* root_copy_main = root, * root_copy_right = root->right;
		root = root_copy_right->left;
		root_copy_main->right = root->left;
		root_copy_right->left = root->right;
		root->left = root_copy_main;
		root->right = root_copy_right;

		update(root->left);
		update(root->right);
		update(root);
	}

	// Single Right Rotation
	template<typename T, typename T_Height>
	void AVLTree<T, T_Height>::SingleRightRotation(Node*& root)
	{
		Node* root_copy = root;
		root = root->left;
		root_copy->left = root->right;
		root->right = root_copy;

		update(root->right);
		update(root);
	}

	// Double Right Roration
	template<typename T, typename T_Height>
	void AVLTree<T, T_Height>::DoubleRightRotation(Node*& root)
	{
		Node* root_copy_main = root, * root_copy_left = root->left;
		root = root_copy_left->right;
		root_copy_main->left = root->right;
		root_copy_left->right = root->left;
		root->right = root_copy_main;
		root->left = root_copy_left;

		update(root->right);
		update(root->left);
		update(root);
	}


	// Get The Correct Height
	template<typename T, typename T_Height>
	T_Height AVLTree<T, T_Height>::height(Node* root) const
	{
		return root ? root->height : 0;
	}

	template<typename T, typename T_Height>
	inline unsigned char AVLTree<T, T_Height>::abs(signed char element) const
	{
		return element > 0 ? element : -element;
	}

	// Update Height
	template<typename T, typename T_Height>
	void AVLTree<T, T_Height>::update(Node* root)
	{
		root->height = (height(root->left) > height(root->right) ? height(root->left) : height(root->right)) + 1;
	}

	// Get Balance Factor
	template<typename T, typename T_Height>
	signed char AVLTree<T, T_Height>::balance_factor(Node* root) const
	{
		return height(root->left) - height(root->right);
	}

	// Balance Root + Update Height
	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::Node* AVLTree<T, T_Height>::balance(Node* root)
	{
		signed char bal_factor = balance_factor(root);
		if (abs(bal_factor) <= 1)
		{
			update(root);
		}
		else
		{
			if (bal_factor == -2) // Left Rotation
			{
				signed char bal_factor_right = balance_factor(root->right);
				if (bal_factor_right <= 0) // Single Left Rotation
					SingleLeftRotation(root);

				else if (bal_factor_right > 0) // Double Left Roration
					DoubleLeftRotation(root);
			}
			else if (bal_factor == 2) // Right Rotation
			{
				signed char bal_factor_left = balance_factor(root->left);
				if (bal_factor_left >= 0) // Single Right Rotation
					SingleRightRotation(root);

				else if (bal_factor_left < 0) // Double Right Roration
					DoubleRightRotation(root);
			}
		}

		return root;
	}

	// R || Insert Element + Balance
	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::Node* AVLTree<T, T_Height>::insert_(Node* root, const T& data)
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