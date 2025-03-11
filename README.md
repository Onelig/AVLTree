# 🌲 AVLTree — Self-Balancing AVL Tree in C++  

**AVLTree** is an implementation of a self-balancing binary search tree (AVL) that provides efficient data storage and fast access. The implementation includes support for standard insert, delete, and search operations, as well as iterators and a unique `distance` method, which works faster than the equivalent functionality in `std::set`.  

## 🚀 Features  

- 🔹 **Fast insertion and deletion**: `bool insert(const T& data)`, `bool erase(const T& data)`  
- 🔹 **Element search**: `const Node* find(const T& data) const&`  
- 🔹 **Tree clearing**: `void clear()`  
- 🔹 **Tree swapping**: `void swap(Tree::AVLTree<T, T_Height>& AvlTree)`  
- 🔹 **Get tree size**: `unsigned short size() const`  
- 🔹 **Fast distance calculation between elements**: `unsigned int distance(const T& element1, const T& element2) const` (faster than `std::set`)  
- 🔹 **Iterator support** for easy traversal of tree elements  

## 🧪 Testing  

The `tests` branch contains unit tests that check the correctness of the tree’s functionality.  

## 📦 Installation and Usage  

1. Clone the repository:  
   ```sh
   git clone https://github.com/Onelig/AVLTree.git
   cd AVLTree
   ```
2. Include the header file AVLTree.hpp in your project
   ```sh
   #include "AVLTree.hpp"
   ```

## 🎉 Acknowledgments and Support
If you like this project, feel free to give it a star! ⭐ Always happy to hear your feedback and suggestions. If you have any questions or ideas for improvement — feel free to create issues or pull requests. The tree will keep growing and evolving! 🚀

## License
Password Generator is licensed under the MIT License, see [LICENSE](https://github.com/Onelig/AVLTree/blob/main/LICENSE) for more information.


# 🌲 AVLTree — Самобалансирующееся AVL-дерево на C++  

**AVLTree** — это реализация сбалансированного двоичного дерева поиска (AVL), обеспечивающего эффективное хранение и быстрый доступ к данным. Реализация включает поддержку стандартных операций вставки, удаления и поиска, а также итераторов и уникального метода `distance`, работающего быстрее, чем аналогичный функционал в `std::set`.  

## 🚀 Возможности  

- 🔹 **Быстрая вставка и удаление**: `bool insert(const T& data)`, `bool erase(const T& data)`  
- 🔹 **Поиск элемента**: `const Node* find(const T& data) const&`  
- 🔹 **Очистка дерева**: `void clear()`  
- 🔹 **Обмен деревьями**: `void swap(Tree::AVLTree<T, T_Height>& AvlTree)`  
- 🔹 **Получение размера**: `unsigned short size() const`  
- 🔹 **Быстрое вычисление расстояния между элементами**: `unsigned int distance(const T& element1, const T& element2) const` (быстрее, чем `std::set`)  
- 🔹 **Поддержка итераторов** для удобной работы с элементами дерева  

## 🧪 Тестирование  

Ветка `tests` содержит модульные тесты, проверяющие корректность работы дерева.  

## 📦 Установка и использование  

1. Клонируй репозиторий:  
   ```sh
   git clone https://github.com/Onelig/AVLTree.git
   cd AVLTree
   ```
2. Подключи заголовочный файл AVLTree.hpp в своём проекте:
   ```sh
   #include "AVLTree.hpp"
   ```

## 🎉 Благодарности и поддержка
Если тебе понравился этот проект, ставь звезды! ⭐ Всегда рад фидбекам и предложениям. Если возникнут вопросы или идеи по улучшению - создавайте issues или pull request. Дерево будет расти и развиваеться! 🚀

## Лицензия
Проект распространяется под лицензией **MIT**. Подробнее см. [LICENSE](https://github.com/Onelig/AVLTree/blob/main/LICENSE).
