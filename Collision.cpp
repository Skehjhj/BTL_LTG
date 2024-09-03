#include <Collision.h>
#include <ECS/Collider.h>

bool Collision::AABB(const SDL_Rect& a, const SDL_Rect& b, const Vector2D& vela, const Vector2D& velb){
    float velax = vela.x;
    float velay = vela.y;
    float velbx = velb.x;
    float velby = velb.y;
    // if ((vela.x > 0 && a.x < 600) || (vela.x < 0 && a.x > 600)){
    //     velax;
    // }
    

    if (a.x + velax + a.w >= b.x + velbx &&    
        a.x + velax <= b.x + velbx + b.w &&    
        a.y + velay + a.h >= b.y + velby  &&    
        a.y + velay  <= b.y + velby + b.h) {    
        return true;            
    }
    return false;  
}

// bool Collision::AABB(const ColliderComponent& a, const ColliderComponent& b, const TransformComponent& vela, const TransformComponent& velb){
//     if(!AABB(a.collider, b.collider, vela.velocity, velb.velocity)) return false;
//     return true;
// }