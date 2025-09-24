#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "tree.cpp"

using namespace std;

int main(){
    tree t;

    // Open file
    ifstream infile("test-io/input-files/6.txt");
    if (!infile){
        cout << "Failed to open input file." << endl;
        return 1;
    }

    int numCommands;
    infile >> numCommands;
    infile.ignore(); // skip newline

    // Read all commands into a vector
    vector<string> commands;
    for (int i = 0; i < numCommands; i++){
        string line;
        getline(infile, line);
        commands.push_back(line);
    }
    infile.close();

    for (string line : commands){
        if (line.find("insert") == 0){
            int firstQuote = line.find('"');
            int secondQuote = line.find('"', firstQuote + 1);
            string name = line.substr(firstQuote + 1, secondQuote - firstQuote - 1);
            string ID = line.substr(secondQuote + 2); // skip space
            t.insert(name, ID);
        }
        else if (line.find("search") == 0) {
            string arg = line.substr(7); // after "search "
            if (arg[0] == '"') {
                arg = arg.substr(1, arg.size() - 2); // remove quotes
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
    }

    return 0;
}