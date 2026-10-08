#include <cstdint>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace
{
const std::uint32_t RENDER2D = 1u;
const std::uint32_t RENDER3D = 2u;
const std::uint32_t TEXT = 4u;
const std::uint32_t UI = 8u;
const std::uint32_t SHADOW = 16u;
const std::uint32_t POST_PROCESS = 32u;
const std::uint32_t VFX = 64u;
const std::uint32_t ANIMATION = 128u;
const std::uint32_t OVERLAY = 256u;
const std::uint32_t SIMULATION = 512u;
const std::uint32_t OFFSCREEN = 1024u;
const std::uint32_t RAYTRACING = 2048u;
const std::uint32_t GPU_CULLING = 4096u;
const std::uint32_t TOUS = 4294967295u;

// Les treize drapeaux simples, avec leur nom et leur valeur.
struct Simple
{
    const char* nom;
    std::uint32_t valeur;
};

const Simple SIMPLES[13] = {
    {"RENDER2D", RENDER2D}, {"RENDER3D", RENDER3D}, {"TEXT", TEXT},
    {"UI", UI}, {"SHADOW", SHADOW}, {"POST_PROCESS", POST_PROCESS},
    {"VFX", VFX}, {"ANIMATION", ANIMATION}, {"OVERLAY", OVERLAY},
    {"SIMULATION", SIMULATION}, {"OFFSCREEN", OFFSCREEN}, {"RAYTRACING", RAYTRACING},
    {"GPU_CULLING", GPU_CULLING}};

// Un drapeau et les drapeaux dont il a besoin, dans l'ordre imposé.
struct Dependance
{
    const char* nom;
    std::uint32_t valeur;
    std::vector<std::pair<const char*, std::uint32_t>> besoins;
};
} // namespace

int main()
{
    // Table des noms connus (simples et composés).
    std::map<std::string, std::uint32_t> connus;
    for (const Simple& s : SIMPLES)
        connus[s.nom] = s.valeur;
    connus["NONE"] = 0u;
    connus["2D_ESSENTIALS"] = RENDER2D | TEXT;
    connus["3D_BASE"] = RENDER3D | SHADOW | POST_PROCESS;
    connus["DEBUG"] = OVERLAY | SIMULATION;
    connus["ALL"] = TOUS;

    int n = 0;
    if (!(std::cin >> n))
        return 0;

    // Sans aucun nom, la configuration garde sa valeur par défaut : ALL.
    std::uint32_t valeur = (n == 0) ? TOUS : 0u;

    for (int i = 0; i < n; ++i)
    {
        std::string nom;
        std::cin >> nom;

        const auto it = connus.find(nom);
        if (it == connus.end())
            std::cout << "INCONNU " << nom << "\n";
        else
            valeur |= it->second; // OU binaire, jamais d'addition
    }

    std::cout << "VALEUR " << valeur << "\n";

    char hexa[16];
    std::snprintf(hexa, sizeof(hexa), "0x%08X", static_cast<unsigned int>(valeur));
    std::cout << "HEXA " << hexa << "\n";

    // Dépendances, dans l'ordre : TEXT, UI, SHADOW, OVERLAY.
    const std::vector<Dependance> dependances = {
        {"TEXT", TEXT, {{"RENDER2D", RENDER2D}}},
        {"UI", UI, {{"RENDER2D", RENDER2D}, {"TEXT", TEXT}}},
        {"SHADOW", SHADOW, {{"RENDER3D", RENDER3D}}},
        {"OVERLAY", OVERLAY, {{"RENDER2D", RENDER2D}, {"TEXT", TEXT}}}};

    for (const Dependance& d : dependances)
    {
        if ((valeur & d.valeur) == 0u)
            continue; // un drapeau éteint ne réclame rien
        for (const auto& besoin : d.besoins)
            if ((valeur & besoin.second) == 0u)
                std::cout << "MANQUE " << d.nom << " " << besoin.first << "\n";
    }

    int allumes = 0;
    for (const Simple& s : SIMPLES)
        if ((valeur & s.valeur) != 0u)
            ++allumes;

    std::cout << "ALLUMES " << allumes << "\n";
    std::cout << "ETEINTS " << (13 - allumes) << "\n";
    return 0;
}