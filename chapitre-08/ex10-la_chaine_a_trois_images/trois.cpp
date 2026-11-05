#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    int nombreScenarios = 0;
    if (!(std::cin >> nombreScenarios))
        return 0;

    for (int scenario = 0; scenario < nombreScenarios; ++scenario)
    {
        int nombreImages = 0;
        int dureeLecture = 0;
        int nombreTrames = 0;
        std::cin >> nombreImages >> dureeLecture >> nombreTrames;

        std::vector<int> imagesSoumises;
        int conflits = 0;
        for (int trame = 1; trame <= nombreTrames; ++trame)
        {
            const int image = (trame - 1) % nombreImages;
            bool conflit = false;
            const int premiereTrameLue = std::max(1, trame - dureeLecture);
            for (int precedente = premiereTrameLue; precedente < trame; ++precedente)
            {
                if (imagesSoumises[static_cast<std::size_t>(precedente - 1)] == image)
                {
                    conflit = true;
                    break;
                }
            }

            imagesSoumises.push_back(image);
            if (conflit)
            {
                ++conflits;
                std::cout << trame << " IMAGE " << image << " CONFLIT\n";
            }
            else
            {
                std::cout << trame << " IMAGE " << image << " LIBRE\n";
            }
        }

        std::cout << "CONFLITS " << nombreImages << ' '
                  << dureeLecture << ' ' << conflits << '\n';
    }
    return 0;
}
