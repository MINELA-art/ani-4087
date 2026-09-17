Idée mathématique :

On veut une fonction Composer(pose2, pose1) telle qu'appliquer la pose composée à un point donne le même résultat que d'appliquer d'abord pose1, puis pose2 sur le résultat :

Composer(pose2, pose1)(p) = pose2(pose1(p))

En développant :

pose1(p)        = R1(p) + t1
pose2(pose1(p)) = R2(R1(p) + t1) + t2
                = R2(R1(p)) + R2(t1) + t2      (linéarité de la rotation)

On en déduit la pose composée :

rotation = q2 * q1 (produit de quaternions — l'ordre compte, on applique q1 en premier donc il est "à droite")
position = R2(t1) + t2 (on tourne la translation de pose1 par la rotation de pose2, puis on ajoute la translation de pose2)

Il faut donc écrire la multiplication de deux quaternions, qui n'était pas encore nécessaire dans les exercices précédents.

CODE:

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

Vec3 appliquerPose(const Pose& pose, const Vec3& point) {
    Vec3 pointTourne = appliquerRotation(pose.rotation, point);
    return {
        pointTourne.x + pose.position.x,
        pointTourne.y + pose.position.y,
        pointTourne.z + pose.position.z
    };
}

// Produit de deux quaternions : a * b
Quat multiplierQuat(const Quat& a, const Quat& b) {
    return {
        a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
        a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
        a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
        a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w
    };
}

// Compose deux poses : appliquer pose1 puis pose2
Pose Composer(const Pose& pose2, const Pose& pose1) {
    Pose resultat;
    resultat.rotation = multiplierQuat(pose2.rotation, pose1.rotation);
    Vec3 t1Tourne = appliquerRotation(pose2.rotation, pose1.position);
    resultat.position = {
        t1Tourne.x + pose2.position.x,
        t1Tourne.y + pose2.position.y,
        t1Tourne.z + pose2.position.z
    };
    return resultat;
}

int main() {
    Pose pose1, pose2;
    Vec3 point;

    std::cin >> pose1.position.x >> pose1.position.y >> pose1.position.z;
    std::cin >> pose1.rotation.w >> pose1.rotation.x >> pose1.rotation.y >> pose1.rotation.z;

    std::cin >> pose2.position.x >> pose2.position.y >> pose2.position.z;
    std::cin >> pose2.rotation.w >> pose2.rotation.x >> pose2.rotation.y >> pose2.rotation.z;

    std::cin >> point.x >> point.y >> point.z;

    // Méthode 1 : composer puis appliquer
    Pose composee = Composer(pose2, pose1);
    Vec3 resultat1 = appliquerPose(composee, point);

    // Méthode 2 : appliquer l'une après l'autre
    Vec3 intermediaire = appliquerPose(pose1, point);
    Vec3 resultat2 = appliquerPose(pose2, intermediaire);

    Vec3 ecart = {
        resultat1.x - resultat2.x,
        resultat1.y - resultat2.y,
        resultat1.z - resultat2.z
    };

    std::cout << std::fixed << std::setprecision(4);
    std::cout << resultat1.x << " " << resultat1.y << " " << resultat1.z << "\n";
    std::cout << resultat2.x << " " << resultat2.y << " " << resultat2.z << "\n";
    std::cout << ecart.x << " " << ecart.y << " " << ecart.z << "\n";

    return 0;
}
```