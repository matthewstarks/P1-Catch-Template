//Matthew Starks UFID: 85876541
#include "catch/catch_amalgamated.hpp"
#include "../src/tree.cpp"
#include <vector>
#include <string>

TEST_CASE("Right Right Case", "[AVL]") {
    tree tree;
    tree.insert("matthew", "12423432");
    tree.insert("matthew", "22423432");
    tree.insert("matthew", "32423432");
    std::vector<string> actual = tree.testInorder();
    std::vector<string> expected = {"32432", "342", "3214324"};
    REQUIRE(actual == expected);
}

TEST_CASE("Left Left Case", "[AVL]") {
    tree tree;
    tree.insert("matthew", "32423432");
    tree.insert("matthew", "22423432");
    tree.insert("matthew", "12423432");
    std::vector<string> actual = tree.testInorder();
    std::vector<string> expected = {"32432", "342", "3214324"};
    REQUIRE(actual == expected);
}

TEST_CASE("Left Right Case", "[AVL]") {
    tree tree;
    tree.insert("matthew", "32423432");
    tree.insert("matthew", "12423432");
    tree.insert("matthew", "22423432");
    std::vector<string> actual = tree.testInorder();
    std::vector<string> expected = {"32432", "342", "3214324"};
    REQUIRE(actual == expected);
}

TEST_CASE("Right Left Case", "[AVL]") {
    tree tree;
    tree.insert("matthew", "12423432");
    tree.insert("matthew", "32423432");
    tree.insert("matthew", "22423432");
    std::vector<string> actual = tree.testInorder();
    std::vector<string> expected = {"32432", "342", "3214324"};
    REQUIRE(actual == expected);
}

TEST_CASE("Reject Invalid Inputs", "[AVL]") {
    tree tree;
    REQUIRE_THROWS_AS(tree.insert("A11Y", "32423"), std::invalid_argument);
    REQUIRE_THROWS_AS(tree.insert("AAAAA", "323423"), std::invalid_argument);
    REQUIRE_THROWS_AS(tree.insert("iuhwefiuniushdfih", "34234"), std::invalid_argument);
    REQUIRE_THROWS_AS(tree.insert("98u234nkjfsd", "342342"), std::invalid_argument);
    REQUIRE_THROWS_AS(tree.insert("/.,';", "342432"), std::invalid_argument);
}

TEST_CASE("BST Insert Large", "[AVL]"){
    tree inputTree;
    vector<string> expectedOutput, actualOutput;

    for(int i = 0; i < 100000; i++)
    {
        int randomInput = rand();
        if (count(expectedOutput.begin(), expectedOutput.end(), randomInput) == 0)
        {
            string rand = to_string(randomInput);
            expectedOutput.push_back(rand);
            inputTree.insert(rand, rand);
        }
    }

    actualOutput = inputTree.testInorder();
    REQUIRE(expectedOutput.size() == actualOutput.size());
    sort(expectedOutput.begin(), expectedOutput.end());
    REQUIRE(expectedOutput == actualOutput);

}
