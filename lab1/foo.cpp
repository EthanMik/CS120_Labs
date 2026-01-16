#include "foo.h"
#include <iostream>

Foo::Foo(double number) : 
    number(number) 
{};

void Foo::printFoo() {
    std::cout << number << "\n";
}