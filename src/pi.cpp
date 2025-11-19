#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>
#include "LongNumber.h"

using namespace LongNumber;

struct PiContext {
    LongMath pi;
    std::mutex pi_mutex;
    std::vector<LongMath> powers_of_16;
    std::atomic<int> progress{0};
    int total_terms = 0;

    PiContext(int precision)
        : pi("0.0", precision)
    {}
};

void calculate_pi_bbp_part(PiContext& ctx, int start, int end, int precision) {
    LongMath local_sum("0.0", precision);

    // Константы для потока
    LongMath one("1.0", precision);
    LongMath two("2.0", precision);
    LongMath four("4.0", precision);

    for (int k = start; k < end; ++k) {
        // Прогресс
        int cur = ++ctx.progress;
        if (cur % 5 == 0) {
            int percent = (cur * 100) / ctx.total_terms;
            std::cout << "\rProgress: " << percent << "% ("
                      << cur << "/" << ctx.total_terms << " iterations)" << std::flush;
        }

        // Знаменатели считаем на лету — векторы не нужны
        LongMath d1(std::to_string(8 * k + 1), precision);
        LongMath d2(std::to_string(8 * k + 4), precision);
        LongMath d3(std::to_string(8 * k + 5), precision);
        LongMath d4(std::to_string(8 * k + 6), precision);

        LongMath term1 = four / d1;
        LongMath term2 = two  / d2;
        LongMath term3 = one  / d3;
        LongMath term4 = one  / d4;

        LongMath sum_term = term1 - term2 - term3 - term4;

        // BBP: (sum_term) / 16^k
        LongMath contrib = sum_term / ctx.powers_of_16[k];
        local_sum = local_sum + contrib;
    }

    // Складываем частичную сумму в общий результат
    {
        std::lock_guard<std::mutex> lock(ctx.pi_mutex);
        ctx.pi = ctx.pi + local_sum;
    }
}

LongMath calculate_pi_bbp_parallel(int precision) {
    PiContext ctx(precision);

    std::cout << "Preparing 16^k..." << std::endl;

    // Эмпирика: примерно 1.2 десятичных цифры на один член BBP
    int iterations = static_cast<int>(precision / 1.2) + 5;
    iterations = std::min(iterations, 100); // при желании лимит можно убрать/поднять
    ctx.total_terms = iterations;

    ctx.powers_of_16.resize(iterations);

    LongMath one("1.0", precision);
    LongMath sixteen("16.0", precision);

    ctx.powers_of_16[0] = one;
    for (int k = 1; k < iterations; ++k) {
        if (k % 10 == 0) {
            std::cout << "Calculating 16^" << k << "..." << std::endl;
        }
        ctx.powers_of_16[k] = ctx.powers_of_16[k - 1] * sixteen;
    }

    // Настройка потоков
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 4;
    num_threads = std::min(num_threads, static_cast<unsigned int>(iterations));

    std::cout << "Using " << num_threads << " threads" << std::endl;

    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    int base_chunk = iterations / static_cast<int>(num_threads);
    int remainder  = iterations % static_cast<int>(num_threads);

    int start = 0;
    for (unsigned int i = 0; i < num_threads; ++i) {
        int chunk = base_chunk + (static_cast<int>(i) < remainder ? 1 : 0);
        int end   = start + chunk;

        threads.emplace_back(
            [&, start, end, precision]() {
                calculate_pi_bbp_part(ctx, start, end, precision);
            }
        );

        start = end;
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << std::endl;
    return ctx.pi;
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
        } catch (const std::exception&) {
            std::cerr << "Некорректный аргумент" << std::endl;
            return 1;
        }
    }

    std::cout << "Calculating π with " << precision << " digits..." << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();
    LongMath pi = calculate_pi_bbp_parallel(precision);
    auto end_time   = std::chrono::high_resolution_clock::now();
    auto duration   = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "π = " << pi.to_decimal() << std::endl;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;

    std::string known_pi =
        "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679";
    std::string calculated_pi = pi.to_decimal();

    int correct_digits = 0;
    int limit = static_cast<int>(std::min(known_pi.size(), calculated_pi.size()));
    for (int i = 0; i < limit; ++i) {
        if (known_pi[i] == calculated_pi[i]) {
            ++correct_digits;
        } else {
            break;
        }
    }

    std::cout << "Correct digits: " << correct_digits << std::endl;
    return 0;
}
