// Exercice 8 - Deux poses, deux images
// On dessine avec une pose (5,0 deg), la tete est a 6,4 deg a l'affichage.
// Le compositeur corrige de (pose reelle - pose soumise).
// Il faut soumettre la pose du RENDU, pas la pose actuelle.
#include <iostream>

void afficher(const char* titre, float poseRendu, float poseSoumise, float poseReelle)
{
    float correction = poseReelle - poseSoumise;  // ce que fait le compositeur
    float bonneCorrection = poseReelle - poseRendu; // ce qu'il faudrait
    float erreur = bonneCorrection - correction;

    std::cout << titre << "\n";
    std::cout << "  pose soumise = " << poseSoumise << ", correction = " << correction
              << ", erreur = " << erreur << " deg";
    if (erreur == 0.0f)
        std::cout << " -> image juste\n";
    else
        std::cout << " -> le monde glisse\n";
}

int main()
{
    // deux yeux, donc deux images avec chacune sa pose de rendu
    float poseRendu[2] = {5.0f, 5.0f};
    float poseReelle = 6.4f;
    const char* nomOeil[2] = {"Oeil gauche", "Oeil droit"};

    for (int oeil = 0; oeil < 2; ++oeil)
    {
        std::cout << "== " << nomOeil[oeil] << " ==\n";
        afficher("Soumission de la pose du rendu :", poseRendu[oeil], poseRendu[oeil], poseReelle);
        afficher("Soumission de la pose actuelle :", poseRendu[oeil], poseReelle, poseReelle);
    }
    return 0;
}
