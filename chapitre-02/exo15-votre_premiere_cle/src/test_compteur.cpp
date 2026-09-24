#include <iostream>
#include "compteur.h"
#include "test_compteur.h"

void testerCompteur() {
#ifdef COMPTEUR_COMPLET
    Compteur c(10);
    c.incrementer();
    c.incrementer();
    c.decrementer();
    std::cout << "Version complete -> valeur du compteur : " << c.getValeur() << std::endl;
#else
    Compteur c; // coquille vide, juste instanciable
    std::cout << "Version coquille vide -> aucune fonctionnalite disponible." << std::endl;
#endif
}
