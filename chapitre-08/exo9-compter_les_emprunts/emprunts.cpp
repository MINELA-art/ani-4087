#include <iostream>
#include <string>
#include <vector>

int main()
{
    int nombreImages = 0;
    int nombreTrames = 0;
    if (!(std::cin >> nombreImages >> nombreTrames))
        return 0;

    std::vector<std::string> modes(static_cast<std::size_t>(nombreTrames));
    for (std::string& mode : modes)
        std::cin >> mode;

    bool empruntee = false;
    int reussies = 0;
    int refusees = 0;
    int liberations = 0;
    int premiereFuite = 0;

    for (int i = 0; i < nombreTrames; ++i)
    {
        const int numero = i + 1;
        const std::string& mode = modes[static_cast<std::size_t>(i)];
        if (empruntee)
        {
            ++refusees;
            std::cout << numero << " BLOQUEE\n";
            continue;
        }

        ++reussies;
        empruntee = true;
        if (mode == "sortie")
        {
            if (premiereFuite == 0)
                premiereFuite = numero;
            std::cout << numero << " FUITE\n";
        }
        else if (mode == "double")
        {
            ++refusees;
            ++liberations;
            empruntee = false;
            std::cout << numero << " DOUBLE\n";
        }
        else
        {
            ++liberations;
            empruntee = false;
            std::cout << numero << " OK\n";
        }
    }

    std::cout << "REUSSIES " << reussies << '\n';
    std::cout << "REFUSEES " << refusees << '\n';
    std::cout << "LIBERATIONS " << liberations << '\n';
    std::cout << "ECART " << reussies - liberations << '\n';
    if (premiereFuite == 0)
        std::cout << "PREMIERE FUITE AUCUNE\n";
    else
        std::cout << "PREMIERE FUITE " << premiereFuite << '\n';
    return 0;
}
