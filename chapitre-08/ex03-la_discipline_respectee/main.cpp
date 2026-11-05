#include <iostream>
#include <string>
#include <vector>

int main()
{
    int nombreImages = 0;
    int nombreOrdres = 0;
    if (!(std::cin >> nombreImages >> nombreOrdres))
        return 0;

    int prochaine = 0;
    int imageEmpruntee = -1;
    int derniereRelachee = -1;
    bool dessinEnCours = false;
    bool derniereRelacheeDessinee = false;
    bool aSoumettre = false;
    int soumises = 0;
    int refus = 0;
    int horsEmprunt = 0;

    for (int i = 0; i < nombreOrdres; ++i)
    {
        std::string ordre;
        std::cin >> ordre;

        if (ordre == "acquire")
        {
            if (imageEmpruntee != -1)
            {
                ++refus;
                std::cout << "ACQUIRE REFUSE\n";
            }
            else
            {
                imageEmpruntee = prochaine;
                dessinEnCours = false;
                std::cout << "ACQUIRE " << imageEmpruntee << '\n';
            }
        }
        else if (ordre == "draw")
        {
            if (imageEmpruntee == -1)
            {
                ++horsEmprunt;
                std::cout << "DRAW HORS EMPRUNT\n";
            }
            else
            {
                dessinEnCours = true;
                std::cout << "DRAW " << imageEmpruntee << '\n';
            }
        }
        else if (ordre == "release")
        {
            if (imageEmpruntee == -1)
            {
                ++refus;
                std::cout << "RELEASE REFUSE\n";
            }
            else
            {
                derniereRelachee = imageEmpruntee;
                derniereRelacheeDessinee = dessinEnCours;
                aSoumettre = true;
                prochaine = (prochaine + 1) % nombreImages;
                imageEmpruntee = -1;
                std::cout << "RELEASE OK\n";
            }
        }
        else if (ordre == "submit")
        {
            if (imageEmpruntee != -1)
            {
                ++refus;
                std::cout << "SUBMIT REFUSE EMPRUNTEE\n";
            }
            else if (!aSoumettre)
            {
                ++refus;
                std::cout << "SUBMIT REFUSE RIEN\n";
            }
            else
            {
                ++soumises;
                std::cout << "SUBMIT " << derniereRelachee;
                if (!derniereRelacheeDessinee)
                    std::cout << " VIDE";
                std::cout << '\n';
                aSoumettre = false;
            }
        }
    }

    std::cout << "SOUMISES " << soumises << '\n';
    std::cout << "REFUS " << refus << '\n';
    std::cout << "HORS EMPRUNT " << horsEmprunt << '\n';
    return 0;
}
