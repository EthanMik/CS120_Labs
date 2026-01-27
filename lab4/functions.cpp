#include <iostream>
#include "functions.h"

// returns the boolean value true
// if and only if 1,000 <= a <= b < 1,000,000,000,000
bool is_valid_range(int64_t a, int64_t b) {
    if (a <= b && a >= 1000 && b >= 1000 && a < 1000000000000 && b < 1000000000000) return true;
    return false;
}

// returns 'p' if number is a plateau,
//         'b' if number is a basin,
//         'n' if number is neither
char classify_geo_type(int64_t number) {    
    int nextDigit = number % 10;
    int prevDigit = nextDigit;
    number /= 10;

    bool platSame = false;
    int platMiddle = -1;
    bool platFailed = false;
    int platIncreasing = 0;
    int platDecreasing = 0;

    bool basSame = false;
    int basMiddle = -1;
    bool basFailed = false;
    int basIncreasing = 0;
    int basDecreasing = 0;

    char type = 'n';

    while (number > 0) {
        nextDigit = number % 10;

        if (nextDigit > prevDigit && platDecreasing == 0 && !platSame) {
            platIncreasing++;            
        } else if (nextDigit == prevDigit && platIncreasing > 0 && (!platSame || nextDigit == platMiddle)) {
            platSame = true;
            platMiddle = nextDigit;
        } else if (nextDigit < prevDigit && platSame && platIncreasing > 0) {
            platDecreasing++;
        } else {
            platFailed = true;
        }
        
        if (nextDigit < prevDigit && basIncreasing == 0 && !basSame) {
            basDecreasing++;            
        } else if (nextDigit == prevDigit && basDecreasing > 0 && (!basSame || nextDigit == basMiddle)) {
            basSame = true;
            basMiddle = nextDigit;
        } else if (nextDigit > prevDigit && basSame && basDecreasing > 0) {
            basIncreasing++;
        } else {
            basFailed = true;
        }
        
        prevDigit = nextDigit;
        number /= 10;
    }
    
    if (!platFailed && platDecreasing > 0 && platIncreasing > 0) type = 'p';
    if (!basFailed && basDecreasing > 0 && basIncreasing > 0) type = 'b';
    
    return type;
}

// returns how many numbers in the range [a, b] are plateaus and basins
plateaus_and_basins count_pb_numbers(int64_t a, int64_t b) {
    int number_of_plateaus = 0;
    int number_of_basins = 0;

    while (a <= b) {
        const char type = classify_geo_type(a);
        switch (type) {
            case 'p': number_of_plateaus++; break;
            case 'b': number_of_basins++; break;
            default: break;
        }

        a++;
    }

    return {number_of_plateaus, number_of_basins};
}
