```cpp
#include <iostream>

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

// Applique une rotation à un vecteur via un quaternion (déjà normalisé)
Vec3 appliquerRotation(const Quat& q, const Vec3& v) {
    // Formule optimisée équivalente à q * (0,v) * q_conjugué
    double qw = q.w, qx = q.x, qy = q.y, qz = q.z;

    // t = 2 * cross(q.xyz, v)
    double tx = 2.0 * (qy * v.z - qz * v.y);
    double ty = 2.0 * (qz * v.x - qx * v.z);
    double tz = 2.0 * (qx * v.y - qy * v.x);

    // v' = v + qw * t + cross(q.xyz, t)
    Vec3 result;
    result.x = v.x + qw * tx + (qy * tz - qz * ty);
    result.y = v.y + qw * ty + (qz * tx - qx * tz);
    result.z = v.z + qw * tz + (qx * ty - qy * tx);

    return result;
}

// Applique une pose complète : rotation puis translation
Vec3 appliquerPose(const Pose& pose, const Vec3& point) {
    Vec3 pointTourne = appliquerRotation(pose.rotation, point);

    Vec3 resultat;
    resultat.x = pointTourne.x + pose.position.x;
    resultat.y = pointTourne.y + pose.position.y;
    resultat.z = pointTourne.z + pose.position.z;

    return resultat;
}

int main() {
    Pose pose;
    Vec3 point;

    std::cin >> pose.position.x >> pose.position.y >> pose.position.z;
    std::cin >> pose.rotation.w >> pose.rotation.x >> pose.rotation.y >> pose.rotation.z;
    std::cin >> point.x >> point.y >> point.z;

    Vec3 resultat = appliquerPose(pose, point);

    std::cout << resultat.x << " " << resultat.y << " " << resultat.z << "\n";

    return 0;
}
```