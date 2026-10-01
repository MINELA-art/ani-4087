le fichier jenga a été rendu dans le dossier de cet exercice. 

le code minimal étant: 
````cpp

#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig config;
    config.title  = "Ma salle";
    config.width  = 1280;
    config.height = 720;

    NkWindow fenetre(config);
    if (!fenetre.IsValid()) {
        return 1;
    }

    while (fenetre.IsOpen()) {
        NkEvents().PollEvents();
    }
}
```

cette tache m'a pris exactement 2 jours pour installer tout le necessaire jusqu'à obtenir le resultat 