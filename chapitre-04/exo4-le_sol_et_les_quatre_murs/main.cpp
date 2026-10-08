#include <iostream>
#include <string>
#include <vector>

struct Rect
{
    long long xmin;
    long long xmax;
    long long zmin;
    long long zmax;
};

// Un mur contient le carré si son emprise couvre entièrement le carré.
static bool Contient(const Rect& mur, const Rect& carre)
{
    return mur.xmin <= carre.xmin && mur.xmax >= carre.xmax &&
           mur.zmin <= carre.zmin && mur.zmax >= carre.zmax;
}

int main()
{
    long long L = 0;
    long long e = 0;
    int n = 0;
    if (!(std::cin >> L >> e >> n))
        return 0;

    std::vector<Rect> murs;

    for (int i = 0; i < n; ++i)
    {
        std::string nom;
        long long cx = 0;
        long long cz = 0;
        long long sx = 0;
        long long sz = 0;
        std::cin >> nom >> cx >> cz >> sx >> sz;

        // sx et sz sont pairs : les demi-tailles sont exactes.
        const Rect r = {cx - sx / 2, cx + sx / 2, cz - sz / 2, cz + sz / 2};
        murs.push_back(r);

        std::cout << nom << " " << r.xmin << " " << r.xmax << " " << r.zmin << " " << r.zmax << "\n";
    }

    // L est pair : h est exact.
    const long long h = L / 2;

    const std::string noms[4] = {"FOND_GAUCHE", "FOND_DROIT", "ENTREE_GAUCHE", "ENTREE_DROIT"};
    const Rect angles[4] = {
        {-h - e, -h, -h - e, -h}, // FOND_GAUCHE
        {h, h + e, -h - e, -h},   // FOND_DROIT
        {-h - e, -h, h, h + e},   // ENTREE_GAUCHE
        {h, h + e, h, h + e}};    // ENTREE_DROIT

    int trous = 0;
    for (int a = 0; a < 4; ++a)
    {
        bool bouche = false;
        for (const Rect& mur : murs)
        {
            if (Contient(mur, angles[a]))
            {
                bouche = true;
                break;
            }
        }
        if (!bouche)
            ++trous;
        std::cout << noms[a] << " " << (bouche ? "BOUCHE" : "TROU") << "\n";
    }

    std::cout << "TROUS " << trous << "\n";
    return 0;
}