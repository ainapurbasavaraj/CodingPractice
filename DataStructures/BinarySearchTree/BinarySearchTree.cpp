// BinarySearchTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "BinarySearchTree.hpp"

void testBST() {
    shared_ptr<BST<int>> node = std::make_shared<BST<int>>(5);
    node->_left = std::make_shared<BST<int>>(3);
    node->_right = std::make_shared<BST<int>>(10);
    node->_left->_left = std::make_shared<BST<int>>(2);
    node->_left->_right = std::make_shared<BST<int>>(4);
    node->_right->_left = std::make_shared<BST<int>>(80);

    node->display(node);
    if (node->isBST(node)) {
        cout << "This is Binary search tree" << endl;
    }
    else {
        cout << "This is not Binary search treee" << endl;
    }
}

int main()
{
    shared_ptr<BST<int>> node = std::make_shared<BST<int>>(5);
    node->insert(node, 2);
    node->insert(node, 10);
    node->insert(node, 12);
    node->insert(node, 7);
    node->insert(node, 6);
    node->insert(node, 3);
    node->insert(node, 11);
    node->insert(node, 4);
    node->display(node);
    //testBST();

    auto deletedNode = node->deleteNode(node, nullptr, 2);
    cout << "Tree after deleting 6" << endl;
    node->display(deletedNode);
    if (node->isBST(deletedNode)) {
        cout << "This is Binary search tree" << endl;
    }
    else {
        cout << "This is not Binary search treee" << endl;
    }

    deletedNode = node->deleteNode(node, nullptr, 5);
    cout << "Tree after deleting 5" << endl;
    node->display(deletedNode);
    if (node->isBST(deletedNode)) {
        cout << "This is Binary search tree" << endl;
    }
    else {
        cout << "This is not Binary search treee" << endl;
    }

    //Finding the node
    cout << "Searching for node" << endl;
    auto tempNode = node->find(node, 7);
    if (tempNode)
        cout << "Found the node " << tempNode->getValue() << endl;
    else
        cout << "Node not found" << endl;
}
