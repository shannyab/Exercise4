#ifndef HEAP_ITERATOR_HPP
#define HEAP_ITERATOR_HPP
#include "node.hpp"
#include <vector>
#include <algorithm>
#include <iostream>


template <typename T>
class heap_iterator {
private:
//vector for the heap
    std::vector<Node<T>*> vec_heap; 
    //struct compareNodes
    
    struct CompareNodes {
        bool operator()(const Node<T>* a, const Node<T>* b) const 
        {
            return a->value > b->value;
        }
    };
//collect node 
    void collect_nodes(Node<T>* node) {
        if (node) 
        {
            vec_heap.push_back(node);
            for (auto& child : node->descendence) {
                if (child) 
                {
                    collect_nodes(child.get());
                }
            }
        }
    }

public:
//constractor
    heap_iterator(Node<T>* root, int k) {
    //check if the binary is tree
        if (k == 2) {
            if (root) {
                collect_nodes(root);
                std::make_heap(vec_heap.begin(), vec_heap.end(), CompareNodes());
            }
        } 
        //if the tree is not binary not possible 
        else if (k > 2) {
            std::cout << "Not possible .The k is different of 2." << std::endl;
        }
    }


//operator ++  
    heap_iterator& operator++() 
    {
        std::pop_heap(vec_heap.begin(), vec_heap.end(), CompareNodes());
        vec_heap.pop_back();
        return *this;
    }

//operator =  

    heap_iterator& operator=(const heap_iterator& other) 
    {
        if (this != &other) {
            vec_heap = other.vec_heap;
        }
        return *this;
    }

//operator ==
    bool operator==(const heap_iterator& other) const
     {
     //check if equal
        return vec_heap == other.vec_heap;
    }

//operator !=
    bool operator!=(const heap_iterator& other) const 
    {
    //check if different
        return !(*this == other);

    }

//operator *
    T& operator*() const 
    {
    //return the value of the front 
        return vec_heap.front()->value;
    }


//operator ->

    T* operator->() const 
    {
        return &(vec_heap.front()->value);
    }


};

#endif 
