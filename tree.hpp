#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include "bfs_iterator.hpp"
#include "dfs_iterator.hpp"
#include "pre_order_iterator.hpp"
#include "post_order_iterator.hpp"
#include "in_order_iterator.hpp"
#include "heap_iterator.hpp"
#include <queue>
#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
class tree {
private:
//root of the tree
    std::unique_ptr<Node<T>> root;
    //number of childrens in the tree
    int k;
    

public:
//constractor
    tree(int k = 2) : root(nullptr), k(k) {}
    
//add root
    void add_root(const T& value) 
    {
        root = std::make_unique<Node<T>>(value, k);
    }
    
//add sub node
    void add_sub_node(const T& parent_value, const T& child_value) 
    {
    //check if the tree is empty 
        if (!root) 
        {
            throw std::runtime_error("Error:The Tree is empty");
        }

        std::queue<Node<T>*> my_queu;
        my_queu.push(root.get());

        while (!my_queu.empty()) 
        {
            Node<T>* tem = my_queu.front();
            my_queu.pop();

            if (tem->value == parent_value) {
                for (int i = 0; i < k; ++i) {
                    if (!tem->descendence[i]) 
                    {
                        tem->descendence[i] = std::make_unique<Node<T>>(child_value, k);
                        return;
                    }
                }
                //error the number of children is >k 
                throw std::runtime_error("Not possible .Number of childrens is > k");
            }

            for (auto& child : tem->descendence) {
                if (child) 
                {
                    my_queu.push(child.get());
                }
            }
        }
        
        //error not found the parent 
        throw std::runtime_error("Parent of the node not found");
    }
//get root of the tree
    Node<T>* getRoot() const 
    { 
           return root.get(); 
    }
//begin bfs
    bfs_iterator<T> begin_bfs_scan() 
    {
        return bfs_iterator<T>(root.get());
    }
//end dfs
    bfs_iterator<T> end_bfs_scan() 
    {
        return bfs_iterator<T>(nullptr);
    }
//begin dfs
    dfs_iterator<T> begin_dfs_scan() 
    {
        return dfs_iterator<T>(root.get());
    }
//end dfs
    dfs_iterator<T> end_dfs_scan() 
    {
        return dfs_iterator<T>(nullptr);
    }
//begin pre order
    pre_order_iterator<T> begin_pre_order() 
    {
        return pre_order_iterator<T>(root.get());
    }
//end pre order
    pre_order_iterator<T> end_pre_order() 
    {
        return pre_order_iterator<T>(nullptr);
    }
//begin in order
    in_order_iterator<T> begin_in_order() 
    {
        return in_order_iterator<T>(root, k);
    }
//end in order
    in_order_iterator<T> end_in_order() 
    {
        return in_order_iterator<T>(nullptr, k);
    }
//begin post order
    post_order_iterator<T> begin_post_order() 
    {
        return post_order_iterator<T>(root.get(), k);
    }
//end post order
    post_order_iterator<T> end_post_order() 
    {
        return post_order_iterator<T>(nullptr, k);
    }
//begin heap 
    heap_iterator<T> begin_heap()
    {
        return heap_iterator<T>(root.get(), k);
    }
//end heap
    heap_iterator<T> end_heap() 
    {
        return heap_iterator<T>(nullptr, k);
    }

    ~tree() = default;
};



#endif 
