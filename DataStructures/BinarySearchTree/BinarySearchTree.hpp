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

    const T& getValue() const { return value; }
    std::shared_ptr<BST<T>> insert(std::shared_ptr<BST<T>>& node, T value);
    std::shared_ptr<BST<T>> createNewNode(T value);
    std::shared_ptr<BST<T>> deleteNode(std::shared_ptr<BST<T>> root, std::shared_ptr<BST<T>> parent, const T value);
    std::shared_ptr<BST<T>> find(std::shared_ptr<BST<T>>& root, const T& value);
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
std::shared_ptr<BST<T>> BST<T>::deleteNode(std::shared_ptr<BST<T>> root, std::shared_ptr<BST<T>> parent, const T value) {
    if (!parent || !root)
        return root;

    if (value < root->value) {
        deleteNode(root->_left, root, value);
    }
    else if (value > root->value) {
        deleteNode(root->_right, root, value);
    }
    else {//if node to be deleted is on right part of the parent
        if (root->value > parent->value){
            if (root->_right)
                parent->_right = root->_right;
            else if (root->_left)
                parent->_right = root->_left;
            else
                parent->_right = nullptr;
            
            parent = parent->_right;
            if (root->_left && root->_left->value != parent->value) {
                while (1) {
                    if (parent->_left)
                        parent = parent->_left;
                    else {
                        parent->_left = root->_left;
                        break;
                    }
                }
            }
        }//if node to be deleted is on the left subtree of the parent
        else if (root->value < parent->value) {
            if (root->_left)
                parent->_left = root->_left;
            else if (root->_right)
                parent->_left = root->_right;
            else
                parent->_left = nullptr;

            parent = parent->_left;
            if (root->_right && root->_right->value != parent->value) {
                while (1) {
                    if (parent->_right)
                        parent = parent->_right;
                    else {
                        parent->_right = root->_right;
                        break;
                    }
                }
            }
        }else {//root itself needs to be deleted.
            auto temp = root;
            
            if (temp->_left) {
                temp = temp->_left;
                while (temp->_right)
                    temp = temp->_right;

                temp->_right = root->_right;
                root = root->_left;
            }
            else if (root->_right) {
                root = root->_right;
            }
            
         }
    }
    return root;
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

template <typename T>
std::shared_ptr<BST<T>> BST<T>::find(std::shared_ptr<BST<T>>& root, const T& value) {
    if (!root)
        return nullptr;

    if (root->value == value)
        return root;
    else if (root->value < value)
        return find(root->_right, value);
    else
        return find(root->_left, value);
}