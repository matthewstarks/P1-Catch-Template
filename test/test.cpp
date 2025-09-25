// // Matthew Starks UFID: 85876541
// #define CATCH_CONFIG_MAIN
// #include "catch/catch_amalgamated.hpp"
// #include "../src/tree.cpp"
// #include <vector>
// #include <string>

// TEST_CASE("AVL", "[AVL]"){
//     tree t;

//     SECTION("Invalid Inserts)") {
//         REQUIRE(t.insert("Alice", "123") == "unsuccessful");
//         REQUIRE(t.insert("Bob", "abcdefgh") == "unsuccessful");
//         REQUIRE(t.insert("Charlie", "1234567a") == "unsuccessful");
//         REQUIRE(t.insert("F4nk", "10000004") == "unsuccessful");
//         REQUIRE(t.insert("", "10000005") == "unsuccessful");
//         REQUIRE(t.insert("   ", "10000006") == "unsuccessful");
//         REQUIRE(t.insert("Zelda", "00000000") == "successful");
//         REQUIRE(t.insert("LongNameWithSpaces ", "99999999") == "successful");
//     }

//     SECTION("Valid Inserts") {
//         REQUIRE(t.insert("Alice", "10000001") == "successful");
//         REQUIRE(t.insert("Bob", "10000002") == "successful");
//         REQUIRE(t.insert("Charlie", "10000003") == "successful");
//         REQUIRE(t.insert("David", "10000001") == "unsuccessful");
//         REQUIRE(t.insert("Alice", "10000001") == "unsuccessful");
//     }

//     SECTION("Search") {
//         t.insert("Alice", "10000001");
//         t.insert("Bob", "10000002");
//         t.insert("Charlie", "10000003");
//         t.insert("Alice", "10000004"); // same name different ID

//         REQUIRE(t.search("10000001") == "Alice");
//         REQUIRE(t.search("10000004") == "Alice");
//         REQUIRE(t.search("99999999") == "unsuccessful");
//         REQUIRE(t.search("Alice") == "successful");
//         REQUIRE(t.search("Charlie") == "successful");
//         REQUIRE(t.search("1234abcd") == "unsuccessful");
//         REQUIRE(t.search("Noname") == "unsuccessful");
//     }

//     SECTION("Deletions") {
//         t.insert("Alice", "10000001");
//         t.insert("Bob", "10000002");
//         t.insert("Charlie", "10000003");
//         t.insert("David", "10000004");
//         t.insert("Eve", "10000005");

//         REQUIRE(t.remove("10000005") == "successful"); // Eve
//         REQUIRE(t.remove("10000004") == "successful"); // David
//         REQUIRE(t.remove("10000002") == "successful"); // Bob
//         REQUIRE(t.remove("10000001") == "successful"); // Alice
//         REQUIRE(t.remove("99999999") == "unsuccessful");
//     }

//     SECTION("removeInorder edge cases") {
//         t.insert("Alice", "10000001");
//         t.insert("Bob", "10000002");
//         t.insert("Charlie", "10000003");
//         t.insert("David", "10000004");

//         REQUIRE(t.removeInorder(0) == "successful");

//         REQUIRE(t.removeInorder(1) == "successful");
//         REQUIRE(t.removeInorder(1) == "successful");
//         REQUIRE(t.removeInorder(10) == "unsuccessful");
//         REQUIRE(t.removeInorder(-1) == "unsuccessful");
//     }

//     SECTION("Traversals") {
//         t.insert("C", "10000003");
//         t.insert("A", "10000001");
//         t.insert("B", "10000002");
//         t.insert("D", "10000004");

//         auto inorder = t.printInorder();
//         auto preorder = t.printPreorder();
//         auto postorder = t.printPostorder();

//         REQUIRE(inorder[0]->name == "A");
//         REQUIRE(inorder[1]->name == "B");
//         REQUIRE(inorder[2]->name == "C");
//         REQUIRE(inorder[3]->name == "D");

//         REQUIRE(preorder.size() == 4);
//         REQUIRE(postorder.size() == 4);
//     }

//     SECTION("Rotations and balancing") {
//         tree rot1, rot2, rot3, rot4;

//         // Left
//         rot1.insert("A", "20000001");
//         rot1.insert("B", "20000002");
//         rot1.insert("C", "20000003");
//         REQUIRE(rot1.printLevelCount() <= 2);

//         // Right
//         rot2.insert("C", "30000003");
//         rot2.insert("B", "30000002");
//         rot2.insert("A", "30000001");
//         REQUIRE(rot2.printLevelCount() <= 2);

//         // LeftRight
//         rot3.insert("C", "40000003");
//         rot3.insert("A", "40000001");
//         rot3.insert("B", "40000002");
//         REQUIRE(rot3.printLevelCount() <= 2);

//         // RightLeft
//         rot4.insert("A", "50000001");
//         rot4.insert("C", "50000003");
//         rot4.insert("B", "50000002");
//         REQUIRE(rot4.printLevelCount() <= 2);
//     }

//     SECTION("Stress Test") {
//         tree t2;

//         for (int i = 1; i <= 50; i++) {
//             string id = to_string(30000000 + i);
//             string name = "User";
//             REQUIRE(t2.insert(name, id) == "successful");

//         }

//         REQUIRE(t2.printLevelCount() <= 6);
//     }
// }
