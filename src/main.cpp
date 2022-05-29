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

    v[0] = 5;
    cout << "front " << v.front() << '\n';

    cout << "back " << v.back() << '\n';

    cout << "at 7 " << v.at(7) << '\n';


    cout << "last element " << v.back() << '\n';
    cout << "size " << v.size() << '\n';
    cout << "capacity " << v.capacity() << '\n';
    v.pop_back();
    cout << "last element " << v.back() << '\n';
    cout << "size " << v.size() << '\n';
    cout << "capacity " << v.capacity() << '\n';

    return EXIT_SUCCESS;
}
