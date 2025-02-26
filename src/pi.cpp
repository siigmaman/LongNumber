#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>
#include "LongNumber.h"

using namespace LongNumber;

namespace {
    LongMath pi;
    std::mutex pi_mutex;
    std::vector<LongMath> powers_of_16;
    std::atomic<int> progress(0);
    int total_terms = 0;
}

void calculate_pi_bbp_part(int start, int end, int precision) {
    LongMath local_sum("0.0", precision);
    LongMath one("1.0", precision);
    LongMath four("4.0", precision);
    LongMath two("2.0", precision);
    
    std::vector<LongMath> denominators1, denominators2, denominators3, denominators4;
    
    for (int k = start; k < end; k++) {
        denominators1.emplace_back(std::to_string(8*k+1), precision);
        denominators2.emplace_back(std::to_string(8*k+4), precision);
        denominators3.emplace_back(std::to_string(8*k+5), precision);
        denominators4.emplace_back(std::to_string(8*k+6), precision);
    }
    
    for (int i = 0; i < end - start; i++) {
        int k = start + i;
        
        if (++progress % 5 == 0) {
            int current = progress.load();
            int percent = (current * 100) / total_terms;
            std::cout << "\rProgress: " << percent << "% (" 
                      << current << "/" << total_terms << " iterations)" << std::flush;
        }
        
        LongMath term1 = four / denominators1[i];
        LongMath term2 = two / denominators2[i];
        LongMath term3 = one / denominators3[i];
        LongMath term4 = one / denominators4[i];
        
        LongMath sum_term = term1 - term2 - term3 - term4;
        
        LongMath contrib = sum_term / powers_of_16[k];
        
        local_sum = local_sum + contrib;
    }
    
    {
        std::lock_guard<std::mutex> lock(pi_mutex);
        pi = pi + local_sum;
    }
}

LongMath calculate_pi_bbp_parallel(int precision) {
    pi = LongMath("0.0", precision);
    powers_of_16.clear();
    progress = 0;
    
    std::cout << "Preparing 16^k..." << std::endl;
    
    int iterations = static_cast<int>(precision / 1.2) + 5;
    iterations = std::min(iterations, 100);
    total_terms = iterations;
    
    powers_of_16.resize(iterations);
    powers_of_16[0] = LongMath("1.0", precision);
    
    LongMath sixteen("16.0", precision);
    
    for (int k = 1; k < iterations; k++) {
        if (k % 10 == 0) {
            std::cout << "Calculating 16^" << k << "..." << std::endl;
        }
        
        powers_of_16[k] = powers_of_16[k-1] * sixteen;
    }
    
    unsigned int num_threads = std::thread::hardware_concurrency();
    num_threads = std::min(num_threads, static_cast<unsigned int>(iterations));
    
    if (num_threads == 0) num_threads = 4;
    
    std::cout << "Using " << num_threads << " threads" << std::endl;
    
    std::vector<std::thread> threads;
    
    int iterations_per_thread = iterations / num_threads;
    int remaining_iterations = iterations % num_threads;
    
    int start = 0;
    for (unsigned int i = 0; i < num_threads; i++) {
        int thread_iterations = iterations_per_thread + (i < remaining_iterations ? 1 : 0);
        int end = start + thread_iterations;
        
        threads.push_back(std::thread(calculate_pi_bbp_part, start, end, precision));
        start = end;
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    std::cout << std::endl;
    return pi;
}

int main(int argc, char *argv[]) {
    int precision = 100;

    if (argc > 1) {
        try {
            precision = std::stoi(argv[1]);
            if (precision <= 0) {
                std::cerr << "Точность должна быть положительным числом" << std::endl;
                return 1;
            }
        } catch (std::exception& e) {
            std::cerr << "Некорректный аргумент" << std::endl;
            return 1;
        }
    }

    std::cout << "Calculating π with " << precision << " digits..." << std::endl;
    auto start_time = std::chrono::high_resolution_clock::now();
    LongMath pi = calculate_pi_bbp_parallel(precision);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "π = " << pi.to_decimal() << std::endl;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
    std::string known_pi = "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679";
    std::string calculated_pi = pi.to_decimal();
    int correct_digits = 0;
    for (int i = 0; i < std::min(known_pi.length(), calculated_pi.length()); i++) {
        if (known_pi[i] == calculated_pi[i]) {
            correct_digits++;
        } else {
            break;
        }
    }
    std::cout << "Correct digits: " << correct_digits << std::endl;
    return 0;
}