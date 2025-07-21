#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <iostream>
#include <stdexcept>

template<typename T>
class SinglyLinkedList {
private:
    // Private inner struct for the Node.
    // This is good practice as the user of the list doesn't need to know about Node's structure.
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

public:
    // Default constructor
    SinglyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    // --- The Rule of Three: Destructor, Copy Constructor, Copy Assignment ---

    // 1. Destructor: Cleans up all nodes to prevent memory leaks.
    ~SinglyLinkedList() {
        while (head != nullptr) {
            pop_front();
        }
    }

    // 2. Copy Constructor: Performs a deep copy of the list.
    SinglyLinkedList(const SinglyLinkedList& other) : head(nullptr), tail(nullptr), count(0) {
        // Walk through the other list and push_back each element to this one.
        for (Node* current = other.head; current != nullptr; current = current->next) {
            push_back(current->data);
        }
    }

    // 3. Copy Assignment Operator
    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this == &other) { // Handle self-assignment
            return *this;
        }
        // Clear the current list
        while (!empty()) {
            pop_front();
        }
        // Copy elements from the other list
        for (Node* current = other.head; current != nullptr; current = current->next) {
            push_back(current->data);
        }
        return *this;
    }

    // --- Core Operations ---

    // Adds an element to the front of the list. O(1)
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        count++;
    }

    // Adds an element to the end of the list. O(1) thanks to the tail pointer.
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    // Removes the element from the front. O(1)
    void pop_front() {
        if (empty()) {
            throw std::out_of_range("Cannot pop_front from an empty list.");
        }
        Node* oldHead = head;
        head = head->next;
        delete oldHead;
        count--;
        if (empty()) {
            tail = nullptr; // Important: if list becomes empty, update tail
        }
    }

    // Removes the element from the back. O(N)
    // This is the key trade-off for a singly linked list.
    void pop_back() {
        if (empty()) {
            throw std::out_of_range("Cannot pop_back from an empty list.");
        }
        if (head == tail) { // Only one element
            delete head;
            head = tail = nullptr;
        } else {
            // To delete the tail, we must find the node BEFORE it.
            // This requires traversing the list from the head. O(N) operation.
            Node* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        count--;
    }

    // --- Accessors ---

    T& front() const {
        if (empty()) throw std::out_of_range("List is empty.");
        return head->data;
    }

    T& back() const {
        if (empty()) throw std::out_of_range("List is empty.");
        return tail->data;
    }

    // --- Utility Functions ---

    int size() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
};

#endif // SINGLY_LINKED_LIST_H