#pragma once
#include <bits/stdc++.h>

struct ZoneNode {
    int id;
    std::string name;
    std::string details;
    int height;
    ZoneNode *left;
    ZoneNode *right;
    ZoneNode(int i, std::string n, std::string d)
        : id(i), name(std::move(n)), details(std::move(d)), height(1), left(nullptr), right(nullptr) {}
};

class ZoneBST {
protected:
    ZoneNode *root = nullptr;

    static int h(ZoneNode *n) { return n ? n->height : 0; }
    static void update(ZoneNode *n) { if (n) n->height = std::max(h(n->left), h(n->right)) + 1; }

    ZoneNode* insertRec(ZoneNode* node, int id, const std::string &name, const std::string &details) {
        if (!node) return new ZoneNode(id, name, details);
        if (name < node->name) node->left = insertRec(node->left, id, name, details);
        else node->right = insertRec(node->right, id, name, details);
        update(node);
        return node; // no balancing in BST
    }

    void inorderRec(ZoneNode* n, std::vector<std::string> &out) const {
        if (!n) return; inorderRec(n->left, out); out.push_back(n->name); inorderRec(n->right, out);
    }
    void preorderRec(ZoneNode* n, std::vector<std::string> &out) const {
        if (!n) return; out.push_back(n->name); preorderRec(n->left, out); preorderRec(n->right, out);
    }
    void postorderRec(ZoneNode* n, std::vector<std::string> &out) const {
        if (!n) return; postorderRec(n->left, out); postorderRec(n->right, out); out.push_back(n->name);
    }

public:
    virtual ~ZoneBST() { clearRec(root); }
    void clearRec(ZoneNode *n) { if (!n) return; clearRec(n->left); clearRec(n->right); delete n; }

    virtual void insert(int id, const std::string &name, const std::string &details) {
        root = insertRec(root, id, name, details);
    }

    std::vector<std::string> inorder() const { std::vector<std::string> out; inorderRec(root, out); return out; }
    std::vector<std::string> preorder() const { std::vector<std::string> out; preorderRec(root, out); return out; }
    std::vector<std::string> postorder() const { std::vector<std::string> out; postorderRec(root, out); return out; }
};

class ZoneAVL : public ZoneBST {
    static int balance(ZoneNode* n) { return n ? h(n->left) - h(n->right) : 0; }
    static ZoneNode* rotateRight(ZoneNode* y) {
        ZoneNode* x = y->left; ZoneNode* T2 = x->right; x->right = y; y->left = T2; update(y); update(x); return x;
    }
    static ZoneNode* rotateLeft(ZoneNode* x) {
        ZoneNode* y = x->right; ZoneNode* T2 = y->left; y->left = x; x->right = T2; update(x); update(y); return y;
    }

    ZoneNode* insertAVL(ZoneNode* node, int id, const std::string &name, const std::string &details) {
        if (!node) return new ZoneNode(id, name, details);
        if (name < node->name) node->left = insertAVL(node->left, id, name, details);
        else node->right = insertAVL(node->right, id, name, details);
        update(node);
        int b = balance(node);
        if (b > 1 && name < node->left->name) return rotateRight(node);
        if (b < -1 && name > node->right->name) return rotateLeft(node);
        if (b > 1 && name > node->left->name) { node->left = rotateLeft(node->left); return rotateRight(node);} 
        if (b < -1 && name < node->right->name) { node->right = rotateRight(node->right); return rotateLeft(node);} 
        return node;
    }

public:
    void insert(int id, const std::string &name, const std::string &details) override {
        root = insertAVL(root, id, name, details);
    }
};