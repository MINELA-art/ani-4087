#include <iostream>
#include <string>
#include <vector>

struct Cible
{
    int largeur;
    int hauteur;
};

int main()
{
    int largeurFenetre = 0;
    int hauteurFenetre = 0;
    int nombreTampons = 0;
    int nombreOrdres = 0;
    if (!(std::cin >> largeurFenetre >> hauteurFenetre >> nombreTampons >> nombreOrdres))
        return 0;

    bool offscreenAllume = false;
    std::vector<Cible> cibles;
    int cibleCourante = 0;
    int largeurRendu = largeurFenetre;
    int hauteurRendu = hauteurFenetre;
    std::vector<bool> tamponsOccupes(static_cast<std::size_t>(nombreTampons), false);
    int images = 0;
    bool bloque = false;

    for (int i = 0; i < nombreOrdres; ++i)
    {
        std::string ordre;
        std::cin >> ordre;

        if (ordre == "allume")
        {
            std::string nom;
            std::cin >> nom;
            if (!bloque && nom == "OFFSCREEN")
                offscreenAllume = true;
        }
        else if (ordre == "cible")
        {
            int largeur = 0;
            int hauteur = 0;
            std::cin >> largeur >> hauteur;
            if (bloque)
                continue;
            if (!offscreenAllume)
            {
                std::cout << "CIBLE NULLE\n";
            }
            else
            {
                cibles.push_back({largeur, hauteur});
                std::cout << "CIBLE " << cibles.size() << ' '
                          << largeur << ' ' << hauteur << '\n';
            }
        }
        else if (ordre == "vers")
        {
            int numero = 0;
            std::cin >> numero;
            if (bloque)
                continue;
            if (numero < 0 || numero > static_cast<int>(cibles.size()))
            {
                std::cout << "VERS REFUSE\n";
            }
            else
            {
                cibleCourante = numero;
            }
        }
        else if (ordre == "taille")
        {
            int largeur = 0;
            int hauteur = 0;
            std::cin >> largeur >> hauteur;
            if (!bloque)
            {
                largeurRendu = largeur;
                hauteurRendu = hauteur;
            }
        }
        else if (ordre == "image" && !bloque)
        {
            const int numeroImage = images + 1;
            const int tampon = (numeroImage - 1) % nombreTampons;
            if (tamponsOccupes[static_cast<std::size_t>(tampon)])
            {
                std::cout << "BLOQUE " << numeroImage << '\n';
                bloque = true;
                continue;
            }

            ++images;
            if (cibleCourante == 0)
            {
                std::cout << "IMAGE " << numeroImage << " FENETRE\n";
            }
            else
            {
                const Cible& cible = cibles[static_cast<std::size_t>(cibleCourante - 1)];
                std::cout << "IMAGE " << numeroImage << " CIBLE " << cibleCourante << '\n';
                if (largeurRendu > cible.largeur || hauteurRendu > cible.hauteur)
                    tamponsOccupes[static_cast<std::size_t>(tampon)] = true;
            }
        }
    }

    std::cout << "IMAGES " << images << '\n';
    std::cout << "ETAT " << (bloque ? "BLOQUE" : "LIBRE") << '\n';
    return 0;
}
