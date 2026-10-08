#include <iostream>
#include <string>

// Teste les causes dans l'ordre imposé et renvoie la première qui s'applique.
static std::string Verdict(long long drapeaux, long long sx, long long sy, long long sz,
                           long long distance, long long lumieres, long long ambiante,
                           long long proche)
{
    // 1. Le dessin 3D (bit de valeur 2) est éteint.
    if ((drapeaux & 2) == 0)
        return "RENDER3D ETEINT";

    // 2. Une des trois tailles est nulle.
    if (sx == 0 || sy == 0 || sz == 0)
        return "ECHELLE NULLE";

    // 3. Face avant du cube : distance - sz / 2 (sz est pair, la division est exacte).
    const long long faceAvant = distance - sz / 2;
    if (faceAvant <= 0)
        return "CAMERA DANS LE CUBE";

    // 4. Face avant strictement en deçà du plan rapproché.
    if (faceAvant < proche)
        return "COUPE PAR LE PLAN PROCHE";

    // 5. Ni lumière ni ambiante.
    if (lumieres == 0 && ambiante == 0)
        return "PAS DE LUMIERE";

    // 6. Sinon, le cube est visible.
    return "VISIBLE";
}

int main()
{
    int n = 0;
    if (!(std::cin >> n))
        return 0;

    int visibles = 0;
    int enPanne = 0;

    for (int i = 0; i < n; ++i)
    {
        std::string nom;
        long long drapeaux = 0;
        long long sx = 0;
        long long sy = 0;
        long long sz = 0;
        long long distance = 0;
        long long lumieres = 0;
        long long ambiante = 0;
        long long proche = 0;

        std::cin >> nom >> drapeaux >> sx >> sy >> sz >> distance >> lumieres >> ambiante >> proche;

        const std::string verdict = Verdict(drapeaux, sx, sy, sz, distance, lumieres, ambiante, proche);

        if (verdict == "VISIBLE")
            ++visibles;
        else
            ++enPanne;

        std::cout << nom << " " << verdict << "\n";
    }

    std::cout << "VISIBLES " << visibles << "\n";
    std::cout << "EN PANNE " << enPanne << "\n";
    return 0;
}