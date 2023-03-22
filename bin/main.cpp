#include <lib/number.h>
#include <iostream>

int main() {
    uint2022_t a = from_string("12345354");
    uint2022_t b = from_string("555");

    uint2022_t res = a / b;

    std::cout << from_string("0");


    return 0;
}
