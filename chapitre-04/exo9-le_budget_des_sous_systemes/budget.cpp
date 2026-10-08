#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace
{
const int NB_MESURES = 10;

struct Resultat
{
    long long mediane;
    long long moyenne;
};

// Lit une configuration (deux lignes), affiche ses trois lignes et rend mediane et moyenne.
Resultat LireConfiguration(const std::map<std::string, std::uint32_t>& drapeaux)
{
    std::string nom;
    int k = 0;
    std::cin >> nom >> k;

    // La valeur est le OU binaire des drapeaux, jamais leur somme.
    std::uint32_t valeur = 0;
    for (int i = 0; i < k; ++i)
    {
        std::string d;
        std::cin >> d;
        const auto it = drapeaux.find(d);
        if (it != drapeaux.end())
            valeur |= it->second;
    }

    std::vector<long long> temps(NB_MESURES, 0);
    long long somme = 0;
    for (int i = 0; i < NB_MESURES; ++i)
    {
        std::cin >> temps[i];
        somme += temps[i];
    }

    // La médiane trie d'abord, puis moyenne les cinquième et sixième valeurs.
    std::sort(temps.begin(), temps.end());
    const long long mediane = (temps[4] + temps[5]) / 2;
    const long long moyenne = somme / NB_MESURES;

    std::cout << nom << " VALEUR " << valeur << "\n";
    std::cout << nom << " MEDIANE " << mediane << "\n";
    std::cout << nom << " MOYENNE " << moyenne << "\n";
    return {mediane, moyenne};
}
} // namespace

int main()
{
    const std::map<std::string, std::uint32_t> drapeaux = {
        {"RENDER2D", 1u}, {"RENDER3D", 2u}, {"TEXT", 4u},
        {"UI", 8u}, {"SHADOW", 16u}, {"POST_PROCESS", 32u},
        {"ALL", 4294967295u}};

    const Resultat premiere = LireConfiguration(drapeaux);
    const Resultat seconde = LireConfiguration(drapeaux);

    std::cout << "ECART MEDIANES " << premiere.mediane - seconde.mediane << "\n";
    std::cout << "ECART MOYENNES " << premiere.moyenne - seconde.moyenne << "\n";
    return 0;
}
