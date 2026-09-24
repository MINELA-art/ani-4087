## le fichier rendu

Voici `workspace_salle.jenga`, le fichier que je garde pour tout le livre. il reprend ce qui est deja actif depuis le chapitre 1 et 2 (le projet `projet_salle`, le compteur avec `COMPTEUR_COMPLET`, les modules A et B, les tests) et j'ai ajoute une ligne commentee par chapitre a venir, du chapitre 3 au chapitre 17. chaque ligne dit ce qu'il faudra decocher, et je les deocherai une par une au fur et a mesure du livre.

```python
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# workspace_salle - Jenga Workspace
# Genere par `jenga workspace` le 2026-09-23 09:00:16
# Mis a jour a l'exercice 12 : fichier de projet pour tout le livre.
#
# Chapitres 1 et 2 : actifs (projet minimal, compteur, module A/module B, tests).
# Chapitres 3 a 17 : UNE ligne commentee par chapitre, a decocher dans l'ordre.
# Chaque ligne n'AJOUTE que ce qui est nouveau, on ne touche jamais aux lignes
# deja decochees. Quand un chapitre concerne Windows precisement, une ligne de
# plus, marquee du meme numero, attend dans le filtre "system:Windows".

from Jenga import *

with workspace("workspace_salle"):
    configurations(['Debug', 'Release'])
    targetoses([TargetOS.WINDOWS])
    targetarchs([TargetArch.X86_64])

    # Default toolchain (auto-detected)
    # usetoolchain("host-gcc")

    # Uncomment to use Unitest testing framework
    # with unitest() as u:
    #     u.Precompiled()

    # Project: projet_salle
    with project("projet_salle"):
        consoleapp()
        language("C++")
        cppdialect("C++17")
        location("projet_salle")
        files(["src/**.cpp", "include/**.hpp"])
        defines(["COMPTEUR_COMPLET"])

        # ----- Un chapitre, une ligne -------------------------------------------
        # Ch. 3  NKWindow et NKEvent : passer en windowedapp() et lier la fenetre + les evenements
        # windowedapp(); from jengaconfig import *; nkentseudependson(["NKWindow", "NKEvent"], extra_includes=["src"])
        # Ch. 4  NKRHI et NKRenderer : le rendu, les shaders (GLSlang/SPIRVCross explicites), les en-tetes Vulkan
        # nkentseudependson(["NKRHI", "NKRenderer", "NKSL", "NKGLSlang", "NKSPIRVCross", "NKGlad"], extra_includes=["%{wks.location}/Externals/Libs/Vulkan-Headers-1.4.350/include"]); defines(["NK_RHI_VK_ENABLED"])
        # Ch. 5  Images, modeles, textes, sons : le son (images/modeles viennent deja avec NKRenderer)
        # nkentseudependson(["NKAudio"])
        # Ch. 6  La tete, l'orientation et les deux yeux : le module XR (poses, espaces, simulateur)
        # nkentseudependson(["NKXR"])
        # Ch. 7  La cadence et la prediction : rien a lier, juste le code du chapitre
        # files(["src/cadence/**.cpp"])
        # Ch. 8  Les chaines d'echange : une chaine d'echange par oeil
        # files(["src/swapchain/**.cpp"])
        # Ch. 9  Les actions : les entrees abstraites de NKXR
        # files(["src/actions/**.cpp"])
        # Ch. 10 La composition et les couches : couches de projection et quads
        # files(["src/couches/**.cpp"])
        # Ch. 11 Le vrai backend, deux backends : les en-tetes OpenXR
        # includedirs(["%{wks.location}/Externals/Libs/NKOpenXR/include"])
        # Ch. 12 Rendre deux fois : deux vues, deux projections
        # files(["src/stereo/**.cpp"])
        # Ch. 13 La porte s'ouvre : la camera (passthrough)
        # nkentseudependson(["NKCamera"])
        # Ch. 14 Panneaux qu'on lit, et le son qui place les choses : l'interface
        # nkentseudependson(["NKUI"])
        # Ch. 15 Quelqu'un d'autre entre : le reseau
        # nkentseudependson(["NKNetwork"])
        # Ch. 16 Batir et livrer : les informations du paquet
        # apppublisher("Rihen"); appversion("1.0.0"); licensefile("LICENSE")
        # Ch. 17 Approfondissement : pas de nouvelle dependance prevue, relire et nettoyer le fichier
        # pass

        with filter("system:Windows"):
            defines(["WIN32_LEAN_AND_MEAN"])
            # Ch. 3  links(["dwmapi", "shell32"])
            # Ch. 4  links(["opengl32", "d3d11", "d3d12", "dxgi", "dxguid", "d3dcompiler", "uuid", "ole32"])
            # Ch. 11 links(["advapi32"])      # trouver le runtime OpenXR actif dans le registre
            # Ch. 15 links(["ws2_32"])        # sockets Windows

        with filter("config:Debug"):
            defines(["_DEBUG"])
            symbols(True)
            optimize("Off")

        with filter("config:Release"):
            defines(["NDEBUG"])
            symbols(False)
            optimize("Speed")
```

## d'ou viennent ces lignes

je suis allee voir dans le depot Nkentseu (`config/modules.jenga`, `Kernel/Runtime/NKXR`) pour trouver les vrais noms des modules a lier plus tard : NKWindow, NKEvent, NKRHI, NKRenderer, NKAudio, NKXR, NKCamera, NKUI, NKNetwork. je les ai mis dans l'ordre des chapitres 3 a 17 du cours.

il y a deux chapitres ou je ne suis pas sure : le 13 (la camera, je devine d'apres le titre) et les chapitres 7 a 10 et 12, ou je n'ai trouve aucun nouveau module a lier, seulement du code a ajouter dans `src/`. je corrigerai si le chapitre demande autre chose.

## pourquoi une seule ligne par chapitre

parce que jenga accumule : `nkentseudependson`, `files`, `links` et `defines` s'additionnent d'un appel a l'autre. decocher le chapitre 6 ne touche jamais aux lignes des chapitres 3 a 5. j'ai verifie ca dans le code de Jenga et de Nkentseu avant de rendre le fichier.

## ce que j'ai verifie

tel quel, avec toutes les lignes futures commentees, le fichier se construit normalement dans les deux configurations, exactement comme a l'exercice 3.

je n'ai pas pu verifier que ca marche une fois les lignes decochees : il faut pour ca le moteur Nkentseu complet, qui arrive au chapitre 3.
