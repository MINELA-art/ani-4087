#include <iostream>
#include <string>

struct Chaine
{
    int index = 0;
    bool empruntee = false;
};

int main()
{
    int tailleChaine = 0;
    int nombreAppels = 0;
    if (!(std::cin >> tailleChaine >> nombreAppels))
        return 0;
    if (tailleChaine < 1)
        tailleChaine = 1;

    bool trameOuverte = false;
    Chaine chaines[2]; // 0 = gauche, 1 = droit
    int journal = 0;
    int avertissements = 0;
    int silencieux = 0;

    for (int i = 1; i <= nombreAppels; ++i)
    {
        std::string appel;
        std::cin >> appel;
        std::cout << i << ' ' << appel << ' ';

        if (appel == "wait")
        {
            if (trameOuverte)
            {
                std::cout << "REFUSE\n";
                ++journal;
            }
            else
            {
                std::cout << "OK\n";
            }
        }
        else if (appel == "begin")
        {
            if (trameOuverte)
            {
                std::cout << "REFUSE\n";
                ++journal;
            }
            else
            {
                trameOuverte = true;
                std::cout << "OK\n";
            }
        }
        else if (appel == "acquire" || appel == "release")
        {
            std::string oeil;
            std::cin >> oeil;
            Chaine& chaine = chaines[oeil == "G" ? 0 : 1];

            if (appel == "acquire")
            {
                if (chaine.empruntee)
                {
                    std::cout << "REFUSE\n";
                    ++silencieux;
                }
                else
                {
                    chaine.empruntee = true;
                    std::cout << "OK " << chaine.index << '\n';
                }
            }
            else
            {
                if (!chaine.empruntee)
                {
                    std::cout << "REFUSE\n";
                    ++silencieux;
                }
                else
                {
                    chaine.empruntee = false;
                    chaine.index = (chaine.index + 1) % tailleChaine;
                    std::cout << "OK\n";
                }
            }
        }
        else if (appel == "end")
        {
            // projection nulle "-" ou deux valeurs g d
            std::string premier;
            std::cin >> premier;
            bool projection = (premier != "-");
            bool renseignee[2] = {false, false};
            if (projection)
            {
                int d = 0;
                std::cin >> d;
                renseignee[0] = (premier == "1");
                renseignee[1] = (d == 1);
            }

            if (!trameOuverte)
            {
                std::cout << "REFUSE AUCUNE\n";
                ++journal;
                continue;
            }

            trameOuverte = false; // la trame se ferme dans tous les cas

            if (projection && renseignee[0] && chaines[0].empruntee)
            {
                std::cout << "REFUSE ACQUISE G\n";
                ++journal;
            }
            else if (projection && renseignee[1] && chaines[1].empruntee)
            {
                std::cout << "REFUSE ACQUISE D\n";
                ++journal;
            }
            else
            {
                std::cout << "OK";
                if (projection && (!renseignee[0] || !renseignee[1]))
                {
                    std::cout << " AVERT";
                    if (!renseignee[0])
                    {
                        std::cout << " G";
                        ++avertissements;
                    }
                    if (!renseignee[1])
                    {
                        std::cout << " D";
                        ++avertissements;
                    }
                }
                std::cout << '\n';
            }
        }
        else
        {
            std::cout << "REFUSE\n";
        }
    }

    std::cout << "JOURNAL " << journal << '\n';
    std::cout << "AVERTISSEMENTS " << avertissements << '\n';
    std::cout << "SILENCIEUX " << silencieux << '\n';
    return 0;
}
