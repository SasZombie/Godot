#ifndef BULLET_H
#define BULLET_H

#include <AnimatedSprite.hpp>
#include <Godot.hpp>
#include <RigidBody2D.hpp>

namespace godot
{
class Bullet : public godot::RigidBody2D
{
private:
    GODOT_CLASS(Bullet, godot::RigidBody2D)
    godot::AnimatedSprite *_animated_sprite;
    float healhPoints;
public:
    void _init(){}
    void _ready();
    void _on_VisibilityNotifier2D_screen_exited();

    static void _register_methods();
};

}
#endif