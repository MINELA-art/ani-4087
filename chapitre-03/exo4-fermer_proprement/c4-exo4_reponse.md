## 1. Rappel sur `NkWindowCloseEvent`

Un rappel sur `NkWindowCloseEvent` met un booléen à faux. La boucle porte sur ce booléen plutôt que sur `IsOpen()`.

**Code :**

```cpp
bool tourne = true;

// Fermer la fenêtre avec la croix
evenements.AddEventCallback<NkWindowCloseEvent>(
    [&](NkWindowCloseEvent *) {
        tourne = false;
    }
);

while (tourne) {
    evenements.PollEvents();
}
```

**Notes sur ce que j'ai écrit :**

> Le booléen `tourne` est déclaré avant les rappels et capturé par référence (`[&]`), ce qui permet au rappel de modifier la variable locale de `nkmain`.

**Vérification (clic sur la croix de la fenêtre) :**

> la boucle s'arrête imédiatement! je l'ai constaté en lançant le programme et en cliquant sur la croix et la fenetre s'est fermée

---

## 2. Rappel sur `NkKeyPressEvent` (touche Échap)

Un second rappel, sur `NkKeyPressEvent`, met le même booléen à faux lorsque la touche pressée est Échap.

**Code :**

```cpp
// Fermer la fenêtre avec la touche Échap
evenements.AddEventCallback<NkKeyPressEvent>(
    [&](NkKeyPressEvent *e) {
        if (e->GetKey() == NkKey::NK_ESCAPE) {
            tourne = false;
        }
    }
);
```

**Notes sur ce que j'ai écrit :**

> Le rappel reçoit toutes les pressions de touche. Le test `GetKey() == NkKey::NK_ESCAPE` filtre pour ne réagir qu'à Échap, les autres touches sont ignorées. Le rappel modifie le même booléen `tourne` que le premier.

**Vérification (appui sur Échap) :**

>la boucle s'arrête imédiatement! je l'ai constaté en lançant le programme et en appuyant sur echap et la fenetre s'est fermée

---

## 3. Code final complet

```cpp
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
```


## 4. Pourquoi les deux chemins de sortie doivent aboutir au même endroit

Dans mon programme, ni la croix ni Échap ne ferment quoi que ce soit directement. Les deux rappels font exactement la même chose : ils mettent `tourne` à `false`. La sortie réelle se fait ensuite à un seul endroit : la condition `while (tourne)` s'arrête, puis `fenetre.Close()` et `return 0` s'exécutent, une seule fois, quelle que soit la façon dont l'utilisateur a demandé à quitter.

Il y a plusieurs raisons à cela.

**1. Le nettoyage n'est écrit qu'une fois.**
Si chaque rappel fermait la fenêtre lui-même, il faudrait recopier `fenetre.Close()` (et tout autre nettoyage futur : libération de ressources, sauvegarde) dans chacun. Il suffirait d'en oublier un pour que l'un des deux chemins quitte proprement et l'autre non. En faisant converger les chemins vers un point unique, le comportement de sortie est identique par construction.

**2. Les rappels s'exécutent au milieu de `PollEvents()`.**
Les rappels sont appelés pendant que `PollEvents()` traite la file d'événements. Fermer ou détruire la fenêtre à cet instant risquerait de le faire pendant que le système d'événements travaille encore dessus, avec d'autres événements de la même passe potentiellement encore à distribuer. Mettre un booléen à faux ne détruit rien : la fermeture est repoussée à un moment sûr, une fois `PollEvents()` terminé et la boucle quittée.

**3. Les deux demandes peuvent arriver ensemble.**
Rien n'empêche l'utilisateur d'appuyer sur Échap puis de cliquer sur la croix avant la fin de la passe. Avec deux fermetures indépendantes, la fenêtre pourrait être fermée deux fois. Avec le booléen, affecter `false` deux fois est sans effet supplémentaire : l'opération est idempotente, et `Close()` n'est appelé qu'une fois.

**4. Le code de retour et l'état final sont les mêmes.**
Que l'on parte par la croix ou par Échap, il s'agit d'une sortie normale voulue par l'utilisateur. Les deux doivent donc se terminer de la même façon (`return 0`, fenêtre fermée), et pas par deux comportements qui divergeraient peu à peu.

**5. Le programme reste facile à faire évoluer.**
Ajouter un troisième chemin de sortie (un menu « Quitter », un signal du système) ne demande qu'un nouveau rappel qui met `tourne` à `false`. La boucle et le nettoyage ne changent pas.

**En résumé :** les rappels ne font que *signaler* l'intention de quitter ; la boucle et le code qui suit *décident* de la sortie. Séparer les deux garantit un point de sortie unique, sûr et identique pour tous les chemins.

---

## 5. Conclusion

> Remplacer la fenêtre `IsOpen()` par un booléen que je contrôle permet de gérer plusieurs origines de fermeture (croix, Échap) avec un seul point de sortie. Les rappels se contentent d'indiquer qu'il faut quitter, et le nettoyage a lieu une fois, hors de `PollEvents()`, ce qui évite les doublons et les fermetures au mauvais moment.