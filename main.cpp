#include "tree.hpp"
#include "complex.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath> 
#include <sstream> 

using namespace std;

template <typename T>
int depth_tree(Node<T>* node) 
{
    if (!node) return 0;
    int ans = 0;
    for (auto& temp : node->descendence) {
        ans = max(ans, depth_tree(temp.get()));
    }
    return ans + 1;
}

template <typename T>
void draw_tree(sf::RenderWindow &window, Node<T>* node, sf::Vector2f position, float space_horizontal, float space_verticale) 
{
    //check if the root exists
    if (!node) return;
    //we drwa the circle
    sf::CircleShape c(30);
     //update position for the circle
    c.setPosition(position.x - c.getRadius(), position.y - c.getRadius()); 
    //update color for the circle
    c.setFillColor(sf::Color::Yellow); 
    //draw the circle
    window.draw(c);
    //load tthe font
    sf::Font f;
    if (!f.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) 
    {
        cerr << "Error in the load of font" << endl;
        return;
    }

    sf::Text value_of_node;
    value_of_node.setFont(f);
    std::ostringstream s;
    s << node->value;
    //update the text to be the value of the node
    value_of_node.setString(s.str());
    //update the size of the text 
    value_of_node.setCharacterSize(15); 
    //update the color to write the value of the node
    value_of_node.setFillColor(sf::Color::Red); 
    //update the position of the text 
    value_of_node.setPosition(position);
    //draw the value ofthe node
    window.draw(value_of_node);
    //check the number childrens of the node
    int descendence = node->descendence.size();
    float t= -80.0f - (descendence - 1) * 20.0f; 
    //we pas on his all childrens
    for (int i = 0; i < descendence ; ++i) {
        auto& temp = node->descendence[i];
        if (temp) { 
            float t1= (t + i * 30.0f )* M_PI / 180.0f;
            sf::Vector2f new_position = position + sf::Vector2f(cos(t1) * space_horizontal, space_verticale);
            
            //line for the two childrens
            //position of the left children and the children right 
            
            sf::Vertex line[] = {
                sf::Vertex(position + sf::Vector2f(0, 30)),
                sf::Vertex(new_position + sf::Vector2f(0, -30))
            };
            //update color of the line
            line->color = sf::Color::Black; 
            //draw the line for the two childrens (left and right)
            window.draw(line, 2, sf::Lines);
            //continue by recursively 
            draw_tree(window, temp.get(), new_position, space_horizontal / 1.9f, space_verticale * 1.0f); 
        }
    }
}


template <typename T>
void visualize_tree(sf::RenderWindow& window, tree<T>& tree) 
{
    Node<T>* root = tree.getRoot();
    int depth = depth_tree(root);
    sf::Vector2f emplacement_root(window.getSize().x / 2, 30);
    draw_tree(window, root, emplacement_root,  window.getSize().x / (pow(2, depth - 1) + 1) * 2.5, window.getSize().y / (depth + 1) * 1.5);
}

int main() {
    // Create a binary tree with integers
    tree<int> tree1(2);
    //create the children of the tree
    tree1.add_root(1);
    tree1.add_sub_node(1, 2); 
    tree1.add_sub_node(1, 3); 
    tree1.add_sub_node(2, 4); 
    tree1.add_sub_node(2, 5); 
    tree1.add_sub_node(3, 6); 
    tree1.add_sub_node(3, 7); 

    cout << "Pre-order for binary tree with int: ";
    for (auto it = tree1.begin_pre_order(); it != tree1.end_pre_order(); ++it) 
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-order for binary tree with int: ";
    for (auto it = tree1.begin_post_order(); it != tree1.end_post_order(); ++it)
     {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-order for binary tree with int: ";
    for (auto it = tree1.begin_in_order(); it != tree1.end_in_order(); ++it)
     {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Bfs for binary tree with int: ";
    for (auto it = tree1.begin_bfs_scan(); it != tree1.end_bfs_scan(); ++it) 
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Dfs for binary tree with int: ";
    for (auto it = tree1.begin_dfs_scan(); it != tree1.end_dfs_scan(); ++it) 
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Heap for binary tree with int: ";
    for (auto it = tree1.begin_heap(); it != tree1.end_heap(); ++it) 
    {
        cout << *it << " ";
    }
    cout << endl;


    // Create a binary tree with Complex numbers
    tree<Complex> tree2(2);
//create the children of the tree
    tree2.add_root(Complex(1, 1));
    tree2.add_sub_node(Complex(1, 1), Complex(2, 2)); 
    tree2.add_sub_node(Complex(1, 1), Complex(3, 3)); 
    tree2.add_sub_node(Complex(2, 2), Complex(4, 4)); 
    tree2.add_sub_node(Complex(2, 2), Complex(5, 5)); 
    tree2.add_sub_node(Complex(3, 3), Complex(6, 6)); 
    tree2.add_sub_node(Complex(3, 3), Complex(7, 7)); 

    cout << "Pre-order for binary tree with complex number: ";
    for (auto it = tree2.begin_pre_order(); it != tree2.end_pre_order(); ++it) 
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-order for binary tree with complex number : ";
    for (auto it = tree2.begin_post_order(); it != tree2.end_post_order(); ++it) 
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-order for binary tree with complex number: ";
    for (auto it = tree2.begin_in_order(); it != tree2.end_in_order(); ++it) 
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Bfs for binary tree with complex number: ";
    for (auto it = tree2.begin_bfs_scan(); it != tree2.end_bfs_scan(); ++it)
     {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Dfs for binary tree with complex number: ";
    for (auto it = tree2.begin_dfs_scan(); it != tree2.end_dfs_scan(); ++it) 
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Heap for binary tree with complex number: ";
    for (auto it = tree2.begin_heap(); it != tree2.end_heap(); ++it) 
    {
        cout << *it << " ";
    }
    cout << endl;

    // Create a k-3 tree with integers
    tree<int> tree3(3);
    //create the children of the treev
    tree3.add_root(1);
    tree3.add_sub_node(1, 2);
    tree3.add_sub_node(1, 3);
    tree3.add_sub_node(1, 4);
    tree3.add_sub_node(2, 5);
    tree3.add_sub_node(2, 6);
    tree3.add_sub_node(3, 7);
    tree3.add_sub_node(3, 8);
    tree3.add_sub_node(4, 9);
    tree3.add_sub_node(4, 10);

    cout << "Pre-order for k-3 tree with integer: ";
    for (auto it = tree3.begin_pre_order(); it != tree3.end_pre_order(); ++it)
     {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-order for k-3 tree with integer: ";
    for (auto it = tree3.begin_post_order(); it != tree3.end_post_order(); ++it)
     {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-order for k-3 tree with integer: ";
    for (auto it = tree3.begin_in_order(); it != tree3.end_in_order(); ++it) 
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Bfs for k-3 tree with integer: ";
    for (auto it = tree3.begin_bfs_scan(); it != tree3.end_bfs_scan(); ++it)
     {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Dfs for k-3 tree with integer: ";
    for (auto it = tree3.begin_dfs_scan(); it != tree3.end_dfs_scan(); ++it)
     {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Heap for k-3 tree with integer: ";
    for (auto it = tree3.begin_heap(); it != tree3.end_heap(); ++it)
    
     {
        cout << *it << " ";
    }
    cout << endl;



 // Create a binary tree with double
    tree<double> tree4(2);
    //create the children of the tree
    tree4.add_root(1.1);
    tree4.add_sub_node(1.1, 2.2); 
    tree4.add_sub_node(1.1, 3.3); 
    tree4.add_sub_node(2.2, 4.4); 
    tree4.add_sub_node(2.2, 5.5); 
    tree4.add_sub_node(3.3, 6.6); 
    tree4.add_sub_node(3.3, 7.7); 

    cout << "Pre-order for binary tree with double: ";
    for (auto it = tree4.begin_pre_order(); it != tree4.end_pre_order(); ++it) 
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-order for binary tree with double: ";
    for (auto it = tree4.begin_post_order(); it != tree4.end_post_order(); ++it)
     {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-order for binary tree with double: ";
    for (auto it = tree4.begin_in_order(); it != tree4.end_in_order(); ++it)
     {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Bfs for binary tree with double: ";
    for (auto it = tree4.begin_bfs_scan(); it != tree4.end_bfs_scan(); ++it) 
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Dfs for binary tree with double: ";
    for (auto it = tree4.begin_dfs_scan(); it != tree4.end_dfs_scan(); ++it) 
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Heap for binary tree with double: ";
    for (auto it = tree4.begin_heap(); it != tree4.end_heap(); ++it) 
    {
        cout << *it << " ";
    }
    cout << endl;

    

//visualize tree for binary tree
    sf::RenderWindow first_screen(sf::VideoMode(1600, 1300), "Visualization Binary Tree with int"); 

    while (first_screen.isOpen()) 
    {
        sf::Event e;
        while (first_screen.pollEvent(e)) 
        {
            if (e.type == sf::Event::Closed)
                first_screen.close();
        }

        first_screen.clear(sf::Color::White);
        visualize_tree(first_screen, tree1);
        first_screen.display();
    }

//visualize tree for binary tree with complex number 
    sf::RenderWindow second_screen(sf::VideoMode(1800, 1400), "Visualization Binary Tree with complex numbers"); 
    while (second_screen.isOpen()) 
    {
        sf::Event e;
        while (second_screen.pollEvent(e))
         {
            if (e.type == sf::Event::Closed)
                second_screen.close();
        }

        second_screen.clear(sf::Color::White);
        visualize_tree(second_screen, tree2);
        second_screen.display();
    }

//visualize tree for k-3 tree with int
    sf::RenderWindow three_screen(sf::VideoMode(1600, 1300), "Visualization  k-3 Tree with int"); 

    while (three_screen.isOpen()) {
        sf::Event e;
        while (three_screen.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                three_screen.close();
        }

        three_screen.clear(sf::Color::White);
        visualize_tree(three_screen, tree3);
        three_screen.display();
    }

    //visualize binar tree with double
    sf::RenderWindow four_screen(sf::VideoMode(1600, 1300), "Visualization binar tree with double"); 

    while (four_screen.isOpen()) {
        sf::Event e;
        while (four_screen.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                four_screen.close();
        }

        four_screen.clear(sf::Color::White);
        visualize_tree(four_screen, tree4);
        four_screen.display();
    }

    return 0;}
