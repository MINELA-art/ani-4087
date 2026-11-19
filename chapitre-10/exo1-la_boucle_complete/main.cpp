#include <iostream>
#include <string>

// Etat d'une image : chaque image repart de zero.
struct EtatImage
{
    bool attendu = false;
    bool commence = false;
    bool vues = false;
    bool termine = false;
    bool emprunte[2] = {false, false}; // 0 = gauche, 1 = droit
};

// Renvoie le code de la faute, ou une chaine vide si l'appel est juste.
std::string verifier(EtatImage& etat, const std::string& appel)
{
    if (etat.termine)
        return "APRES_END";

    if (appel == "WAIT")
    {
        if (etat.commence)
            return "WAIT_APRES_BEGIN";
        etat.attendu = true;
    }
    else if (appel == "BEGIN")
    {
        if (!etat.attendu)
            return "BEGIN_SANS_WAIT";
        if (etat.commence)
            return "DOUBLE_BEGIN";
        etat.commence = true;
    }
    else if (appel == "VUES")
    {
        if (!etat.attendu)
            return "VUES_SANS_WAIT";
        etat.vues = true;
    }
    else if (appel == "PREND_G" || appel == "PREND_D")
    {
        const int oeil = (appel == "PREND_G") ? 0 : 1;
        if (!etat.commence)
            return "PREND_SANS_BEGIN";
        if (!etat.vues)
            return "PREND_SANS_VUES";
        if (etat.emprunte[oeil])
            return "DOUBLE_PREND";
        etat.emprunte[oeil] = true;
    }
    else if (appel == "LACHE_G" || appel == "LACHE_D")
    {
        const int oeil = (appel == "LACHE_G") ? 0 : 1;
        if (!etat.emprunte[oeil])
            return "LACHE_SANS_PREND";
        etat.emprunte[oeil] = false;
    }
    else if (appel == "END")
    {
        if (!etat.commence)
            return "END_SANS_BEGIN";
        if (etat.emprunte[0] || etat.emprunte[1])
            return "END_IMAGE_PRISE";
        etat.termine = true;
    }
    return "";
}

int main()
{
    int nombreImages = 0;
    if (!(std::cin >> nombreImages))
        nombreImages = 0;

    int justes = 0;
    int fautives = 0;

    for (int t = 1; t <= nombreImages; ++t)
    {
        int nombreAppels = 0;
        std::cin >> nombreAppels;

        EtatImage etat;
        int place = 0;
        std::string code;

        for (int p = 1; p <= nombreAppels; ++p)
        {
            std::string appel;
            std::cin >> appel;
            if (!code.empty())
                continue; // apres la premiere faute, on ignore la suite

            code = verifier(etat, appel);
            if (!code.empty())
                place = p;
        }

        if (code.empty() && !etat.termine)
        {
            code = "SANS_END";
            place = nombreAppels + 1;
        }

        if (code.empty())
        {
            std::cout << t << " OK\n";
            ++justes;
        }
        else
        {
            std::cout << t << " FAUTE " << place << ' ' << code << '\n';
            ++fautives;
        }
    }

    std::cout << "JUSTES " << justes << '\n';
    std::cout << "FAUTIVES " << fautives << '\n';
    return 0;
}
