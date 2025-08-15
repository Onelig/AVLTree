include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

# base test
add_executable(baseTest base_test.cpp)
target_link_libraries(baseTest PRIVATE GTest::gtest_main AVLTree)

add_test(BaseTest baseTest)

# test std::set<int> + AVLTree
add_executable(setTest set_int_test.cpp)
target_link_libraries(setTest PRIVATE GTest::gtest_main AVLTree)

add_test(SetTest setTest)

# test std::set<std::pair<dobule, int>> + AVLTree
add_executable(pairTest set_pair_test.cpp)
target_link_libraries(pairTest PRIVATE GTest::gtest_main AVLTree)

add_test(PairTest pairTest)