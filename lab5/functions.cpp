// add more includes as necessary
#include "functions.h"
#include <string>
#include <iostream>
#include <sstream>

using std::cout, std::endl;

// deobfuscate a sentence
// arg 1: obfuscated sentence
// arg 2: deobfuscation details
// returns the deobfuscated sentence
std::string deobfuscate(std::string, std::string) {
    // TODO(student): give the function parameters descriptive names
    // TODO(student): implement the function
    return "";
}

// replace filter word with octothorpes (#)
// arg 1: sentence
// arg 2: filter word
// returns the filtered sentence
std::string wordFilter(std::string sentence, std::string filter) {
    size_t start = 0;
    std::string filter_text(filter.size(), '#');
    
    while (start < sentence.size()) {
        start = sentence.find(filter, start);
        if (start == std::string::npos) return sentence;
        sentence.replace(start, filter.size(), filter_text);
        start++;
    }
    return sentence;
}

// convert a string to a secure password
// arg 1: text
// returns a secure password based on the text
std::string passwordConverter(std::string) {
    // TODO(student): give the function parameter a descriptive name
    // TODO(student): implement the function
    return "";
}

// calculate the result of an arithmetic expression in words
// arg 1: expression using words
// returns an arithmetic equation using numerals and arithmetic symbols
std::string wordCalculator(std::string sentence) {

    return "";
}

// count the palindromes in the text
// arg 1: text
// returns the number of palindromes in the text
unsigned int palindromeCounter(std::string sentence) {
    std::stringstream ss(sentence);
    unsigned int counter = 0;

    std::string word;
    std::string reversed{};
    
    if (sentence.size() == 1 || sentence.size() == 0) return 1;

    while (ss >> word) {
        for (auto it = word.rbegin(); it != word.rend(); ++it) {
            reversed += *it;
        }

        if (word == reversed) {
            counter++;
        }

        reversed = "";
    }
    return counter;
}
