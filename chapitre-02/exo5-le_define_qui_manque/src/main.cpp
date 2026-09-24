#include <iostream>
#include "moduleA.h"   // pour pouvoir appeler somme_plus_1000()
#include "compteur.h"
#include "test_compteur.h"

int main() {
    int a = 5;
    int b = 7;

    int resultat = somme_plus_1000(a, b);

    std::cout << "somme_plus_1000(" << a << ", " << b << ") = " << resultat << std::endl;

    testerCompteur();

    return 0;
}
