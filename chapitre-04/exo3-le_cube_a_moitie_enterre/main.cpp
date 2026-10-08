#include <iostream>
#include <string>

// Verdict selon la position du bas et du haut du cube par rapport au sol (y = 0).
static std::string Verdict(long long bas, long long haut)
{
    if (haut <= 0)
        return "SOUS LE SOL";
    if (bas < 0)
        return "ENTERRE";
    if (bas == 0)
        return "POSE";
    return "FLOTTE";
}

static long long ValeurAbsolue(long long v)
{
    return v < 0 ? -v : v;
}

int main()
{
    int n = 0;
    if (!(std::cin >> n))
        return 0;

    int aCorriger = 0;
    long long pire = 0;

    for (int i = 0; i < n; ++i)
    {
        std::string nom;
        long long e = 0;
        long long y = 0;
        std::cin >> nom >> e >> y;

        // e est pair : la demi-hauteur est exacte.
        const long long demi = e / 2;
        const long long bas = y - demi;
        const long long haut = y + demi;

        const std::string verdict = Verdict(bas, haut);

        if (verdict != "POSE")
            ++aCorriger;

        const long long ecart = ValeurAbsolue(bas);
        if (ecart > pire)
            pire = ecart;

        // La hauteur du centre qui pose le cube sur le sol ne dépend pas de y.
        std::cout << nom << " " << bas << " " << haut << " " << verdict << " " << demi << "\n";
    }

    std::cout << "A CORRIGER " << aCorriger << "\n";
    std::cout << "PIRE " << pire << "\n";
    return 0;
}