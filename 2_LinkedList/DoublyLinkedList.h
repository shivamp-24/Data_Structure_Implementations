#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>
#include <stdexcept>

template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& val) : data(val), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    // --- The Rule of Three ---

    ~DoublyLinkedList() {
        while (!empty()) {
            pop_front();
        }
    }

    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), count(0) {
        for (Node* current = other.head; current != nullptr; current = current->next) {
            push_back(current->data);
        }
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this == &other) {
            return *this;
        }
        while (!empty()) {
            pop_front();
        }
        for (Node* current = other.head; current != nullptr; current = current->next) {
            push_back(current->data);
        }
        return *this;
    }

    // --- Core Operations ---

    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        count++;
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
    }

    void pop_front() {
        if (empty()) {
            throw std::out_of_range("Cannot pop_front from an empty list.");
        }
        Node* oldHead = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete oldHead;
        count--;
    }

    // Removes the element from the back. O(1)
    // This is the primary advantage of a doubly linked list.
    void pop_back() {
        if (empty()) {
            throw std::out_of_range("Cannot pop_back from an empty list.");
        }
        Node* oldTail = tail;
        if (head == tail) { // Only one element
            head = tail = nullptr;
        } else {
            // The tail's `prev` pointer gives us O(1) access to the new tail.
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete oldTail;
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
        std::cout << "nullptr <- ";
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) {
                std::cout << " <-> ";
            }
            current = current->next;
        }
        std::cout << " -> nullptr" << std::endl;
    }
};

#endif // DOUBLY_LINKED_LIST_H