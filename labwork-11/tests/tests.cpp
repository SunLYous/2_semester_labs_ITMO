
#include <gtest/gtest.h>
#include <sstream>
#include <lib/StandardAlgorithm.h>
#include "lib/XrangeClass.h"
#include "lib/ZipClass.h"
#include <vector>
#include <algorithm>
#include <list>
#include <iostream>

TEST(StandardAlgorithm, AllOf) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(algo::all_of(v.begin(), v.end(), [](int i) { return i > 0; }), true);
    EXPECT_EQ(algo::all_of(v.begin(), v.end(), [](int i) { return i < 0; }), false);
}

TEST(StandardAlgorithm, AnyOf) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(algo::any_of(v.begin(), v.end(), [](int i) { return i > 0; }), true);
    EXPECT_EQ(algo::any_of(v.begin(), v.end(), [](int i) { return i < 0; }), false);
}

TEST(StandardAlgorithm, NoneOf) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(algo::none_of(v.begin(), v.end(), [](int i) { return i > 0; }), false);
    EXPECT_EQ(algo::none_of(v.begin(), v.end(), [](int i) { return i < 0; }), true);
}

TEST(StandardAlgorithm, OneOf) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(algo::one_of(v.begin(), v.end(), [](int i) { return i == 3; }), true);
    EXPECT_EQ(algo::one_of(v.begin(), v.end(), [](int i) { return i == 1; }), true);
}

TEST(StandardAlgorithm, IsSorted) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(algo::is_sorted(v.begin(), v.end(), [](int i, int j) { return i < j; }), true);
    EXPECT_EQ(algo::is_sorted(v.begin(), v.end(), [](int i, int j) { return i > j; }), false);
}

TEST(StandardAlgorithm, IsPartitioned) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(algo::is_palindrome(v.begin(), v.end(), [](int i, int j) { return i == j; }), false);
    EXPECT_EQ(algo::is_palindrome(v.begin(), v.end(), [](int i, int j) { return i != j; }), true);
}

TEST(StandardAlgorithm, FindNot) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(*algo::find_not(v.begin(), v.end(), [](int i) { return i % 2 == 0; }), 1);
    EXPECT_EQ(*algo::find_not(v.begin(), v.end(), [](int i) { return i % 2 != 0; }), 2);
}

TEST(StandardAlgorithm, FindBackward) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(*algo::find_backward(v.begin(), v.end(), [](int i) { return i % 2 == 0; }), 4);
    EXPECT_EQ(*algo::find_backward(v.begin(), v.end(), [](int i) { return i % 2 != 0; }), 5);
}

TEST(StandardAlgorithm, IsPalindrome) {
    std::vector<int> v = {1, 2, 3, 2, 1};
    EXPECT_EQ(algo::is_palindrome(v.begin(), v.end(), [](int i, int j) { return i == j; }), true);
    EXPECT_EQ(algo::is_palindrome(v.begin(), v.end(), [](int i, int j) { return i != j; }), false);
}

TEST(StandardAlgorithm, IsPalindrome1) {
    std::vector<int> v = {1, 2, 3, 2, 1};
    EXPECT_EQ(algo::is_palindrome(v.begin(), v.end(), [](int i, int j) { return i == j; }), true);
    EXPECT_EQ(algo::is_palindrome(v.begin(), v.end(), [](int i, int j) { return i != j; }), false);
}

TEST(XrangeClass, Constructor) {
    XrangeClass x(1, 6, 2);
    std::vector<int> v{x.begin(), x.end()};
    std::vector<int> v1 = {1, 3, 5};
    EXPECT_EQ(v, v1);
}

TEST(XrangeClass, Constructor1) {
    XrangeClass x(1, 6);
    std::vector<int> v{x.begin(), x.end()};
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    EXPECT_EQ(v, v1);
}

TEST(XrangeClass, Constructor2) {
    XrangeClass x(6);
    std::vector<int> v{x.begin(), x.end()};
    std::vector<int> v1 = {0, 1, 2, 3, 4, 5};
    EXPECT_EQ(v, v1);
}

TEST(XrangeClass, Constructor3) {
    XrangeClass x(1, 6, -2);
    std::vector<int> v{x.begin(), x.end()};
    std::vector<int> v1 = {};
    EXPECT_EQ(v, v1);
}

TEST(XrangeClass, Constructor4) {
    XrangeClass x(6, 1, -2);
    std::vector<int> v{x.begin(), x.end()};
    std::vector<int> v1 = {6, 4, 2};
    EXPECT_EQ(v, v1);
}

TEST(XrangeClass, Constructor5) {
    XrangeClass x(6, 1);
    std::vector<int> v{x.begin(), x.end()};
    std::vector<int> v1 = {};
    EXPECT_EQ(v, v1);
}

TEST(XrangeClass, Constructor6) {
    XrangeClass x(1, 6, 0);
    std::vector<int> v{x.begin(), x.end()};
    std::vector<int> v1 = {};
    EXPECT_EQ(v, v1);
}

TEST(XrangeClass, Constructor7) {
    XrangeClass x(1, 6, 1);
    std::vector<int> v{x.begin(), x.end()};
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    EXPECT_EQ(v, v1);
}

TEST(XrangeClass, Constructor8) {
    XrangeClass x(1, 6, 6);
    std::vector<int> v{x.begin(), x.end()};
    std::vector<int> v1 = {1};
    EXPECT_EQ(v, v1);
}

TEST(XrangeClass, Constructor9) {
    XrangeClass x(1, 6, 7);
    std::vector<int> v{x.begin(), x.end()};
    std::vector<int> v1 = {1};
    EXPECT_EQ(v, v1);
}

TEST(XrangeClass, Constructor10) {
    XrangeClass x(-10, 6, 7);
    std::vector<int> v{x.begin(), x.end()};
    std::vector<int> v1 = {-10, -3, 4};
    EXPECT_EQ(v, v1);
}

TEST(XrangeClass, Constructor11) {
    XrangeClass x(1.5);
    std::vector<float> v{x.begin(), x.end()};
    std::vector<float> v1 = {0, 1};
    EXPECT_EQ(v, v1);
}

TEST(XrangeClass, Constructor12) {
    XrangeClass x(1.5, 6.5);
    std::vector<float> v{x.begin(), x.end()};
    std::vector<float> v1 = {1.5, 2.5, 3.5, 4.5, 5.5};
    EXPECT_EQ(v, v1);
}

TEST(XrangeClass, Constructor13) {
    XrangeClass x(1.5, 6.5, 2.5);
    std::vector<float> v{x.begin(), x.end()};
    std::vector<float> v1 = {1.5, 4};
    EXPECT_EQ(v, v1);
}

TEST(XrangeClass, Constructor14) {
    XrangeClass x(1.5, 6.5, 0.5);
    std::vector<float> v{x.begin(), x.end()};
    std::vector<float> v1 = {1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6};
    EXPECT_EQ(v, v1);
}

/*TEST(XrangeClass, Constructor15) {
    XrangeClass x(1.5, 6.5, 0);
    std::vector<float> v{x.begin(), x.end()};
    std::vector<float> v1 = {};
    EXPECT_EQ(v, v1);
}*/


TEST(XrangeClass, Constructor16) {
    XrangeClass x(1.5, 6.5, -0.5);
    std::vector<float> v{x.begin(), x.end()};
    std::vector<float> v1 = {};
    EXPECT_EQ(v, v1);
}

TEST(XrangeClass, Constructor17) {
    XrangeClass x(6.5, 1.5, -0.5);
    std::vector<float> v{x.begin(), x.end()};
    std::vector<float> v1 = {6.5, 6, 5.5, 5, 4.5, 4, 3.5, 3, 2.5, 2};
    EXPECT_EQ(v, v1);
}

TEST(XrangeClass, Constructor18) {
    XrangeClass x(6.5, 1.5, 0.5);
    std::vector<float> v{x.begin(), x.end()};
    std::vector<float> v1 = {};
    EXPECT_EQ(v, v1);
}

/*TEST(XrangeClass, Constructor19) {
    XrangeClass x(6.5, 1.5, 0);
    std::vector<float> v{x.begin(), x.end()};
    std::vector<float> v1 = {};
    EXPECT_EQ(v, v1);
}*/

TEST(XrangeClass, Constructor20) {
    XrangeClass x(6.5, 1.5, 0.5);
    std::vector<float> v{x.begin(), x.end()};
    std::vector<float> v1 = {};
    EXPECT_EQ(v, v1);
}

TEST(XrangeClass, Constructor21) {
    XrangeClass x(1, 6, 0.5);
    std::vector<float> v{x.begin(), x.end()};
    std::vector<float> v1 = {};
    EXPECT_EQ(v, v1);
}

/*TEST(XrangeClass, Constructor21) {
    XrangeClass x(1, 6.5, 5);
    std::vector<float> v{x.begin(), x.end()};
    std::vector<float> v1 = {};
    EXPECT_EQ(v, v1);
}*/

TEST(ZipClass, Constructor1) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};
    ZipClass z(v1, v2);
    std::vector<std::pair<int, int>> v(z.begin(), z.end());
    std::vector<std::pair<int, int>> v3 = {{1, 4}, {2, 5}, {3, 6}};
    EXPECT_EQ(v, v3);
}

TEST(ZipClass, Constructor2) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6, 7};
    ZipClass z(v1, v2);
    std::vector<std::pair<int, int>> v(z.begin(), z.end());
    std::vector<std::pair<int, int>> v3 = {{1, 4}, {2, 5}, {3, 6}};
    EXPECT_EQ(v, v3);
}

TEST(ZipClass, Constructor3) {
    std::vector<int> v1 = {1, 2, 3, 4};
    std::vector<int> v2 = {4, 5, 6};
    ZipClass z(v1, v2);
    std::vector<std::pair<int, int>> v(z.begin(), z.end());
    std::vector<std::pair<int, int>> v3 = {{1, 4}, {2, 5}, {3, 6}};
    EXPECT_EQ(v, v3);
}

TEST(ZipClass, Constructor4) {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<char> v2 = {'a', 'b', 'c'};
    ZipClass z(v1, v2);
    std::vector<std::pair<int, char>> v(z.begin(), z.end());
    std::vector<std::pair<int, char>> v3 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
    EXPECT_EQ(v, v3);
}






