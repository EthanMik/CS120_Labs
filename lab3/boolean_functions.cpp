#include <iostream>
#include <string>
#include "boolean_functions.h"

void printNOT() {
    std::cout << "--- printNOT ---" << std::endl;

    std::cout << " x | NOT x" << std::endl;
    std::cout << "---+-------" << std::endl;
    std::cout << " 0 |   1" << std::endl;
    std::cout << " 1 |   0" << std::endl;

    std::cout << std::endl;
}

void printOR() {
    std::cout << "--- printOR ---" << std::endl;

    std::cout << " x | y | x OR y" << std::endl;
    std::cout << "---+---+--------" << std::endl;
    std::cout << " 0 | 0 |   0" << std::endl;
    std::cout << " 0 | 1 |   1" << std::endl;
    std::cout << " 1 | 0 |   1" << std::endl;
    std::cout << " 1 | 1 |   1" << std::endl;

    std::cout << std::endl;
}

void printAND() {
    std::cout << "--- printAND ---" << std::endl;

    std::cout << " x | y | x AND y" << std::endl;
    std::cout << "---+---+---------" << std::endl;
    std::cout << " 0 | 0 |    0" << std::endl;
    std::cout << " 0 | 1 |    0" << std::endl;
    std::cout << " 1 | 0 |    0" << std::endl;
    std::cout << " 1 | 1 |    1" << std::endl;

    std::cout << std::endl;
}

void printXOR() {
    std::cout << "--- printXOR ---" << std::endl;

    std::cout << " x | y | x XOR y" << std::endl;
    std::cout << "---+---+---------" << std::endl;
    std::cout << " 0 | 0 |    0" << std::endl;
    std::cout << " 0 | 1 |    1" << std::endl;
    std::cout << " 1 | 0 |    1" << std::endl;
    std::cout << " 1 | 1 |    0" << std::endl;

    std::cout << std::endl;
}

bool booleanLogic1(bool x, bool y, bool z) {
    std::cout << "--- booleanLogic1 ---" << std::endl;

    bool value = x || y || z;

    std::cout << std::boolalpha;
    std::cout << x << " OR " << y << " OR " << z << " = ";
    std::cout << value << std::endl;

    std::cout << std::endl;
    return value;
}

bool booleanLogic2(bool x, bool y, bool z) {
    std::cout << "--- booleanLogic2 ---" << std::endl;

    bool value = x && y && z;

    std::cout << std::boolalpha;
    std::cout << x << " AND " << y << " AND " << z << " = ";
    std::cout << value << std::endl;

    std::cout << std::endl;
    return value;
}

bool booleanLogic3(bool x, bool y, bool z) {
    std::cout << "--- booleanLogic3 ---" << std::endl;

    bool value = x ^ y ^ z;

    std::cout << std::boolalpha;
    std::cout << x << " XOR " << y << " XOR " << z << " = ";
    std::cout << value << std::endl;

    std::cout << std::endl;
    return value;
}

// this function should count the number of letters in a string
unsigned int countLetters(std::string str) {
    std::cout << "--- countLetters ---" << std::endl;

    unsigned int count = 0;
    for (unsigned int i = 0; i < str.size(); ++i) {
        if (isalpha((str.at(i)))) {
            count++;
        }
    }
    return count;
}

// this function should implement the mystery function
bool f(bool x, bool y, bool z) {
    std::cout << "--- f ---" << std::endl;

    bool boolVal = (!x && !y && z) || (!x && y && !z) || (!x && y && z) || (x && !y && !z) || (x && y && z);

    return boolVal;
}

// set the values of w, x, y, and z
// you'll learn what bool& in the function signature means later this semester
void setAssignments(bool& w, bool& x, bool& y, bool& z) {
    std::cout << "--- setAssignments ---" << std::endl;

    w = false;
    x = true;
    y = true;
    z = true;
}
