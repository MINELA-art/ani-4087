Écrivons Inverser(pose)

Idée mathématique :
La pose transforme un point par p' = R(p) + t. Pour "défaire" cette opération, il faut trouver la pose inverse telle que Inverse(Pose(p)) = p.
On isole p :

p' = R(p) + t
p' - t = R(p)
R⁻¹(p' - t) = p

Comme le quaternion est normalisé, son inverse R⁻¹ est simplement son conjugué : q⁻¹ = (w, -x, -y, -z).

En développant R⁻¹(p' - t) = R⁻¹(p') - R⁻¹(t) (linéarité de la rotation), on voit que la pose inverse est :

rotation = conjugué de q
position = R⁻¹(-t), c'est-à-dire la position opposée, tournée par le conjugué — exactement ce que demande l'énoncé.

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

// Inverse d'une pose : conjugué du quaternion, position opposée tournée par ce conjugué
Pose Inverser(const Pose& pose) {
    Quat conjugue = {
        pose.rotation.w,
        -pose.rotation.x,
        -pose.rotation.y,
        -pose.rotation.z
    };

    Vec3 positionOpposee = {
        -pose.position.x,
        -pose.position.y,
        -pose.position.z
    };

    Pose inverse;
    inverse.rotation = conjugue;
    inverse.position = appliquerRotation(conjugue, positionOpposee);

    return inverse;
}

int main() {
    Pose pose;
    Vec3 point;

    std::cin >> pose.position.x >> pose.position.y >> pose.position.z;
    std::cin >> pose.rotation.w >> pose.rotation.x >> pose.rotation.y >> pose.rotation.z;
    std::cin >> point.x >> point.y >> point.z;

    Vec3 transforme = appliquerPose(pose, point);

    Pose poseInverse = Inverser(pose);
    Vec3 retour = appliquerPose(poseInverse, transforme);

    Vec3 ecart = {
        retour.x - point.x,
        retour.y - point.y,
        retour.z - point.z
    };

    std::cout << std::fixed << std::setprecision(4);
    std::cout << ecart.x << " " << ecart.y << " " << ecart.z << "\n";

    return 0;
}
```