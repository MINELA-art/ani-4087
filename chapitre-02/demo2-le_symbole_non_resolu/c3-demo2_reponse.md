j'ai repris les memes fichiers de l'eXO 4 et j'ai retiré une dépendance (moduleB.h). l'erreur est la suivante :



╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     mingw

Build Order (1 projects):
  1. demo2 [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: demo2                                                           Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 3 source file(s)

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: moduleA.cpp                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ D:\cours_niveau_4\AR et                                                                      ║
║ VR\ani-4087\chapitre-02\demo2-le_symbole_non_resolu\DEMO2\demo2\src\moduleA.cpp:2:55: fatal  ║
║ error: moduleB.h: No such file or directory                                                  ║
║  #include "moduleB.h"   // pour pouvoir appeler somme()                                      ║
║                                                        ^                                     ║
║ compilation terminated.                                                                      ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: D:\cours_niveau_4\AR et VR\ani-4087\chapitre-02\demo2-le_symbole_non_resolu\DEMO2\demo2\src\moduleA.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: moduleB.cpp                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ D:\cours_niveau_4\AR et                                                                      ║
║ VR\ani-4087\chapitre-02\demo2-le_symbole_non_resolu\DEMO2\demo2\src\moduleB.cpp:1:21: fatal  ║
║ error: moduleB.h: No such file or directory                                                  ║
║  #include "moduleB.h"                                                                        ║
║                      ^                                                                       ║
║ compilation terminated.                                                                      ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: D:\cours_niveau_4\AR et VR\ani-4087\chapitre-02\demo2-le_symbole_non_resolu\DEMO2\demo2\src\moduleB.cpp
✓   [3/3] Compiled: main.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 0.60s  │
│ Errors: 2  | Failed files: 2                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  0/1
Failed:         1
Errors:         2
Time:           0.60s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ demo2



j'ai donner l'erreur à trois personnes et leur réponse était la même. l'information qui permet de trouver l'erreur est : VR\ani-4087\chapitre-02\demo2-le_symbole_non_resolu\DEMO2\demo2\src\moduleB.cpp:1:21: fatal  ║
║ error: moduleB.h: No such file or directory     