#include <iostream>
#include <stdexcept>
#include <vector>
#include <cctype>
using namespace std; 

struct Node {
    string ID;
    string Name;
    Node* left;
    Node* right;
    int height;
    int balanceFactor;
    Node(string ID, string name) : ID(ID), Name(name), left(nullptr), right(nullptr), height(1), balanceFactor(0) {}
};

class tree {
private:
    Node* root = nullptr;

    Node* insertNode(Node* n, string ID, string name) {
        if (n == nullptr) {
            return new Node(ID, name);
        }
        if (stoi(ID) < stoi(n->ID)) {
            n->left = insertNode(n->left, ID, name);
        } 
        else{
            n->right = insertNode(n->right, ID, name);
        }
        
        n->height = height(n);
        n->balanceFactor = balanceFactor(n);

        // if (n->balanceFactor < -1){ //right heavy
        //     if(n->right->balanceFactor > 1){ // right subtree left heavy
        //         return rotateRightLeft(n);
        //     }
        //     else{
        //         return rotateLeft(n);
        //     }
        // }
        // else if (n->balanceFactor > 1) { // left heavy
        //     if (n->left->balanceFactor < -1){
        //         return rotateLeftRight(n);
        //     }
        //     else{
        //         return rotateRight(n);
        //     }
        // } 
        return n;
    }

    int height(Node* n){
        if(n==nullptr){
            return 0;
        }
        return 1+max(height(n->left), height(n->right));
    }

    int balanceFactor(Node* n){
        if(n==nullptr){
            return 0;
        }
        return height(n->left) - height(n->right);
    }

    Node* rotateRight(Node* n){
        return n;
    }

    Node* rotateRightLeft(Node* n){
        return n;
    }

    Node* rotateLeftRight(Node* n){
        return n;
    }

    Node* rotateLeft(Node* n){
        Node* grandchild = n->right->left;
        Node* newParent = n->right;
        newParent->left = n;
        n->right = grandchild;
        return newParent;
    }

public:
    bool isNumeric(const string& s){
        for (char c : s){
            if(!isdigit(c)){
                return false;
            }
        }
        return  !s.empty();
    }

    void insert(string ID, string name) {
        if(!isNumeric(ID)){
            throw invalid_argument("ID must contain only digits");
        }
        if(name.empty()){
            throw invalid_argument("Name cannot be empty");
        }
        root = insertNode(root, ID, name);
    }

    void searchID(string ID){
        return;
    }

    void removeID(string ID){
        return;
    }

    void searchName(string Name){  
        return;
    }

    Node* getRoot(){
        return this->root;
    }

    vector<string> testInorder(){ //using for tests
        vector<string> vec;
        return vec;
    }

    void printInorder(Node* root){ //prints names in tree
        if (root == nullptr){
            return;
        }
        else{
            printInorder(root->left);
            cout << root->Name << " ";
            printInorder(root->right);
        }
    }

    void printPreorder(Node* root){ //prints names in tree
        if (root == nullptr){
            return;
        }
        else{
            printPreorder(root->left);
            printPreorder(root->right);
            cout << root->Name << " ";
        }
    }

    void printPostorder(Node* root){ //prints names in tree
        if (root == nullptr){
            return;
        }
        else{
            printPostorder(root->left);
            printPostorder(root->right);
            cout << root->Name << " ";
        }
    }

    void printLevelCount(){  //prints number of levels in tree, 0 if head of tree is null
        return;
    }

    void removeInorder(int n){
        return;
    }

};