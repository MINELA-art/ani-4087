#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig config;

    NkEventSystem &evenements = NkEvents();

    config.title  = "Ma salle";
    config.width  = 1280;
    config.height = 720;

    NkWindow fenetre(config);

    if (!fenetre.IsValid()) {
        return 1;
    }

    bool tourne = true;

    // Fermer la fenêtre avec la croix
    evenements.AddEventCallback<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent *) {
            tourne = false;
        }
    );

    // Fermer la fenêtre avec la touche Échap
    evenements.AddEventCallback<NkKeyPressEvent>(
        [&](NkKeyPressEvent *e) {
            if (e->GetKey() == NkKey::NK_ESCAPE) {
                tourne = false;
            }
        }
    );

    // Boucle principale
    while (tourne) {
        evenements.PollEvents();
    }

    fenetre.Close();

    return 0;
}