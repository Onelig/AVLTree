# 🧪 Google Test Cases for AVLTree

This branch contains unit tests for the **AVLTree** implementation, written using the **Google Test** framework. These tests ensure that all the core functionalities of the tree are working as expected, with a focus on correctness, performance, and balance.

## 🚀 What’s Covered

- 🔹 **Insertion and Deletion**: Verifying that elements are inserted and removed correctly, ensuring the tree remains balanced after each operation.
- 🔹 **Searching**: Ensuring that the search operation returns the correct node for any given element.
- 🔹 **Distance Calculation**: Testing that the `distance` method works correctly and is faster than `std::set`.
- 🔹 **Iterator Functionality**: Validating that the iterators properly traverse through the tree’s elements.
- 🔹 **Tree Balance**: Ensuring the tree is balanced after every insertion and deletion operation.

## 📦 How to Run Tests with Google Test

1. Clone the repository (if you haven't already):  
  ```sh
   git clone https://github.com/Onelig/AVLTree.git
   cd AVLTree
  ```
2. Change branch:
  ```sh
   git checkout main_test
   git submodule update --init --recursive
  ```
3. Build and run the tests using your preferred build system:
  ```sh
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ctest -C Debug
  ```
## 🎉 Acknowledgments and Support
If you like this project, feel free to give it a star! ⭐ Always happy to hear your feedback and suggestions. If you have any questions or ideas for improvement — feel free to create issues or pull requests. The tree will keep growing and evolving! 🚀

## License
Password Generator is licensed under the MIT License, see LICENSE for more information.


 
# 🧪 Тесты Google для AVLTree
Этот раздел содержит юнит-тесты для реализации AVLTree, написанные с использованием фреймворка Google Test. Эти тесты обеспечивают корректную работу всех основных функций дерева с акцентом на правильность, производительность и сбалансированность.

## 🚀 Что покрыто тестами
- 🔹 **Вставка и удаление**: Проверка корректности вставки и удаления элементов, с гарантией, что дерево останется сбалансированным после каждой операции.
- 🔹 **Поиск**: Проверка правильности работы операции поиска, которая должна возвращать правильный узел для любого заданного элемента.
- 🔹 **Вычисление расстояния**: Тестирование метода `distance`, который должен работать корректно и быть быстрее, чем `std::set`.
- 🔹 **Работа с итераторами**: Проверка правильности работы итераторов, которые должны корректно обходить элементы дерева.
- 🔹 **Балансировка дерева**: Проверка, что дерево сбалансировано после каждой операции вставки и удаления.
## 📦 Как запустить тесты с Google Test
1. Клонируйте репозиторий (если еще не сделали это):
  ```sh
   git clone https://github.com/Onelig/AVLTree.git
   cd AVLTree
   ```
2. Переключитесь на нужную ветку:
  ```sh
   git checkout main_test
   git submodule update --init --recursive
  ```
3. Постройте и запустите тесты, используя вашу предпочитаемую систему сборки:
  ```sh
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ctest -C Debug
  ```

## 🎉 Благодарности и поддержка
Если тебе понравился этот проект, ставь звезды! ⭐ Всегда рад фидбекам и предложениям. Если возникнут вопросы или идеи по улучшению - создавайте issues или pull request. Дерево будет расти и развиваеться! 🚀

## Лицензия
Проект распространяется под лицензией MIT. Подробнее см. LICENSE.
