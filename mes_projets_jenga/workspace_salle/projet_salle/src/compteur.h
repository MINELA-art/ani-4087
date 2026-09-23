//#ifndef COMPTEUR_H
// #define COMPTEUR_H
 
#ifdef COMPTEUR_COMPLET
 
// Version complète : activée si COMPTEUR_COMPLET est défini
class Compteur {
private:
    int valeur;
 
public:
    Compteur(int depart = 0) : valeur(depart) {}
 
    void incrementer() { valeur++; }
    void decrementer() { valeur--; }
    int getValeur() const { return valeur; }
};
 
#else
 
// Coquille vide : aucun membre, aucune fonctionnalité
class Compteur {
};
 
#endif // COMPTEUR_COMPLET
 
#endif // COMPTEUR_H
 