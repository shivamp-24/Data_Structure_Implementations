#include <iostream>
#include <string>
#include "HashTable_Chaining.h"

int main() {
    // Use the namespaced HashTable
    using CustomDataStructures::HashTable;

    // Start with a small capacity to easily see resizing.
    HashTable<std::string, int> student_scores(4); 

    std::cout << "Inserting key-value pairs..." << std::endl;
    student_scores.insert("Alice", 88);
    student_scores.insert("Bob", 92);
    student_scores.insert("Charlie", 75); // Should trigger a resize (3/4 = 0.75)
    
    student_scores.print();

    std::cout << "\nInserting another pair..." << std::endl;
    student_scores.insert("David", 100);
    // Note: The hash of "Eve" and "Alice" might collide depending on the STL implementation.
    // This will demonstrate the separate chaining in our custom list.
    student_scores.insert("Eve", 68);
    
    student_scores.print();

    std::cout << "\n--- Testing Search ---" << std::endl;
    int score;
    if (student_scores.search("Alice", score)) {
        std::cout << "Alice's score is: " << score << std::endl;
    } else {
        std::cout << "Alice not found." << std::endl;
    }

    if (student_scores.search("Frank", score)) {
        std::cout << "Frank's score is: " << score << std::endl;
    } else {
        std::cout << "Frank not found." << std::endl;
    }

    std::cout << "\n--- Testing Update ---" << std::endl;
    std::cout << "Updating Alice's score to 95." << std::endl;
    student_scores.insert("Alice", 95);
    if (student_scores.search("Alice", score)) {
        std::cout << "Alice's new score is: " << score << std::endl;
    }
    
    student_scores.print();

    std::cout << "\n--- Testing Remove ---" << std::endl;
    std::cout << "Removing Bob..." << std::endl;
    if (student_scores.remove("Bob")) {
        std::cout << "Bob removed successfully." << std::endl;
    } else {
        std::cout << "Bob not found for removal." << std::endl;
    }

    std::cout << "Current size: " << student_scores.size() << std::endl;
    student_scores.print();

    return 0;
}