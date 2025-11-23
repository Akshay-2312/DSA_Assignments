#ifndef TREE_H
#define TREE_H

#include "BuildingADT.h"
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

// Node structure for BST and AVL Tree
template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
    int height; // For AVL tree

    TreeNode(T val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

// Binary Search Tree implementation
template <typename T>
class BST {
protected:
    TreeNode<T>* root;

    // Helper methods
    virtual TreeNode<T>* insertNode(TreeNode<T>* node, T data) {
        if (node == nullptr) {
            return new TreeNode<T>(data);
        }

        if (data < node->data) {
            node->left = insertNode(node->left, data);
        } else if (data > node->data) {
            node->right = insertNode(node->right, data);
        }

        return node;
    }

    void inorderTraversal(TreeNode<T>* node,  vector<T>& result) const {
        if (node == nullptr) return;
        inorderTraversal(node->left, result);
        result.push_back(node->data);
        inorderTraversal(node->right, result);
    }

    void preorderTraversal(TreeNode<T>* node,  vector<T>& result) const {
        if (node == nullptr) return;
        result.push_back(node->data);
        preorderTraversal(node->left, result);
        preorderTraversal(node->right, result);
    }

    void postorderTraversal(TreeNode<T>* node,  vector<T>& result) const {
        if (node == nullptr) return;
        postorderTraversal(node->left, result);
        postorderTraversal(node->right, result);
        result.push_back(node->data);
    }

    TreeNode<T>* findNode(TreeNode<T>* node, T data) const {
        if (node == nullptr || node->data == data) {
            return node;
        }

        if (data < node->data) {
            return findNode(node->left, data);
        } else {
            return findNode(node->right, data);
        }
    }

    void destroyTree(TreeNode<T>* node) {
        if (node == nullptr) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    virtual ~BST() {
        destroyTree(root);
    }

    // Insert a new node
    virtual void insert(T data) {
        root = insertNode(root, data);
    }

    // Find a node
    bool find(T data) const {
        return findNode(root, data) != nullptr;
    }

    // Get node data if found
    T* getData(T data) const {
        TreeNode<T>* node = findNode(root, data);
        return node ? &(node->data) : nullptr;
    }

    // Traversal methods
     vector<T> inorder() const {
         vector<T> result;
        inorderTraversal(root, result);
        return result;
    }

     vector<T> preorder() const {
         vector<T> result;
        preorderTraversal(root, result);
        return result;
    }

     vector<T> postorder() const {
         vector<T> result;
        postorderTraversal(root, result);
        return result;
    }

    // Level order traversal (BFS)
     vector<T> levelOrder() const {
         vector<T> result;
        if (root == nullptr) return result;

         queue<TreeNode<T>*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode<T>* current = q.front();
            q.pop();
            result.push_back(current->data);

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }

        return result;
    }
};

// AVL Tree implementation (extends BST)
template <typename T>
class AVLTree : public BST<T> {
private:
    // Get height of a node
    int height(TreeNode<T>* node) const {
        return node ? node->height : 0;
    }

    // Get balance factor
    int getBalanceFactor(TreeNode<T>* node) const {
        return node ? height(node->left) - height(node->right) : 0;
    }

    // Update height of a node
    void updateHeight(TreeNode<T>* node) {
        if (node) {
            node->height = 1 +  max(height(node->left), height(node->right));
        }
    }

    // Right rotation
    TreeNode<T>* rightRotate(TreeNode<T>* y) {
        TreeNode<T>* x = y->left;
        TreeNode<T>* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Left rotation
    TreeNode<T>* leftRotate(TreeNode<T>* x) {
        TreeNode<T>* y = x->right;
        TreeNode<T>* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Override insertNode to maintain AVL property
    TreeNode<T>* insertNode(TreeNode<T>* node, T data) override {
        // Standard BST insert
        if (node == nullptr) {
            return new TreeNode<T>(data);
        }

        if (data < node->data) {
            node->left = insertNode(node->left, data);
        } else if (data > node->data) {
            node->right = insertNode(node->right, data);
        } else {
            // Duplicate keys not allowed
            return node;
        }

        // Update height of current node
        updateHeight(node);

        // Get balance factor
        int balance = getBalanceFactor(node);

        // Left Left Case
        if (balance > 1 && data < node->left->data) {
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && data > node->right->data) {
            return leftRotate(node);
        }

        // Left Right Case
        if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

public:
    // Override insert method
    void insert(T data) override {
        this->root = insertNode(this->root, data);
    }
};

// Building Tree specialization
using BuildingBST = BST<Building>;
using BuildingAVL = AVLTree<Building>;

#endif // TREE_H