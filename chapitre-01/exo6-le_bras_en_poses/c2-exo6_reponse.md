Un bras articulé est une chaîne de poses : chaque articulation ne connaît que sa position relative à l'articulation précédente (son parent). Pour obtenir sa position dans le monde, il faut composer récursivement toutes les poses depuis la racine :

pose_monde(épaule) = pose_locale(épaule)                              // racine, pas de parent
pose_monde(coude)  = Composer(pose_monde(épaule), pose_locale(coude))
pose_monde(main)   = Composer(pose_monde(coude),  pose_locale(main))

C'est exactement la fonction Composer de l'exercice précédent. Et comme la position d'une pose appliquée à l'origine (0,0,0) redonne simplement pose.position (car R(0) + t = t), la position de chaque articulation dans le monde est directement pose_monde.position.

Convention : le bras et l'avant-bras s'étendent le long de Avant() (axe X), au repos.

CODE : 
```cpp
#include <iostream>
#include <cmath>
#include <iomanip>

struct Vec3 {
    double x, y, z;
};

struct Quat {
    double w, x, y, z;
};

struct Pose {
    Vec3 position;
    Quat rotation;
};

Vec3 Avant() { return {1.0, 0.0, 0.0}; }

Vec3 appliquerRotation(const Quat& q, const Vec3& v) {
    double qw = q.w, qx = q.x, qy = q.y, qz = q.z;

    double tx = 2.0 * (qy * v.z - qz * v.y);
    double ty = 2.0 * (qz * v.x - qx * v.z);
    double tz = 2.0 * (qx * v.y - qy * v.x);

    return {
        v.x + qw * tx + (qy * tz - qz * ty),
        v.y + qw * ty + (qz * tx - qx * tz),
        v.z + qw * tz + (qx * ty - qy * tx)
    };
}

Quat multiplierQuat(const Quat& a, const Quat& b) {
    return {
        a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
        a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
        a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
        a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w
    };
}

// Compose deux poses : appliquer poseLocale dans le repère de poseParent
Pose Composer(const Pose& poseParent, const Pose& poseLocale) {
    Pose resultat;
    resultat.rotation = multiplierQuat(poseParent.rotation, poseLocale.rotation);
    Vec3 tTourne = appliquerRotation(poseParent.rotation, poseLocale.position);
    resultat.position = {
        tTourne.x + poseParent.position.x,
        tTourne.y + poseParent.position.y,
        tTourne.z + poseParent.position.z
    };
    return resultat;
}

double norme(const Vec3& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 soustraire(const Vec3& a, const Vec3& b) {
    return { a.x - b.x, a.y - b.y, a.z - b.z };
}

int main() {
    double longueurBras, longueurAvantBras;
    std::cin >> longueurBras >> longueurAvantBras;

    Quat rotationEpaule;
    std::cin >> rotationEpaule.w >> rotationEpaule.x >> rotationEpaule.y >> rotationEpaule.z;

    Quat identite = {1.0, 0.0, 0.0, 0.0};

    // Poses locales : chaque articulation dans le repère de sa précédente
    Pose localCoude = { { longueurBras * Avant().x, longueurBras * Avant().y, longueurBras * Avant().z }, identite };
    Pose localMain  = { { longueurAvantBras * Avant().x, longueurAvantBras * Avant().y, longueurAvantBras * Avant().z }, identite };

    std::cout << std::fixed << std::setprecision(4);

    // --- Cas 1 : épaule au repos (rotation identité) ---
    Pose mondeEpaule1 = { {0.0, 0.0, 0.0}, identite };
    Pose mondeCoude1  = Composer(mondeEpaule1, localCoude);
    Pose mondeMain1   = Composer(mondeCoude1, localMain);

    std::cout << "Avant rotation de l'epaule :\n";
    std::cout << "Coude : " << mondeCoude1.position.x << " " << mondeCoude1.position.y << " " << mondeCoude1.position.z << "\n";
    std::cout << "Main  : " << mondeMain1.position.x << " " << mondeMain1.position.y << " " << mondeMain1.position.z << "\n";

    // --- Cas 2 : épaule tournée ---
    Pose mondeEpaule2 = { {0.0, 0.0, 0.0}, rotationEpaule };
    Pose mondeCoude2  = Composer(mondeEpaule2, localCoude);
    Pose mondeMain2   = Composer(mondeCoude2, localMain);

    std::cout << "Apres rotation de l'epaule :\n";
    std::cout << "Coude : " << mondeCoude2.position.x << " " << mondeCoude2.position.y << " " << mondeCoude2.position.z << "\n";
    std::cout << "Main  : " << mondeMain2.position.x << " " << mondeMain2.position.y << " " << mondeMain2.position.z << "\n";

    // --- Verification : les longueurs des segments sont preservees ---
    double distEpauleCoude2 = norme(soustraire(mondeCoude2.position, mondeEpaule2.position));
    double distCoudeMain2   = norme(soustraire(mondeMain2.position, mondeCoude2.position));

    std::cout << "Verification (longueurs preservees) :\n";
    std::cout << "Epaule-Coude : " << distEpauleCoude2 << " (attendu " << longueurBras << ")\n";
    std::cout << "Coude-Main   : " << distCoudeMain2 << " (attendu " << longueurAvantBras << ")\n";

    return 0;
}
```