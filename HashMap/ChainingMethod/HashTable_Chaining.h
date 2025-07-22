#ifndef CUSTOM_HASH_TABLE_H
#define CUSTOM_HASH_TABLE_H

#include <vector>
#include <functional> //For hash
#include <stdexcept>
#include <iostream>

namespace CustomDataStructures {

template<typename K, typename V>
class HashTable {
private:
    // --- Private Inner Structures ---

    // Node for our custom singly linked list.
    // Each node stores one key-value pair.
    struct Node {
        K key;
        V value;
        Node* next;

        Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

    // --- Member Variables ---

    // The underlying storage is a vector of Node pointers.
    // Each element is a pointer to the head of a linked list (a chain).
    std::vector<Node*> table;
    size_t current_size;
    std::hash<K> hash_function;

    /**
     * @brief Deletes all nodes in a given chain to prevent memory leaks.
     */
    void clear_chain(Node* head) {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    /**
     * @brief Rehashes the table when the load factor is too high.
     */
    void resize_and_rehash() {
        size_t old_capacity = table.size();
        size_t new_capacity = old_capacity * 2;

        std::cout << "[INFO] Load factor exceeded. Resizing from " << old_capacity 
                  << " to " << new_capacity << " buckets." << std::endl;
        
        // Create a new table with the new capacity
        std::vector<Node*> new_table(new_capacity, nullptr);

        // Move all nodes from the old table to the new one
        for (size_t i = 0; i < old_capacity; ++i) {
            Node* current_node = table[i];
            while (current_node != nullptr) {
                // Find the new bucket index for the current node
                size_t new_index = hash_function(current_node->key) % new_capacity;

                // Unlink the node from the old chain
                Node* node_to_move = current_node;
                current_node = current_node->next;

                // Prepend the node to the chain in the new table
                node_to_move->next = new_table[new_index];
                new_table[new_index] = node_to_move;
            }
        }
        
        // The old table's nodes have been moved, not copied. We just need to swap the tables.
        table = std::move(new_table);
    }

public:
    /**
     * @brief Constructor.
     * @param initial_capacity The initial number of buckets.
     */
    explicit HashTable(size_t initial_capacity = 16) : current_size(0) {
        if (initial_capacity == 0) initial_capacity = 16;
        table.resize(initial_capacity, nullptr);
    }

    /**
     * @brief Destructor.
     * Cleans up all allocated nodes across all buckets.
     */
    ~HashTable() {
        for (Node* head : table) {
            clear_chain(head);
        }
    }

    // --- Rule of Five: Disallow Copying ---
    // For a complex class managing memory, it's good practice to either implement
    // deep copy semantics correctly or explicitly disallow copying.
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    HashTable(HashTable&&) = delete;
    HashTable& operator=(HashTable&&) = delete;


    /**
     * @brief Inserts a key-value pair or updates the value if the key already exists.
     */
    void insert(const K& key, const V& value) {
        if (static_cast<float>(current_size) / table.size() > 0.75f) {
            resize_and_rehash();
        }

        size_t index = hash_function(key) % table.size();
        Node* head = table[index];

        // Traverse the chain to check if the key already exists
        Node* current = head;
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value; // Update existing key
                return;
            }
            current = current->next;
        }

        // If key not found, create a new node and prepend it to the chain
        Node* newNode = new Node(key, value);
        newNode->next = head;
        table[index] = newNode;
        current_size++;
    }

    /**
     * @brief Finds a value by its key.
     */
    bool search(const K& key, V& value_out) const {
        size_t index = hash_function(key) % table.size();
        Node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                value_out = current->value;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    /**
     * @brief Removes a key-value pair from the table.
     */
    bool remove(const K& key) {
        size_t index = hash_function(key) % table.size();
        Node* current = table[index];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) { // The node to remove is the head of the chain
                    table[index] = current->next;
                } else { // The node to remove is in the middle or at the end
                    prev->next = current->next;
                }
                delete current;
                current_size--;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false; // Key not found
    }

    size_t size() const { return current_size; }
    bool empty() const { return current_size == 0; }

    void print() const {
        std::cout << "--- Hash Table Contents ---" << std::endl;
        std::cout << "Size: " << current_size << ", Capacity: " << table.size() << std::endl;
        for (size_t i = 0; i < table.size(); ++i) {
            std::cout << "Bucket " << i << ": ";
            Node* current = table[i];
            if (current == nullptr) {
                std::cout << "[empty]" << std::endl;
            } else {
                while (current != nullptr) {
                    std::cout << "[\"" << current->key << "\": " << current->value << "] -> ";
                    current = current->next;
                }
                std::cout << "nullptr" << std::endl;
            }
        }
        std::cout << "--------------------------" << std::endl;
    }
};

} // namespace CustomDataStructures

#endif // CUSTOM_HASH_TABLE_H