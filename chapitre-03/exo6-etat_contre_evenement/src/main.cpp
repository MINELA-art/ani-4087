#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkEventDispatcher.h"
#include "NKTime/NkClock.h"

#include <iostream>

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    (void)state;

    NkWindowConfig cfg;
    cfg.title = "MaFenetre - exo6";
    cfg.width = 1280;
    cfg.height = 720;

    NkWindow fenetre(cfg);

    if (!fenetre.IsValid())
        return 1;

    bool tourne = true;

    uint64 compteurEtat = 0;
    uint64 compteurEvenement = 0;

    NkEventSystem &evenements = NkEvents();

    // Compteur événement : un compteur à chaque appui sur Espace
    evenements.AddEventCallback<NkKeyPressEvent>(
        [&](NkKeyPressEvent *e) {
            if (e->GetKey() == NkKey::NK_SPACE)
                ++compteurEvenement;

            if (e->GetKey() == NkKey::NK_ESCAPE)
                tourne = false;
        }
    );

    // Fermeture avec la croix
    evenements.AddEventCallback<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent *) {
            tourne = false;
        }
    );

    while (tourne) {
        evenements.PollEvents();

        // Compteur état : une fois par tour tant que Espace est tenue
        if (NkInput.IsKeyDown(NkKey::NK_SPACE))
            ++compteurEtat;

        NkClock::Sleep((int64)10);
    }

    fenetre.Close();

    std::cout << "Compteur Etat (IsKeyDown) : "
              << compteurEtat << std::endl;

    std::cout << "Compteur Evenement (NkKeyPressEvent) : "
              << compteurEvenement << std::endl;

    return 0;
}