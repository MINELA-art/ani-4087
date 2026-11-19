#include <cmath>
#include <cstdlib>
#include <iostream>

int main()
{
    long long nombre = 0;
    long long duree = 0;
    if (!(std::cin >> nombre >> duree))
        return 0;

    long long sommePosition = 0;
    long long sommeAngle = 0;

    for (long long t = 1; t <= nombre; ++t)
    {
        long long x1 = 0, z1 = 0, a1 = 0;
        long long x2 = 0, z2 = 0, a2 = 0;
        std::cin >> x1 >> z1 >> a1 >> x2 >> z2 >> a2;

        // distance entre la pose du rendu et la pose de fin de trame
        double dx = static_cast<double>(x2 - x1);
        double dz = static_cast<double>(z2 - z1);
        long long position = std::llround(std::sqrt(dx * dx + dz * dz));

        // ecart de lacet sans son signe
        long long angle = std::llabs(a2 - a1);

        sommePosition += position;
        sommeAngle += angle;
        std::cout << t << " POSITION " << position << " ANGLE " << angle << '\n';
    }

    if (nombre == 0 || duree == 0)
    {
        std::cout << "AUCUNE\n";
        return 0;
    }

    // les valeurs sont positives : la division entiere arrondit a l'entier inferieur
    std::cout << "MOYENNE POSITION " << sommePosition / nombre << '\n';
    std::cout << "MOYENNE ANGLE " << sommeAngle / nombre << '\n';
    // milliemes de degre par milliseconde = degres par seconde
    std::cout << "VITESSE " << sommeAngle / (nombre * duree) << '\n';
    return 0;
}
