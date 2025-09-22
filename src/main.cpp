#include <iostream>
#include <stdexcept>
#include <vector>
#include "tree.cpp"

using namespace std;

int main(){
	cout << "Hello AVL!\n";

	tree t;

	t.insert("20", "20");
    t.insert("10", "10");
    t.insert("30", "30");
    t.insert("5", "5");
    t.insert("15", "15");

	t.printInorder(t.getRoot());

	

	return 0;
}






