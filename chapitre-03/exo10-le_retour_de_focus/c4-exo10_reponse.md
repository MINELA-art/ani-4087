# Exercice 10 — Retour de focus

## Code

```cpp
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

    evenements.AddEventCallback<NkMouseRawEvent>(
        [&](NkMouseRawEvent *e) {
            accumulateurX += e->GetDeltaX();
        }
    );

    evenements.AddEventCallback<NkWindowFocusLostEvent>(
        [&](NkWindowFocusLostEvent *) {
            aLeFocus = false;
        }
    );

    evenements.AddEventCallback<NkWindowFocusGainedEvent>(
        [&](NkWindowFocusGainedEvent *) {
            aLeFocus = true;

            std::cout << "Retour du focus : accumulateur = "
                      << accumulateurX << std::endl;
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

            if (e->GetKey() == NkKey::NK_A)
                viderHorsFocus = false;

            if (e->GetKey() == NkKey::NK_B)
                viderHorsFocus = true;
        }
    );

    while (tourne) {
        NkInput.NewFrame();
        evenements.PollEvents();

        if (aLeFocus || viderHorsFocus) {
            accumulateurX = 0;
        }

        NkClock::Sleep((int64)10);
    }

    fenetre.Close();

    return 0;
}
```

## Expérience

### Mode A — sans remise à zéro hors focus

J'ai utilisé le mode **A**, puis :

1. cliqué dans la fenêtre ;
2. cliqué sur une autre fenêtre ;
3. déplacé la souris pendant environ 10 secondes ;
4. cliqué à nouveau dans la fenêtre.

Résultat au retour du focus :

```text
Retour du focus : accumulateur = 723
```

L'accumulateur contient les déplacements reçus pendant que la fenêtre n'avait pas le focus.

### Mode B — avec remise à zéro hors focus

J'ai refait la même expérience avec le mode **B**.

Résultat :

```text
Retour du focus : accumulateur = 289
```

Cette fois, l'accumulateur ne conserve pas les déplacements effectués pendant la perte de focus.

## Observation

En **mode A**, les mouvements effectués pendant les dix secondes hors focus restent dans l'accumulateur et peuvent donc être récupérés au retour du focus.

En **mode B**, l'accumulateur est remis à zéro à chaque image, même lorsque la fenêtre n'a pas le focus. Les mouvements effectués ailleurs sont donc jetés.

## Conclusion

L'expérience montre que **si l'accumulateur n'est pas consommé et remis à zéro pendant la perte de focus, les événements reçus hors focus peuvent s'accumuler et réapparaître au retour du focus**. La remise à zéro pendant la perte de focus empêche cet ancien mouvement d'être appliqué brutalement au retour.
