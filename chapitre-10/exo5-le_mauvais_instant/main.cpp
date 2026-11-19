#include <iostream>

long long valeurAbsolue(long long v)
{
    return v < 0 ? -v : v;
}

int main()
{
    long long vitesse = 0;
    int nombreImages = 0;
    if (!(std::cin >> vitesse >> nombreImages))
        return 0;

    int fausses = 0;
    long long pireCasque = 0;
    long long pireSimulateur = 0;

    for (int t = 1; t <= nombreImages; ++t)
    {
        long long predit = 0;
        long long soumission = 0;
        long long affichage = 0;
        char mode = 'R';
        std::cin >> predit >> soumission >> affichage >> mode;

        // on dessine toujours avec la pose predite
        const long long lacetRendu = vitesse * predit;
        const long long poseSoumise = (mode == 'F') ? vitesse * soumission : lacetRendu;

        const long long casque = poseSoumise - lacetRendu;
        const long long simulateur = vitesse * affichage - vitesse * predit;

        if (casque != 0)
            ++fausses;
        if (valeurAbsolue(casque) > pireCasque)
            pireCasque = valeurAbsolue(casque);
        if (valeurAbsolue(simulateur) > pireSimulateur)
            pireSimulateur = valeurAbsolue(simulateur);

        std::cout << t << " CASQUE " << casque << " SIMULATEUR " << simulateur << '\n';
    }

    std::cout << "FAUSSES " << fausses << '\n';
    std::cout << "PIRE CASQUE " << pireCasque << '\n';
    std::cout << "PIRE SIMULATEUR " << pireSimulateur << '\n';
    return 0;
}
