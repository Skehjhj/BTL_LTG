#ifndef Collision_H
#define Collision_H
#include <SDL2/SDL.h>
#include <Vecto2D.h>

class ColliderComponent;

class Collision{
    public:
    static bool AABB(const SDL_Rect& a, const SDL_Rect& b, const Vector2D& vela, const Vector2D& velb);
    // static bool AABB(const ColliderComponent& a, const ColliderComponent& b, const TransformComponent& vela, const TransformComponent& velb);
};

#endif