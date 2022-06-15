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
    void printcurrentLevel(std::shared_ptr<BST<T>>& root, int level,string space, bool isLeft=true);
    bool isBST(std::shared_ptr<BST<T>>& root);
    bool isBST(std::shared_ptr<BST<T>>& root, T minvalue, T maxvalue);
    T getMinValue(std::shared_ptr<BST<T>> root);
    int getHeight(std::shared_ptr<BST<T>> root);
    //friend function to test binary search tree
    friend void testBST();
};

template<typename T>
int BST<T>::getHeight(std::shared_ptr<BST<T>> root){
    if (root == nullptr)
        return 0;
    return (1 + max(getHeight(root->_left),getHeight(root->_right))); 
}

template<typename T>
void BST<T>::printcurrentLevel(std::shared_ptr<BST<T>>& root, int level,string space, bool isLeft)
{
    if (root == nullptr)
       return;
    if (level == 1){
        if (isLeft)
	    cout<<space<< root->value << " ";
	else
	    cout<<space<< root->value;
    }else{
	printcurrentLevel(root->_left,level-1,space.substr(0,space.length()-1),true);
	printcurrentLevel(root->_right,level-1,space.substr(0,space.length()+1),false);
    }

}

//TO DO - DISPLAY PROPERLY
template<typename T>
void BST<T>::display(std::shared_ptr<BST<T>>& root) {
    
    int h = this->getHeight(root);
    std::string space(h,' ');
    for (int i=1; i<=h; i++){
	printcurrentLevel(root,i,space,false);
        cout<<endl;
    }
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

template<typename T>
T BST<T>::getMinValue(std::shared_ptr<BST<T>> root){

	while (root->_left != nullptr){
	    root = root->_left;
	}
	return root->value;
}

template <typename T>
std::shared_ptr<BST<T>> BST<T>::deleteNode(std::shared_ptr<BST<T>> root, std::shared_ptr<BST<T>> parent, const T value){

    auto currentNode = root;
    while (currentNode != nullptr){
	if (currentNode->value < value){
	    parent = currentNode;
            currentNode = currentNode->_right;
	}else if (currentNode->value > value){
	    parent = currentNode;
            currentNode = currentNode->_left;
	}else{
	    if (currentNode->_left != nullptr && currentNode->_right != nullptr){
	        currentNode->value = this->getMinValue(currentNode->_right);
                deleteNode(currentNode->_right,nullptr,currentNode->value); 
            }else if (parent == nullptr){
		if (currentNode->_left != nullptr){
  		    auto temp = currentNode;
		    currentNode = currentNode->_left;
                    temp->_left = nullptr;
		}else if (currentNode->_right != nullptr){
		    auto temp = currentNode;
		    currentNode = currentNode->_right;
                    temp->_right = nullptr;
		}else{
		    return nullptr;
		}
	    }else if (parent->_left == currentNode){
	        parent->_left = currentNode->_left != nullptr ? currentNode->_left : currentNode->_right;
 	    }else if (parent->_right == currentNode){
	        parent->_right = currentNode->_right != nullptr ? currentNode->_right : currentNode->_left;
	    }else{
		break;
	    }
	}
    }
    return root;
}

/*
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
*/
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
