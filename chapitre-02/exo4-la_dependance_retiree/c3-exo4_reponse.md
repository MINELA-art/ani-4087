## L'erreur:
L'erreur obtenue après avoir lancé la commande pour construire le projet (en ayant déjà supprimé Un moduleB.cpp qui était lié à module A.cpp qui était à son tour lié à main.cpp) est:

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

ℹ Found 2 source file(s)
✓   [1/2] Compiled: moduleA.cpp
✓   [2/2] Compiled: main.cpp
ℹ Linking...
╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: Link Failed                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ D:\cours_niveau_4\AR et                                                                      ║
║ VR\ani-4087\mes_projets_jenga\workspace_salle\Build\Obj\Debug-Windows\projet_salle\src_modul ║
║ eA.obj: In function `Z15somme_plus_1000ii':                                                  ║
║ D:/cours_niveau_4/AR et                                                                      ║
║ VR/ani-4087/mes_projets_jenga/workspace_salle/projet_salle/src/moduleA.cpp:7: undefined      ║
║ reference to `somme(int, int)'                                                               ║
║ collect2.exe: error: ld returned 1 exit status                                               ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝
✗ Link failed: Build\Bin\Debug-Windows\projet_salle\projet_salle.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 1.40s  │
│ Errors: 2  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  0/1
Failed:         1
Errors:         2
Time:           1.41s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ projet_salle

## à laquelle des quatre étapes de la chaîne de construction il appartient-elle ?
Elle appartient à l'édition des liens. Le message d'erreur le précise clairement
