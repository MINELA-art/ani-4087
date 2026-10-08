#include <iostream>
#include <string>

static long long ValeurAbsolue(long long v)
{
    return v < 0 ? -v : v;
}

static long long Maximum(long long a, long long b)
{
    return a > b ? a : b;
}

int main()
{
    int n = 0;
    if (!(std::cin >> n))
        return 0;

    int deplaces = 0;
    long long pire = 0;

    for (int i = 0; i < n; ++i)
    {
        std::string nom;
        long long tx = 0;
        long long ty = 0;
        long long tz = 0;
        long long sx = 0;
        long long sy = 0;
        long long sz = 0;
        std::cin >> nom >> tx >> ty >> tz >> sx >> sy >> sz;

        // Mauvais ordre : l'échelle de chaque axe s'applique à la translation de cet axe.
        // On multiplie avant de diviser ; la division entière tronque vers zéro.
        const long long x = sx * tx / 1000;
        const long long y = sy * ty / 1000;
        const long long z = sz * tz / 1000;

        const long long ecart = Maximum(ValeurAbsolue(tx - x),
                                        Maximum(ValeurAbsolue(ty - y), ValeurAbsolue(tz - z)));

        if (ecart != 0)
            ++deplaces;
        if (ecart > pire)
            pire = ecart;

        std::cout << nom << " " << x << " " << y << " " << z << " " << ecart << "\n";
    }

    std::cout << "DEPLACES " << deplaces << "\n";
    std::cout << "PIRE " << pire << "\n";
    return 0;
}