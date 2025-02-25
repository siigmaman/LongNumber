#include "Helpers.h"

namespace LongNumber {
    std::string IncrementString(std::string str) {
        int i = str.size() - 1;
        while (i >= 0 && str[i] == '9') {
            str[i] = '0';
            i--;
        }
        if (i < 0) {
            str = '1' + str;
        } else {
            str[i]++;
        }
        return str;
    }

    std::string MultiplyStringByTwo(std::string str) {
        int carry = 0;    
        for (int i = str.size() - 1; i >= 0; i--) {
            int digit = (str[i] - '0') * 2 + carry;
            str[i] = (digit % 10) + '0';
            carry = digit / 10;
        }
        if (carry > 0) {
            str = char(carry + '0') + str;
        }
        return str;
    }
}