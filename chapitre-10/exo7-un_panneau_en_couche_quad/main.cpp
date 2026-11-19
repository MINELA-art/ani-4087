#include <cmath>
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

int main()
{
    Pose ancre;
    if (!(std::cin >> ancre.x >> ancre.y >> ancre.z >> ancre.k))
        return 0;

    long long oeilX = 0;
    long long oeilY = 0;
    long long oeilZ = 0;
    std::cin >> oeilX >> oeilY >> oeilZ;

    int nombre = 0;
    std::cin >> nombre;

    for (int i = 1; i <= nombre; ++i)
    {
        char espace = '-';
        Pose panneau;
        long long largeur = 0;
        long long hauteur = 0;
        std::cin >> espace >> panneau.x >> panneau.y >> panneau.z >> panneau.k >> largeur >> hauteur;

        // un panneau sans espace precise est dans LOCAL
        const bool dansStage = (espace == 'S');

        Pose centre = panneau;
        if (!dansStage)
        {
            tourner(centre.x, centre.z, ancre.k);
            centre.x += ancre.x;
            centre.y += ancre.y;
            centre.z += ancre.z;
            centre.k = (ancre.k + panneau.k) % 4;
        }

        std::cout << "PANNEAU " << i << (dansStage ? " STAGE" : " LOCAL") << '\n';

        // coins dans le plan x, y du panneau, dans l'ordre demande
        const long long demiL = largeur / 2;
        const long long demiH = hauteur / 2;
        const long long coinsX[4] = {-demiL, demiL, demiL, -demiL};
        const long long coinsY[4] = {-demiH, -demiH, demiH, demiH};

        for (int c = 0; c < 4; ++c)
        {
            long long x = coinsX[c];
            long long z = 0;
            tourner(x, z, centre.k);
            std::cout << centre.x + x << ' ' << centre.y + coinsY[c] << ' ' << centre.z + z << '\n';
        }

        const double dx = static_cast<double>(centre.x - oeilX);
        const double dy = static_cast<double>(centre.y - oeilY);
        const double dz = static_cast<double>(centre.z - oeilZ);
        const long long distance = std::llround(std::sqrt(dx * dx + dy * dy + dz * dz));
        std::cout << "DISTANCE " << distance << '\n';
    }

    std::cout << "PANNEAUX " << (nombre > 0 ? nombre : 0) << '\n';
    return 0;
}
