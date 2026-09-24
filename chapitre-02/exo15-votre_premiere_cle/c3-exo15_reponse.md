## la commande employee

lancee depuis mon dossier utilisateur, en dehors du depot `ani-4087` :

```text
mkdir "D:\cours_niveau_4\AR et VR\cles"
jenga keygen -i --alias projetsalle --output "D:\cours_niveau_4\AR et VR\cles\projetsalle.jks"
```

pas de mot de passe dans la commande : avec `-i` (mode interactif), jenga le demande pendant l'execution et la saisie ne s'affiche pas a l'ecran.

sortie obtenue :

```text
============================================================
Generate Android Keystore
============================================================

Key alias [projetsalle]:
Validity (days) [10000]:
Distinguished Name (CN=Name, OU=Org, O=Company, L=City, ST=State, C=Country) [CN=Jenga User]: CN=Minela
Keystore password:
Key password (default: same as keystore):
Generating keystore...
Keystore generated: D:\cours_niveau_4\AR et VR\cles\projetsalle.jks
Alias: projetsalle
```

## ce que j'ai du installer avant

`jenga keygen` s'appuie sur `keytool`, l'outil de Java, et je ne l'avais pas :

```text
where keytool
INFO: Impossible de trouver le fichier specifie.
```

j'ai installe un JDK, puis reouvert le terminal :

```text
winget install EclipseAdoptium.Temurin.21.JDK
where keytool
C:\Program Files\Eclipse Adoptium\jdk-21.0.4.7-hotspot\bin\keytool.exe
```

## ou sont ranges la cle et le mot de passe

- **la cle** est dans `D:\cours_niveau_4\AR et VR\cles\projetsalle.jks`, un dossier de mon disque qui n'est pas dans le depot `ani-4087` et qui n'a jamais ete suivi par Git.
- **le mot de passe**, avec l'emplacement du fichier et l'alias `projetsalle`, je l'ai note dans un carnet chez moi, pas sur l'ordinateur. il n'apparait dans aucun fichier, ni ici ni dans le depot.

pour etre sure qu'une cle ne parte jamais par erreur sur GitHub, mon `.gitignore` exclut `*.jks`, `*.keystore` et `*.p12`.

## deux pieges a eviter avec "jenga keygen"

- **sans `-i`**, jenga ne demande aucun mot de passe : il prend "android" par defaut pour le magasin et pour la cle, un mot de passe que tout le monde connait. la cle ne protege plus rien.
- **sans `--output`**, la cle est creee sous le nom `keystore.jks` dans le dossier courant. si je l'avais lancee depuis le dossier de l'exercice, elle finissait dans le depot.

## pourquoi je note le mot de passe quelque part

une application Android doit etre signee avec la meme cle a chaque mise a jour. si je perds le mot de passe, la cle devient inutilisable et je ne peux plus jamais publier de mise a jour sous le meme nom d'application. le garder juste dans ma tete, ce n'est pas suffisant.
