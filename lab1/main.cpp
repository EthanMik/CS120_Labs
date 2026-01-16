#include <iostream>
#include "foo.h"

int main() {
    Foo foo(12);
    foo.printFoo();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}