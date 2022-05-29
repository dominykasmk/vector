#include <cstdlib>
#include <iostream>

#include "../headers/Vec.hpp"

int main() {
    
    Vec<int> v;
    v.push_back(1);

    for (auto i : v) {
        std::cout << i << ' ';
    }

    std::cout << '\n';
    return EXIT_SUCCESS;
}
