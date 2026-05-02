#pragma once

#include <variant>
#include "HUGO.h"
#include "HugoComponentMacros.h"
using namespace HUGO;

struct MRU {
    float s = 0.f; // speed (m/s)
};
struct MRUA {
    float s = 0.f; // speed (m/s)
    float a = 0.f; // acceleration (m/s2);
};
struct SIN {
    float A = 1.f; // amplitude
    float b = 0.f; // phase shift
    float c = 0.f; // vertical shift
    float k = 1.f; // periodicity factor (period = 2PI / k)
};

using ProjectilePath = std::variant<MRU, MRUA, SIN>;


HCOMPONENT(ProjectileComponent)

SERIALIZED_MEMBER(HUGO::Int, lifetime); // m/s

enum PathType {
    mru = 0,
    mrua = 1,
    sin = 2
};

enum class PathInfo {
    s = 0,
    a = 1,
    A = 0,
    b = 1,
    c = 2,
    k = 3
};

// projectiles move in a straight path by default
// pathX represents movement in the right vector
DEFAULT_SERIALIZED_MEMBER(HUGO::Int, pathTypeX, 0);
DEFAULT_SERIALIZED_MEMBER(HUGO::Vector4, pathInfoX, Vector4(0., 0., 0., 0.));

// pathY represents movement in the up vector
DEFAULT_SERIALIZED_MEMBER(HUGO::Int, pathTypeY, 0);
DEFAULT_SERIALIZED_MEMBER(HUGO::Vector4, pathInfoY, Vector4(0., 0., 0., 0.));

// // pathZ represents movement in the forward vector
DEFAULT_SERIALIZED_MEMBER(HUGO::Int, pathTypeZ, 0);
DEFAULT_SERIALIZED_MEMBER(HUGO::Vector4, pathInfoZ, Vector4(0., 0., 0., 0.));
// DEFAULT_SERIALIZED_MEMBER(ProjectilePath, pathZ, MRU());

ProjectilePath pathX;
ProjectilePath pathY;
ProjectilePath pathZ;

// Must be called from system when a projectile is instanced
inline void setPaths() {
    setPath(pathX, pathTypeX, pathInfoX);
    setPath(pathY, pathTypeY, pathInfoY);
    setPath(pathZ, pathTypeZ, pathInfoZ);
}

private:
inline void setPath(ProjectilePath& path, HUGO::Int type, const HUGO::Vector4& info) {
    switch (type) {
    case PathType::mrua:
        path = MRUA{
            info[static_cast<int>(PathInfo::s)], 
            info[static_cast<int>(PathInfo::a)]
        };
        break;
    case PathType::sin:
        path = SIN{
            info[static_cast<int>(PathInfo::A)],
            info[static_cast<int>(PathInfo::b)],
            info[static_cast<int>(PathInfo::c)],
            info[static_cast<int>(PathInfo::k)],
        };
        break;
    case PathType::mru:
    default:
        path = MRU{
            info[static_cast<int>(PathInfo::s)]
        };
        break;
    }
}

END_HCOMPONENT()
