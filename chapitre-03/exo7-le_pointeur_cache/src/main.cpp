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
    cfg.title = "MaFenetre - exo7";
    cfg.width = 1280;
    cfg.height = 720;
    cfg.centered = true;

    NkWindow fenetre(cfg);

    if (!fenetre.IsValid())
        return 1;

    fenetre.ShowMouse(false);
    fenetre.ClipMouseToClient(true);

    bool tourne = true;

    NkEventSystem &evenements = NkEvents();

    evenements.AddEventCallback<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent *) {
            tourne = false;
        }
    );

    evenements.AddEventCallback<NkKeyPressEvent>(
        [&](NkKeyPressEvent *e) {
            if (e->GetKey() == NkKey::NK_ESCAPE)
                tourne = false;
        }
    );

    while (tourne) {
        NkInput.NewFrame();
        evenements.PollEvents();

        std::cout << "x=" << NkInput.MouseX()
                  << " y=" << NkInput.MouseY()
                  << " rawDelta=("
                  << NkInput.MouseRawDeltaX()
                  << ","
                  << NkInput.MouseRawDeltaY()
                  << ")"
                  << std::endl;

        NkClock::Sleep((int64)10);
    }

    // Toujours rendre le contrôle de la souris
    fenetre.ClipMouseToClient(false);
    fenetre.ShowMouse(true);

    fenetre.Close();

    return 0;
}