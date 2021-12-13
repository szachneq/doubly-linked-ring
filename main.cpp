#include <iostream>
#include <string>
#include "ring.h"

int main() {
    Ring<std::string, int> first;
    first.push_end("uno", 1);
    first.push_end("due", 2);
    first.push_end("tre", 3);
    first.push_end("quattro", 4);
    std::cout << "First ring:" << std::endl;
    std::cout << first;

    Ring<std::string, int> second;
    second.push_end("bir", 1);
    second.push_end("iki", 2);
    second.push_end("uc", 3);
    second.push_end("dort", 4);
    second.push_end("bes", 5);
    std::cout << "Second ring:" << std::endl;
    std::cout << second;

    Ring<std::string, int> result = shuffle(first, 1, second, 2, 3);
    std::cout << "Shuffle:" << std::endl;
    std::cout << result;
    return 0;
}
