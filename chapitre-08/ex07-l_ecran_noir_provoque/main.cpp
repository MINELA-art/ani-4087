#include <iostream>
#include <cstdint>
#include <string>

int main()
{
    int nombreOrdres = 0;
    if (!(std::cin >> nombreOrdres))
        return 0;

    std::uint64_t poigneeCourante = 0;
    std::uint64_t poigneeEnregistree = 0;
    std::uint64_t prochainePoignee = 101;
    int images = 0;
    int affichees = 0;
    int noires = 0;
    int perimees = 0;

    for (int i = 0; i < nombreOrdres; ++i)
    {
        std::string ordre;
        std::cin >> ordre;

        if (ordre == "cible")
        {
            int largeur = 0;
            int hauteur = 0;
            std::cin >> largeur >> hauteur;
            poigneeCourante = prochainePoignee++;
            std::cout << "CIBLE " << poigneeCourante << ' '
                      << largeur << ' ' << hauteur << '\n';
        }
        else if (ordre == "chaine")
        {
            poigneeEnregistree = 0;
        }
        else if (ordre == "enregistre")
        {
            poigneeEnregistree = poigneeCourante;
        }
        else if (ordre == "image")
        {
            ++images;
            if (poigneeEnregistree == 0)
            {
                ++noires;
                std::cout << "IMAGE " << images << " NOIR\n";
            }
            else if (poigneeEnregistree != poigneeCourante)
            {
                ++perimees;
                std::cout << "IMAGE " << images << " PERIMEE "
                          << poigneeEnregistree << '\n';
            }
            else
            {
                ++affichees;
                std::cout << "IMAGE " << images << " AFFICHE "
                          << poigneeEnregistree << '\n';
            }
        }
    }

    std::cout << "AFFICHEES " << affichees << '\n';
    std::cout << "NOIRES " << noires << '\n';
    std::cout << "PERIMEES " << perimees << '\n';
    return 0;
}
