Idée mathématique d'abord, avant le code :

Rotation puis translation : p' = R(p) + t
Translation puis rotation : p'' = R(p + t) = R(p) + R(t) (la rotation est linéaire, donc elle se distribue)

Les deux résultats coïncident quand :

R(p) + t = R(p) + R(t)
        ⟺  t = R(t)

C'est-à-dire quand le vecteur de translation t est invariant par la rotation — ce qui ne dépend pas du point p (il se simplifie des deux côtés), mais uniquement de la pose elle-même. Concrètement, t doit être sur l'axe de rotation du quaternion (ou alors la rotation est l'identité, ou t est nul).

CODE:
```cPP
#include <iostream>
#include <cmath>

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

Vec3 appliquerRotation(const Quat& q, const Vec3& v) {
    double qw = q.w, qx = q.x, qy = q.y, qz = q.z;

    double tx = 2.0 * (qy * v.z - qz * v.y);
    double ty = 2.0 * (qz * v.x - qx * v.z);
    double tz = 2.0 * (qx * v.y - qy * v.x);

    Vec3 result;
    result.x = v.x + qw * tx + (qy * tz - qz * ty);
    result.y = v.y + qw * ty + (qz * tx - qx * tz);
    result.z = v.z + qw * tz + (qx * ty - qy * tx);

    return result;
}

// Rotation puis translation : p' = R(p) + t
Vec3 appliquerPoseRotationDabord(const Pose& pose, const Vec3& point) {
    Vec3 pointTourne = appliquerRotation(pose.rotation, point);
    return {
        pointTourne.x + pose.position.x,
        pointTourne.y + pose.position.y,
        pointTourne.z + pose.position.z
    };
}

// Translation puis rotation : p' = R(p + t)
Vec3 appliquerPoseTranslationDabord(const Pose& pose, const Vec3& point) {
    Vec3 pointTranslate = {
        point.x + pose.position.x,
        point.y + pose.position.y,
        point.z + pose.position.z
    };
    return appliquerRotation(pose.rotation, pointTranslate);
}

int main() {
    Pose pose;
    Vec3 point;

    std::cin >> pose.position.x >> pose.position.y >> pose.position.z;
    std::cin >> pose.rotation.w >> pose.rotation.x >> pose.rotation.y >> pose.rotation.z;
    std::cin >> point.x >> point.y >> point.z;

    Vec3 resultat1 = appliquerPoseRotationDabord(pose, point);
    Vec3 resultat2 = appliquerPoseTranslationDabord(pose, point);

    std::cout << resultat1.x << " " << resultat1.y << " " << resultat1.z << "\n";
    std::cout << resultat2.x << " " << resultat2.y << " " << resultat2.z << "\n";

    return 0;
}
```

Exemple où les deux coïncident :

Prenons une rotation de 90° autour de l'axe Z, et une translation le long de l'axe Z :

Position (translation) : (0, 0, 5)
Quaternion (w x y z)   : (0.70710678, 0, 0, 0.70710678)
Point                  : (1, 2, 3)

Ici t = (0, 0, 5) est aligné avec l'axe Z, qui est justement l'axe de rotation du quaternion. Une rotation autour d'un axe laisse ce même axe inchangé : R(t) = t. Le point (1, 2, 3) peut être n'importe quoi, le résultat sera identique dans les deux ordres — essaie, tu verras que les deux lignes affichées sont égales.

Si on change la translation pour qu'elle ne soit plus alignée avec l'axe de rotation (par exemple position = (5, 0, 0) avec la même rotation autour de Z), les deux résultats divergent : la rotation "entraîne" alors la translation dans une direction différente selon l'ordre des opérations.