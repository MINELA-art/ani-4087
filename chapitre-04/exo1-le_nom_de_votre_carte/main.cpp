#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

// Ordre d'essai des interfaces selon la plateforme.
static std::vector<std::string> OrdrePlateforme(const std::string& plateforme)
{
    if (plateforme == "WINDOWS")
        return {"VULKAN", "DX12", "DX11", "OPENGL", "SOFTWARE"};
    if (plateforme == "MACOS")
        return {"METAL", "OPENGL", "SOFTWARE"};
    if (plateforme == "IOS")
        return {"METAL", "SOFTWARE"};
    if (plateforme == "ANDROID")
        return {"VULKAN", "OPENGL", "SOFTWARE"};
    return {"VULKAN", "OPENGL", "SOFTWARE"};
}

// Nom lisible d'une interface.
static std::string NomLisible(const std::string& api)
{
    static const std::map<std::string, std::string> noms = {
        {"VULKAN", "Vulkan"},
        {"DX12", "DirectX 12"},
        {"DX11", "DirectX 11"},
        {"OPENGL", "OpenGL"},
        {"METAL", "Metal"},
        {"SOFTWARE", "Software"}};
    const auto it = noms.find(api);
    return it != noms.end() ? it->second : api;
}

int main()
{
    int n = 0;
    if (!(std::cin >> n))
        return 0;

    int ignorees = 0;
    int logiciel = 0;
    std::set<std::string> differentes;

    for (int i = 0; i < n; ++i)
    {
        std::string nom;
        std::string plateforme;
        int k = 0;
        std::cin >> nom >> plateforme >> k;

        std::set<std::string> dispo;
        for (int j = 0; j < k; ++j)
        {
            std::string api;
            std::cin >> api;
            dispo.insert(api);
        }

        const std::vector<std::string> ordre = OrdrePlateforme(plateforme);
        const std::set<std::string> dansOrdre(ordre.begin(), ordre.end());

        // Interfaces listées mais absentes de l'ordre de la plateforme.
        for (const std::string& api : dispo)
            if (dansOrdre.count(api) == 0)
                ++ignorees;

        // Première interface de l'ordre présente dans la liste ;
        // SOFTWARE marche partout, même s'il n'est pas listé.
        std::string choisie = "SOFTWARE";
        for (const std::string& api : ordre)
        {
            if (api == "SOFTWARE" || dispo.count(api) > 0)
            {
                choisie = api;
                break;
            }
        }

        if (choisie == "SOFTWARE")
            ++logiciel;

        const std::string lisible = NomLisible(choisie);
        differentes.insert(lisible);
        std::cout << nom << " " << lisible << "\n";
    }

    std::cout << "IGNOREES " << ignorees << "\n";
    std::cout << "LOGICIEL " << logiciel << "\n";
    std::cout << "DIFFERENTES " << differentes.size() << "\n";
    return 0;
}