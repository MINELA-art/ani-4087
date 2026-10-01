# Exercice 5 — Redimensionnement de la fenêtre

## Code

```cpp
#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKTime/NkClock.h"

#include <iostream>

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title = "MaFenetre";
    cfg.width = 1280;
    cfg.height = 720;
    cfg.resizable = true;

    NkWindow fenetre(cfg);

    if (!fenetre.IsValid())
        return 1;

    NkEventSystem &evenements = NkEvents();

    evenements.AddEventCallback<NkWindowResizeEvent>(
        [&](NkWindowResizeEvent *e) {
            std::cout << e->GetWidth()
                      << " x "
                      << e->GetHeight()
                      << std::endl;
        }
    );

    while (true) {
        evenements.PollEvents();
        NkClock::Sleep((int64)10);
    }

    return 0;
}
```

## Redimensionnement lent

J'ai redimensionné la fenêtre lentement et j'ai obtenu la série suivante :

```text
1298 x 759
1280 x 712
1301 x 759
1283 x 712
1303 x 759
1285 x 712
1305 x 759
1287 x 712
1309 x 760
1291 x 713
1313 x 760
1295 x 713
1314 x 760
1296 x 713
1315 x 761
1297 x 714
1316 x 761
1298 x 714
 
...
```

**Nombre d'événements reçus :** [à compléter]

## Redimensionnement rapide

J'ai ensuite redimensionné la fenêtre d'un coup et j'ai obtenu :

```text
1312 x 764
1294 x 717
1404 x 795
1386 x 748
1473 x 821
1455 x 774
1548 x 855
1530 x 808
1621 x 886
1603 x 839
1621 x 1028
1621 x 918
1603 x 871
1621 x 1028
1621 x 923
1603 x 876
1619 x 1028
1619 x 923
1601 x 876
1601 x 981
...
```

**Nombre d'événements reçus :** [à compléter]

## Conclusion

En comparant les deux séries, je constate que le nombre d'événements `NkWindowResizeEvent` dépend de la manière dont la fenêtre est redimensionnée.

Lors d'un redimensionnement **lent**, davantage de changements intermédiaires sont observés et donc davantage d'événements peuvent être reçus.

Lors d'un redimensionnement **rapide**, moins de changements intermédiaires peuvent être observés et donc moins d'événements peuvent être reçus.

On peut donc conclure que **le nombre d'événements reçus n'est pas nécessairement identique pour un redimensionnement lent et un redimensionnement rapide**.
