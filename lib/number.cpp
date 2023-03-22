#include "number.h"
#include <string>
#include <iomanip>

uint2022_t from_uint(uint32_t i) {
    uint2022_t res;
    res.value[res.SIZE - 1] = i % static_cast<int>(1e9);
    res.value[res.SIZE - 2] = i / static_cast<int>(1e9);
    return res;
}

uint2022_t from_string(const char* buff) {
    uint2022_t res;

    if (buff == "0") { return res; }
    char r[9] = "00000000";
    int j = strlen(buff);
    for (int i = res.value.size() - 1; i >= 0; i--) {
        for (int k = 8; k >= 0; k--) {
            j--;
            r[k] = buff[j];
            if (j == 0) { break; }
        }

        int l = 0;
        bool f = false;
        for (int k = 8; k >= 0; k--) {
            if (!f && r[l] != '0') { f = true; }
            if (f) { res.value[i] += (r[l] - '0') * pow(10, k); }
            l++;
        }

        for (int i = 0; i < 9; i++) { r[i] = '0'; }

        if (j == 0) { break; }
    }

    return res;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t res;

    int buff = 0;
    for (int i = res.value.size() - 1; i >= 0; i--) {
        buff = buff + lhs.value[i] + rhs.value[i];
        res.value[i] = buff % static_cast<int>(1e9);
        buff /= (int)1e9;
    }

    return res;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t res;

    if (rhs > lhs) { return from_uint(0); }

    for (int i = res.value.size() - 1; i >= 0; i--) {
        res.value[i] = lhs.value[i] - rhs.value[i];
    }

    return res;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t res;

    uint64_t buff = 0;
    for (int i = res.SIZE - 1; i >= 0; i--) {
        for (int j = res.SIZE - 1; i + j - res.SIZE + 1 > 0; j--) {
            buff = res.value[i + j - res.SIZE + 1] + static_cast<uint64_t>(lhs.value[i]) * static_cast<uint64_t>(rhs.value[j]) + buff;
            res.value[i + j - res.SIZE + 1] = buff % static_cast<int>(1e9);
            buff /= static_cast<int>(1e9);
        }
    }

    return res;
}

int NumericDigitCounter(uint2022_t& a, uint2022_t& b) {
    int counter = 0;
    while (a > b * from_uint(10)) {
        b = b * from_uint(10);
        counter++;
    }

    return counter;
}

uint2022_t Pow(int counter) {
    uint2022_t res;

    res = from_uint(1);

    uint2022_t buff = from_uint(10);

    for (int i = 0; i < counter; i++) {
        res = res * buff;
    }

    return res;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t res;

    uint2022_t a = lhs;
    uint2022_t b = rhs;

    uint2022_t one = from_uint(1);

    int c = 0;
    int counter = 0;
    do {
        counter = NumericDigitCounter(a, b);
        c = 0;
        while (!(b > a)) {
            a = a - b;
            c += 1;
        }

        res = res + from_uint(c) * Pow(counter);

        b = rhs;
    } while (counter != 0);

    while (!(b > a)) {
        a = a - b;
        res = res + one;
    }

    return res;
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (int i = 0; i < lhs.SIZE; i++) {
        if (lhs.value[i] != rhs.value[i]) {
            return false;
        }
    }

    return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return !(lhs == rhs);
}

bool operator>(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (int i = 0; i < lhs.SIZE; i++) {
        if (lhs.value[i] < rhs.value[i]) {
            return false;
        }
        if (lhs.value[i] > rhs.value[i]) {
            return true;
        }
    }

    return false;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    bool f = false;

    if (value == from_uint(0)) {
        stream << '0';
        return stream;
    }

    for (int i = 0; i < value.SIZE; i++) {
        if (f) {
            stream << std::setw(9);
            stream << std::setfill('0');
            stream << value.value[i];
        }
        else if (value.value[i] != 0 && !f) {
            f = true;
            stream << value.value[i];
        }
    }

    return stream;
}
