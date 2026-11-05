#include <array>
#include <cstdint>
#include <iostream>
#include <string>

int main()
{
    int nombreImages = 0;
    std::uint64_t valeurInitiale = 0;
    int nombreOrdres = 0;
    if (!(std::cin >> nombreImages >> valeurInitiale >> nombreOrdres))
        return 0;

    std::array<std::uint64_t, 26> variables;
    variables.fill(valeurInitiale);
    int prochaine = 0;
    bool empruntee = false;

    for (int i = 0; i < nombreOrdres; ++i)
    {
        std::string ordre;
        std::cin >> ordre;

        if (ordre == "acquire")
        {
            char nom = '\0';
            std::cin >> nom;
            const std::size_t index = static_cast<std::size_t>(nom - 'a');
            if (empruntee)
            {
                std::cout << "ACQUIRE FAUX " << nom << ' ' << variables[index] << '\n';
            }
            else
            {
                empruntee = true;
                variables[index] = static_cast<std::uint64_t>(prochaine);
                std::cout << "ACQUIRE VRAI " << nom << ' ' << variables[index] << '\n';
            }
        }
        else if (ordre == "release")
        {
            if (!empruntee)
            {
                std::cout << "RELEASE FAUX\n";
            }
            else
            {
                prochaine = (prochaine + 1) % nombreImages;
                empruntee = false;
                std::cout << "RELEASE VRAI\n";
            }
        }
        else if (ordre == "last")
        {
            const int derniere = (prochaine + nombreImages - 1) % nombreImages;
            std::cout << "LAST " << derniere << '\n';
        }
    }

    std::cout << "EMPRUNTEE " << (empruntee ? "OUI" : "NON") << '\n';
    std::cout << "PROCHAINE " << prochaine << '\n';
    return 0;
}
