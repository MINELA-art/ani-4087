#include <iostream>
#include <chrono>
#include <cmath>

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    double total = 0.0;
    const long long n = 100'000'000;
    for(long long i =0; i < n ; i++){
        total += std::sqrt(static_cast<double> (i));
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Resultat:" << total <<std::endl;
    std::cout << "Temps ecoule:" << elapsed.count() << " secondes" << std::endl;

    return 0;
}
