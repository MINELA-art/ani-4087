#include <iostream>
#include <string>

int main()
{
    std::string facon;
    int nombreImages = 0;
    if (!(std::cin >> facon >> nombreImages))
        return 0;

    std::string signes;
    if (nombreImages > 0)
        std::cin >> signes;

    bool trameOuverte = false;
    int rendues = 0;
    int perdues = 0;
    int erreurs = 0;
    int premierRefus = 0; // 0 = aucun

    for (int t = 1; t <= nombreImages; ++t)
    {
        const char signe = signes[static_cast<std::size_t>(t - 1)];
        bool rendre = false; // etat neuf

        // WaitFrame
        std::string attente = "OK";
        if (trameOuverte)
        {
            attente = "REFUSE";
            ++erreurs;
            if (premierRefus == 0)
                premierRefus = t;
        }
        else
        {
            rendre = (signe == '1');
        }

        // BeginFrame
        std::string debut = "OK";
        if (trameOuverte)
        {
            debut = "REFUSE";
            ++erreurs;
        }
        else
        {
            trameOuverte = true;
        }

        if (rendre)
            ++rendues;
        else if (signe == '1')
            ++perdues;

        // EndFrame selon la facon de faire
        std::string fin = "-";
        if (facon == "TOUJOURS" || rendre)
        {
            if (trameOuverte)
            {
                fin = "OK";
                trameOuverte = false;
            }
            else
            {
                fin = "REFUSE";
                ++erreurs;
            }
        }

        std::cout << t << ' ' << attente << ' ' << debut << ' '
                  << (rendre ? "OUI" : "NON") << ' ' << fin << '\n';
    }

    std::cout << "RENDUES " << rendues << '\n';
    std::cout << "PERDUES " << perdues << '\n';
    std::cout << "ERREURS " << erreurs << '\n';
    if (premierRefus == 0)
        std::cout << "PREMIER REFUS AUCUN\n";
    else
        std::cout << "PREMIER REFUS " << premierRefus << '\n';
    return 0;
}
