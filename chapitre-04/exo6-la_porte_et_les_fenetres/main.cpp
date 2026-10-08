#include <iostream>
#include <string>

int main()
{
    long long W = 0;
    long long H = 0;
    long long seuil = 0;
    int n = 0;
    if (!(std::cin >> W >> H >> seuil >> n))
        return 0;

    int ok = 0;
    int aReprendre = 0;

    for (int i = 0; i < n; ++i)
    {
        std::string nom;
        long long u = 0;
        long long y = 0;
        long long l = 0;
        long long h = 0;
        long long e = 0;
        long long d = 0;
        std::cin >> nom >> u >> y >> l >> h >> e >> d;

        // l, h et e sont pairs : les demi-valeurs sont exactes.
        const long long saillie = d + e / 2;
        const long long arriere = d - e / 2;

        // Les tests de débordement sont écrits sans diviser W, pour rester exacts
        // même si W est impair.
        const bool deborde = (2 * u - l < -W) || (2 * u + l > W) ||
                             (2 * y - h < 0) || (2 * y + h > 2 * H);

        std::string verdict;
        if (deborde)
            verdict = "DEBORDE";
        else if (saillie <= 0)
            verdict = "INVISIBLE";
        else if (saillie < seuil)
            verdict = "CLIGNOTE";
        else if (arriere > seuil)
            verdict = "DECOLLE";
        else
            verdict = "OK";

        if (verdict == "OK")
            ++ok;
        else
            ++aReprendre;

        std::cout << nom << " " << saillie << " " << verdict << "\n";
    }

    std::cout << "OK " << ok << "\n";
    std::cout << "A REPRENDRE " << aReprendre << "\n";
    return 0;
}