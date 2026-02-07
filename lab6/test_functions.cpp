#include <iostream>
#include "functions.h"
#include "test.h"

// TODO(student): declare other functions, as needed

void test_add() {
    assert_equal(add("9999", "1"), "10000");
    assert_equal(add("1", "0"), "1");
    assert_equal(add("0", "1"), "1");

    assert_equal(add("-5", "2"), "-3");
    assert_equal(add("5", "-2"), "3");
    assert_equal(add("-5", "-5"), "-10");

    assert_equal(add("0", "0"), "0");
    assert_equal(add("-0", "0"), "0");
    assert_equal(add("123", "456"), "579");
    // TODO(student): add tests for add
}

void test_subtract() {
    assert_equal(subtract("1000", "1"), "999");
    assert_equal(subtract("0", "1"), "-1");
    assert_equal(subtract("1", "0"), "1");

    assert_equal(subtract("-5", "2"), "-7");
    assert_equal(subtract("5", "-2"), "7");
    assert_equal(subtract("-5", "-2"), "-3");

    assert_equal(subtract("2", "5"), "-3");

    assert_equal(subtract("0", "0"), "0");
    assert_equal(subtract("-0", "0"), "0");
    // TODO(student): add tests for subtract
}

void test_multiply() {
    assert_equal(multiply("4", "100"), "400");
    assert_equal(multiply("1", "0"), "0");
    assert_equal(multiply("0", "1"), "0");

    assert_equal(multiply("-5", "3"), "-15");
    assert_equal(multiply("5", "-3"), "-15");
    assert_equal(multiply("-5", "-3"), "15");

    assert_equal(multiply("12", "12"), "144");
    assert_equal(multiply("99", "99"), "9801");

    assert_equal(multiply("0", "0"), "0");
    assert_equal(multiply("-0", "5"), "0");
    // TODO(student): add tests for multiply
}

// TODO(student): add tests for other functions, as needed

int main() {
    test_add();
    test_subtract();
    test_multiply();

    // TODO(student): invoke tests for other functions

    return 0;
}
