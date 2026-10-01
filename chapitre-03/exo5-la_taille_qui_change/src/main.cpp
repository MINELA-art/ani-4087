#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKTime/NkClock.h"

#include <iostream>

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    (void)state;

    NkWindowConfig cfg;
    cfg.title = "MaFenetre - redimensionnez-moi";
    cfg.width = 1280;
    cfg.height = 720;
    cfg.resizable = true;

    NkWindow fenetre(cfg);

    if (!fenetre.IsValid())
        return 1;

    bool tourne = true;

    NkEventSystem &evenements = NkEvents();

    evenements.AddEventCallback<NkWindowResizeEvent>(
        [&](NkWindowResizeEvent *e) {
            std::cout << e->GetWidth()
                      << " x "
                      << e->GetHeight()
                      << std::endl;
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
        evenements.PollEvents();
        NkClock::Sleep((int64)10);
    }

    fenetre.Close();

    return 0;
}
