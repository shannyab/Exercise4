#ifndef IN_ORDER_ITERATOR_HPP
#define IN_ORDER_ITERATOR_HPP
#include <stack>
#include <memory>
#include "node.hpp"
//finish 

template <typename T>
class in_order_iterator {
private:
//stack of nodes
    std::stack<Node<T>*> nodes;
    Node<T>* curr;
    int k;

    void push_left(Node<T>* temp) 
    {
        while (temp) 
        {
            nodes.push(temp);
            if (!temp->descendence.empty()) 
            {
                temp = temp->descendence[0].get();
            } 
            else 
            {
                break;
            }
        }
    }

public:

//constractor
    in_order_iterator(const std::unique_ptr<Node<T>>& temp, int k) : curr(nullptr), k(k) {
        if (k == 2) 
        {
            push_left(temp.get());
        } 
        else if (temp) 
        {
            nodes.push(temp.get());
        }
        ++(*this); 
    }

//operator !=
    bool operator!=(const in_order_iterator& other) const 
    {
        return curr != other.curr;
    }

//operator *
    T& operator*() 
    {
        return curr->value;
    }

//operator ++
    in_order_iterator& operator++() 
    {
        if (k == 2) 
        {
            if (curr && curr->descendence.size() > 1) {
                    push_left(curr->descendence[1].get());
            }
            
            if (!nodes.empty()) 
            {
                curr = nodes.top();
                nodes.pop();
            } 
            else 
            {
                curr = nullptr;
            }
        }
         else 
         {
            // General tree DFS traversal for k-ary
            if (!nodes.empty()) {
                Node<T>* temp = nodes.top();
                nodes.pop();
                curr = temp;
                for (auto it = temp->descendence.rbegin(); it != temp->descendence.rend(); ++it) {
                    if (*it) 
                    {
                        nodes.push(it->get());
                    }
                }
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