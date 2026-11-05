#include <iostream>
#include <string>

int main()
{
    int nombreChaines = 0;
    if (!(std::cin >> nombreChaines))
        return 0;

    int acceptees = 0;
    int occupees = 0;
    int gauche = 0;
    int droit = 0;
    int sansNom = 0;

    for (int i = 0; i < nombreChaines; ++i)
    {
        int largeur = 0;
        int hauteur = 0;
        int images = 0;
        int oeil = 0;
        std::string nom;
        std::cin >> largeur >> hauteur >> images >> oeil >> nom;

        const std::string nomAffiche = nom == "-" ? "SANS-NOM" : nom;
        if (largeur == 0 || hauteur == 0)
        {
            std::cout << "REFUSEE " << nomAffiche << " TAILLE\n";
        }
        else if (images == 0 || images > 4)
        {
            std::cout << "REFUSEE " << nomAffiche << " IMAGES\n";
        }
        else
        {
            ++acceptees;
            occupees += images;
            if (oeil == 0)
                ++gauche;
            else
                ++droit;
            if (nom == "-")
                ++sansNom;

            std::cout << "CHAINE " << nomAffiche << ' ' << largeur << ' '
                      << hauteur << ' ' << images << ' '
                      << (oeil == 0 ? "GAUCHE" : "DROIT") << '\n';
        }
    }

    std::cout << "ACCEPTEES " << acceptees << '\n';
    std::cout << "EMPLACEMENTS " << 4 * acceptees << '\n';
    std::cout << "OCCUPES " << occupees << '\n';
    std::cout << "GAUCHE " << gauche << '\n';
    std::cout << "DROIT " << droit << '\n';
    std::cout << "SANS NOM " << sansNom << '\n';
    return 0;
}
