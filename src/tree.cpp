#include <iostream>
#include <stdexcept>
#include <vector>
#include <cctype>
#include <regex>
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

    void inorderHelper(Node* n, vector<Node*>& nodes){ //turns tree into inorder vector
        if(n == nullptr){
            return;
        }
        inorderHelper(n->left, nodes);
        nodes.push_back(n);
        inorderHelper(n->right, nodes);
    }

    int levelCountHelper(Node* n){
        if(n == nullptr){
            return 0;
        }
        return 1 + max(levelCountHelper(n->left), levelCountHelper(n->right));
    }

    bool isID(string& s){
        regex ID("^[0-9]{8}$"); // cited from regex slide deck
        return regex_match(s, ID);
    }

    bool isName(string& s){
        regex name("^[A-Za-z ]+$"); // cited from regex slide deck
        if(!regex_match(s, name)){
            return false;
        }

        //at least one letter
        for(char c : s){
            if (isalpha(c)){
                return true;
            }
        }
        return false;
    }

    Node* insertNode(Node* n, string name, string ID) {
        if (n == nullptr) {
            return new Node(ID, name);
        }
        if (ID < n->ID) {
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

    void printInorderHelper(Node* n, vector<Node*>& nodes){
        if(n == nullptr){
            return;
        }
        printInorderHelper(n->left, nodes);
        nodes.push_back(n);
        printInorderHelper(n->right, nodes);
    }

    void printPostorderHelper(Node* n, vector<Node*>& nodes){
        if(n == nullptr){
            return;
        }
        printPostorderHelper(n->left, nodes);
        printPostorderHelper(n->right, nodes);
        nodes.push_back(n);
    }

    void printPreorderHelper(Node*n, vector<Node*>& nodes){
        if(n == nullptr){
            return;
        }
        nodes.push_back(n);
        printPreorderHelper(n->left, nodes);
        printPreorderHelper(n->right, nodes);
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

        n->balanceFactor = balanceFactor(n);
        newParent->balanceFactor = balanceFactor(newParent);

        return newParent;
    }

    Node* rotateLeft(Node* n){
        Node* grandchild = n->right->left;
        Node* newParent = n->right;

        newParent->left = n;
        n->right = grandchild;

        n->height = 1 + max(height(n->left), height(n->right));
        newParent->height = 1 + max(height(newParent->left), height(newParent->right));

        n->balanceFactor = balanceFactor(n);
        newParent->balanceFactor = balanceFactor(newParent);

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

    Node* removeNode(Node* n, string ID, bool& removed){ //has public helper
        if(n==nullptr){
            return nullptr;
        }
        if (ID < n->ID){
            n->left = removeNode(n->left, ID, removed);
        }
        else if (ID > n->ID){
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
                n->right = removeNode(n->right, inorderSuccessor->ID, removed);
            }
        }
        n->height = height(n);
        n->balanceFactor = balanceFactor(n);

        return n;
    }

public:

    string remove(string ID){
        bool removed = false;
        root = removeNode(root, ID, removed); //reassign root to possible new root
        if(removed){
            cout << "successful" << endl;
            return "successful"; //all return functions used for unit tests
        }
        else{
            cout << "unsuccessful" << endl;
            return "unsuccessful";
        }
        return ".";
    }

    // bool isNumeric(const string& s){
    //     for (char c : s){
    //         if(!isdigit(c)){
    //             return false;
    //         }
    //     }
    //     return  !s.empty();
    // }

    string insert(string name, string ID){
        if(!isID(ID) || !isName(name)){
            cout << "unsuccessful" << endl;
            return "unsuccessful";
            // throw invalid_argument("Invalid name or ID");
        }

        Node* existing = searchIDHelper(root, ID);
        if(existing != nullptr){
            cout << "unsuccessful" << endl;
            return "unsuccessful";
        }

        root = insertNode(root, name, ID);
        cout << "successful" << endl;
        return "successful";
    }

    string search(string s){
        if(isID(s)){ //if its an ID
            Node* result = searchIDHelper(root, s);

            if(result == nullptr){
                cout << "unsuccessful" << endl;
                return "unsuccessful";
            }
            else{
                cout << result->name << endl;
                return result->name;
            }
        }
        else{ //if its a name
            vector<string> id;
            searchNameHelper(root, s, id);

            if(id.empty()){
                cout << "unsuccessful" << endl;
                return "unsuccessful";
            }
            else{
                for (auto& id : id){
                    cout << id << endl;
                }
                return "successful";
            }
        }
    }

    Node* getRoot(){
        return this->root;
    }

    vector<Node*> printInorder() {
        vector<Node*> nodes;
        printInorderHelper(root, nodes);
        for (size_t i = 0; i < nodes.size(); ++i) {
            cout << nodes[i]->name;
            if (i != nodes.size() - 1) cout << ", ";
        }
        cout << endl;
        return nodes;
    }

    vector<Node*> printPreorder() {
        vector<Node*> nodes;
        printPreorderHelper(root, nodes);
        for (size_t i = 0; i < nodes.size(); ++i) {
            cout << nodes[i]->name;
            if (i != nodes.size() - 1) cout << ", "; //cited from stackoverflow https://stackoverflow.com/questions/22702736/for-loop-prints-an-extra-comma
        }
        cout << endl;
        return nodes;
    }

    vector<Node*> printPostorder() {
        vector<Node*> nodes;
        printPostorderHelper(root, nodes);
        for (size_t i = 0; i < nodes.size(); ++i) {
            cout << nodes[i]->name;
            if (i != nodes.size() - 1) cout << ", ";
        }
        cout << endl;
        return nodes;
    }

    int printLevelCount(){ //prints number of levels in tree, 0 if head of tree is null
        int n = levelCountHelper(root);
        cout << n << endl;
        return n;
    }

    string removeInorder(int n){
        vector<Node*> nodes;
        inorderHelper(root, nodes);

        if(n < 0 || n >= nodes.size()){
            cout << "unsuccessful" << endl;
            return "unsuccessful";
        }
        string removal = nodes[n]->ID;
        bool removed2 = false;
        root = removeNode(root, removal, removed2);
        cout << "successful" << endl;
        return "successful";
    }

};