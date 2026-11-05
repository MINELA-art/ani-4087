#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int main()
{
    int nombreImages = 0;
    int nombreOrdres = 0;
    if (!(std::cin >> nombreImages >> nombreOrdres))
        return 0;

    std::vector<std::uint64_t> emplacements(static_cast<std::size_t>(nombreImages), 0);
    std::unordered_set<std::uint64_t> textures;
    int mortes = 0;
    int larges = 0;

    for (int i = 0; i < nombreOrdres; ++i)
    {
        std::string ordre;
        std::cin >> ordre;

        if (ordre == "cree" || ordre == "detruit")
        {
            std::uint64_t poignee = 0;
            std::cin >> poignee;
            if (ordre == "cree")
                textures.insert(poignee);
            else
                textures.erase(poignee);
        }
        else if (ordre == "set")
        {
            std::uint64_t index = 0;
            std::uint64_t poignee = 0;
            std::cin >> index >> poignee;
            if (index >= static_cast<std::uint64_t>(nombreImages))
            {
                std::cout << "SET IGNORE " << index << '\n';
            }
            else
            {
                emplacements[static_cast<std::size_t>(index)] = poignee;
            }
        }
        else if (ordre == "get")
        {
            std::uint64_t index = 0;
            std::cin >> index;
            const std::uint64_t poignee =
                index < static_cast<std::uint64_t>(nombreImages)
                    ? emplacements[static_cast<std::size_t>(index)]
                    : 0;

            if (poignee == 0)
            {
                std::cout << "GET " << index << " 0 VIDE\n";
            }
            else
            {
                if (poignee > UINT32_MAX)
                    ++larges;
                if (textures.count(poignee) != 0)
                {
                    std::cout << "GET " << index << ' ' << poignee << " VIVANTE\n";
                }
                else
                {
                    ++mortes;
                    std::cout << "GET " << index << ' ' << poignee << " MORTE\n";
                }
            }
        }
    }

    std::cout << "MORTES " << mortes << '\n';
    std::cout << "LARGES " << larges << '\n';
    return 0;
}
