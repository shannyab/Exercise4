#ifndef POST_ORDER_ITERATOR_HPP
#define POST_ORDER_ITERATOR_HPP
#include <stack>
#include "node.hpp"


template <typename T>
class post_order_iterator {
private:
//stack of nodes
    std::stack<Node<T>*> nodes;
    //current node
    Node<T>* curr;
    //number of children in the tree
    int k;

    void pushLeftmostPath(Node<T>* node) 
    {
        while (node) 
        {
            nodes.push(node);
            if (!node->descendence.empty()) 
            {
                node = node->descendence[0].get();
            } 
            else 
            {
                break;
            }
        }
    }

public:
//constractor
    post_order_iterator(Node<T>* root, int k) : curr(nullptr), k(k) {
        if (root) {
        //if tree binary 
            if (k == 2) 
            {
                pushLeftmostPath(root);
            } 
            //if tree not binary 
            else 
            {
                nodes.push(root);
            }
        }
        ++(*this);
    }

//operator !=
    bool operator!=(const post_order_iterator& other) const 
    {
    //check if  different
        return curr != other.curr;
    }
    
//operaotr *
    T& operator*() 
    {
    //return the value of the current node
        return curr->value;
    }

//operator ++
    post_order_iterator& operator++() {
    //check if the tree is binary 
        if (k == 2) {
            // Post-order traversal for binary trees
            //check if the stack is not empty 
            if (!nodes.empty()) {
                Node<T>* node = nodes.top();
                nodes.pop();
                if (!nodes.empty()) 
                {
                    Node<T>* parent = nodes.top();
                    if (parent->descendence.size() > 1 && node == parent->descendence[0].get()) 
                    {
                        pushLeftmostPath(parent->descendence[1].get());
                    }
                }
                curr = node;
            } 
            //if empty 
            else 
            {
                curr = nullptr;
            }
        } 
        //if the tree is not binary 
        else 
        {
            // DFS for k-ary trees
            if (!nodes.empty()) {
                Node<T>* node = nodes.top();
                nodes.pop();
                for (auto it = node->descendence.rbegin(); it != node->descendence.rend(); ++it) {
                    if (*it) 
                    {
                        nodes.push(it->get());
                    }
                }
                curr = node;
            } 
            else 
            {
                curr = nullptr;
            }
        }
        return *this;
    }


};

#endif 
