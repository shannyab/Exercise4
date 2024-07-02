#ifndef DFS_ITERATOR_HPP
#define DFS_ITERATOR_HPP
#include <stack>
#include "node.hpp"


template <typename T>
class dfs_iterator {
private:
//stack of nodes
    std::stack<Node<T>*> nodes;
    //curent node
    Node<T>* curr;

public:

//constractor
    dfs_iterator(Node<T>* root);

//operator !=
     bool operator!=(const dfs_iterator& other) const;

//operator *
    T& operator*();

//operator++
    dfs_iterator& operator++();   
    
};

template <typename T>
dfs_iterator<T>::dfs_iterator(Node<T>* root) : curr(root) 
{
//check if exist root
    if (root) 
    {
        nodes.push(root);
    }
}

template <typename T>
bool dfs_iterator<T>::operator!=(const dfs_iterator& other) const 
{
//check if differen
    return curr != other.curr;
}


template <typename T>
T& dfs_iterator<T>::operator*() 
{
//return the value of the current node
    return curr->value;
}

template <typename T>
dfs_iterator<T>& dfs_iterator<T>::operator++() 
{
//check if not empty 
    if (!nodes.empty()) 
    {
        Node<T>* temp = nodes.top();
        nodes.pop();
        for (auto it = temp->descendence.rbegin(); it != temp->descendence.rend(); ++it) {
            if (*it) 
            {
                nodes.push(it->get());
            }
        }

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
