// Exercice 4 - La chaine oubliee
// La couche de projection a une vue par oeil. Si on oublie la chaine
// d'un oeil, cet oeil est noir et l'autre est correct.
#include <iostream>

struct VueProjection
{
    int chaine; // -1 = pas de chaine (oubliee)
    int image;
};

struct CoucheProjection
{
    VueProjection vues[2];
};

void composer(const CoucheProjection& couche)
{
    const char* nomOeil[2] = {"gauche", "droit"};
    for (int oeil = 0; oeil < 2; ++oeil)
    {
        if (couche.vues[oeil].chaine < 0)
        {
            std::cout << "  AVERTISSEMENT : pas de chaine pour l'oeil " << nomOeil[oeil] << "\n";
            std::cout << "  oeil " << nomOeil[oeil] << " : NOIR\n";
        }
        else
        {
            std::cout << "  oeil " << nomOeil[oeil] << " : image " << couche.vues[oeil].image
                      << " de la chaine " << couche.vues[oeil].chaine << "\n";
        }
    }
}

int main()
{
    CoucheProjection fautive;
    fautive.vues[0] = {0, 2};
    fautive.vues[1] = {-1, 0}; // chaine oubliee pour l'oeil droit

    std::cout << "Couche fautive :\n";
    composer(fautive);

    CoucheProjection correcte;
    correcte.vues[0] = {0, 2};
    correcte.vues[1] = {1, 2};

    std::cout << "Couche correcte :\n";
    composer(correcte);
    return 0;
}
