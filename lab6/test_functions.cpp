#include <iostream>
#include "functions.h"
#include "test.h"

// TODO(student): declare other functions, as needed

void test_add() {
    add("1", "1");
    // assert_equal(add("1", "1"), "2");
    // TODO(student): add tests for add
}

void test_subtract() {
    assert_equal(subtract("1", "1"), "0");
    // TODO(student): add tests for subtract
}

void test_multiply() {
    assert_equal(multiply("1", "1"), "1");
    // TODO(student): add tests for multiply
}

// TODO(student): add tests for other functions, as needed

int main() {
    test_add();
    // test_subtract();
    // test_multiply();

    // TODO(student): invoke tests for other functions

    return 0;
}
