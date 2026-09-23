#include <iostream>
#include "moduleA.h"   // pour pouvoir appeler somme_plus_1000()
#include "Compteur.h"
 
int main() {
    int a = 5;
    int b = 7;
 
    int resultat = somme_plus_1000(a, b);
 
    std::cout << "somme_plus_1000(" << a << ", " << b << ") = " << resultat << std::endl;
    #ifdef COMPTEUR_COMPLET
    Compteur c(10);
    c.incrementer();
    c.incrementer();
    c.decrementer();
    std::cout << "Valeur du compteur : " << c.getValeur() << std::endl;
    #else
        Compteur c;
        std::cout << "Compteur : coquille vide, pas de fonctionnalite." << std::endl;
    #endif
 
    return 0;
}
