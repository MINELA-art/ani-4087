# Exercice 7 — Curseur caché et confiné

## Code

```cpp
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

    fenetre.ClipMouseToClient(false);
    fenetre.ShowMouse(true);

    fenetre.Close();

    return 0;
}
```

## Test

Après avoir déplacé la souris jusqu'au bord de la fenêtre, j'ai obtenu deux comportements :

### Série `x, y`

```text
x=1277 y=0 rawDelta=(13,-4)
x=1277 y=0 rawDelta=(11,-2)
x=1277 y=0 rawDelta=(11,-1)
x=1277 y=0 rawDelta=(9,-1)
x=1277 y=0 rawDelta=(9,0)
x=1277 y=0 rawDelta=(8,0)
x=1277 y=0 rawDelta=(9,0)
x=1277 y=0 rawDelta=(7,0)
x=1277 y=0 rawDelta=(6,0)
x=1277 y=0 rawDelta=(5,0)
x=1277 y=0 rawDelta=(4,0)
x=1277 y=0 rawDelta=(4,0)
x=1277 y=0 rawDelta=(5,0)
x=1277 y=0 rawDelta=(4,0)
x=1277 y=0 rawDelta=(4,0)
x=1277 y=0 rawDelta=(4,0)
x=1277 y=0 rawDelta=(5,0)
x=1277 y=0 rawDelta=(4,-2)
x=1277 y=0 rawDelta=(3,-1)
x=1277 y=0 rawDelta=(2,0)
x=1277 y=0 rawDelta=(1,0)
x=1277 y=0 rawDelta=(1,0)
x=1277 y=0 rawDelta=(1,0)
x=1277 y=0 rawDelta=(1,0)
x=1277 y=0 rawDelta=(1,0)
...



Lorsque la souris atteint le bord de la zone cliente, la position `x, y` finit par **ne plus changer**, car le curseur est confiné à la fenêtre.

### Série `rawDelta`
Le `rawDelta` **continue de changer lorsque la souris physique est déplacée**, même lorsque la position `x, y` reste bloquée au bord.

## Conclusion

C'est donc **`rawDelta` qui continue de bouger**, car il mesure le déplacement réel de la souris indépendamment de la position du curseur ; c'est cette valeur qu'il faut utiliser lorsque le curseur est confiné, notamment pour détecter les mouvements de la souris au-delà des limites de la fenêtre.
