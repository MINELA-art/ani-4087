#include <iostream>

int main() {
    #ifdef FILTRE_OK
        std::cout << "FILTRE_OK is defined" << std::endl;
    #else
        std::cout << "FILTRE_OK is not defined" << std::endl;
    #endif
    return 0;
}
