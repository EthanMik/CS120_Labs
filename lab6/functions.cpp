#include <iostream>
#include <string>
#include "functions.h"

using std::string, std::cout, std::endl, std::cerr;

string removeZeros(string str) {
    while (str.size() > 1 && str[0] == '0') {
        str.erase(0, 1);
    }
    return str;
}

string add(const string& lhs, const string& rhs) {
    if (lhs == "-0") return add("0", rhs);
    if (rhs == "-0") return add(lhs, "0");

    
    if (lhs[0] == '-' && rhs[0] != '-') return subtract(rhs, lhs.substr(1));
    if (rhs[0] == '-' && lhs[0] != '-') return subtract(lhs, rhs.substr(1));

    bool neg = (lhs[0] == '-' && rhs[0] == '-');

    string l = neg ? lhs.substr(1) : lhs;
    string r = neg ? rhs.substr(1) : rhs;

    while (r.size() < l.size()) {
        r.insert(0, 1, '0');
    }
    while (l.size() < r.size()) {
        l.insert(0, 1, '0');
    }

    std::string sum{ "" };
    int carry = 0;

    for (int i = l.size() - 1; i >= 0; --i) {
        int eq = static_cast<int>(l.at(i) - '0') + static_cast<int>(r.at(i) - '0') + carry;
        carry = eq / 10;
        eq = eq % 10;
        sum.insert(0, 1, static_cast<char>(eq + '0'));
    }

    if (carry > 0) sum.insert(0, 1, static_cast<char>(carry + '0'));
    sum = removeZeros(sum);
    if (neg && sum != "0")
        sum.insert(0, "-");

    return sum;
}

string subtract(const string& lhs, const string& rhs) {
    if (lhs == "-0") return subtract("0", rhs);
    if (rhs == "-0") return subtract(lhs, "0");

    if (lhs[0] == '-' && rhs[0] == '-') return subtract(rhs.substr(1), lhs.substr(1));

    if (lhs[0] == '-') return "-" + add(lhs.substr(1), rhs);

    if (rhs[0] == '-') return add(lhs, rhs.substr(1));

    if (lhs.size() < rhs.size() || (lhs.size() == rhs.size() && lhs < rhs))
        return "-" + subtract(rhs, lhs);

    std::string l = lhs;
    std::string r = rhs;
    while (r.size() < l.size()) {
        r.insert(0, 1, '0');
    }
    while (l.size() < r.size()) {
        l.insert(0, 1, '0');
    }

    std::string sum{ "" };
    int carry = 0;

    for (int i = l.size() - 1; i >= 0; --i) {
        int l_int = static_cast<int>(l.at(i) - '0') - carry, r_int = static_cast<int>(r.at(i) - '0');

        if (l_int < r_int) {
            l_int += 10;
            carry = 1;
        } else {
            carry = 0;
        }

        int eq = l_int - r_int;

        sum.insert(0, 1, static_cast<char>(eq + '0'));
    }

    return removeZeros(sum);
}

string multiply(const string& lhs, const string& rhs) {
    if (lhs == "-0") return multiply("0", rhs);
    if (rhs == "-0") return multiply(lhs, "0");

    
    bool neg = false;
    std::string l = lhs;
    std::string r = rhs;
    
    if (l[0] == '-') { neg = !neg; l = l.substr(1); }
    if (r[0] == '-') { neg = !neg; r = r.substr(1); }

    if (l == "0" || r == "0") return "0";
    
    std::string result{ "" };
    int zeros = 0;

    for (int i = l.size() - 1; i >= 0; --i) {
        int carry = 0;
        int l_int = static_cast<int>(l.at(i) - '0');
        std::string sum{ "" };

        for (int j = r.size() - 1; j >= 0; --j) {
            int r_int = static_cast<int>(r.at(j) - '0');

            int eq = l_int * r_int + carry;
            carry = eq / 10;
            eq = eq % 10;
            sum.insert(0, 1, static_cast<char>(eq + '0'));
        }
        if (carry > 0)
            sum.insert(0, 1, static_cast<char>(carry + '0'));

        for (int k = 0; k < zeros; ++k)
            sum.push_back('0');

        result = add(result, sum);

        zeros++;
    }

    while (result.size() > 1 && result[0] == '0') {
        result.erase(0, 1);
    }

    result = removeZeros(result);
    if (neg && result != "0")
        result.insert(0, "-");
    return result;
}
