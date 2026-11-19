// Exercice 7 - Un panneau en couche quad
// On soumet deux couches : la projection (la scene) puis un quad (un menu).
// Le compositeur les empile dans l'ordre. Le quad est compose en dernier,
// a pleine resolution, donc plus net qu'un panneau dessine dans la scene.
#include <iostream>
#include <string>

struct Couche
{
    std::string type;
    std::string contenu;
    int reechantillonnages; // nombre de fois ou l'image est re-echantillonnee
};

struct CoucheQuad
{
    float largeur; // metres
    float hauteur; // metres
    float distance; // metres devant l'utilisateur
};

int main()
{
    CoucheQuad menu = {1.0f, 0.5f, 1.5f};

    // panneau dessine dans la scene : rendu, deformation lentilles, reprojection
    Couche panneauDansScene = {"projection", "scene + panneau", 3};
    // quad : compose directement a la fin
    Couche panneauQuad = {"quad", "menu", 1};

    Couche couches[2] = {{"projection", "scene", 3}, panneauQuad};

    std::cout << "Menu quad : " << menu.largeur << " x " << menu.hauteur
              << " m a " << menu.distance << " m\n";

    std::cout << "Ordre de composition :\n";
    for (int i = 0; i < 2; ++i)
        std::cout << "  " << i + 1 << ". " << couches[i].type << " (" << couches[i].contenu << ")\n";

    std::cout << "Panneau dans la scene : " << panneauDansScene.reechantillonnages
              << " re-echantillonnages -> texte flou\n";
    std::cout << "Panneau en quad       : " << panneauQuad.reechantillonnages
              << " re-echantillonnage -> texte net\n";
    return 0;
}
