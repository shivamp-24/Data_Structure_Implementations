#include <iostream>
#include "DynamicVector.h"

void print_vector_stats(const Vector<int>& vec) {
    std::cout << ">> Size: " << vec.size() 
              << ", Capacity: " << vec.get_capacity() << std::endl;
    std::cout << "   Contents: ";
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n------------------------------------" << std::endl;
}

int main() {
    std::cout << "Creating a Vector<int>..." << std::endl;
    Vector<int> my_vector;
    print_vector_stats(my_vector);

    std::cout << "\nPushing first element (10)..." << std::endl;
    my_vector.push_back(10);
    print_vector_stats(my_vector);

    std::cout << "\nPushing second element (20)..." << std::endl;
    // This will trigger a reallocation because size (1) == capacity (1)
    my_vector.push_back(20);
    print_vector_stats(my_vector);

    std::cout << "\nPushing third element (30)..." << std::endl;
    // This will trigger another reallocation because size (2) == capacity (2)
    my_vector.push_back(30);
    print_vector_stats(my_vector);

    std::cout << "\nPushing fourth element (40)..." << std::endl;
    my_vector.push_back(40);
    print_vector_stats(my_vector);

    std::cout << "\nPushing fifth element (50)..." << std::endl;
    // This will trigger another reallocation because size (4) == capacity (4)
    my_vector.push_back(50);
    print_vector_stats(my_vector);

    std::cout << "\nRemoving last element with pop_back()..." << std::endl;
    my_vector.pop_back();
    print_vector_stats(my_vector);

    return 0;
}