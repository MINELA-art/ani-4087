#include <iostream>
#include <string>
#include <vector>

int main()
{
    int nombre = 0;
    if (!(std::cin >> nombre))
        return 0;

    int muettes = 0;

    for (int i = 1; i <= nombre; ++i)
    {
        std::string fin;
        int g = 0;
        int d = 0;
        char instant = ' ';
        char pose = ' ';
        char espace = ' ';
        std::cin >> fin >> g >> d >> instant >> pose >> espace;

        // symptomes sur un casque, dans l'ordre demande
        std::vector<std::string> symptomes;
        if (fin == "JAMAIS")
            symptomes.push_back("FIGE");
        if (fin == "SI_RENDU")
            symptomes.push_back("NE_REPART_PAS");
        if (g == 0)
            symptomes.push_back("OEIL_NOIR_G");
        if (d == 0)
            symptomes.push_back("OEIL_NOIR_D");
        if (instant == 'N')
            symptomes.push_back("TREMBLE");
        if (pose == 'F')
            symptomes.push_back("DE_TRAVERS");
        if (espace == 'L')
            symptomes.push_back("DECALE");

        std::cout << i << " CASQUE";
        if (symptomes.empty())
        {
            std::cout << " AUCUN";
        }
        else
        {
            for (const std::string& symptome : symptomes)
                std::cout << ' ' << symptome;
        }
        std::cout << '\n';

        // le simulateur ne voit que la fin de trame et les chaines
        bool simulateurDit = (fin != "TOUJOURS") || g == 0 || d == 0;
        std::cout << i << " SIMULATEUR " << (simulateurDit ? "DIT" : "MUET") << '\n';

        if (!symptomes.empty() && !simulateurDit)
            ++muettes;
    }

    std::cout << "MUETTES " << muettes << '\n';
    return 0;
}
