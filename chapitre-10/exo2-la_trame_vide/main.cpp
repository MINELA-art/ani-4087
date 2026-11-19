// Exercice 2 - La trame vide
// Quand le systeme dit de ne rien dessiner, on termine quand meme la trame
// avec zero couche. On compte les debuts et les fins.
#include <iostream>

int main()
{
    // false = casque retire (le systeme dit de ne rien dessiner)
    bool doitDessiner[6] = {true, false, false, false, true, true};

    int debuts = 0;
    int fins = 0;

    for (int trame = 0; trame < 6; ++trame)
    {
        ++debuts; // debut de trame

        int nombreCouches = 0;
        if (doitDessiner[trame])
            nombreCouches = 1; // on aurait dessine la scene

        ++fins; // fin de trame : TOUJOURS, meme vide
        std::cout << "Trame " << trame + 1 << " : fin avec "
                  << nombreCouches << " couche(s)\n";
    }

    std::cout << "Debuts = " << debuts << ", fins = " << fins << "\n";
    if (debuts == fins)
        std::cout << "Le programme reprend normalement quand on remet le casque.\n";
    return 0;
}
