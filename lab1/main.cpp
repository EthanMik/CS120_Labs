#include <iostream>
#include <vector>

using std::cout, std::endl;

bool has_odd_differences(unsigned long long n) {

    if (n / 10 < 1) return true;

    while (n > 0) {
        const auto pair1 = n % 10;
        n /= 10;

        const auto pair2 = n % 10;
        if ((pair2 - pair1) % 2 == 0) return false; 

        n /= 10;
    }

    return true;
}

int main() {
    std::vector<int> i({1, 2, 3});

    std::vector<int> newi(i.rbegin(), i.rend());

    for (const auto n : newi) {
        cout << n << endl;
    }
    return 0;
}