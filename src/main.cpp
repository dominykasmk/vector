#include <cstdlib>
#include <iostream>
#include <vector>
#include <climits>

#include "../headers/Vec.hpp"

using std::cout;
using std::vector;

int main() {
    
    Vec<int> v;
    v.reserve(20);
    cout << "capacity " << v.capacity() << '\n';
    cout << "empty? " << v.empty() << '\n';
    for (size_t i{}; i < 10; i++) {
        v.push_back(i);
        cout << v[i] << ' ';
    }

    v.shrink_to_fit();
    std::cout << '\n';


    return EXIT_SUCCESS;
}
