#ifndef HASH_TABLE_OA_H
#define HASH_TABLE_OA_H

#include <vector>
#include <functional>
#include <stdexcept>
#include <iostream>
#include <optional> // Used to cleanly handle search results

namespace CustomDataStructures {

template<typename K, typename V>
class HashTableOA {
private:
    // --- Private Inner Structures ---

    // An enum to represent the state of each bucket in the table.
    // This is crucial for handling deletions correctly in open addressing.
    enum class SlotState { EMPTY, OCCUPIED, DELETED };

    // Represents a single slot in the hash table.
    struct Slot {
        K key;
        V value;
        SlotState state = SlotState::EMPTY;
    };

    // --- Member Variables ---

    std::vector<Slot> table;
    size_t current_size; // Number of OCCUPIED slots
    std::hash<K> hash_function;

    /**
     * @brief Finds the index for a key. Returns the index of the key if it exists,
     * or the index of the first available (EMPTY or DELETED) slot.
     * @return The index of the slot.
     */
    size_t find_slot(const K& key) const {
        size_t index = hash_function(key) % table.size();
        size_t initial_index = index;

        while (table[index].state != SlotState::EMPTY) {
            // If we find an occupied slot with the correct key, return its index.
            if (table[index].state == SlotState::OCCUPIED && table[index].key == key) {
                return index;
            }
            // Move to the next slot (linear probing)
            index = (index + 1) % table.size();
            // If we've probed the entire table and returned to the start, the table is full.
            if (index == initial_index) {
                throw std::runtime_error("Hash table is full, cannot find slot.");
            }
        }
        return index; // Return index of the first EMPTY slot found
    }
    
    /**
     * @brief Rehashes the table when the load factor is too high.
     */
    void resize_and_rehash() {
        size_t old_capacity = table.size();
        size_t new_capacity = old_capacity * 2;
        
        std::cout << "[INFO] Load factor exceeded. Resizing from " << old_capacity 
                  << " to " << new_capacity << " slots." << std::endl;

        std::vector<Slot> old_table = std::move(table);
        table.assign(new_capacity, Slot()); // Re-initialize the table with new capacity
        current_size = 0;

        // Re-insert all OCCUPIED elements from the old table into the new one.
        for (const auto& slot : old_table) {
            if (slot.state == SlotState::OCCUPIED) {
                insert(slot.key, slot.value);
            }
        }
    }

public:
    explicit HashTableOA(size_t initial_capacity = 16) : current_size(0) {
        if (initial_capacity == 0) initial_capacity = 16;
        table.resize(initial_capacity);
    }
    
    ~HashTableOA() = default; // No raw pointers, default destructor is fine.

    // Disallow copying and moving for simplicity in this example.
    HashTableOA(const HashTableOA&) = delete;
    HashTableOA& operator=(const HashTableOA&) = delete;

    /**
     * @brief Inserts a key-value pair or updates if key exists.
     */
    void insert(const K& key, const V& value) {
        // Resize if the load factor (including DELETED slots as "used") is too high.
        if (static_cast<float>(current_size) / table.size() >= 0.7f) {
            resize_and_rehash();
        }

        size_t index = find_slot(key);
        
        // If the slot is not currently occupied, it's a new element.
        if (table[index].state != SlotState::OCCUPIED) {
            current_size++;
        }
        
        table[index].key = key;
        table[index].value = value;
        table[index].state = SlotState::OCCUPIED;
    }

    /**
     * @brief Searches for a key and returns its value.
     * @return An std::optional<V> containing the value if found, otherwise empty.
     */
    std::optional<V> search(const K& key) const {
        size_t index = find_slot(key);
        if (table[index].state == SlotState::OCCUPIED && table[index].key == key) {
            return table[index].value;
        }
        return std::nullopt; // Key not found
    }

    /**
     * @brief Removes a key-value pair by marking its slot as DELETED.
     */
    bool remove(const K& key) {
        size_t index = find_slot(key);
        if (table[index].state == SlotState::OCCUPIED && table[index].key == key) {
            table[index].state = SlotState::DELETED;
            current_size--; // We reduce the count of occupied slots
            return true;
        }
        return false;
    }

    size_t size() const { return current_size; }
    bool empty() const { return current_size == 0; }

    void print() const {
        std::cout << "--- Hash Table (Open Addressing) ---" << std::endl;
        std::cout << "Size: " << current_size << ", Capacity: " << table.size() << std::endl;
        for (size_t i = 0; i < table.size(); ++i) {
            std::cout << "Slot " << i << ": ";
            switch (table[i].state) {
                case SlotState::EMPTY:
                    std::cout << "[EMPTY]";
                    break;
                case SlotState::DELETED:
                    std::cout << "[DELETED]";
                    break;
                case SlotState::OCCUPIED:
                    std::cout << "[\"" << table[i].key << "\": " << table[i].value << "]";
                    break;
            }
            std::cout << std::endl;
        }
        std::cout << "------------------------------------" << std::endl;
    }
};

} // namespace CustomDataStructures

#endif // HASH_TABLE_OA_H