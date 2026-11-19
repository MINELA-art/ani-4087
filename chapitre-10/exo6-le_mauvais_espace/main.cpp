// Exercice 6 - Le mauvais espace
// Les poses sont demandees dans un espace, la couche en declare un autre.
// Aucune erreur, mais la scene est decalee d'une hauteur de personne.
#include <iostream>
#include <string>

const double HAUTEUR_YEUX = 1.70; // metres

// hauteur de l'origine de chaque espace par rapport au sol
double origine(const std::string& espace)
{
    if (espace == "LOCAL")
        return HAUTEUR_YEUX; // origine a la hauteur des yeux
    return 0.0;              // STAGE : origine au sol
}

void tester(const std::string& espacePoses, const std::string& espaceCouche)
{
    double decalage = origine(espacePoses) - origine(espaceCouche);

    std::cout << "Poses en " << espacePoses << ", couche en " << espaceCouche << " : ";
    if (decalage == 0.0)
        std::cout << "scene correcte\n";
    else if (decalage > 0.0)
        std::cout << "en levitation a " << decalage << " m\n";
    else
        std::cout << "enterre dans le sol de " << -decalage << " m\n";
}

int main()
{
    tester("STAGE", "STAGE");
    tester("LOCAL", "STAGE");
    tester("STAGE", "LOCAL");
    return 0;
}
