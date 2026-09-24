Le montage : un seul fichier source (src/main.cpp), et deux chemins volontairement invalides dans exo9.jenga — "src/modules/**.cpp" dans files (le dossier n'existe pas) et "include_absent" dans includedirs (idem).

jenga info : ne dit rien du problème. Il liste le workspace, les projets et les toolchains disponibles, mais n'affiche jamais les chemins ni les motifs de files/includedirs — donc rien à signaler, même en présence des deux erreurs.

jenga build : presque rien non plus. Le build réussit sans erreur ni avertissement — Found 1 source file(s), compilation, lien, Build Successful. Le seul indice discret est ce compte de fichiers trouvés.

Contre-épreuve : en retirant les deux chemins fautifs, jenga info donne une sortie identique ligne pour ligne, et jenga build aussi (seul le temps d'exécution change légèrement). Rien ne distingue donc visuellement le projet fautif du projet propre.

Conclusion : c'est jenga build, et seulement lui, qui aurait pu faire gagner du temps — via le nombre de fichiers trouvés (Found 1 au lieu du nombre attendu), à condition de savoir combien de fichiers on attend. jenga info n'aide en rien. Pour le dossier d'inclusion absent, aucune des deux commandes n'alerte : l'erreur ne surgira que plus tard, au moment d'un #include qui échoue, et elle pointera vers la ligne du #include, pas vers le .jenga.