#include <cstdint>
#include <iostream>

int main()
{
    int nombreEtats = 0;
    if (!(std::cin >> nombreEtats))
        return 0;

    int refusees = 0;
    int fauxSigne = 0;
    int fauxNonSigne = 0;

    for (int i = 0; i < nombreEtats; ++i)
    {
        int nombreImages = 0;
        std::uint64_t relachements = 0;
        std::cin >> nombreImages >> relachements;

        if (nombreImages == 0 || nombreImages > 4)
        {
            ++refusees;
            std::cout << nombreImages << ' ' << relachements << " REFUSEE\n";
            continue;
        }

        const int prochaine = static_cast<int>(relachements % static_cast<std::uint64_t>(nombreImages));
        const int juste = (prochaine + nombreImages - 1) % nombreImages;
        const int signe = (prochaine - 1) % nombreImages;
        const std::uint32_t nonSigne =
            static_cast<std::uint32_t>(prochaine - 1) % static_cast<std::uint32_t>(nombreImages);

        if (signe != juste)
            ++fauxSigne;
        if (nonSigne != static_cast<std::uint32_t>(juste))
            ++fauxNonSigne;

        std::cout << nombreImages << ' ' << relachements << ' ' << prochaine << ' '
                  << juste << ' ' << signe << ' ' << nonSigne << '\n';
    }

    std::cout << "REFUSEES " << refusees << '\n';
    std::cout << "FAUX SIGNE " << fauxSigne << '\n';
    std::cout << "FAUX NON SIGNE " << fauxNonSigne << '\n';
    return 0;
}
