// Code minimal pour ouvrir une fenêtre avec NKWindow

#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkEvent.h"

using namespace nkentseu;

int nkmain(const NkEntryState& state){
    NkWindowConfig config;
    config.title  = "Mon_app";
    config.width  = 1280;
    config.height = 720;

    config.centered = false;
    config.fullscreen = false;
    config.movable = false;
    config.maximizable = false;
    config.minimizable = false;
    

    NkWindow fenetre(config);
    if (!fenetre.IsValid()) {
        return 1;
    }

    while (fenetre.IsOpen()) {
        NkEvents().PollEvents();
    }
    return 0;
}