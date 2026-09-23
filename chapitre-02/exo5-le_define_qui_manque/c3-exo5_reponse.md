##  sortie de la Compileation avec le define.
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
  1. projet_salle [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: projet_salle                                                    Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 4 source file(s)
✓   [1/4] Compiled: moduleB.cpp
✓   [2/4] Compiled: moduleA.cpp
✓   [3/4] Compiled: main.cpp
✓   [4/4] Compiled: test_compteur.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\projet_salle\projet_salle.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.75s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           0.75s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

##  sortie de la Compileation sans le define.


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
  1. projet_salle [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: projet_salle                                                    Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 4 source file(s)
✓   [1/4] Compiled: moduleA.cpp
✓   [2/4] Compiled: moduleB.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                 Compilation Error: main.cpp                                  ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ In file included from D:\cours_niveau_4\AR et                                                ║
║ VR\ani-4087\mes_projets_jenga\workspace_salle\projet_salle\src\main.cpp:3:0:                 ║
║ D:\cours_niveau_4\AR et                                                                      ║
║ VR\ani-4087\mes_projets_jenga\workspace_salle\projet_salle\src\Compteur.h:27:2: error:       ║
║ #endif without #if                                                                           ║
║  #endif // COMPTEUR_H                                                                        ║
║   ^~~~~                                                                                      ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: D:\cours_niveau_4\AR et VR\ani-4087\mes_projets_jenga\workspace_salle\projet_salle\src\main.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: test_compteur.cpp                             ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ In file included from D:\cours_niveau_4\AR et                                                ║
║ VR\ani-4087\mes_projets_jenga\workspace_salle\projet_salle\src\test_compteur.cpp:2:0:        ║
║ D:\cours_niveau_4\AR et                                                                      ║
║ VR\ani-4087\mes_projets_jenga\workspace_salle\projet_salle\src\Compteur.h:27:2: error:       ║
║ #endif without #if                                                                           ║
║  #endif // COMPTEUR_H                                                                        ║
║   ^~~~~                                                                                      ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: D:\cours_niveau_4\AR et VR\ani-4087\mes_projets_jenga\workspace_salle\projet_salle\src\test_compteur.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 0.42s  │
│ Errors: 2  | Failed files: 2                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  0/1
Failed:         1
Errors:         2
Time:           0.43s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ projet_salle


## ce que j'aurai pu diagnostiquer :
c'est le premier vu qu'il ne cause pas de problème. le second naturellemant serais plus difficile car il génère une erreur bienque la classe a été déclaré