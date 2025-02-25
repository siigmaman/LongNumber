#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "LongNumber.h"

using namespace LongNumber;

LongMath calculate_pi(int precision) {
    LongMath pi("0.0", precision);
    LongMath C3_OVER_24("0.42441318157825351629", precision); // C³/24
    LongMath constant_A("13591409.0", precision);
    LongMath constant_B("545140134.0", precision);
    LongMath constant_C("640320.0", precision);
    LongMath constant_D("426880.0", precision);
    LongMath constant_E("10005.0", precision);
    LongMath constant_F("-262537412640768000.0", precision);
    
    int iterations = precision / 14 + 2;
    
    std::cout << "Потребуется примерно " << iterations << " итераций" << std::endl;
    
    std::vector<LongMath> powers;
    LongMath power("1.0", precision);
    powers.push_back(power);
    
    for (int i = 1; i <= iterations; i++) {
        power = power * constant_C;
        powers.push_back(power);
    }
    
    LongMath sum("0.0", precision);
    LongMath term("1.0", precision);
    
    for (int k = 0; k < iterations; k++) {
        LongMath numerator;
        if (k == 0) {
            numerator = constant_A;
        } else {
            LongMath factor_6k("1.0", precision);
            for (int i = 1; i <= 6; i++) {
                factor_6k = factor_6k * LongMath(std::to_string(6*k - 6 + i), precision);
            }
            
            numerator = factor_6k * (constant_A + constant_B * LongMath(std::to_string(k), precision));
        }
        
        LongMath denominator;
        if (k == 0) {
            denominator = LongMath("1.0", precision);
        } else {
            LongMath factorial_k("1.0", precision);
            for (int i = 1; i <= k; i++) {
                factorial_k = factorial_k * LongMath(std::to_string(i), precision);
            }
            LongMath factorial_k_cubed = factorial_k * factorial_k * factorial_k;

            denominator = factorial_k_cubed * powers[k];
        }
        if (k % 2 == 0) {
            sum = sum + (numerator / denominator);
        } else {
            sum = sum - (numerator / denominator);
        }
        std::cout << "Итерация " << k+1 << " из " << iterations << std::endl;
    }

    LongMath sqrt_C3_OVER_24("0.65146066212179770815", precision); // √(C³/24)
    pi = constant_D * LongMath("100.025", precision) / sum;

    return pi;
}

int main(int argc, char *argv[]) {
    int precision = 100;

    if (argc > 1) {
        try {
            precision = std::stoi(argv[1]);
            if (precision <= 0) {
                std::cerr << "Precision must be a positive integer" << std::endl;
                return 1;
            }
        } catch (std::exception& e) {
            std::cerr << "Invalid argument" << std::endl;
            return 1;
        }
    }
    std::cout << "Calculating π with precision " << precision << " digits..." << std::endl;
    LongMath pi = calculate_pi(precision);
    std::cout << "π = " << pi.to_decimal() << std::endl;
    return 0;
} 