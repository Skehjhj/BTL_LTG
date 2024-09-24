#include <Collision.h>
#include <ECS/Collider.h>

bool Collision::AABB(const SDL_Rect& a, const SDL_Rect& b, const Vector2D& vela, const Vector2D& velb){
    return (a.x + vela.x + a.w >= b.x + velb.x &&    
            a.x + vela.x <= b.x + velb.x + b.w &&    
            a.y + vela.y + a.h >= b.y + velb.y &&    
            a.y + vela.y <= b.y + velb.y + b.h);
}

// bool Collision::AABB(const ColliderComponent& a, const ColliderComponent& b, const TransformComponent& vela, const TransformComponent& velb){
//     if(!AABB(a.collider, b.collider, vela.velocity, velb.velocity)) return false;
//     return true;
// }