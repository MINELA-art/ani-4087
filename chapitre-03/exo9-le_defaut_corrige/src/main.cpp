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
    cfg.title = "MaFenetre - exo8";
    cfg.width = 1280;
    cfg.height = 720;

    NkWindow fenetre(cfg);

    if (!fenetre.IsValid())
        return 1;

    bool tourne = true;
    int32 accumulateurX = 0;

    NkEventSystem &evenements = NkEvents();

    evenements.AddEventCallback<NkMouseRawEvent>(
        [&](NkMouseRawEvent *e) {
            accumulateurX += e->GetDeltaX();
        }
    );

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

        int32 totalX = accumulateurX;
        accumulateurX = 0;

        std::cout << "Accumulateur : " << totalX
                  << " | Delta image : "
                  << NkInput.MouseDeltaThisFrameX()
                  << std::endl;

        NkClock::Sleep((int64)10);
    }

    fenetre.Close();

    return 0;
}