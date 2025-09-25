#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "tree.cpp"

using namespace std;

int main() {
    tree t;
    int numCommands;
    cin >> numCommands;
    cin.ignore();

    for (int i = 0; i < numCommands; i++){
        string line;
        getline(cin, line);

        if (line.find("insert") == 0){
            int firstQuote = line.find('"');
            int secondQuote = line.find('"', firstQuote + 1);
            string name = line.substr(firstQuote + 1, secondQuote - firstQuote - 1);
            string ID = line.substr(secondQuote + 2);
            t.insert(name, ID);
        }
        else if (line.find("search") == 0){
            string arg = line.substr(7);
            if (arg[0] == '"') {
                arg = arg.substr(1, arg.size() - 2);
            }
            t.search(arg);
        }
        else if (line.find("removeInorder") == 0) {
            string indexStr = line.substr(14);
            int index = stoi(indexStr);
            t.removeInorder(index);
        }
        else if (line.find("remove") == 0) {
            string ID = line.substr(7);
            t.remove(ID);
        }
        else if (line == "printInorder") {
            t.printInorder();
        }
        else if (line == "printPreorder") {
            t.printPreorder();
        }
        else if (line == "printPostorder") {
            t.printPostorder();
        }
        else if (line == "printLevelCount") {
            t.printLevelCount();
        }
        else {
            cout << "Unknown command" << endl;
        }
    }

    return 0;
}