// Exercice 9 - Le garde-fou
// Un simulateur plus severe que le vrai materiel :
// - il REFUSE une fin de trame sans debut
// - il AVERTIT quand une couche de projection n'a pas de chaine pour un oeil
// - il AVERTIT si l'instant soumis n'est pas l'instant predit
#include <iostream>

struct CoucheProjection
{
    int chaines[2]; // -1 = pas de chaine
};

struct Simulateur
{
    bool trameOuverte = false;
    long long instantPredit = 0;

    void attendre(long long instant)
    {
        instantPredit = instant;
    }

    void debut()
    {
        trameOuverte = true;
        std::cout << "debut de trame\n";
    }

    void fin(long long instant, const CoucheProjection* couche)
    {
        if (!trameOuverte)
        {
            std::cout << "REFUSE : fin de trame sans debut\n";
            return;
        }
        if (instant != instantPredit)
            std::cout << "AVERTISSEMENT : instant " << instant
                      << " different de l'instant predit " << instantPredit << "\n";
        if (couche != nullptr)
        {
            for (int oeil = 0; oeil < 2; ++oeil)
                if (couche->chaines[oeil] < 0)
                    std::cout << "AVERTISSEMENT : pas de chaine pour l'oeil " << oeil << "\n";
        }
        trameOuverte = false;
        std::cout << "fin de trame acceptee\n";
    }
};

int main()
{
    Simulateur sim;

    std::cout << "-- Cas 1 : trame correcte --\n";
    CoucheProjection bonne = {{0, 1}};
    sim.attendre(100);
    sim.debut();
    sim.fin(100, &bonne);

    std::cout << "-- Cas 2 : fin sans debut --\n";
    sim.fin(100, nullptr);

    std::cout << "-- Cas 3 : chaine oubliee --\n";
    CoucheProjection mauvaise = {{0, -1}};
    sim.attendre(111);
    sim.debut();
    sim.fin(111, &mauvaise);

    std::cout << "-- Cas 4 : mauvais instant --\n";
    sim.attendre(122);
    sim.debut();
    sim.fin(107, &bonne);
    return 0;
}
