#include <iostream>

struct Pose
{
    long long x = 0;
    long long y = 0;
    long long z = 0;
    int k = 0; // lacet en quarts de tour
};

// Tourne (x, z) de k quarts de tour. y ne tourne pas.
void tourner(long long& x, long long& z, int k)
{
    const long long ancienX = x;
    const long long ancienZ = z;
    if (k == 1)
    {
        x = ancienZ;
        z = -ancienX;
    }
    else if (k == 2)
    {
        x = -ancienX;
        z = -ancienZ;
    }
    else if (k == 3)
    {
        x = -ancienZ;
        z = ancienX;
    }
}

// Passage de LOCAL a STAGE : l'ancre composee avec la pose.
Pose composer(const Pose& ancre, const Pose& p)
{
    Pose resultat = p;
    tourner(resultat.x, resultat.z, ancre.k);
    resultat.x += ancre.x;
    resultat.y += ancre.y;
    resultat.z += ancre.z;
    resultat.k = (ancre.k + p.k) % 4;
    return resultat;
}

int main()
{
    Pose ancre;
    if (!(std::cin >> ancre.x >> ancre.y >> ancre.z >> ancre.k))
        return 0;

    int nombre = 0;
    std::cin >> nombre;

    int justes = 0;
    int fausses = 0;

    for (int i = 1; i <= nombre; ++i)
    {
        char demande = 'S';
        char declare = 'S';
        Pose p;
        std::cin >> demande >> declare >> p.x >> p.y >> p.z >> p.k;

        const Pose vraie = (demande == 'L') ? composer(ancre, p) : p;
        const Pose crue = (declare == 'L') ? composer(ancre, p) : p;

        const long long dx = crue.x - vraie.x;
        const long long dy = crue.y - vraie.y;
        const long long dz = crue.z - vraie.z;
        const int dk = (crue.k - vraie.k + 4) % 4;

        std::cout << i << " CRU " << crue.x << ' ' << crue.y << ' ' << crue.z << ' ' << crue.k << '\n';
        std::cout << i << " ECART " << dx << ' ' << dy << ' ' << dz << ' ' << dk << '\n';

        if (dx == 0 && dy == 0 && dz == 0 && dk == 0)
            ++justes;
        else
            ++fausses;
    }

    std::cout << "JUSTES " << justes << '\n';
    std::cout << "FAUSSES " << fausses << '\n';
    return 0;
}
