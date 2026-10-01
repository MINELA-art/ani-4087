#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkMouseEvent.h"
#include "NKEvent/NkEventDispatcher.h"
#include "NKTime/NkClock.h"

#include <iostream>

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    (void)state;

    NkWindowConfig cfg;
    cfg.title = "MaFenetre - exo10";
    cfg.width = 1280;
    cfg.height = 720;
    cfg.centered = true;

    NkWindow fenetre(cfg);

    if (!fenetre.IsValid())
        return 1;

    bool tourne = true;
    bool aLeFocus = true;
    bool viderHorsFocus = false;

    int32 accumulateurX = 0;

    NkEventSystem &evenements = NkEvents();

    // Accumulation des déplacements
    evenements.AddEventCallback<NkMouseRawEvent>(
        [&](NkMouseRawEvent *e) {
            accumulateurX += e->GetDeltaX();
        }
    );

    // Perte du focus
    evenements.AddEventCallback<NkWindowFocusLostEvent>(
        [&](NkWindowFocusLostEvent *) {
            aLeFocus = false;
        }
    );

    // Retour du focus
    evenements.AddEventCallback<NkWindowFocusGainedEvent>(
        [&](NkWindowFocusGainedEvent *) {
            aLeFocus = true;

            std::cout << "Retour du focus : accumulateur = "
                      << accumulateurX << std::endl;
        }
    );

    // Fermeture avec la croix
    evenements.AddEventCallback<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent *) {
            tourne = false;
        }
    );

    // Échap, A et B
    evenements.AddEventCallback<NkKeyPressEvent>(
        [&](NkKeyPressEvent *e) {
            if (e->GetKey() == NkKey::NK_ESCAPE)
                tourne = false;

            if (e->GetKey() == NkKey::NK_A)
                viderHorsFocus = false;

            if (e->GetKey() == NkKey::NK_B)
                viderHorsFocus = true;
        }
    );

    while (tourne) {
        NkInput.NewFrame();
        evenements.PollEvents();

        // Avec le focus : on consomme toujours.
        // Sans le focus : on consomme seulement en mode B.
        if (aLeFocus || viderHorsFocus) {
            accumulateurX = 0;
        }

        NkClock::Sleep((int64)10);
    }

    fenetre.Close();

    return 0;
}
