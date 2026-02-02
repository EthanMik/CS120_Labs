#include <iostream>
#include <string>
#include "functions.h"

using std::string, std::cout, std::endl, std::cerr;

string add(const string& lhs, const string& rhs) {
    std::string l = lhs;
    std::string r = rhs;
    while (r.size() < l.size()) {
        r.insert(0, 1, '0');
    }
    while (l.size() < r.size()) {
        l.insert(0, 1, '0');
    }

    std::string sum{""};
    int carry = 0;

    for (int i = l.size() - 1; i >= 0; --i) {
        int eq = static_cast<int>(l.at(i) - '0') + static_cast<int>(r.at(i) - '0') + carry;
        carry = eq / 10;
        eq = eq % carry; 

        sum.insert(0, 1, static_cast<char>(eq));
    }
    
    cout << sum << endl;
    return sum;
}

string subtract(const string& lhs, const string& rhs) {
    // TODO(student): compute difference of arguments
    return "0";
}

string multiply(const string& lhs, const string& rhs) {
    // TODO(student): compute product of arguments
    return "0";
}
