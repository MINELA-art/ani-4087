#include "moduleA.h"
#include "moduleB.h"   // pour pouvoir appeler somme()
 
// Définition de la fonction somme_plus_1000()
// Elle appelle somme() du module B, puis ajoute 1000
int somme_plus_1000(int a, int b) {
    return somme(a, b) + 1000;
}
