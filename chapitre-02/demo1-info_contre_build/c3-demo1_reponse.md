Lerreur volontaire était d"ecrire dans le fichier jenga G++ au lieu de C++

extrait de code : 
```python
from Jenga import *

with workspace("DEMO1"):
    configurations(['Debug', 'Release'])
    targetoses([TargetOS.WINDOWS])
    targetarchs([TargetArch.X86_64])

    # Project: demo1
    with project("demo1"):
        consoleapp()
        language("C++")
        cppdialect("G++17") # <--ici
        location("demo1")
        files(["src/**.cpp", "include/**.hpp"])

```

# resultat complet de jenga build : 

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
  1. demo1 [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: demo1                                                           Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                 Compilation Error: main.cpp                                  ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ gcc.exe: error: unrecognized command line option '-std=g++17'; did you mean '-std=c++17'?    ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: D:\cours_niveau_4\AR et VR\ani-4087\chapitre-02\demo1-info_contre_build\DEMO1\demo1\src\main.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 0.07s  │
│ Errors: 1  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  0/1
Failed:         1
Errors:         1
Time:           0.07s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ demo1

# resultat complet de jenga info :

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

============================ Jenga Workspace: DEMO1 ============================

Location: D:\cours_niveau_4\AR et VR\ani-4087\chapitre-02\demo1-info_contre_build\DEMO1
Entry file: D:\cours_niveau_4\AR et VR\ani-4087\chapitre-02\demo1-info_contre_build\DEMO1\DEMO1.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: Windows
Target Architectures: x86_64


Projects
------------------------------------------------------------
Name    Kind         Language   Test   External
===============================================
demo1   ConsoleApp   C++        No     No


Available Toolchains
------------------------------------------------------------
Name       Family   Target OS   Arch     Env  
==============================================
host-gcc   gcc      Windows     x86_64   mingw
msvc       msvc     Windows     x86_64   msvc
mingw      gcc      Windows     x86_64   mingw


Daemon
------------------------------------------------------------
Status: Not running

# Réponse de la classe à la question de savoir laquelle des 2 sorties Présente l'erreur
C'est la sortie de Jingle Build En réalité Jingle Info Affiche Worksp local Et on a l'impression que tout est Ok Cette commande ne permet pas De localiser Une erreur quand on a un fichier. Et pourtant jenga build affiche clairement L'erreur dans les lignes suivantes :

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                 Compilation Error: main.cpp                                  ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ gcc.exe: error: unrecognized command line option '-std=g++17'; did you mean '-std=c++17'?    ║