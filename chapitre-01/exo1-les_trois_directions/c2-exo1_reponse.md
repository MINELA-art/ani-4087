```cpp
#include <iostream>
#include <cmath> // utile pour arrondir

struct Vec3 {
    double x, y, z;
};


// Les trois fonctions qui fixent la convention
Vec3 Avant()  { return {1.0, 0.0, 0.0}; }
Vec3 Haut()   { return {0.0, 0.0, 1.0}; }
Vec3 Droite() { return {0.0, 1.0, 0.0}; }

//la fonction pour calculer le prod scalaire
double produitScalaire(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// fonction pour arrondir sans necessairement utiliser std::round
double arrondi4(double v) {
    return std::round(v * 10000.0) / 10000.0;
}

int main() {
    double x, y, z;
    std::cin >> x >> y >> z; //lire 3 entrées

    Vec3 p = {x, y, z};

    std::cout << arrondi4(produitScalaire(p, Avant()))  << "\n";
    std::cout << arrondi4(produitScalaire(p, Haut()))   << "\n";
    std::cout << arrondi4(produitScalaire(p, Droite())) << "\n";

    return 0;
}
```