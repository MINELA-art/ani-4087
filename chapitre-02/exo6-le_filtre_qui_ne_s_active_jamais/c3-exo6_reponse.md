## fichier .jenga avec filtre appliqué non appliqué
```python
from Jenga import *

with workspace("workspace2"):
    configurations(['Debug', 'Release'])
    targetoses([TargetOS.WINDOWS])
    targetarchs([TargetArch.X86_64])
    
    

    # Project: projet2
    with project("projet2"):
        consoleapp()
        language("C++")
        cppdialect("C++17")
        location("projet2")
        files(["src/**.cpp", "include/**.hpp"])

        with filter("system:Linux"):
           defines(["FILTRE_OK"])
           
```
## fichier main:
#include <iostream>

int main() {
    #ifdef FILTRE_OK
        std::cout << "FILTRE_OK is defined" << std::endl;
    #else
        std::cout << "FILTRE_OK is not defined" << std::endl;
    #endif
    return 0;
}

# le résultat après les commandes jenga build et jenga run: 
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  projet2.exe
     D:\cours_niveau_4\AR et VR\ani-4087\jenga2\workspace2\Build\Bin\Debug-Windows\projet2\projet2.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

FILTRE_OK is not defined

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (0.13s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
PS D:\cours_niveau_4\AR et VR\ani-4087\jenga2\workspace2\projet2> 


## fichier . jenga avec filtre appliqué 
```python
from Jenga import *

with workspace("workspace2"):
    configurations(['Debug', 'Release'])
    targetoses([TargetOS.WINDOWS])
    targetarchs([TargetArch.X86_64])
    
    

    # Project: projet2
    with project("projet2"):
        consoleapp()
        language("C++")
        cppdialect("C++17")
        location("projet2")
        files(["src/**.cpp", "include/**.hpp"])

        with filter("system:Windows"):
           defines(["FILTRE_OK"])
           
```

# sortie après les commandes jenga build et jenga run
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  projet2.exe
     D:\cours_niveau_4\AR et VR\ani-4087\jenga2\workspace2\Build\Bin\Debug-Windows\projet2\projet2.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

FILTRE_OK is defined

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (0.04s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━