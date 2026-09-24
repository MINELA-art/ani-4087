Ce que ça construit

Une application fenêtrée (windowedapp) en C++17, nommée NKXRDemo — l'étage 0 de la mission NKXR : une scène NKRenderer rendue en stéréo simulée via le module NKXR et son backend simulateur desktop (souris = mouvements de tête, ZQSD/WASD pour le déplacement, rendu stéréo côte à côte).

Architecture (d'après le commentaire d'en-tête) :

Un renderer compositeur For2D qui possède la frame finale.
Un renderer ForGame par œil, en rendu offscreen partagé — même patron que NK3DModeler / NkAnimaEditor.
Aucune passe de NKRenderer n'est modifiée : l'effet stéréo est obtenu en composant deux rendus offscreen, pas en touchant au moteur de rendu lui-même.
Points d'ancrage pour un agent : NK_XR_SIM_POSE (pose figée), NK_XR_SHOT (captures par œil), NK_XR_EXIT.
Ce dont il dépend

Liste explicite via nkentseudependson(...) — une chaîne de dépendances qui va du XR jusqu'aux fondations :

NKXR → NKRenderer → NKRHI → NKSL → NKGLSlang / NKSPIRVCross → NKSerialization → NKReflection → NKFileSystem → NKFont → NKImage → NKGlad → NKEvent → NKWindow → NKMath → NKTime → NKLogger → NKStream → NKContainers → NKMemory → NKCore → NKPlatform → NKThreading

Plus un include externe : les en-têtes Vulkan-Headers 1.4.350, nécessaires parce que NkVulkanDevice.h (la liaison OpenXR) inclut vulkan.h.

Ce qui change d'un système à l'autre
Système	Toolchain	Defines spécifiques	Liens
Windows (hors UWP, hors Xbox)	TC_WINDOWS	WIN32_LEAN_AND_MEAN, _UNICODE, UNICODE	user32, gdi32, opengl32, dwmapi, shell32, advapi32, d3d11, d3d12, dxgi, dxguid, d3dcompiler, uuid, ole32
Linux (Xlib, défaut)	clang-native	NKENTSEU_FORCE_WINDOWING_XLIB_ONLY	pthread, X11, Xext, GL
macOS	clang-native	—	frameworks Cocoa, QuartzCore, OpenGL

À quoi s'ajoute, indépendamment du système : NK_RHI_VK_ENABLED (global au projet, pas filtré par plateforme — donc actif sur les trois), et un couple de blocs Debug/Release classiques (_DEBUG/DEBUG non optimisé avec symboles, vs NDEBUG optimisé sans symboles).

Les trois pièges documentés

1. Dépendances explicites à NKGLSlang / NKSPIRVCross

« Le linker d'un exécutable qui tire NKSL/NKRHI ne les récupère pas transitivement (piège documenté dans NkLocomotionDemo.jenga, 2026-07-23). »

Sans cette ligne : NKSL/NKRHI sont bien listés comme dépendances, mais leur propre dépendance vers NKGLSlang/NKSPIRVCross ne remonterait pas automatiquement jusqu'à l'exécutable final. Résultat attendu : échec à l'édition de liens (symboles manquants de ces deux bibliothèques), alors même que la compilation de chaque .cpp réussirait — un piège classique et difficile à diagnostiquer puisque l'erreur n'apparaît qu'au link, loin de sa cause.

2. Le define NK_RHI_VK_ENABLED

« Define LOCAL de NKRHI (non propagé) : sans lui, NkVulkanDevice.h montre sa classe STUB et la liaison OpenXR ne compile pas. »

Sans cette ligne : NkVulkanDevice.h exposerait une classe stub vide au lieu de l'implémentation réelle. Le code de liaison OpenXR, qui s'attend à une vraie classe Vulkan fonctionnelle, ne compilerait tout simplement pas (méthodes/membres attendus absents de la classe stub) — un échec à la compilation cette fois, pas au link.

3. Le lien advapi32 sous Windows

« RegGetValueA de la découverte du runtime OpenXR actif (NkXrOpenXRBackend, étape 2a). »

Sans cette ligne : le code appelant RegGetValueA (utilisé pour lire le registre Windows et détecter quel runtime OpenXR est actif) échouerait au link avec un symbole externe non résolu — puisque RegGetValueA vit dans advapi32.lib, qui ne fait pas partie des bibliothèques Windows liées par défaut (user32, gdi32, etc.).

Point commun aux trois pièges : ce sont tous des cas où une dépendance réelle du code (une bibliothèque, une fonction Windows, une macro conditionnelle) n'est pas détectée automatiquement par la chaîne de build — soit parce que la propagation transitive ne fonctionne pas comme on l'attendrait, soit parce qu'un define local conditionne silencieusement le contenu d'un header.