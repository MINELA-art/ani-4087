#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    int nombreImages = 0;
    int nombreTrames = 0;
    long long depart = 0;
    long long pas = 0;
    if (!(std::cin >> nombreImages >> nombreTrames >> depart >> pas))
        return 0;

    std::string modes;
    std::cin >> modes;

    std::vector<int> derniereTrame(static_cast<std::size_t>(nombreImages), 0);
    int prochaine = 0;
    bool aMontre = false;
    long long positionPrecedente = 0;
    bool aSauts = false;
    long long sautMin = 0;
    long long sautMax = 0;

    for (int trame = 1; trame <= nombreTrames; ++trame)
    {
        const int empruntee = prochaine;
        derniereTrame[static_cast<std::size_t>(empruntee)] = trame;
        const char mode = modes[static_cast<std::size_t>(trame - 1)];

        int soumise = empruntee;
        if (mode == 'P')
            soumise = (prochaine + nombreImages - 1) % nombreImages;

        prochaine = (prochaine + 1) % nombreImages;
        if (mode == 'D')
            soumise = (prochaine + nombreImages - 1) % nombreImages;

        const int trameMontree = derniereTrame[static_cast<std::size_t>(soumise)];
        if (trameMontree == 0)
        {
            std::cout << trame << " NOIR -\n";
            aMontre = false;
            continue;
        }

        const long long position = depart + pas * trameMontree;
        if (!aMontre || trame == 1)
        {
            std::cout << trame << ' ' << position << " -\n";
            aMontre = true;
            positionPrecedente = position;
            continue;
        }

        const long long saut = position - positionPrecedente;
        std::cout << trame << ' ' << position << ' ' << saut << '\n';
        if (!aSauts)
        {
            sautMin = saut;
            sautMax = saut;
            aSauts = true;
        }
        else
        {
            sautMin = std::min(sautMin, saut);
            sautMax = std::max(sautMax, saut);
        }
        positionPrecedente = position;
        aMontre = true;
    }

    if (!aSauts)
    {
        std::cout << "SAUTS AUCUN\n";
    }
    else
    {
        std::cout << "SAUT MIN " << sautMin << '\n';
        std::cout << "SAUT MAX " << sautMax << '\n';
        std::cout << "TREMBLE " << (sautMin != sautMax ? "OUI" : "NON") << '\n';
    }
    return 0;
}
