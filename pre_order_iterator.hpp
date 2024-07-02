#ifndef PRE_ORDER_ITERATOR_HPP
#define PRE_ORDER_ITERATOR_HPP
#include <stack>
#include "node.hpp"


template <typename T>
class pre_order_iterator {
private:
//stack of nodes
    std::stack<Node<T>*> nodes;
    //curent node 
    Node<T>* curr;

public:
//constractor
    pre_order_iterator(Node<T>* root);
    //operator !=
    bool operator!=(const pre_order_iterator& other) const;
    //operator *
    T& operator*();
    //operator++
    pre_order_iterator& operator++();
};

template <typename T>
pre_order_iterator<T>::pre_order_iterator(Node<T>* root) : curr(root) 
{
//check if exists root
    if (root) 
    {
        nodes.push(root);
    }
}


template <typename T>
bool pre_order_iterator<T>::operator!=(const pre_order_iterator& other) const 
{
//check if different
    return curr != other.curr;
}

template <typename T>
T& pre_order_iterator<T>::operator*()
{
//return the value of the current node
    return curr->value;
}



template <typename T>
pre_order_iterator<T>& pre_order_iterator<T>::operator++() {
//check if the stack is not empty 
    if (!nodes.empty()) {
        Node<T>* temp = nodes.top();
        nodes.pop();
        for (auto it = temp->descendence.rbegin(); it != temp->descendence.rend(); ++it) 
        {
            if (*it) 
            {
                nodes.push(it->get());
            }
        }
//update the current node to be the top of the stack 
        if (!nodes.empty()) 
        {
            curr = nodes.top();
        } 
        else 
        {
            curr = nullptr;
        }
    }
    return *this;
}



#endif 
