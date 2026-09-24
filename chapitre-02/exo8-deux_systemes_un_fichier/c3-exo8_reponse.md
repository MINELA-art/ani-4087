Sur windows le filtre fonctionne. 
Extrait de code : 
```python
    with filter("system:Windows"):
        consoleapp()
        usetoolchain(TC_WINDOWS)
        defines(["WIN32_LEAN_AND_MEAN"])
        links([])

    with filter("system:Linux"):
        consoleapp()
        usetoolchain("clang-native")
        links([])  

    with filter("config:Debug"):
        defines(["_DEBUG", "DEBUG"])
        optimize("Off")
        symbols(True)
    with filter("config:Release"):
        defines(["NDEBUG"])
        optimize("Speed")
        symbols(False)
```

## ce que je n'ai pas pu vérifier

La syntaxe du filtre Linux — with filter("system:Linux"): et usetoolchain("clang-native") : je les ai écrits par analogie avec NKXRDemo.jenga, mais rien ne garantit que "clang-native" est le nom exact du toolchain attendu dans le jengaconfig.py de votre workspace (ça pourrait être "gcc-native", "linux-clang", etc., selon comment il a été configuré).
La compilation réelle avec clang/g++ sous Linux — impossible à exécuter depuis un poste Windows sans machine virtuelle, WSL, ou accès distant.
links([]) avec une liste vide côté Linux — même incertitude que côté Windows : est-ce accepté tel quel par l'outil, ou faut-il omettre l'appel ?
La résolution des chemins %{wks.location}/Build/Obj/... sous un système de fichiers Linux (séparateurs /, sensibilité à la casse) — potentiellement différente de ce qui se passe sous Windows.
L'exécution du binaire produit — confirmer que somme_plus_1000(5, 7) = 1012 et les messages du compteur s'affichent identiquement dans un terminal Linux.