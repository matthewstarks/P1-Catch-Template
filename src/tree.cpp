#include <iostream>
#include <stdexcept>
#include <vector>
#include <cctype>
using namespace std; 

struct Node {
    string ID;
    string name;
    Node* left;
    Node* right;
    int height;
    int balanceFactor;
    Node(string ID, string name) : ID(ID), name(name), left(nullptr), right(nullptr), height(1), balanceFactor(0) {}
};

class tree {
private:
    Node* root = nullptr;

    Node* insertNode(Node* n, string name, string ID) {
        if (n == nullptr) {
            return new Node(ID, name);
        }
        if (stoi(ID) < stoi(n->ID)) {
            n->left = insertNode(n->left, name, ID);
        } 
        else{
            n->right = insertNode(n->right, name, ID);
        }
        
        n->height = height(n);
        n->balanceFactor = balanceFactor(n);

        if (n->balanceFactor > 1) { // left heavy
            if (n->left != nullptr && n->left->balanceFactor < 0)
                return rotateLeftRight(n);
            else
                return rotateRight(n);
        } 
        else if (n->balanceFactor < -1) { // right heavy
            if (n->right != nullptr && n->right->balanceFactor > 0)
                return rotateRightLeft(n);
            else
                return rotateLeft(n);
        }
        return n;
    }

    void printInorderHelper(Node* n){
        if(n == nullptr){
            return;
        }
        printInorderHelper(n->left);
        cout << n->name << " ";
        printInorderHelper(n->right);
    }

    void searchNameHelper(Node* n, const string& name, vector<string>& ids){
        if (n == nullptr){
            return;
        } 

        if (n->name == name) {
            ids.push_back(n->ID);
        }

        searchNameHelper(n->left, name, ids);
        searchNameHelper(n->right, name, ids);
        
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
        Node* grandchild = n->left->right;
        Node* newParent = n->left;

        newParent->right = n;
        n->left = grandchild;

        n->height = 1 + max(height(n->left), height(n->right));
        newParent->height = 1 + max(height(newParent->left), height(newParent->right));

        return newParent;
    }

    Node* rotateLeft(Node* n){
        Node* grandchild = n->right->left;
        Node* newParent = n->right;

        newParent->left = n;
        n->right = grandchild;

        n->height = 1 + max(height(n->left), height(n->right));
        newParent->height = 1 + max(height(newParent->left), height(newParent->right));

        return newParent;
    }

    Node* rotateLeftRight(Node* n){
        n->left = rotateLeft(n->left);
        return rotateRight(n);
    }

    Node* rotateRightLeft(Node* n){
        n->right = rotateRight(n->right);
        return rotateLeft(n);
    }


    Node* searchIDHelper(Node* n, string ID){
        if(n == nullptr){
            return nullptr;
        }
        if(n->ID > ID){
            return searchIDHelper(n->left, ID);
        }
        else if (n->ID < ID){
            return searchIDHelper(n->right, ID);
        }
        else{
            return n;
        }
    }

    Node* removeNode(Node* n, int ID, bool &removed){
        if(n==nullptr){
            return nullptr;
        }
        if (ID < stoi(n->ID)){
            n->left = removeNode(n->left, ID, removed);
        }
        else if (ID > stoi(n->ID)){
            n->right = removeNode(n->right, ID, removed);
        }
        else{
            removed = true;

            //no child
            if(!n->left && !n->right){
                delete n;
                return nullptr;
            }
            //one child
            else if(!n->left){
                Node* temp = n->right;
                delete n;
                return temp;
            }
            else if(!n->right){
                Node* temp = n->left;
                delete n;
                return temp;
            }
            //twi children
            else{
                Node* inorderSuccessor = n->right;
                while(inorderSuccessor->left != nullptr){
                    inorderSuccessor = inorderSuccessor->left;
                }
                //transfer successor data to original node
                n->ID = inorderSuccessor->ID;
                n->name = inorderSuccessor->name;
                //delete successor
                n->right = removeNode(n->right, stoi(inorderSuccessor->ID), removed);
            }
        }
        n->height = height(n);
        n->balanceFactor = balanceFactor(n);

        return n;
    }

public:

    void remove(int ID){
        bool removed = false;
        root = removeNode(root,  ID, removed); //reassign root to possible new root
        if(removed){
            cout << "successful" << endl;
        }
        else{
            cout << "unsuccessful" << endl;
        }
        return;
    }

    // bool isNumeric(const string& s){
    //     for (char c : s){
    //         if(!isdigit(c)){
    //             return false;
    //         }
    //     }
    //     return  !s.empty();
    // }

    void insert(string name, int ID){
        if(ID < 0){
            throw invalid_argument("ID is negative");
        }
        if(name.empty()){
            throw invalid_argument("Name cant be empty");
        }

        Node* existing = searchIDHelper(root, to_string(ID));
        if(existing != nullptr){
            cout << "unsuccessful" << endl;
            return;
        }

        root = insertNode(root, name, to_string(ID));
        cout << "successful" << endl;
    }

    void search(int ID){
        string strID = to_string(ID);
        Node* val = searchIDHelper(root, strID);
        if(val != nullptr){
            cout << val->name << endl;
        }
        else{
            cout << "unsuccessful" << endl;
        }
    }

    void search(string name){
        vector<string> ids;
        searchNameHelper(root, name, ids);

        if (ids.empty()) {
            cout << "unsuccessful" << endl;
        } else {
            for (auto& id : ids) {
                cout << id << endl;
            }
        }
    }

    Node* getRoot(){
        return this->root;
    }

    void printInorder(){ //prints names in tree
        printInorderHelper(root);
    }

    void printPreorder(Node* root){ //prints names in tree
        if (root == nullptr){
            return;
        }
        else{
            printPreorder(root->left);
            printPreorder(root->right);
            cout << root->name << " ";
        }
    }

    void printPostorder(Node* root){ //prints names in tree
        if (root == nullptr){
            return;
        }
        else{
            printPostorder(root->left);
            printPostorder(root->right);
            cout << root->name << " ";
        }
    }

    int levelCountHelper(Node* n){
        if(n == nullptr){
            return 0;
        }
        return 1 + max(levelCountHelper(n->left), levelCountHelper(n->right));
    }

    void printLevelCount(){ //prints number of levels in tree, 0 if head of tree is null
        cout << levelCountHelper(root) << endl;
    }

    void inorderHelper(Node* n, vector<Node*>& nodes){ //turns tree into inorder vector
        if(n == nullptr){
            return;
        }
        inorderHelper(n->left, nodes);
        nodes.push_back(n);
        inorderHelper(n->right, nodes);
    }

    void removeInorder(int n){
        vector<Node*> nodes;
        inorderHelper(root, nodes);

        if(n >= 0 && n < nodes.size()){
            remove(stoi(nodes[n]->ID));
        }
        else{
            cout << "unsuccessful" << endl;
        }
    }

};