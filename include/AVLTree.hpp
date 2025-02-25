#pragma once
#include <initializer_list>
#include <stdexcept> 

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

		enum class ITER
		{
			cIter, rIter
		};

	private:
		Node* root;
		bool isSuccessfully = true;
		unsigned short size_ = 0;

		static constexpr AVLTree::Node* BEGIN = reinterpret_cast<AVLTree::Node*>(0x1);
		static constexpr AVLTree::Node* END = reinterpret_cast<AVLTree::Node*>(0x2);

		//
		// Private Methods
		//

		// static Methods
		
		// Get Next Element
		static Node* getNext(Node* current, Node* root);

		// Get Previous Element
		static Node* getPrevious(Node* current, Node* root);

		// Get Next Lvl + !!! DO NOT USE FOR MIDDLE ELEMENT !!!
		static Node* GetLvlUp(const T& data, Node* root);
		static Node* GetLvlDw(const T& data, Node* root);

		// Get Minimal Element
		static Node* GetMinElement(Node* root);

		// Get Maximal Element
		static Node* GetMaxElement(Node* root);

		// _static Methods

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

		// _Balancing

		// Remove All Elements (NEED THAT SIZE > 0)
		Node* RemoveAllNode(Node* root);

		// Copy Data to root from other_root
		Node* CopyAVLTree(Node* root, const Node* other_root);

		// Remove Minimal Element + Balance Tree
		Node* RemBalMin(Node* root, Node* minroot);

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

		// R || Erase Element + Balance
		Node* erase_(Node* root, const T& data);

		// R || Find Element
		Node* find_(Node* root, const T& data) const;

		// _Private Methods
	public: // Constructors
		AVLTree() : root(nullptr) { }
		AVLTree(const T& data) : root(new Node(data)) { }
		AVLTree(const std::initializer_list<T>& init_list);

		AVLTree(const AVLTree<T, T_Height>& other);
		AVLTree(AVLTree<T, T_Height>&& other);

		AVLTree<T, T_Height>& operator=(const AVLTree<T, T_Height>& other);
		AVLTree<T, T_Height>& operator=(AVLTree<T, T_Height>&& other) noexcept;

		virtual ~AVLTree();
	public: // Methods
		bool insert(const T& data);
		bool erase(const T& data);
		const Node* find(const T& data) const&;
		void clear();
		void swap(Tree::AVLTree<T, T_Height>& AvlTree);
		unsigned short size();

		friend class cIterator;
	public: // cIterator
		class cIterator
		{
		private:
			Node* current;
			Node* root;

		public:
			cIterator(Node* current, Node* root)
				: root(root), current(current) { }

			const T& operator*() const;

			cIterator& operator++() noexcept(false);

			cIterator operator++(int) noexcept(false);

			cIterator& operator--() noexcept(false);

			cIterator operator--(int) noexcept(false);

			bool operator==(const cIterator& other) const;

			bool operator!=(const cIterator& other) const;

			T* operator->() const;
		};

	};

	//
	// Private Methods
	//
	
	// Balancing

	// Single Left Rotation
	template<typename T, typename T_Height>
	inline void AVLTree<T, T_Height>::SingleLeftRotation(Node*& root)
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
	inline void AVLTree<T, T_Height>::DoubleLeftRotation(Node*& root)
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
	inline void AVLTree<T, T_Height>::SingleRightRotation(Node*& root)
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
	inline void AVLTree<T, T_Height>::DoubleRightRotation(Node*& root)
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

	// _Balancing

	// Remove All Elements (NEED THAT SIZE > 0)
	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::Node* AVLTree<T, T_Height>::RemoveAllNode(Node* root)
	{
		if (root->left != nullptr)
		{
			root->left = RemoveAllNode(root->left);
		}
		if (root->right != nullptr)
		{
			root->right = RemoveAllNode(root->right);
		}

		delete root;
		return nullptr;
	}

	// Copy Data to root from other_root
	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::Node* AVLTree<T, T_Height>::CopyAVLTree(Node* root, const Node* other_root)
	{
		if (other_root == nullptr)
		{
			return nullptr;
		}

		root = new Node(other_root->data);
		root->height = other_root->height;

		root->left = CopyAVLTree(root->left, other_root->left);
		root->right = CopyAVLTree(root->right, other_root->right);

		return root;
	}

	// Remove Minimal Element + Balance Tree
	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::Node* AVLTree<T, T_Height>::RemBalMin(Node* root, Node* minroot)
	{
		if (root->left == minroot)
		{
			delete minroot;
			root->left = nullptr;
		}
		else
		{
			root->left = RemBalMin(root->left, minroot);
		}

		return balance(root);
	}

	// Get The Correct Height
	template<typename T, typename T_Height>
	inline T_Height AVLTree<T, T_Height>::height(Node* root) const
	{
		return root ? root->height : 0;
	}


	// static Methods

	// Get Next Element
	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::Node* AVLTree<T, T_Height>::getNext(Node* current, Node* root)
	{
		Node* return_node = nullptr;
		if (current->right)
		{
			return_node = GetMinElement(current->right);
		}
		else
		{
			return_node = GetLvlUp(current->data, root);
		}

		return return_node;
	}

	// Get Previous Element
	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::Node* AVLTree<T, T_Height>::getPrevious(Node* current, Node* root)
	{
		Node* return_node = nullptr;
		if (current->left)
		{
			return_node = GetMaxElement(current->left);
		}
		else
		{
			return_node = GetLvlDw(current->data, root);
		}

		return return_node;
	}

	// Get Next Lvl UP ! DO NOT USE FOR MID ELEMENT
	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::Node* AVLTree<T, T_Height>::GetLvlUp(const T& data, Node* root)
	{
		if (root && root->left)
		{
			if (root->left->data <= data)
			{
				if (root->data > data)
				{
					if (GetMaxElement(root->left)->data > data)
					{
						return GetLvlUpL(data, root->left->right);
					}

					return root;
				}
				else if (root->data < data)
				{
					return GetLvlUp(data, root->right);
				}
			}
			return GetLvlUp(data, root->left);
		}

		return root;
	}


	// Get Next Lvl Down ! DO NOT USE FOR MID ELEMENT
	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::Node* AVLTree<T, T_Height>::GetLvlDw(const T& data, Node* root)
	{
		if (root && root->right)
		{
			if (root->right->data >= data)
			{
				if (root->data < data)
				{
					if (GetMixElement(root->right)->data < data)
					{
						return GetLvlUpL(data, root->right->left);
					}

					return root;
				}
				else if (root->data > data)
				{
					return GetLvlDw(data, root->left);
				}
			}
			return GetLvlDw(data, root->right);
		}

		return root;
	}

	// Get Minimal Element
	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::Node* AVLTree<T, T_Height>::GetMinElement(Node* root)
	{
		return root->left == nullptr ? root : GetMinElement(root->left);
	}

	// Get Maximal Element
	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::Node* AVLTree<T, T_Height>::GetMaxElement(Node* root)
	{
		return root->right == nullptr ? root : GetMaxElement(root->right);
	}


	// _static Methods

	template<typename T, typename T_Height>
	inline unsigned char AVLTree<T, T_Height>::abs(signed char element) const
	{
		return element > 0 ? element : -element;
	}

	// Update Height
	template<typename T, typename T_Height>
	inline void AVLTree<T, T_Height>::update(Node* root)
	{
		root->height = (height(root->left) > height(root->right) ? height(root->left) : height(root->right)) + 1;
	}

	// Get Balance Factor
	template<typename T, typename T_Height>
	inline signed char AVLTree<T, T_Height>::balance_factor(Node* root) const
	{
		return height(root->left) - height(root->right);
	}

	// Balance Root + Update Height
	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::Node* AVLTree<T, T_Height>::balance(Node* root)
	{
		if (root)
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

	// R || Erase Element + Balance
	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::Node* AVLTree<T, T_Height>::erase_(Node* root, const T& data)
	{
		if (root == nullptr)
		{
			isSuccessfully = false;
			return nullptr;
		}
		else if (root->data == data)
		{
			if (root->right != nullptr)
			{
				Node* minroot = GetMinElement(root->right);
				if (minroot == root->right)
				{
					Node* copy_root = root;
					root = root->right;
					root->left = copy_root->left;
					delete copy_root;
				}
				else
				{
					root->data = minroot->data;
					root->right = RemBalMin(root->right, minroot);	
				}
			}
			else
			{
				Node* copy_root = root;
				root = root->left;
				delete copy_root;
			}
		}
		else if (data < root->data)
		{
			root->left = erase_(root->left, data);
		}
		else if (data > root->data)
		{
			root->right = erase_(root->right, data);
		}

		return isSuccessfully ? balance(root) : root;
	}

	// R || Find Element
	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::Node* AVLTree<T, T_Height>::find_(Node* root, const T& data) const
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		else if (root->data == data)
		{
			return root;
		}
		else if (data < root->data)
		{
			return find_(root->left, data);
		}
		else if (data > root->data)
		{
			return find_(root->right, data);
		}

		return nullptr;
	}

	// _Private Methods

	//
	// Public Constructors
	//

	template<typename T, typename T_Height>
	inline AVLTree<T, T_Height>::AVLTree(const std::initializer_list<T>& data)
		: root(nullptr)
	{
		for (const T& value : data)
		{
			insert(value);
		}
	}

	template<typename T, typename T_Height>
	inline AVLTree<T, T_Height>::AVLTree(const AVLTree<T, T_Height>& other)
		: size_(other.size_)
	{
		root = CopyAVLTree(root, other.root);
	}

	template<typename T, typename T_Height>
	inline AVLTree<T, T_Height>::AVLTree(AVLTree<T, T_Height>&& other)
		: root(other.root), size_(other.size_)
	{
		other.root = nullptr;
	}

	template<typename T, typename T_Height>
	inline AVLTree<T, T_Height>& AVLTree<T, T_Height>::operator=(const AVLTree<T, T_Height>& other)
	{
		if (this != &other)
		{
			this->clear();
			size_ = other.size_;
			root = CopyAVLTree(root, other.root);
		}

		return *this;
	}

	template<typename T, typename T_Height>
	inline AVLTree<T, T_Height>& AVLTree<T, T_Height>::operator=(AVLTree<T, T_Height>&& other) noexcept
	{
		if (this != &other)
		{
			this->clear();

			size_ = other.size_;
			root = other.root;
			other.root = nullptr;
		}

		return *this;
	}

	template<typename T, typename T_Height>
	inline AVLTree<T, T_Height>::~AVLTree()
	{
		this->clear();
	}

	// _Public Constructors


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

	template<typename T, typename T_Height>
	inline bool AVLTree<T, T_Height>::erase(const T& data)
	{
		isSuccessfully = true;
		root = erase_(root, data);
		size_ -= isSuccessfully;
		return isSuccessfully;
	}

	template<typename T, typename T_Height>
	inline typename const AVLTree<T, T_Height>::Node* AVLTree<T, T_Height>::find(const T& data) const&
	{
		return find_(root, data);
	}

	template<typename T, typename T_Height>
	inline void AVLTree<T, T_Height>::clear()
	{
		if (root != nullptr)
		{
			root = RemoveAllNode(root);
			size_ = 0;
		}
	}

	template<typename T, typename T_Height>
	inline void AVLTree<T, T_Height>::swap(Tree::AVLTree<T, T_Height>& AvlTree)
	{
		Node* copy_root = root;
		root = AvlTree.root;
		AvlTree.root = copy_root;

		unsigned short copy_size = size_;
		size_ = AvlTree.size_;
		AvlTree.size_ = copy_size;
	}
	
	template<typename T, typename T_Height>
	inline unsigned short AVLTree<T, T_Height>::size()
	{
		return size_;
	}

	// _Public Methods

	//
	// cIterator
	//

	template<typename T, typename T_Height>
	inline const T& AVLTree<T, T_Height>::cIterator::operator*() const noexcept(false)
	{
		if (current == END || current == BEGIN)
		{
			throw std::out_of_range("Out of range");
		}
		return current->data;
	}

	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::cIterator& AVLTree<T, T_Height>::cIterator::operator++() noexcept(false)
	{
		if (current == END)
		{
			throw std::out_of_range("Out of range");
		}
		else if (current == BEGIN)
		{
			current = GetMinElement(root);
		}
		else if (GetMaxElement(root) == current)
		{
			current = END;
		}
		else
		{
			current = getNext(current, root);
		}
		return *this;
	}

	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::cIterator AVLTree<T, T_Height>::cIterator::operator++(int) noexcept(false)
	{
		cIterator copy_iter = *this;
		if (current == END)
		{
			throw std::out_of_range("Out of range");
		}
		else if (current == BEGIN)
		{
			current = GetMinElement(root);
		}
		else if (GetMaxElement(root) == current)
		{
			curent = END;
		}
		else
		{
			current = getNext(current, root);
		}
		return copy_iter;
	}

	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::cIterator& AVLTree<T, T_Height>::cIterator::operator--() noexcept(false)
	{
		if (current == END)
		{
			current = GetMaxElement(root);
		}
		else if (current == BEGIN)
		{
			throw std::out_of_range("Out of range");
		}
		else if (current == GetMinElement(root))
		{
			current = BEGIN;
		}
		else
		{
			current = getPrevious(current, root);
		}
		return *this;
	}

	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::cIterator AVLTree<T, T_Height>::cIterator::operator--(int) noexcept(false)
	{
		cIterator copy_iter = *this;
		if (current == END)
		{
			current = GetMaxElement(root);
		}
		else if (current == BEGIN)
		{
			throw std::out_of_range("Out of range");
		}
		else if (current == GetMinElement(root))
		{
			current = BEGIN;
		}
		else
		{
			current = getPrevious(current, root);
		}
		return copy_iter;
	}
}