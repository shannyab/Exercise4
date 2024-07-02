#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tree.hpp"
#include "complex.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


TEST_CASE("Tree binary with integer") {
    tree<int> check_tree(2);
    check_tree.add_root(1);
    CHECK(check_tree.getRoot()->value == 1);
    check_tree.add_sub_node(1, 2);
    check_tree.add_sub_node(1, 3);
    Node<int>* root = check_tree.getRoot();
    CHECK(root->descendence[0]->value == 2);
    CHECK(root->descendence[1]->value == 3);
}


TEST_CASE("Tree with double") {
    tree<double> check_tree(3);
    check_tree.add_root(1.1);
    check_tree.add_sub_node(1.1, 2.2);
    check_tree.add_sub_node(1.1, 3.3);
    Node<double>* root = check_tree.getRoot();
    CHECK(check_tree.getRoot()->value == 1.1);
    CHECK(root->descendence[0]->value == 2.2);
    CHECK(root->descendence[1]->value == 3.3);
}


TEST_CASE("Tree with complex") {
    tree<Complex> check_tree(3);
    check_tree.add_root(Complex(1, 1));
    check_tree.add_sub_node(Complex(1, 1), Complex(2, 2));
    check_tree.add_sub_node(Complex(1, 1), Complex(3, 3));
    Node<Complex>* root = check_tree.getRoot();
    CHECK(check_tree.getRoot()->value == Complex(1, 1));
    CHECK(root->descendence[0]->value == Complex(2, 2));
    CHECK(root->descendence[1]->value == Complex(3, 3));
}

TEST_CASE("Tree with integer with 3-children") {
    tree<int> check_tree(3);
    check_tree.add_root(1);
    CHECK(check_tree.getRoot()->value == 1);
    check_tree.add_sub_node(1, 2);
    check_tree.add_sub_node(1, 3);
    check_tree.add_sub_node(1, 4);
    Node<int>* root = check_tree.getRoot();
    CHECK(root->descendence[0]->value == 2);
    CHECK(root->descendence[1]->value == 3);
    CHECK(root->descendence[2]->value == 4);
}


TEST_CASE("Tree with more k children: error") {
    tree<int> check_tree(2);
    check_tree.add_root(1);
    check_tree.add_sub_node(1, 2);
    check_tree.add_sub_node(1, 3);
    CHECK_THROWS_AS(check_tree.add_sub_node(1, 4), std::runtime_error); 
}

TEST_CASE("bfs_iterator for int") {
    tree<int> check_tree(3);
    check_tree.add_root(1);
    check_tree.add_sub_node(1, 2);
    check_tree.add_sub_node(1, 3);
    check_tree.add_sub_node(1, 4);
    check_tree.add_sub_node(2, 5);
    check_tree.add_sub_node(2, 6);
     check_tree.add_sub_node(2, 7);


    std::vector<int> vector_result = {1, 2, 3, 4, 5, 6,7};
    int i = 0;
    for (auto it = check_tree.begin_bfs_scan(); it != check_tree.end_bfs_scan(); ++it) {
        CHECK(*it == vector_result[i]);
        ++i;
    }
}


TEST_CASE("bfs_iterator for double") {
    tree<double> check_tree(3);
    check_tree.add_root(1.1);
    check_tree.add_sub_node(1.1, 2.2);
    check_tree.add_sub_node(1.1, 3.3);
    check_tree.add_sub_node(1.1, 4.4);
    check_tree.add_sub_node(2.2, 5.5);
    std::vector<double> vector_result = {1.1, 2.2, 3.3, 4.4, 5.5};
    int i = 0;
    for (auto it = check_tree.begin_bfs_scan(); it != check_tree.end_bfs_scan(); ++it) {
        CHECK(*it == vector_result[i]);
        ++i;
    }
}

TEST_CASE("bfs_iterator for Complex") {
    tree<Complex> check_tree(3);
    check_tree.add_root(Complex(1, 1));
    check_tree.add_sub_node(Complex(1, 1), Complex(2, 2));
    check_tree.add_sub_node(Complex(1, 1), Complex(3, 3));
    check_tree.add_sub_node(Complex(1, 1), Complex(4, 4));
    check_tree.add_sub_node(Complex(2, 2), Complex(5, 5));
    check_tree.add_sub_node(Complex(3, 3), Complex(6, 6));
    check_tree.add_sub_node(Complex(3, 3), Complex(7, 7));
    check_tree.add_sub_node(Complex(3, 3), Complex(8, 8));
    
    std::vector<Complex> vector_result = {Complex(1, 1), Complex(2, 2), Complex(3, 3), Complex(4, 4), Complex(5, 5), Complex(6, 6),Complex(7, 7),Complex(8, 8)};
    int i = 0;
    for (auto it = check_tree.begin_bfs_scan(); it != check_tree.end_bfs_scan(); ++it) {
        CHECK(*it == vector_result[i]);
        ++i;
    }
}


TEST_CASE("dfs_iterator for int") {
    tree<int> check_tree(3);
    check_tree.add_root(1);
    check_tree.add_sub_node(1, 2);
    check_tree.add_sub_node(1, 3);
    check_tree.add_sub_node(1, 4);
    check_tree.add_sub_node(2, 5);
    check_tree.add_sub_node(2, 6);
    check_tree.add_sub_node(2, 7);
    check_tree.add_sub_node(3, 8);
    check_tree.add_sub_node(3, 9);
    check_tree.add_sub_node(4, 10);

    std::vector<int> dfs_order = {1, 2, 5, 6,7, 3,8,9 ,4,10};
    int i = 0;
    for (auto it = check_tree.begin_dfs_scan(); it != check_tree.end_dfs_scan(); ++it) {
        CHECK(*it == dfs_order[i]);
        ++i;
    }
}

TEST_CASE("dfs_iterator for double") {
    tree<double> check_tree(3);
    check_tree.add_root(1.1);
    check_tree.add_sub_node(1.1, 2.2);
    check_tree.add_sub_node(1.1, 3.3);
    check_tree.add_sub_node(1.1, 4.4);
    check_tree.add_sub_node(2.2, 5.5);
    check_tree.add_sub_node(2.2, 6.6);
     check_tree.add_sub_node(2.2, 7.7);
    check_tree.add_sub_node(3.3, 8.8);
    check_tree.add_sub_node(3.3, 9.9);
    check_tree.add_sub_node(4.4, 10.10);

    std::vector<double> dfs_order = {1.1, 2.2, 5.5, 6.6,7.7, 3.3, 8.8,9.9,4.4,10.10};
    int i = 0;
    for (auto it = check_tree.begin_dfs_scan(); it != check_tree.end_dfs_scan(); ++it) {
        CHECK(*it == dfs_order[i]);
        ++i;
    }
}

TEST_CASE("dfs_iterator for Complex") {
    tree<Complex> check_tree(3);
    check_tree.add_root(Complex(1, 1));
    check_tree.add_sub_node(Complex(1, 1), Complex(2, 2));
    check_tree.add_sub_node(Complex(1, 1), Complex(3, 3));
    check_tree.add_sub_node(Complex(1, 1), Complex(4, 4));
    check_tree.add_sub_node(Complex(2, 2), Complex(5, 5));
    check_tree.add_sub_node(Complex(2, 2), Complex(6, 6));
    check_tree.add_sub_node(Complex(3, 3), Complex(7, 7));

    std::vector<Complex> dfs_order = {Complex(1, 1), Complex(2, 2), Complex(5, 5), Complex(6, 6), Complex(3, 3),Complex(7, 7), Complex(4, 4)};
    int i = 0;
    for (auto it = check_tree.begin_dfs_scan(); it != check_tree.end_dfs_scan(); ++it) {
        CHECK(*it == dfs_order[i]);
        ++i;
    }
}



TEST_CASE("pre_order_iterator for int") {
    tree<int> check_tree(3);
    check_tree.add_root(1);
    check_tree.add_sub_node(1, 2);
    check_tree.add_sub_node(1, 3);
    check_tree.add_sub_node(1, 4);
    check_tree.add_sub_node(2, 5);
    check_tree.add_sub_node(2, 6);
    check_tree.add_sub_node(3, 7);
    check_tree.add_sub_node(3, 8);

    std::vector<int> pre_order = {1, 2, 5, 6, 3, 7,8,4};
    int i = 0;
    for (auto it = check_tree.begin_pre_order(); it != check_tree.end_pre_order(); ++it) {
        CHECK(*it == pre_order[i]);
        ++i;
    }
}

TEST_CASE("pre_order for double") {
    tree<double> check_tree(3);
    check_tree.add_root(1.1);
    check_tree.add_sub_node(1.1, 2.2);
    check_tree.add_sub_node(1.1, 3.3);
    check_tree.add_sub_node(1.1, 4.4);
    check_tree.add_sub_node(2.2, 5.5);
    check_tree.add_sub_node(2.2, 6.6);
    check_tree.add_sub_node(3.3, 7.7);
    check_tree.add_sub_node(3.3, 8.8);

    std::vector<double> pre_order = {1.1, 2.2, 5.5, 6.6, 3.3, 7.7,8.8,4.4};
    int i = 0;
    for (auto it = check_tree.begin_pre_order(); it != check_tree.end_pre_order(); ++it) {
        CHECK(*it == pre_order[i]);
        ++i;
    }
}



TEST_CASE("pre_order for Complex") {
    tree<Complex> check_tree(3);
    check_tree.add_root(Complex(1, 1));
    check_tree.add_sub_node(Complex(1, 1), Complex(2, 2));
    check_tree.add_sub_node(Complex(1, 1), Complex(3, 3));
    check_tree.add_sub_node(Complex(1, 1), Complex(4, 4));
    check_tree.add_sub_node(Complex(2, 2), Complex(5, 5));
    check_tree.add_sub_node(Complex(2, 2), Complex(6, 6));
    check_tree.add_sub_node(Complex(3, 3), Complex(7, 7));
    check_tree.add_sub_node(Complex(3, 3), Complex(8, 8));

    std::vector<Complex> pre_order = {Complex(1, 1), Complex(2, 2), Complex(5, 5), Complex(6, 6), Complex(3, 3),Complex(7, 7) ,Complex(8, 8),Complex(4, 4)};
    int i = 0;
    for (auto it = check_tree.begin_pre_order(); it != check_tree.end_pre_order(); ++it) {
        CHECK(*it == pre_order[i]);
        ++i;
    }
}

TEST_CASE("in_order for int") {
    tree<int> check_tree(2);
    check_tree.add_root(1);
    check_tree.add_sub_node(1, 2);
    check_tree.add_sub_node(1, 3);
    check_tree.add_sub_node(2, 4);
    check_tree.add_sub_node(2, 5);

    std::vector<int> in_order = {4, 2, 5, 1, 3};
    int i = 0;
    for (auto it = check_tree.begin_in_order(); it != check_tree.end_in_order(); ++it) {
        CHECK(*it == in_order[i]);
        ++i;
    }
}

TEST_CASE("heap for int") {
    tree<int> check_tree(3);
    check_tree.add_root(5);
    check_tree.add_sub_node(5, 3);
    check_tree.add_sub_node(5, 8);
    check_tree.add_sub_node(5, 7);
    check_tree.add_sub_node(3, 1);
    check_tree.add_sub_node(3, 2);

    std::vector<int> heap_order = {1, 2, 3, 5, 7, 8};
    int i = 0;
    for (auto it = check_tree.begin_heap(); it != check_tree.end_heap(); ++it) {
        CHECK(*it == heap_order[i]);
        ++i;
    }
}


TEST_CASE("post_order_iterator for int") {
    tree<int> check_tree(2);
    check_tree.add_root(1);
    check_tree.add_sub_node(1, 2); 
    check_tree.add_sub_node(1, 3);
    check_tree.add_sub_node(2, 4); 
    check_tree.add_sub_node(2, 5); 
    check_tree.add_sub_node(3, 6);
    check_tree.add_sub_node(3, 7); 

    std::vector<int> post_order = {4, 5, 2, 6, 7, 3, 1};
    int i = 0;
    for (auto it = check_tree.begin_post_order(); it != check_tree.end_post_order(); ++it) {
        CHECK(*it == post_order[i]);
        ++i;
    }
}

TEST_CASE("post_order_iterator for double") {
    tree<double> check_tree(2);
    check_tree.add_root(1.1);
    check_tree.add_sub_node(1.1, 2.2); 
    check_tree.add_sub_node(1.1, 3.3); 
    check_tree.add_sub_node(2.2, 4.4); 
    check_tree.add_sub_node(2.2, 5.5); 
    check_tree.add_sub_node(3.3, 6.6);
    check_tree.add_sub_node(3.3, 7.7);

    std::vector<double> post_order = {4.4, 5.5, 2.2, 6.6, 7.7, 3.3, 1.1};
    int i = 0;
    for (auto it = check_tree.begin_post_order(); it != check_tree.end_post_order(); ++it) {
        CHECK(*it == post_order[i]);
        ++i;
    }
}


TEST_CASE("post_order_iterator for Complex") {
    tree<Complex> check_tree(2);
    check_tree.add_root(Complex(1, 1));
    check_tree.add_sub_node(Complex(1, 1), Complex(2, 2)); 
    check_tree.add_sub_node(Complex(1, 1), Complex(3, 3)); 
    check_tree.add_sub_node(Complex(2, 2), Complex(4, 4));
    check_tree.add_sub_node(Complex(2, 2), Complex(5, 5)); 
    check_tree.add_sub_node(Complex(3, 3), Complex(6, 6)); 
    check_tree.add_sub_node(Complex(3, 3), Complex(7, 7)); 

    std::vector<Complex> post_order = {Complex(4, 4), Complex(5, 5), Complex(2, 2), Complex(6, 6), Complex(7, 7), Complex(3, 3), Complex(1, 1)};
    int i = 0;
    for (auto it = check_tree.begin_post_order(); it != check_tree.end_post_order(); ++it) {
        CHECK(*it == post_order[i]);
        ++i;
    }
}







