#include <iostream>
#include "./headers/Vector.hpp"
#include <vector>

using std::cout;


int main() {

    Vector<int> c = {1, 2, 3};
    cout << "The Vector holds: ";
    for(const auto& el: c) cout << el << ' ';
    cout << '\n';
    c.resize(5);
    cout << "After resize up to 5: ";
    for(const auto& el: c) cout << el << ' ';
    cout << '\n';
    c.resize(2);
    cout << "After resize down to 2: ";
    for(const auto& el: c) cout << el << ' ';
    cout << '\n';
    c.resize(6, 4);
    cout << "After resize up to 6 (initializer = 4): ";
    for(const auto& el: c) cout << el << ' ';
    cout << '\n';
    return EXIT_SUCCESS;
}
