// this file is provided. do not modify. do not submit.
#ifndef PROVIDED_TEST_H_
#define PROVIDED_TEST_H_

#include <iostream>
#include <exception>
#include <string>

using std::cout, std::endl, std::string;

// test whether `actual == expected`
// exit with status code 1 if not equal
#define assert_equal(actual, expected) {\
string function = __func__;\
string line = std::to_string(__LINE__);\
string location = function + ":" + line;\
string expression = #actual" == "#expected;\
string location_and_expression = location + ": " + expression;\
try {\
    string actual_value = actual;\
    string expected_value = expected;\
    if (actual_value == expected_value) {\
        cout\
        << "[PASS] " << location_and_expression\
        << '\n';\
    } else {\
        cout\
        << "[FAIL] " << location_and_expression\
        << "\n    actual: \"" << actual_value << '"'\
        << "\n  expected: \"" << expected_value << '"'\
        << '\n';\
        exit(1);\
    }\
} catch (const std::exception& err) {\
    cout\
    << "[FAIL] " << location_and_expression\
    << "\n  caught unexpected exception"\
    << "\n  what: " << err.what()\
    << '\n';\
    exit(1);\
} catch (...) {\
    cout\
    << "[FAIL] " << location_and_expression\
    << "\n  caught unexpected non-standard exception"\
    << '\n';\
    exit(1);\
}\
}

#endif  // PROVIDED_TEST_H_
