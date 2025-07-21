#include <iostream>
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"

int main() {
    std::cout << "--- Demonstrating Singly Linked List ---" << std::endl;
    SinglyLinkedList<int> sll;
    sll.push_back(10);
    sll.push_back(20);
    sll.push_back(30);
    sll.push_front(5);
    std::cout << "Initial list: ";
    sll.print();
    std::cout << "Size: " << sll.size() << ", Front: " << sll.front() << ", Back: " << sll.back() << std::endl;

    std::cout << "\nPopping from back (O(N) operation)..." << std::endl;
    sll.pop_back();
    std::cout << "List after pop_back: ";
    sll.print();

    std::cout << "Popping from front (O(1) operation)..." << std::endl;
    sll.pop_front();
    std::cout << "List after pop_front: ";
    sll.print();
    std::cout << "------------------------------------------\n" << std::endl;


    std::cout << "--- Demonstrating Doubly Linked List ---" << std::endl;
    DoublyLinkedList<int> dll;
    dll.push_back(10);
    dll.push_back(20);
    dll.push_back(30);
    dll.push_front(5);
    std::cout << "Initial list: ";
    dll.print();
    std::cout << "Size: " << dll.size() << ", Front: " << dll.front() << ", Back: " << dll.back() << std::endl;

    std::cout << "\nPopping from back (O(1) operation)..." << std::endl;
    dll.pop_back();
    std::cout << "List after pop_back: ";
    dll.print();

    std::cout << "Popping from front (O(1) operation)..." << std::endl;
    dll.pop_front();
    std::cout << "List after pop_front: ";
    dll.print();
    std::cout << "------------------------------------------" << std::endl;

    return 0;
}