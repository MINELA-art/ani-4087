#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

namespace
{
struct Face
{
    const char* nom;
    long long nx;
    long long ny;
    long long nz;
};

// Les cinq faces et leurs normales intérieures, dans l'ordre imposé.
const Face FACES[5] = {
    {"SOL", 0, 1, 0},
    {"FOND", 0, 0, 1},
    {"ENTREE", 0, 0, -1},
    {"GAUCHE", 1, 0, 0},
    {"DROIT", -1, 0, 0}};

// Arrondi à l'entier le plus proche de num / racine(len2), pour num > 0.
// Quand la longueur est entière, on reste en entiers pour ne pas dépendre
// des erreurs de virgule flottante sur les valeurs à égalité.
long long ArrondiSurLongueur(long long num, long long len2)
{
    const long long r = std::llround(std::sqrt(static_cast<long double>(len2)));
    if (r * r == len2)
        return (2 * num + r) / (2 * r);
    return std::llround(static_cast<long double>(num) / std::sqrt(static_cast<long double>(len2)));
}
} // namespace

int main()
{
    long long ambiante = 0;
    int n = 0;
    if (!(std::cin >> ambiante >> n))
        return 0;

    for (int i = 0; i < n; ++i)
    {
        std::string nom;
        long long dx = 0;
        long long dy = 0;
        long long dz = 0;
        long long intensite = 0;
        std::cin >> nom >> dx >> dy >> dz >> intensite;

        // La direction est normalisée : on divise par sa longueur.
        const long long len2 = dx * dx + dy * dy + dz * dz;

        long long plus = 0;
        long long moins = 0;
        for (int f = 0; f < 5; ++f)
        {
            // c = -(normale . direction) / longueur ; une face dos au soleil a c <= 0.
            const long long produit = -(FACES[f].nx * dx + FACES[f].ny * dy + FACES[f].nz * dz);

            long long apport = 0; // I * max(0, c), arrondi
            if (len2 > 0 && produit > 0)
                apport = ArrondiSurLongueur(intensite * produit, len2);

            // Une face dos au soleil garde l'ambiante.
            const long long lumiere = ambiante + apport;
            std::cout << nom << " " << FACES[f].nom << " " << lumiere << "\n";

            if (f == 0)
            {
                plus = lumiere;
                moins = lumiere;
            }
            else
            {
                plus = std::max(plus, lumiere);
                moins = std::min(moins, lumiere);
            }
        }
        std::cout << nom << " CONTRASTE " << plus - moins << "\n";
    }
    return 0;
}
