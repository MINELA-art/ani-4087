// Exercice 1 - La boucle complete
// Simulation simple de la boucle d'une trame :
// evenements, attente, debut, (rendu si demande), fin de trame TOUJOURS.
#include <iostream>

struct Pose
{
    float lacet; // rotation de la tete en degres
};

struct VueProjection
{
    Pose pose;   // pose AVEC laquelle on a dessine
    float champ; // champ de vision en degres
    int chaine;  // numero de la chaine d'images
    int image;   // derniere image relachee
};

struct CoucheProjection
{
    const char* espace;
    VueProjection vues[2];
};

// ---- petit "systeme" simule ----
long long horloge = 0;         // temps courant en ms
const long long LATENCE = 15;  // ecart entre maintenant et l'affichage
const float VITESSE_TETE = 0.1f; // degres par ms

float lacetTete(long long instant) { return VITESSE_TETE * instant; }

int prochaineImage[2] = {0, 0};
int derniereLiberee[2] = {-1, -1};

int main()
{
    for (int trame = 1; trame <= 5; ++trame)
    {
        // 1. evenements
        std::cout << "Trame " << trame << " : evenements traites\n";

        // 2. attente de la trame : le systeme donne l'instant predit
        horloge += 11;
        long long instantPredit = horloge + LATENCE;
        bool doitDessiner = (trame != 3); // a la trame 3 le systeme dit "ne dessine pas"

        // 3. debut de trame
        std::cout << "  debut, instant predit = " << instantPredit << " ms\n";

        if (!doitDessiner)
        {
            // 4. rien a dessiner : on termine QUAND MEME la trame, sans couche
            std::cout << "  fin de trame avec 0 couche\n";
            continue;
        }

        // 4. localisation des vues pour l'instant predit
        CoucheProjection couche;
        couche.espace = "STAGE";
        for (int oeil = 0; oeil < 2; ++oeil)
        {
            Pose poseRendu = {lacetTete(instantPredit)};

            // acquisition, rendu, liberation
            int image = prochaineImage[oeil];
            std::cout << "  oeil " << oeil << " : rendu dans l'image " << image
                      << " avec lacet " << poseRendu.lacet << "\n";
            derniereLiberee[oeil] = image;
            prochaineImage[oeil] = (image + 1) % 3;

            // remplissage de la couche avec la pose du rendu
            couche.vues[oeil] = {poseRendu, 90.0f, oeil, derniereLiberee[oeil]};
        }

        // 5. fin de trame : toujours
        std::cout << "  fin de trame avec 1 couche (espace " << couche.espace
                  << ", instant " << instantPredit << ")\n";
    }
    return 0;
}
