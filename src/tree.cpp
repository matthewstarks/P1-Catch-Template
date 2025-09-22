#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std; 

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

class MyAVLTree {
private:
    Node* root = nullptr;

    Node* insertNode(Node* n, int key) {
        if (n == nullptr) {
            return new Node(key);
        }
        if (key < n->key) {
            n->left = insertNode(n->left, key);
        } else if (key > n->key) {
            n->right = insertNode(n->right, key);
        }
        return n;
    }

public:
    void insert(int key) {
        root = insertNode(root, key);
    }

    void insert(const char* key) {
        throw std::invalid_argument("Only integers allowed");
    }

    void insert(const std::string& key) {
        throw std::invalid_argument("Only integers allowed");
    }

    void AVLSort() {}
    std::vector<int> levelorder() { return {}; }
};