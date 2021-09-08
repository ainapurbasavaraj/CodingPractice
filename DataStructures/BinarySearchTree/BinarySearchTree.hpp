#pragma once

#include <iostream>
#include <memory>
#include <limits.h>
using namespace std;

template<typename T>
class BST {
private:
    std::shared_ptr<BST> _left = nullptr;
    std::shared_ptr<BST> _right = nullptr;
    T value = 0;

public:
    BST() {}
    BST(T value) {
        this->value = value;
    }

    std::shared_ptr<BST<T>> insert(std::shared_ptr<BST<T>>& node, T value);
    std::shared_ptr<BST<T>> createNewNode(T value);
    //std::shared_ptr<BST> deletevalue(T value);
    //std::shared_ptr<BST> findValue(T value);
    void display(std::shared_ptr<BST<T>>& root);
    bool isBST(std::shared_ptr<BST<T>>& root);
    bool isBST(std::shared_ptr<BST<T>>& root, T minvalue, T maxvalue);

    //friend function to test binary search tree
    friend void testBST();
};

template<typename T>
void BST<T>::display(std::shared_ptr<BST<T>>& root) {
    if (!root)
        return;

    display(root->_left);
    cout << root->value << endl;
    display(root->_right);


}

template<typename T>
std::shared_ptr<BST<T>> BST<T>::createNewNode(T value)
{
    std::shared_ptr<BST> node = make_shared<BST>();
    node->value = value;
    node->_left = nullptr;
    node->_right = nullptr;
    return node;
}

template<typename T>
std::shared_ptr<BST<T>> BST<T>::insert(std::shared_ptr<BST<T>>& node, T value)
{
    if (!node)
        return createNewNode(value);

    if (value < node->value)
        node->_left = insert(node->_left, value);
    else
        node->_right = insert(node->_right, value);

    return node;
}

template <typename T>
bool BST<T>::isBST(std::shared_ptr<BST<T>>& root, T minvalue, T maxvalue) {

    if (!root) {
        return true;
    }

    if (minvalue < INT_MAX && root->value <= minvalue)
        return false;

    if (maxvalue < INT_MAX && root->value >= maxvalue)
        return false;

    return (isBST(root->_left, minvalue, root->value) &&
        isBST(root->_right, root->value, maxvalue));
}

template <typename T>
bool BST<T>::isBST(std::shared_ptr<BST<T>>& root) {

    return isBST(root, INT_MAX, INT_MAX);
}