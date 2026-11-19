// Exercice 5 - Le mauvais instant
// On soumet l'instant courant au lieu de l'instant predit.
// L'erreur d'angle est proportionnelle a la vitesse de la tete : ca tremble.
#include <iostream>

int main()
{
    const double instantCourant = 1000.0; // ms
    const double instantPredit = 1015.0;  // ms, donne par l'attente de trame
    const double ecart = instantPredit - instantCourant;

    double vitesses[4] = {0.0, 50.0, 100.0, 200.0}; // degres par seconde

    std::cout << "Ecart entre instant courant et instant predit : " << ecart << " ms\n";
    for (int i = 0; i < 4; ++i)
    {
        // erreur en degres = vitesse (deg/s) * ecart (s)
        double erreur = vitesses[i] * (ecart / 1000.0);
        std::cout << "Tete a " << vitesses[i] << " deg/s -> erreur de "
                  << erreur << " deg\n";
    }

    std::cout << "Avec l'instant predit, l'erreur est 0 quelle que soit la vitesse.\n";
    return 0;
}
