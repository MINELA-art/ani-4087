#include <iostream>
#include <string>

int main()
{
    int tailleChaine = 0;
    int nombreImages = 0;
    if (!(std::cin >> tailleChaine >> nombreImages))
        return 0;

    if (tailleChaine <= 0 || tailleChaine > 4)
    {
        std::cout << "CHAINE REFUSEE\n";
        return 0;
    }

    std::string signes;
    if (nombreImages > 0)
        std::cin >> signes;

    int prochaine = 0; // image a emprunter dans l'anneau
    int fins = 0;
    int rendues = 0;
    int sautees = 0;

    for (int t = 1; t <= nombreImages; ++t)
    {
        const bool doitRendre = (signes[static_cast<std::size_t>(t - 1)] == '1');

        if (doitRendre)
        {
            // emprunter, dessiner, rendre
            const int image = prochaine;
            const int lacet = t - 1;
            prochaine = (image + 1) % tailleChaine;
            ++rendues;
            std::cout << t << " OUI 1 " << lacet << ' ' << image << '\n';
        }
        else
        {
            // rien a dessiner : l'anneau ne bouge pas, fin de trame avec zero couche
            ++sautees;
            std::cout << t << " NON 0\n";
        }

        ++fins; // une fin de trame a chaque image
    }

    std::cout << "FINS " << fins << '\n';
    std::cout << "RENDUES " << rendues << '\n';
    std::cout << "SAUTEES " << sautees << '\n';
    std::cout << "PROCHAINE " << prochaine << '\n';
    return 0;
}
