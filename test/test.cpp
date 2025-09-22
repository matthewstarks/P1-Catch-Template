//Matthew Starks UFID: 85876541
#include "catch/catch_amalgamated.hpp"
#include "../src/tree.cpp"
#include <vector>
#include <string>

TEST_CASE("Right Right Case", "[AVL]") {
    MyAVLTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
	tree.AVLSort();
    std::vector<int> actual = tree.levelorder();
    std::vector<int> expected = {2, 1, 3};
    REQUIRE(actual == expected);
}

TEST_CASE("Left Left Case", "[AVL]") {
    MyAVLTree tree;
    tree.insert(7);
    tree.insert(6);
    tree.insert(5);
	tree.AVLSort();
    std::vector<int> actual = tree.levelorder();
    std::vector<int> expected = {6, 5, 7};
    REQUIRE(actual == expected);
}

TEST_CASE("Left Right Case", "[AVL]") {
    MyAVLTree tree;
    tree.insert(3);
    tree.insert(1);
    tree.insert(2);
	tree.AVLSort();
    std::vector<int> actual = tree.levelorder();
    std::vector<int> expected = {2, 1, 3};
    REQUIRE(actual == expected);
}

TEST_CASE("Right Left Case", "[AVL]") {
    MyAVLTree tree;
    tree.insert(1);
    tree.insert(3);
    tree.insert(2);
	tree.AVLSort();
    std::vector<int> actual = tree.levelorder();
    std::vector<int> expected = {2, 1, 3};
    REQUIRE(actual == expected);
}

TEST_CASE("Reject Invalid Inputs", "[AVL]") {
    MyAVLTree tree;
    REQUIRE_THROWS_AS(tree.insert("A11Y"), std::invalid_argument);
    REQUIRE_THROWS_AS(tree.insert("AAAAA"), std::invalid_argument);
    REQUIRE_THROWS_AS(tree.insert("iuhwefiuniushdfih"), std::invalid_argument);
    REQUIRE_THROWS_AS(tree.insert("98u234nkjfsd"), std::invalid_argument);
    REQUIRE_THROWS_AS(tree.insert("/.,';"), std::invalid_argument);
}

TEST_CASE("BST Insert Large", "[AVL]"){
    MyAVLTree inputTree;
    vector<int> expectedOutput, actualOutput;

    for(int i = 0; i < 100000; i++)
    {
        int randomInput = rand();
        if (std::count(expectedOutput.begin(), expectedOutput.end(), randomInput) == 0)
        {
            expectedOutput.push_back(randomInput);
            inputTree.insert(randomInput);
        }
    }

	inputTree.AVLSort();
    actualOutput = inputTree.levelorder();
    REQUIRE(expectedOutput.size() == actualOutput.size());
    sort(expectedOutput.begin(), expectedOutput.end());
    REQUIRE(expectedOutput == actualOutput);

}
