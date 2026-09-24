La boucle calcule la sommes des racines carrées de 100.000.000 premiers entiers naturels

```cpp
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
```

# Résultat de la construction en débug:
temps de construction : 
┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 1.21s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘ 
temps d'execution :
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (5.50s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
# Résultats de la construction en release
temps de construction : 
┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 1.30s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘
temps d'execution :
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (5.53s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

## Laquelle des 2 m'aurait fait prendre une mauvaise décision?
en effet 1,21s (1210 s) < 1,30s (1300 ms). ces deux budget déppassent largement le budget de 11ms. mais en conclusion je prendrai quand memela Construction en release Car le temps de construction comme d'execution en realease est supérieur au temps d'en debug