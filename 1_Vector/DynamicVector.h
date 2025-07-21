#ifndef DYNAMIC_VECTOR_H
#define DYNAMIC_VECTOR_H

#include <iostream>
#include <stdexcept> // Required for std::out_of_range

/**
 * @brief A simplified implementation of a dynamic array, similar to std::vector.
 * 
 * This class manages a dynamic array of elements of type T. It handles memory
 * automatically, growing the internal array as needed.
 * @tparam T The type of elements to be stored.
 */
template<typename T>
class Vector {
private:
    T* arr;             // Pointer to the underlying dynamically allocated array
    int current_size;   // Number of elements currently stored in the vector
    int capacity;       // Total storage capacity of the underlying array

public:
    // --- Constructors and Destructor ---

    /**
     * @brief Default constructor.
     * Initializes an empty vector with an initial capacity of 1.
     */
    Vector() : arr(new T[1]), current_size(0), capacity(1) {}

    /**
     * @brief Destructor.
     * Frees the dynamically allocated memory for the array.
     */
    ~Vector() {
        delete[] arr;
    }

    // --- Core Functionality ---

    /**
     * @brief Appends a new element to the end of the vector.
     * This is an amortized O(1) operation. If the current capacity is full,
     * it triggers a reallocation, which is an O(N) operation.
     * @param data The element to add.
     */
    void push_back(const T& data) {
        // Key logic: Check if the array is full.
        if (current_size == capacity) {
            std::cout << "[INFO] Capacity reached (" << capacity << "). Doubling size..." << std::endl;
            
            // 1. Allocate a new array with double the capacity.
            int new_capacity = 2 * capacity;
            T* new_arr = new T[new_capacity];

            // 2. Copy all elements from the old array to the new one.
            for (int i = 0; i < current_size; ++i) {
                new_arr[i] = arr[i];
            }

            // 3. Deallocate the old array's memory.
            delete[] arr;

            // 4. Update the internal pointer and capacity.
            arr = new_arr;
            capacity = new_capacity;
        }

        // Add the new element to the end and increment the size.
        arr[current_size] = data;
        current_size++;
    }

    /**
     * @brief Removes the last element from the vector.
     * Does not shrink the underlying array.
     */
    void pop_back() {
        if (current_size > 0) {
            current_size--;
        }
    }

    // --- Element Access ---

    /**
     * @brief Accesses the element at a specific index with bounds checking.
     * @param index The index of the element to access.
     * @return A reference to the element at the specified index.
     * @throws std::out_of_range if the index is out of bounds.
     */
    T& at(int index) {
        if (index < 0 || index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    /**
     * @brief Accesses the element at a specific index without bounds checking.
     * @param index The index of the element to access.
     * @return A reference to the element at the specified index.
     */
    T& operator[](int index) {
        return arr[index];
    }

    /**
     * @brief Const version of operator[] for read-only access.
     */
    const T& operator[](int index) const {
        return arr[index];
    }

    // --- Capacity and Size ---

    /**
     * @brief Returns the number of elements in the vector.
     * @return The number of elements.
     */
    int size() const {
        return current_size;
    }

    /**
     * @brief Returns the storage capacity of the vector.
     * @return The capacity.
     */
    int get_capacity() const {
        return capacity;
    }

    /**
     * @brief Checks if the vector is empty.
     * @return true if the vector is empty, false otherwise.
     */
    bool empty() const {
        return current_size == 0;
    }

    // --- Rule of Three (for proper memory management) ---

    /**
     * @brief Copy constructor for deep copying.
     */
    Vector(const Vector& other) {
        current_size = other.current_size;
        capacity = other.capacity;
        arr = new T[capacity];
        for (int i = 0; i < current_size; ++i) {
            arr[i] = other.arr[i];
        }
    }

    /**
     * @brief Copy assignment operator for deep copying.
     */
    Vector& operator=(const Vector& other) {
        if (this == &other) { // Handle self-assignment
            return *this;
        }

        delete[] arr; // Free existing memory

        current_size = other.current_size;
        capacity = other.capacity;
        arr = new T[capacity];
        for (int i = 0; i < current_size; ++i) {
            arr[i] = other.arr[i];
        }
        return *this;
    }
};

#endif // DYNAMIC_VECTOR_H