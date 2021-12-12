#include <iostream>
#include <string>
#include "ring.h"

int main() {
    Ring<std::string, double> ring;
    auto insert_iter = ring.insert(ring.begin(), std::string("One"), 2.0);
    insert_iter = ring.insert(ring.begin(), std::string("Three"), 4.0);
    std::cout << ring;
    return 0;
}
