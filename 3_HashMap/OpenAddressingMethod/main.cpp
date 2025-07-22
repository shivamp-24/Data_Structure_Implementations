#include <iostream>
#include <string>
#include <optional>
#include "HashTableOpenAddressing.h"

int main() {
    using CustomDataStructures::HashTableOA;

    HashTableOA<std::string, int> student_scores(5); // Small capacity to show probing

    student_scores.insert("Alice", 88);
    student_scores.insert("Bob", 92);
    student_scores.insert("Charlie", 75);
    
    // This should trigger a resize because 3/5 = 0.6 is close to our 0.7 threshold
    // and the next insert will cross it.
    std::cout << "Before resize:" << std::endl;
    student_scores.print();

    student_scores.insert("David", 100); 
    std::cout << "After resize:" << std::endl;
    student_scores.print();

    std::cout << "\n--- Testing Search ---" << std::endl;
    if (auto score = student_scores.search("Charlie")) {
        std::cout << "Charlie's score is: " << *score << std::endl;
    }
    if (auto score = student_scores.search("Frank")) {
        std::cout << "Frank's score is: " << *score << std::endl;
    } else {
        std::cout << "Frank not found." << std::endl;
    }

    std::cout << "\n--- Testing Remove ---" << std::endl;
    std::cout << "Removing Bob..." << std::endl;
    student_scores.remove("Bob");
    student_scores.print(); // Note that Bob's slot is now [DELETED]

    std::cout << "Searching for Charlie (should still work by probing past DELETED)..." << std::endl;
    if (auto score = student_scores.search("Charlie")) {
        std::cout << "Charlie's score is still found: " << *score << std::endl;
    }

    std::cout << "\nInserting new element 'Eve' (should occupy the DELETED slot)..." << std::endl;
    student_scores.insert("Eve", 68);
    student_scores.print();

    return 0;
}