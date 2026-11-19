// Exercice 3 - Le blocage, provoque
// On oublie volontairement la fin de trame quand il n'y a rien a dessiner.
// Le systeme attend une fin pour chaque debut : l'attente suivante bloque.
#include <iostream>

const bool AVEC_ERREUR = true; // mettre false pour la version correcte

int main()
{
    bool doitDessiner[6] = {true, true, false, true, true, true};
    bool trameOuverte = false;

    for (int trame = 0; trame < 6; ++trame)
    {
        // attente de la trame : bloque si la precedente n'est pas terminee
        if (trameOuverte)
        {
            std::cout << "Trame " << trame + 1
                      << " : BLOQUE, la trame precedente n'a jamais ete terminee\n";
            std::cout << "Le programme se fige (casque remis = rien ne repart).\n";
            return 1;
        }

        trameOuverte = true; // debut de trame

        if (!doitDessiner[trame] && AVEC_ERREUR)
        {
            std::cout << "Trame " << trame + 1 << " : rien a dessiner, fin de trame OUBLIEE\n";
            continue;
        }

        trameOuverte = false; // fin de trame
        std::cout << "Trame " << trame + 1 << " : terminee\n";
    }

    std::cout << "Toutes les trames sont terminees.\n";
    return 0;
}
