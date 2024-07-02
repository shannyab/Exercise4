#ifndef NODE_HPP
#define NODE_HPP
#include <vector>
#include <memory>

//finish

template <typename T>
class Node {
public:
//the value of the node
     T value;
    //the vector store the childrens of the node
    std::vector<std::unique_ptr<Node<T>>> descendence;
    //constractor 
    //the constractor receive two parameters:
    //-the value of the node
    //- the value of the k(the numbe of childrens permitted )
    Node(T val, int k);
};

template <typename T>
Node<T>::Node(T val, int k) : value(val), descendence(k) {}

#endif 
