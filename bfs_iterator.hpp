#ifndef BFS_ITERATOR_HPP
#define BFS_ITERATOR_HPP
#include <queue>
#include "node.hpp"
//finish

template <typename T>
class bfs_iterator {
private:
//queu of nodes
    std::queue<Node<T>*> nodes;
    //current node
    Node<T>* curr;

public:
//constractor
    bfs_iterator(Node<T>* root);

//operator !=
    bool operator!=(const bfs_iterator& other) const;

//operator *
    T& operator*();
    
//operator ++
    bfs_iterator& operator++();
};

template <typename T>
bfs_iterator<T>::bfs_iterator(Node<T>* root) : curr(root) 
{
//check if exist root
    if (root) 
    {
        nodes.push(root);
    }
}

template <typename T>
bool bfs_iterator<T>::operator!=(const bfs_iterator& other) const 
{
//check if differen 
    return curr != other.curr;
}

template <typename T>
T& bfs_iterator<T>::operator*() 
{
//return the value of the current node
    return curr->value;
}

template <typename T>
bfs_iterator<T>& bfs_iterator<T>::operator++() 
{
//check if not empty 
    if (!nodes.empty()) {
        Node<T>* temp = nodes.front();
        nodes.pop();
        for (auto& child : temp->descendence) {
            if (child) 
            {
                nodes.push(child.get());
            }
        }

        if (!nodes.empty()) 
        {
            curr = nodes.front();
        } 
        else 
        {
            curr = nullptr;
        }
    }
    return *this;
}



#endif 
