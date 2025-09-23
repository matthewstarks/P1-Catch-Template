#include <iostream>
#include <stdexcept>
#include <vector>
#include "tree.cpp"

using namespace std;

int main(){
	cout << "Hello AVL!\n";

	tree t;

// insert "Brandon" 45674567
// insert "Brian" 35455565
// insert "Briana" 87878787
// insert "Bella" 95462138
// printInorder
// remove 45674567
// removeInorder 2
// printInorder

	t.insert("Brandon", 45674567);
	t.insert("Brian", 35455565);
	t.insert("Briana", 87878787);
	t.insert("Bella", 95462138);
	t.printInorder();
	t.remove(45674567);
	t.printLevelCount();

	return 0;
}






