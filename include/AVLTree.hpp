#pragma once
#include <initializer_list>
#include <stdexcept> 
#include <limits.h>

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
			Node(T data = T(), Node* right = nullptr, Node* left = nullptr) : data(data), right(right), left(left), height(1), size_r(0), size_l(0) {}

			Node* left;
			Node* right;
			T_Height height;
			unsigned short size_r, size_l;

			friend class AVLTree;
		};

		enum class ITER
		{
			cIter, rIter
		};

	private:
		Node* root;
		mutable bool isSuccessfully = true;
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

		// Compare 2 AVLTrees
		void IsEqual(const Node* myRoot, const Node* other) const;

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

		// Get Distance
		int GetDistance(const T& val, Node* LCA, bool side) const;

		// Find LCA(Lowest Common Ancestor)
		Node* LCA_find(const T& elem1, const T& elem2, Node* root) const;

		// R || Insert Element + Balance
		Node* insert_(Node* root, const T& data);

		// R || Erase Element + Balance
		Node* erase_(Node* root, const T& data);

		// R || Find Element
		Node* find_(Node* root, const T& data) const;

		// _Private Methods
	public: // Constructors
		AVLTree() : root(nullptr) {}
		AVLTree(const T& data) : root(new Node(data)) {}
		AVLTree(const std::initializer_list<T>& init_list);

		AVLTree(const AVLTree<T, T_Height>& other);
		AVLTree(AVLTree<T, T_Height>&& other);

		AVLTree<T, T_Height>& operator=(const AVLTree<T, T_Height>& other);
		AVLTree<T, T_Height>& operator=(AVLTree<T, T_Height>&& other) noexcept;
		bool operator==(const AVLTree<T, T_Height>& other) const;
		bool operator!=(const AVLTree<T, T_Height>& other) const;

		virtual ~AVLTree();
	public: // Methods
		bool insert(const T& data);
		bool erase(const T& data);
		const Node* find(const T& data) const&;
		void clear();
		void swap(Tree::AVLTree<T, T_Height>& AvlTree);
		unsigned short size() const;
		unsigned int distance(const T& element1, const T& element2) const;

	public: // cIterator
		class cIterator
		{
		private:
			Node* current;
			Node* root;

		public:
			cIterator(Node* current, Node* root)
				: root(root), current(current) {
			}

			const T& operator*() const;

			cIterator& operator++() noexcept(false);

			cIterator operator++(int) noexcept(false);

			cIterator& operator--() noexcept(false);

			cIterator operator--(int) noexcept(false);

			bool operator==(const cIterator& other) const;

			bool operator!=(const cIterator& other) const;

			T* operator->() const;
		};

		[[nodiscard]] cIterator begin() const;
		[[nodiscard]] const cIterator cbegin() const;
		[[nodiscard]] cIterator end() const;
		[[nodiscard]] const cIterator cend() const;

	public: // rIterator
		class rIterator
		{
		private:
			Node* current;
			Node* root;

		public:
			rIterator(Node* current, Node* root) : current(current), root(root) {}

			const T& operator*() const noexcept(false);

			rIterator& operator++() noexcept(false);

			rIterator operator++(int) noexcept(false);

			rIterator& operator--() noexcept(false);

			rIterator operator--(int) noexcept(false);

			bool operator==(const rIterator& other) const;

			bool operator!=(const rIterator& other) const;

			T* operator->() const;

			cIterator base() const noexcept(false);
		};

		[[nodiscard]] rIterator rbegin() const;
		[[nodiscard]] const rIterator crbegin() const;
		[[nodiscard]] rIterator rend() const;
		[[nodiscard]] const rIterator crend() const;
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

	template<typename T, typename T_Height>
	inline void AVLTree<T, T_Height>::IsEqual(const Node* myRoot, const Node* other) const
	{
		if (!isSuccessfully)
			return;

		if (myRoot != nullptr && other != nullptr)
		{
			if (myRoot->data != other->data)
			{
				isSuccessfully = false;
			}

			IsEqual(myRoot->right, other->right);
			IsEqual(myRoot->left, other->left);
		}
		else if (myRoot || other)
		{
			isSuccessfully = false;
		}
	}

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
		root->size_l = other_root->size_l;
		root->size_r = other_root->size_r;
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
			Node* copy_minroot = minroot;
			root->left = minroot->right;
			delete minroot;
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
						return GetLvlUp(data, root->left->right);
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
					if (GetMinElement(root->right)->data < data)
					{
						return GetLvlDw(data, root->right->left);
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
		root->size_r = (root->right ? root->right->size_r + root->right->size_l + 1 : 0);
		root->size_l = (root->left ? root->left->size_l + root->left->size_r + 1 : 0);
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

	template<typename T, typename T_Height>
	inline int AVLTree<T, T_Height>::GetDistance(const T& val, Node* LCA, bool side) const // base LCA->data != val
	{
		int elements = 0;

		while (LCA && val != LCA->data)
		{
			if ((side == false && val < LCA->data) || (side == true && val > LCA->data))
			{
				elements += (isSuccessfully ? 0 : (side ? LCA->size_l : LCA->size_r)) + 1;
				isSuccessfully = false;
				LCA = (side ? LCA->right : LCA->left);
			}
			else
			{
				isSuccessfully = false;
				LCA = (side ? LCA->left : LCA->right);
			}
		}

		elements = (LCA ? ((side) ? LCA->size_l : LCA->size_r) + elements : INT_MIN);
		return elements;
	}


	// Find LCA(Lowest Common Ancestor)
	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::Node* AVLTree<T, T_Height>::LCA_find(const T& elem1, const T& elem2, Node* root) const
	{
		while (root)
		{
			if (elem1 < root->data && elem2 < root->data)
				root = root->left;
			else if (elem1 > root->data && elem2 > root->data)
				root = root->right;
			else
				return root;
		}
		return nullptr;
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
	inline bool AVLTree<T, T_Height>::operator==(const AVLTree<T, T_Height>& other) const
	{
		isSuccessfully = (size_ == other.size_);
		if (isSuccessfully)
			IsEqual(root, other.root);

		return isSuccessfully;
	}

	template<typename T, typename T_Height>
	inline bool AVLTree<T, T_Height>::operator!=(const AVLTree<T, T_Height>& other) const
	{
		return !(*this == other);
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
	inline const typename AVLTree<T, T_Height>::Node* AVLTree<T, T_Height>::find(const T& data) const&
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
	inline unsigned short AVLTree<T, T_Height>::size() const
	{
		return size_;
	}

	template<typename T, typename T_Height>
	inline unsigned int AVLTree<T, T_Height>::distance(const T& element1, const T& element2) const
	{
		if (element1 < element2)
		{
			Node* LCA = LCA_find(element1, element2, root);
			if (LCA != nullptr)
			{
				isSuccessfully = true;
				int l_dist = (LCA->data == element1 ? 0 : GetDistance(element1, LCA, false));

				isSuccessfully = true;
				int r_dist = (LCA->data == element2 ? 0 : GetDistance(element2, LCA, true));

				return (l_dist < 0 || r_dist < 0) ? 0 : (l_dist + r_dist);
			}
		}
		return 0;
	}

	// _Public Methods

	//
	// cIterator
	//

	template<typename T, typename T_Height>
	inline const T& AVLTree<T, T_Height>::cIterator::operator*() const noexcept(false)
	{
		if (current == END || current == nullptr)
		{
			throw std::out_of_range("Out of range");
		}
		return current->data;
	}

	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::cIterator& AVLTree<T, T_Height>::cIterator::operator++() noexcept(false)
	{
		if (current == END || current == nullptr)
		{
			throw std::out_of_range("Out of range");
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
		if (current == END || current == nullptr)
		{
			throw std::out_of_range("Out of range");
		}
		else if (GetMaxElement(root) == current)
		{
			current = END;
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
		if (current == END || current == nullptr)
		{
			current = GetMaxElement(root);
		}
		else if (current == GetMinElement(root))
		{
			current = nullptr;
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
		if (current == END || current == nullptr)
		{
			current = GetMaxElement(root);
		}
		else if (current == GetMinElement(root))
		{
			current = nullptr;
		}
		else
		{
			current = getPrevious(current, root);
		}
		return copy_iter;
	}

	template<typename T, typename T_Height>
	inline bool AVLTree<T, T_Height>::cIterator::operator==(const cIterator& other) const
	{
		return other.current == current;
	}

	template<typename T, typename T_Height>
	inline bool AVLTree<T, T_Height>::cIterator::operator!=(const cIterator& other) const
	{
		return other.current != current;
	}

	template<typename T, typename T_Height>
	inline T* AVLTree<T, T_Height>::cIterator::operator->() const
	{
		return &current->data;
	}

	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::cIterator AVLTree<T, T_Height>::begin() const
	{
		if (root == nullptr)
		{
			return cIterator(END, nullptr);
		}
		return cIterator(GetMinElement(root), root);
	}

	template<typename T, typename T_Height>
	inline const typename AVLTree<T, T_Height>::cIterator AVLTree<T, T_Height>::cbegin() const
	{
		if (root == nullptr)
		{
			return cIterator(END, nullptr);
		}
		return cIterator(GetMinElement(root), root);
	}

	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::cIterator AVLTree<T, T_Height>::end() const
	{
		return cIterator(END, root);
	}

	template<typename T, typename T_Height>
	inline const typename AVLTree<T, T_Height>::cIterator AVLTree<T, T_Height>::cend() const
	{
		return cIterator(END, root);
	}

	// _cIterator

	// 
	// rIterator
	// 

	template<typename T, typename T_Height>
	inline const T& AVLTree<T, T_Height>::rIterator::operator*() const noexcept(false)
	{
		if (current == BEGIN || current == nullptr)
		{
			throw std::out_of_range("Out of range");
		}
		return current->data;
	}

	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::rIterator& AVLTree<T, T_Height>::rIterator::operator++() noexcept(false)
	{
		if (current == BEGIN || current == nullptr)
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
	inline typename AVLTree<T, T_Height>::rIterator AVLTree<T, T_Height>::rIterator::operator++(int) noexcept(false)
	{
		rIterator copy_iter = *this;

		if (current == BEGIN || current == nullptr)
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

	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::rIterator& AVLTree<T, T_Height>::rIterator::operator--() noexcept(false)
	{
		if (current == BEGIN || current == nullptr)
		{
			current = GetMinElement(root);
		}
		else if (current == GetMaxElement(root))
		{
			current = nullptr;
		}
		else
		{
			current = getNext(current, root);
		}

		return *this;
	}

	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::rIterator AVLTree<T, T_Height>::rIterator::operator--(int) noexcept(false)
	{
		rIterator copy_iter = *this;

		if (current == BEGIN || current == nullptr)
		{
			current = GetMinElement(root);
		}
		else if (current == GetMaxElement(root))
		{
			current = nullptr;
		}
		else
		{
			current = getNext(current, root);
		}

		return copy_iter;
	}

	template<typename T, typename T_Height>
	inline bool AVLTree<T, T_Height>::rIterator::operator==(const rIterator& other) const
	{
		return current == other.current;
	}

	template<typename T, typename T_Height>
	inline bool AVLTree<T, T_Height>::rIterator::operator!=(const rIterator& other) const
	{
		return current != other.current;
	}

	template<typename T, typename T_Height>
	inline T* AVLTree<T, T_Height>::rIterator::operator->() const
	{
		return &current->data;
	}

	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::cIterator AVLTree<T, T_Height>::rIterator::base() const noexcept(false)
	{
		if (current == GetMaxElement(root))
		{
			return cIterator(END, root);
		}

		return ++cIterator(current, root);
	}

	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::rIterator AVLTree<T, T_Height>::rbegin() const
	{
		if (root == nullptr)
		{
			return rIterator(BEGIN, nullptr);
		}

		return rIterator(GetMaxElement(root), root);
	}

	template<typename T, typename T_Height>
	inline const typename AVLTree<T, T_Height>::rIterator AVLTree<T, T_Height>::crbegin() const
	{
		if (root == nullptr)
		{
			return rIterator(BEGIN, nullptr);
		}

		return rIterator(GetMaxElement(root), root);
	}

	template<typename T, typename T_Height>
	inline typename AVLTree<T, T_Height>::rIterator AVLTree<T, T_Height>::rend() const
	{
		return rIterator(BEGIN, root);
	}

	template<typename T, typename T_Height>
	inline const typename AVLTree<T, T_Height>::rIterator AVLTree<T, T_Height>::crend() const
	{
		return rIterator(BEGIN, root);
	}

	// _rIterator
}