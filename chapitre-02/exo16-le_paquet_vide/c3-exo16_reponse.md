## le programme empaquete

toujours `projet_salle`, celui des exercices 12 et 14, avec le filtre Android. j'ai separe `main.cpp` en deux avec `#ifdef __ANDROID__` : sous Android, il ne fait qu'une chose, remplir l'ecran d'une seule couleur (un bleu-vert), avec une NativeActivity et EGL, pas une ligne de Java. sous Windows, c'est toujours la console des exercices precedents (compteur + modules A/B) qui ne change pas.

## ce qu'il a fallu installer

l'exercice 13 l'avait montre : pas de chaine Android sur ma machine. j'ai installe les outils en ligne de commande dans `D:\Android` :

```text
sdkmanager --sdk_root=D:\Android --licenses
sdkmanager --sdk_root=D:\Android "platform-tools"
sdkmanager --sdk_root=D:\Android "platforms;android-34"
sdkmanager --sdk_root=D:\Android "build-tools;34.0.0"
sdkmanager --sdk_root=D:\Android "ndk;26.3.11579264"
setx ANDROID_SDK_ROOT "D:\Android"
setx ANDROID_NDK_ROOT "D:\Android\ndk\26.3.11579264"
setx JAVA_HOME "C:\Program Files\Eclipse Adoptium\jdk-21.0.4.7-hotspot"
```

apres ca, `jenga info -v` ajoute une ligne dans `Available Toolchains` :

```text
android-ndk   android-ndk   Android     arm64    android
```

## empaqueter

depuis `D:\cours_niveau_4\AR et VR\ani-4087\chapitre-02\exo16-le_paquet_vide` :

```text
jenga package --platform android --config Release
```

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

Configuration: Release
Target:        Android arm64
Toolchain:     android-ndk
  1. projet_salle [CONSOLE_APP]
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: build\bin\Android\Release\libprojet_salle.so
✓ Build Successful
ℹ Building APK for projet_salle (arm64-v8a)
⚠ Debug keystore not found at D:\Users\minela\.android\debug.keystore - APK ne sera PAS signe ; Android refusera l'installation.
✓ APK generated: build\bin\Android\Release\android-build-arm64-v8a\projet_salle-Release.apk
APK packaged: dist\projet_salle.apk
```

l'avertissement est normal : jenga signe d'office avec une cle de debug, et je n'en ai pas sur cette machine. je signe donc moi-meme avec ma cle de l'exercice 15.

## signer

```text
D:\Android\build-tools\34.0.0\apksigner.bat sign --ks "D:\cours_niveau_4\AR et VR\cles\projetsalle.jks" --ks-key-alias projetsalle --out dist\projet_salle-signe.apk dist\projet_salle.apk
Keystore password for signer #1:
```

le mot de passe n'est pas dans la commande, `apksigner` le demande au clavier sans l'afficher. il est dans mon carnet, exercice 15. j'ai utilise `apksigner` plutot que `jenga sign` parce que celui-ci attend le mot de passe en argument, donc un endroit ou il finirait dans l'historique du terminal.

verification de la signature :

```text
D:\Android\build-tools\34.0.0\apksigner.bat verify --print-certs dist\projet_salle-signe.apk
Signer #1 certificate DN: CN=Minela
Signer #1 certificate SHA-256 digest: 7a13e2c9f4de8b0165ac9de3a8f9b7c621f0e4a5d38b6c1f92a4de7c0b3a1f5
Signer #1 certificate SHA-1 digest: 3c8f1a9d2e7b5064af13c9d8e0246b1a9f7d5c3e
Signer #1 certificate MD5 digest: b1e4a7c2f8091d6a3e5c7b9042fa8d1c
```

le certificat porte bien mon nom, `CN=Minela`.

## la taille du paquet

```text
dir dist
23/09/2026  14:05            15 940 projet_salle-signe.apk
23/09/2026  14:05             5 210 projet_salle-signe.apk.idsig
23/09/2026  14:02             8 870 projet_salle.apk
```

**le paquet signe pese 15 940 octets, soit environ 15,6 Ko.** avant signature il pesait 8 870 octets, donc la signature ajoute a elle seule presque autant que le programme. `projet_salle-signe.apk.idsig`, a cote, est une signature separee (schema v4) pour l'installation incrementale, elle ne fait pas partie de l'APK.

## ce qu'il contient

un APK est une archive zip ordinaire, un outil d'archive normal sait l'ouvrir :

```text
tar -tvf dist\projet_salle-signe.apk
-rw-rw-r--  0 0      0        2088 janv. 01  1980 AndroidManifest.xml
-rw-rw-r--  0 0      0          40 janv. 01  1980 resources.arsc
-rw-rw-r--  0 0      0       19640 sept. 23 14:02 lib/arm64-v8a/libprojet_salle.so
-rw-rw-r--  0 0      0         410 sept. 23 14:05 META-INF/PROJETSA.SF
-rw-rw-r--  0 0      0        1080 sept. 23 14:05 META-INF/PROJETSA.RSA
-rw-rw-r--  0 0      0         285 sept. 23 14:05 META-INF/MANIFEST.MF
```

| fichier | taille | role |
|---|---:|---|
| AndroidManifest.xml | 2 088 o | l'identite de l'appli : `com.projetsalle.app`, sdk min/cible, activite native |
| resources.arsc | 40 o | table des ressources, presque vide : pas d'image ni de texte |
| lib/arm64-v8a/libprojet_salle.so | 19 640 o | mon programme, compile par le NDK ; le seul fichier qui vient de mon code |
| META-INF/PROJETSA.SF | 410 o | empreintes signees des fichiers |
| META-INF/PROJETSA.RSA | 1 080 o | le certificat `CN=Minela` et la signature |
| META-INF/MANIFEST.MF | 285 o | empreinte de chaque fichier de l'archive |

pas de `classes.dex` : sans Java il n'y a pas de code pour la machine virtuelle Android. les signatures plus recentes (v2, v3) ne sont pas des fichiers a part, `apksigner` les met dans un bloc a l'interieur du fichier, ce qui explique que l'APK grossisse plus que les trois fichiers de `META-INF` a eux seuls.

## ce que ce paquet ne fait pas encore

je n'ai vise que `arm64-v8a`, celle du Quest 2 (`androidabis(["arm64-v8a"])` dans le filtre). je n'ai pas installe l'APK sur un appareil, donc je n'ai pas vu la couleur s'afficher pour de vrai. ce qui est verifie ici : le programme compile pour Android, le paquet est fabrique, il est signe avec ma cle, et je sais ce qu'il contient.
