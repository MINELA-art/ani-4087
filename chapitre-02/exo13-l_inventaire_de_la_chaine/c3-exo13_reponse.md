## la commande

lancee depuis le dossier de l'exercice 12 :

```text
D:\cours_niveau_4\AR et VR\ani-4087\chapitre-02\exo12-votre_fichier_de_projet>jenga info -v
```

## le tableau "Available Toolchains" en entier

```text
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

======================= Jenga Workspace: workspace_salle =======================

Location: D:\cours_niveau_4\AR et VR\ani-4087\chapitre-02\exo12-votre_fichier_de_projet
Entry file: D:\cours_niveau_4\AR et VR\ani-4087\chapitre-02\exo12-votre_fichier_de_projet\workspace_salle.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: Windows
Target Architectures: x86_64

System
------------------------------------------------------------
Host OS: Windows
Host Architecture: x86_64
Host Environment: msvc
Host Triple: x86_64-pc-windows-msvc
Python: 3.12.4 (tags/v3.12.4:8e8a4ba, Jun  6 2024, 19:30:16) [MSC v.1940 64 bit (AMD64)]
Jenga version: 2.8.0


Projects
------------------------------------------------------------
Name           Kind         Language   Test   External
======================================================
projet_salle   ConsoleApp   C++        No     No


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
```

## ce qui est present

trois lignes, mais deux compilateurs seulement. `host-gcc` et `mingw` designent le meme GCC (celui de MSYS2, deja utilise pour tous mes builds depuis l'exercice 1, `Toolchain: mingw` dans chaque sortie). `msvc` en plus, lui : Visual Studio est bien installe sur ma machine, meme si je ne m'en suis jamais servie jusqu'ici.

attention, `Host Environment: msvc` dans la section System ne veut pas forcement dire que la chaine msvc est installee : cette ligne decrit juste l'hote, pas les chaines disponibles. ici les deux sont vraies en meme temps, mais ce n'est pas garanti.

## ce qui manque

en comparant avec ce que Jenga sait detecter (les chaines listees dans `Jenga/Core/Toolchains.py`) :

- **Clang** : absent. ni `host-clang`, ni `clang-mingw`, ni `clang-cl` dans le tableau.
- **la chaine croisee vers Linux** (`gcc-cross-linux`) : absente, je ne peux rien construire pour Linux depuis cette machine.
- **`android-ndk`** : absent. c'est celle qui va manquer a l'exercice 14 et 16 pour le Quest 2.
- **`emscripten`** (le Web) : absente.
- **les chaines `zig-*`** : absentes.

## ce qu'il faudrait installer en premier

pour le cours, la priorite c'est l'Android NDK : le moteur Nkentseu vise le casque Quest 2 des le chapitre 11 ("le vrai backend") et le paquet a livrer au chapitre 16, et sans NDK ces deux chapitres-la vont bloquer chez moi. Clang vient juste apres, parce que la chaine `nk-windows-clang-mingw` du moteur (`config/toolchain.jenga` dans Nkentseu) l'appelle directement. le reste (Emscripten, Zig, la chaine croisee Linux) n'est annonce dans aucun chapitre du cours, donc pas urgent.

## ce que j'en retiens

le tableau ne dit que ce qui est la. pour savoir que l'Android NDK manque, il faut deja savoir qu'il pourrait etre la — un peu comme a l'exercice 6, ou l'outil ne disait rien non plus sur ce qu'il n'appliquait pas.
