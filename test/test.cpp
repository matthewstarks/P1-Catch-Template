//Matthew Starks UFID: 85876541
#define CATCH_CONFIG_MAIN
#include "catch/catch_amalgamated.hpp"
#include "../src/tree.cpp"
#include <vector>
#include <string>

TEST_CASE("AVL Tree: Full Coverage Using Public API", "[AVL]"){
    tree t;

    SECTION("Insertions"){
        // Valid
        REQUIRE_NOTHROW(t.insert("Alice", "10000001"));
        REQUIRE_NOTHROW(t.insert("Bob", "10000002"));
        REQUIRE_NOTHROW(t.insert("Charlie", "10000003"));

        // Invalid ID
        REQUIRE_THROWS(t.insert("David", "12345"));
        REQUIRE_THROWS(t.insert("Eve", "abcd1234"));

        // Invalid Name
        REQUIRE_THROWS(t.insert("F4nk", "10000004"));
        REQUIRE_THROWS(t.insert("", "10000005"));

        // Duplicate ID
        REQUIRE_NOTHROW(t.insert("Duplicate", "10000001")); // Should print unsuccessful
    }

    SECTION("Searches"){
        t.insert("Alice", "10000001");
        t.insert("Bob", "10000002");
        t.insert("Charlie", "10000003");
        t.insert("Alice", "10000004"); // Duplicate name

        // Search by existing ID
        REQUIRE_NOTHROW(t.search("10000001"));
        REQUIRE_NOTHROW(t.search("10000004"));

        // Search by non-existent ID
        REQUIRE_NOTHROW(t.search("99999999")); // prints unsuccessful

        // Search by name
        REQUIRE_NOTHROW(t.search("Alice")); // should find 10000001 and 10000004
        REQUIRE_NOTHROW(t.search("Charlie")); // should find 10000003
        REQUIRE_NOTHROW(t.search("Noname")); // prints unsuccessful
    }

    SECTION("Deletions"){
        t.insert("Alice", "10000001");
        t.insert("Bob", "10000002");
        t.insert("Charlie", "10000003");
        t.insert("David", "10000004");
        t.insert("Eve", "10000005");

        // Remove leaf
        REQUIRE_NOTHROW(t.remove("10000005")); // Eve

        // Remove node with one child
        REQUIRE_NOTHROW(t.remove("10000004")); // David

        // Remove node with two children
        REQUIRE_NOTHROW(t.remove("10000002")); // Bob

        // Remove non-existent
        REQUIRE_NOTHROW(t.remove("99999999")); // prints unsuccessful
    }

    SECTION("removeInorder"){
        t.insert("Alice", "10000001");
        t.insert("Bob", "10000002");
        t.insert("Charlie", "10000003");

        // Remove first node
        REQUIRE_NOTHROW(t.removeInorder(0)); // Alice

        // Remove last node
        REQUIRE_NOTHROW(t.removeInorder(1)); // Charlie

        // Remove out-of-bounds
        REQUIRE_NOTHROW(t.removeInorder(5)); // prints unsuccessful
    }

    SECTION("Traversals"){
        t.insert("Alice", "10000001");
        t.insert("Bob", "10000002");
        t.insert("Charlie", "10000003");
        t.insert("David", "10000004");
        t.insert("Eve", "10000005");

        // Just ensure public traversal functions run without crashing
        REQUIRE_NOTHROW(t.printInorder());
        REQUIRE_NOTHROW(t.printPreorder());
        REQUIRE_NOTHROW(t.printPostorder());
    }

    SECTION("Rotations & Balancing"){
        tree t2;

        // Insert ascending to force right rotations
        t2.insert("A", "20000001");
        t2.insert("B", "20000002");
        t2.insert("C", "20000003");
        t2.insert("D", "20000004");
        t2.insert("E", "20000005");

        // Insert descending to force left rotations
        tree t3;
        t3.insert("E", "30000005");
        t3.insert("D", "30000004");
        t3.insert("C", "30000003");
        t3.insert("B", "30000002");
        t3.insert("A", "30000001");

        // Traversals should execute fine (inorder sorted by ID)
        REQUIRE_NOTHROW(t2.printInorder());
        REQUIRE_NOTHROW(t2.printPreorder());
        REQUIRE_NOTHROW(t2.printPostorder());

        REQUIRE_NOTHROW(t3.printInorder());
        REQUIRE_NOTHROW(t3.printPreorder());
        REQUIRE_NOTHROW(t3.printPostorder());
    }

    SECTION("Edge Case Inserts"){
        // Large number of nodes
        for (int i = 1; i <= 100; ++i) {
            std::string name = "Name";
            std::string id = std::to_string(10000000 + i);
            REQUIRE_NOTHROW(t.insert(name, id));
        }

        // Duplicate names but different IDs
        REQUIRE_NOTHROW(t.insert("Alice", "20000001"));
        REQUIRE_NOTHROW(t.insert("Alice", "20000002"));
    }

    SECTION("Edge Case Searches"){
        // Searching for many duplicates
        for (int i = 1; i <= 100; ++i) {
            std::string id = std::to_string(10000000 + i);
            REQUIRE_NOTHROW(t.search(id));
        }

        // Non-existent
        REQUIRE_NOTHROW(t.search("55555555"));
    }

    SECTION("Edge Case Removals"){
        // Remove all inserted IDs
        for (int i = 1; i <= 100; ++i) {
            std::string id = std::to_string(10000000 + i);
            REQUIRE_NOTHROW(t.remove(id));
        }

        // Remove again should be unsuccessful
        for (int i = 1; i <= 100; ++i) {
            std::string id = std::to_string(10000000 + i);
            REQUIRE_NOTHROW(t.remove(id));
        }
    }
}
