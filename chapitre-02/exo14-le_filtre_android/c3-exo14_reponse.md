## le filtre ajoute

dans `workspace_salle.jenga`, j'ai ajoute le filtre Android, sur le modele des applications Android du depot Nkentseu (`Mou.jenga`, `NkCameraDemos.jenga`) :

```python
        with filter("system:Android"):
            usetoolchain("android-ndk")
            defines(["SALLE_ANDROID"])
            links(["android", "log", "EGL", "GLESv3"])
            androidapplicationid("com.projetsalle.app")
            androidminsdk(24)
            androidtargetsdk(34)
            androidcompilesdk(34)
            androidabis(["arm64-v8a"])
            androidnativeactivity(True)
            androidscreenorientation("landscape")
```

j'ai du aussi ajouter `TargetOS.ANDROID` et `TargetArch.ARM64` au workspace, sinon le filtre n'a meme pas de plateforme a viser :

```python
    targetoses([TargetOS.WINDOWS, TargetOS.ANDROID])
    targetarchs([TargetArch.X86_64, TargetArch.ARM64])
```

- bibliotheques : `android` (activite native), `log`, `EGL` et `GLESv3` (affichage).
- define : `SALLE_ANDROID`, pour que le code sache qu'il tourne sur le casque plus tard.
- paquet : identifiant `com.projetsalle.app`, sdk min/cible/compile, architecture `arm64-v8a` (celle du Quest 2), activite native, orientation paysage.

## premiere moitie : "jenga info" ne dit rien

j'ai lance `jenga info` une fois avec `filter("system:Android")` (fausse sur ma machine Windows) et une fois en changeant juste ce filtre en `filter("system:Windows")` (vraie), sans rien toucher d'autre. les deux sorties sont identiques, ligne pour ligne :

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

Location: D:\cours_niveau_4\AR et VR\ani-4087\chapitre-02\exo14-le_filtre_android
Entry file: D:\cours_niveau_4\AR et VR\ani-4087\chapitre-02\exo14-le_filtre_android\workspace_salle.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: Windows, Android
Target Architectures: x86_64, arm64


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

pas une ligne ne change entre les deux versions. `jenga info` ne montre ni les defines ni les libs d'un projet, donc il ne peut pas dire si un filtre s'applique ou pas.

## ce qui, par contre, repond

`jenga compile-flags` accepte un `--platform` et ecrit dans `.jenga\compileflags.jcdb` les defines reellement appliques. je l'ai lancee dans les deux etats du filtre.

condition **vraie** (`filter("system:Windows")`) :

```text
std     c++17
def     WIN32_LEAN_AND_MEAN
def     SALLE_ANDROID
def     COMPTEUR_COMPLET
def     _DEBUG
```

condition **fausse** (`filter("system:Android")`, la version rendue) :

```text
std     c++17
def     WIN32_LEAN_AND_MEAN
def     COMPTEUR_COMPLET
def     _DEBUG
```

`SALLE_ANDROID` disparait bien de la deuxieme sortie. la ou `jenga info` donnait deux resultats identiques, `jenga compile-flags` montre la difference tout de suite.

pour la vraie plateforme Android, la meme commande s'arrete chez moi :

```text
D:\...\exo14-le_filtre_android>jenga compile-flags --platform android-arm64
{"error": "builder: No suitable toolchain found for Android arm64"}
```

logique avec l'exercice 13 : pas d'Android NDK sur ma machine.

## deuxieme moitie : comment je verifierais qu'il s'active pour Android

je lancerais `jenga compile-flags --platform android-arm64` puis j'irais lire `.jenga\compileflags.jcdb`, et le filtre s'active bien si la ligne `def SALLE_ANDROID` y apparait. chez moi cette verification attend l'installation du NDK, que je fais a l'exercice 16.
