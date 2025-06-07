#include <string>
#include <iostream>

size_t folding_string_hash(std::string const& s, size_t max) {
    size_t hash = 0;
    for (char c : s) {
        hash += int(c) % max;
    }
    return hash;
}

size_t folding_string_ordered_hash(std::string const& s, size_t max) {
    size_t hash = 0;
    for (size_t i = 0; i < s.size(); i++) {
        hash = (hash + int(s[i] * (i + 1))) % max;
    }
    return hash;
}

size_t polynomial_rolling_hash(const std::string& s, size_t p, size_t max) {
    size_t hash = 0;
    size_t p_pow = p;

    for (size_t i = 0; i < s.size(); i++) {
        hash = (hash + int(s[i] * p_pow)) % max;
        p_pow = (p_pow * p) % max;
    }

    return hash;
}

int main() {
    std::cout << "> Folding String Hash" << std::endl;
    std::cout << folding_string_hash("Hello, World!", 4096) << std::endl << std::endl;

    std::cout << "> Folding String Ordered Hash" << std::endl;
    std::cout << folding_string_ordered_hash("Hello, World!", 4096) << std::endl << std::endl;

    std::cout << "> Polynomial Rolling Hash" << std::endl;
    std::cout << polynomial_rolling_hash("Hello, World!", 31, 1e9 + 9) << std::endl << std::endl;

    return 0;
}
